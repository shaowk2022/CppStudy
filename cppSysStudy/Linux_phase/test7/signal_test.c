#include <errno.h>
#include <error.h>
#include <signal.h>
#include <stdio.h>

void handler(int signal) {
    switch (signal) {
    case SIGINT:
        printf("caught SIGINT.\n");
        break;
    case SIGTSTP:
        printf("caught SIGTSTP.\n");
        break;
    default:
        printf("caught unknown signal %d.\n", signal);
        break;
    }
}

int main(int argc, char* argv[]) {
    __sighandler_t signhandler = signal(SIGINT, handler);
    if (signhandler == SIG_ERR) {
        error(1, errno, "signal handler error: %d\n", SIGINT);
    }
    signhandler = signal(SIGTSTP, handler);
    if (signhandler == SIG_ERR) {
        error(1, errno, "signal handler error: %d\n", SIGTSTP);
    }
    while (1) {
    }

    return 0;
}