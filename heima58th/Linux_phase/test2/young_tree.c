/**
 * @brief 实现一个tree命令来练习处理目录流的能力
 * @date  2025年2月17日
 */

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <error.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int directories = 0;  // 总目录数
int files = 0;  // 总文件数

void dfs_print(const char* path, int width){  // width为前面的空格长度
    // 打开目录流
    DIR* stream = opendir(path);
    if(stream == NULL){
        error(1, errno, "opendir %s", path);
    }

    // 遍历每一个目录项
    errno = 0;  // 重置errno
    struct dirent* pdirent = NULL;  // 指向每一个目录项
    while((pdirent = readdir(stream)) != NULL) {

        // 忽略.和..这两个目录
        char* filename = pdirent->d_name;
        if(strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
            continue;
        
        // 缩进并打印目录项名称
        for (int i = 0; i < width; i++) {
            putchar('-');
        }
        puts(filename);

        //判定是文件还是目录, 是目录则递归处理子目录
        if(pdirent->d_type == DT_DIR) {
            directories++;
            // 拼接路径组成子路径
            char subpath[128];
            sprintf(subpath, "%s/%s", path, filename);
            dfs_print(subpath, width + 4);
        } else {
            files++;
        }

    }  // pdirent == NULL

    closedir(stream);

    if(errno) {  // errno非0则说明出错了
        error(1, errno, "readdir");
    }
}

int main(int argc, char const *argv[])
{
    if(argc != 2) {
        error(1/*非0为出错*/, 0/*errno*/, "Usage: %s dirName.\n", argv[0]);
    }
    puts(argv[1]);  // 输出根目录
    dfs_print(argv[1], 4);
    printf("\n");
    printf("%d  directories. \t %d  files.\n", directories, files);
    return 0;
}
