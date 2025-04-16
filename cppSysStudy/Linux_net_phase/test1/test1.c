/**
 * @brief: 验证数据在本机是否为小端模式存放
 */
#include <arpa/inet.h>   // for htonl()
#include <netinet/in.h>  // for struct sockaddr_in
#include <netinet/ip.h>  // for struct in_addr
#include <stdint.h>      // for uint32_t
#include <stdio.h>
#include <stdlib.h>  // for inet_aton()
#include <string.h>  // for memset()
#include <sys/socket.h>

int main(int argc, char const* argv[]) {
    int num = 0x12345678;
    printf("num: %x \n", num);

    // 通过htonl()函数将num转换为网络字节序(大端模式)
    uint32_t net_num = htonl(num);
    printf("net_num: %x \n", net_num);

    // 点分十进制IP转为网络字节序IP
    struct in_addr addr;
    const char* ip = "192.168.0.1";
    int err = inet_aton(ip, &addr);
    if (err == 0) {  // 成功返回1，失败返回0
        printf("inet_aton error\n");
        return -1;
    }
    printf("addr: %x\n", addr.s_addr);

    // 网络字节序IP转为点分十进制IP
    char* ip_str = inet_ntoa(addr);
    if (ip_str == NULL) {
        printf("inet_ntoa error\n");
        return -1;
    }
    puts(ip_str);
    puts(inet_ntoa(addr));

    // 如何填充一个网络地址
    struct sockaddr_in addr1;
    memset(&addr1, 0, sizeof(addr1));  // 清空内容
    addr1.sin_family = AF_INET;        // IPv4
    addr1.sin_port = htons(8080);
    addr1.sin_addr.s_addr = inet_addr("192.168.0.1");

    // 打印网络地址
    printf("IP: %s, Port: %d\n", inet_ntoa(addr1.sin_addr), ntohs(addr1.sin_port));

    return 0;
}
