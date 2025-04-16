#include <arpa/inet.h>
#include <errno.h>
#include <error.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#define MAX_LEN 10
/**
 * @brief 实现从域名到IP地址的转换
 */
int main(int argc, char const* argv[]) {
    if (argc != 2) {
        error(1, 0, "Usage: %s <domain_name>", argv[0]);
        return 1;
    }
    struct hostent* host = gethostbyname(argv[1]);
    printf("h_name: %s\n", host->h_name);
    for (size_t i = 0; host->h_aliases[i] != NULL; i++) {
        printf("h_aliases[%lu]: %s\n", i, host->h_aliases[i]);
    }
    printf("addr_type: %d\n", host->h_addrtype);
    printf("addr_length: %d\n", host->h_length);

    // 域名转为IP地址
    for (size_t i = 0; host->h_addr_list[i] != NULL; i++) {
        char ip_str[MAX_LEN][INET_ADDRSTRLEN];
        inet_ntop(AF_INET, host->h_addr_list[i], ip_str[i], sizeof(ip_str[i]));
        printf("IP Address[%lu]: %s \n", i, ip_str[i]);
    }

    return 0;
}
