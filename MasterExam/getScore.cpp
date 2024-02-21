#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <curl/curl.h> // 使用 libcurl 发送 HTTP 请求

// 邮件配置
const std::string SMTP_SERVER = "smtp.163.com";
const int SMTP_PORT = 465;
const std::string EMAIL_FROM = "shaowk2022@163.com"; // 发件邮箱
const std::string EMAIL_PASSWORD = "CXUBISXOEVZPNANO"; // 邮箱SMTP服务授权码
const std::string EMAIL_TO = "shaowk2022@163.com"; // 收件人邮箱
const std::string EMAIL_SUBJECT_AVAILABLE = "网站可访问通知";
const std::string EMAIL_BODY_AVAILABLE = "网站现在可以访问了。";

// 发送邮件的函数
bool send_email(const std::string& subject, const std::string& body, const std::string& from_addr, const std::string& to_addr, const std::string& password) {
    // 实现发送邮件的逻辑，可以使用 C++ 的邮件库或者调用系统命令发送邮件
    CURL* curl;
    CURLcode res;
    bool ret = true;

    std::string payload = "From: " + from_addr + "\r\n";
    payload += "To: " + to_addr + "\r\n";
    payload += "Subject: " + subject + "\r\n";
    payload += "\r\n"; // 空行分隔头部和正文
    payload += body;

    // 初始化 curl
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        // 设置邮件服务器和端口
        std::string url = "smtps://" + SMTP_SERVER + ":" + std::to_string(SMTP_PORT);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // 设置登录账号和密码
        curl_easy_setopt(curl, CURLOPT_USERNAME, from_addr.c_str());
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password.c_str());

        // 设置邮件内容
        curl_easy_setopt(curl, CURLOPT_READDATA, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // 设置libcurl的debug级别
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);

        // 发送邮件
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to send email: " << curl_easy_strerror(res) << std::endl;
            ret = false;
        } else {
            std::cout << "Email sent successfully" << std::endl;
        }
        // 清理 curl
        curl_easy_cleanup(curl);
    }
    // 全局清理
    curl_global_cleanup();
    return ret;
}

// 检测网站可达性
bool is_website_available(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize libcurl" << std::endl;
        return false;
    }

    // 设置要请求的 URL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // 不需要将响应数据保存，只需要判断状态码即可
    curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

    // 执行请求
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "Failed to perform HTTP request: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        return false;
    }

    // 获取响应状态码
    long response_code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

    // 清理 curl 实例
    curl_easy_cleanup(curl);

    // 判断状态码，2xx 或 3xx 表示可达性
    return (response_code >= 200 && response_code < 400);
}

// 主程序
int main() {
    unsigned int count = 0;
    std::string url = "https://syk.cqu.edu.cn/cjcx/"; // 学校官网查询网址
    // url = "http://yjszs.tjnu.edu.cn:8080/sscjcx/index";
    // url = "https://yzs.sues.edu.cn/xscx/";

    while (true) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::cout << "当前时间：" << std::ctime(&now_time);
        if (is_website_available(url)) {
            std::cout << "网站可达, 准备发送邮件 ..." << std::endl;
            if(send_email(EMAIL_SUBJECT_AVAILABLE, EMAIL_BODY_AVAILABLE, EMAIL_FROM, EMAIL_TO, EMAIL_PASSWORD)){
                std::cout << "邮件发送成功 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                count++;
                if(count == 3)
                    break; // 如果只需要在网站可访问时发送一次邮件，就使用break退出循环
            }
            std::cout << "发送失败, 2 mins 后重试 ..." << std::endl;
            std::this_thread::sleep_for(std::chrono::minutes(2)); // 每隔2分钟检查一次

            // 播放音频提醒
        } else {
            std::cout << "网站暂时无法访问, 2 mins 后重试..." << std::endl;
            std::this_thread::sleep_for(std::chrono::minutes(2)); // 每隔2分钟检查一次
        }
    }

    return 0;
}
