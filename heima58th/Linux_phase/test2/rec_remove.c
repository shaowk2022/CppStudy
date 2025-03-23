/**
 * @brief 作业2：实现递归删除目录
 */
#include <dirent.h>
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h> // for PATH_MAX

void deleteDir(const char* path) {
    // 打开目录流
    DIR* dir = opendir(path);
    if (NULL == dir) {
        error(1, errno, "opendir %s", path);
    }

    errno = 0;  // 重置errno方便在函数末尾校验

    // 处理每一个目录项
    struct dirent* pdirent = NULL;
    while ((pdirent = readdir(dir)) != NULL) {
        // 忽略.和..目录
        if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
            continue;

        // 获取目录项的路径
        char subPath[PATH_MAX] = {0};
        sprintf(subPath, "%s/%s", path, pdirent->d_name);

        // 判断类型
        if (pdirent->d_type == DT_DIR) {
            // 目录文件则递归删除目录
            deleteDir(subPath);
        } else if (pdirent->d_type == DT_REG) {
            // 普通文件则减少链接数（逻辑删除）
            unlink(subPath);
        }
    }

    // 关闭目录流
    closedir(dir);
    if (errno) {  // 判断处理目录项时是否出现了错误
        error(1, errno, "readdir %s", path);
    }

    // 子目录删除完毕，最后删除根目录
    rmdir(path);
}

int main(int argc, char const* argv[]) {
    // 参数校验
    if (argc != 2) {
        error(1, 0, "Usage: %s DirName", argv[1]);
    }
    deleteDir(argv[1]);
    return 0;
}
