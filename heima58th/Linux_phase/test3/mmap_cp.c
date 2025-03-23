/**
 * @brief 使用mmap实现对大文件的复制
 */

#include <errno.h>
#include <error.h>
#include <fcntl.h>
#include <memory.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MMAP_SIZE (4096 * 10)  // 一次映射内存中的10页

int main(int argc, char const* argv[]) {
    // 参数校验
    if (argc != 3) {
        error(1, 0, "Usage: %s srcFile dstFile", argv[0]);
    }

    // 打开源文件和目标文件
    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd == -1) {
        error(1, errno, "open %s", argv[1]);
    }
    // O_TRUNC是把文件清空（截断为0字节）, 创建文件需要指定mode
    int dstfd = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0666);  // 666 & ~002 = 664
    if (dstfd == -1) {
        error(1, errno, "open %s", argv[2]);
    }

    // 根据源文件大小确定目标文件的大小
    struct stat sb;
    if (fstat(srcfd, &sb) == -1) {
        error(1, errno, "fstat %s", argv[1]);
    }
    off_t size = sb.st_size;
    if (ftruncate(dstfd, size) == -1) {
        error(1, errno, "ftruncate %s", argv[2]);
    }

    off_t offset = 0;  // 已复制过去的数据大小
    while (offset < size) {
        // 计算映射区的长度
        off_t length;
        if (size - offset >= MMAP_SIZE)
            length = MMAP_SIZE;
        else
            length = size - offset;  // 最后一次映射时，可能源文件的剩余内容不足10页

        // 分别将两个文件映射到内存中
        void* addrSrc = mmap(NULL, length, PROT_READ, MAP_SHARED, srcfd, offset);  // 映射必须使用SHARED方式，否则写不到磁盘上
        if (addrSrc == MAP_FAILED) {
            error(1, errno, "mmap %s", argv[1]);
        }
        void* addrDst = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, dstfd, offset);  // 对目标文件既要读也要写
        if (addrDst == MAP_FAILED) {
            error(1, errno, "mmap %s", argv[2]);
        }

        // 在内存中拷贝文件内容
        memcpy(addrDst, addrSrc, length);
        offset += length;  // 更新已复制的大小

        // 解除两个文件对内存的映射
        if (munmap(addrSrc, length) == -1) {
            error(1, errno, "munmap %s", argv[1]);
        }
        if (munmap(addrDst, length) == -1) {
            error(1, errno, "munmap %s", argv[2]);
        }
    } // offset == size

    return 0;
}
