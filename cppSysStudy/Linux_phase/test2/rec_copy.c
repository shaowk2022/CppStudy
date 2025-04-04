/**
 * @brief 作业1：实现递归复制目录, 前序遍历
 */

#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>  // for PATH_MAX
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 4096

void copy_file(const char* src, const char* dst) {
    size_t bytes_read, bytes_written;  // 读取和写入的字节数
    char buffer[BUFFER_SIZE];

    int src_fd = open(src, O_RDONLY);  // 只读方式打开源文件
    if (src_fd == -1)
        error(1, errno, "open %s failed.", src);

    // 写入方式打开目标文件，不存在在创建，存在则截断
    int dst_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst_fd == -1) {
        close(src_fd);  // 关闭源文件
        error(1, errno, "open %s failed.", dst);
    }

    // 循环读取并写入
    while ((bytes_read = read(src_fd, buffer, BUFFER_SIZE)) > 0) {
        // 从src_fd读取BUFFER_SIZE个字节到buffer, 
        //   从buffer写入bytes_read个字节到dst_fd
        bytes_written = write(dst_fd, buffer, bytes_read);
        if(bytes_read != bytes_written){
            // 读取和写入的字节数不相同，说明其中之一出错了，关闭文件
            close(src_fd);
            close(dst_fd);
            error(1, errno, "write %s failed.", dst);
        }
    }

    // 文件复制完成
    close(src_fd);
    close(dst_fd);

    // 若上面那个循环条件的read()返回-1，则读取出错
    if(bytes_read == -1){
        error(1, errno, "read %s failed.", src);
    }
}

void copy_dir(const char* src_path, const char* dst_path) {
    DIR* dir = opendir(src_path);
    if (NULL == dir) {
        error(1, errno, "opendir %s failed.", src_path);
    }

    // 获取原目录信息
    struct stat st;
    if (stat(src_path, &st) == -1) {
        // 源目录信息获取失败
        closedir(dir);
        error(1, errno, "get %s stat failed.", src_path);
    }

    // 创建目标目录
    if (mkdir(dst_path, st.st_mode) == -1) {
        // 返回-1说明创建失败，此时会设置errno
        if (errno != EEXIST) {  // 目录已存在时，不报错
            error(1, errno, "mkdir %s failed.", dst_path);
        }
    }

    errno = 0;  // 重置为0，表示未出错

    // 递归复制源目录里的每一个目录项
    struct dirent* entry = NULL;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0) {
            continue;  // 跳过.和..
        }

        // 构建原路径和目标路径
        char src_full_path[PATH_MAX];
        char dst_full_path[PATH_MAX];

        sprintf(src_full_path, "%s/%s", src_path, entry->d_name);
        sprintf(dst_full_path, "%s/%s", dst_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            // 递归复制子目录
            copy_dir(src_full_path, dst_full_path);
        } else if (entry->d_type == DT_REG) {
            // 复制普通文件
            copy_file(src_full_path, dst_full_path);
        }
    }

    if (errno != 0) {  // errno为0表示未出错
        closedir(dir);
        error(1, errno, "readdir %s failed.", src_path);
    }

    closedir(dir);  // 复制完毕关闭目录
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        error(1, 0, "Usage: %s srcDirName dstDirName.", argv[0]);
    }
    const char* src_path = argv[1];
    const char* dst_path = argv[2];
    copy_dir(src_path, dst_path);
    return 0;
}