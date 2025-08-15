#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
    printf("Mi identificador de proceso es %d\n", getpid());
    exit(0);
}
