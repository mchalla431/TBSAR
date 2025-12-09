/**
 * @file syscalls.c
 * @brief Minimal syscall stubs for newlib-nano
 * Required for printf/vsnprintf with -specs=nano.specs
 */

#include <sys/stat.h>
#include <errno.h>

/* Heap management - required for malloc/vsnprintf */
extern char __heap_start__;  /* Defined in linker script */
extern char _stack_start;    /* Defined in linker script */

void *_sbrk(int incr)
{
    static char *heap_end = 0;
    char *prev_heap_end;
    
    if (heap_end == 0) {
        heap_end = &__heap_start__;
    }
    
    prev_heap_end = heap_end;
    
    /* Check if we're going to overflow into the stack */
    if (heap_end + incr > &_stack_start) {
        return (void *)-1;  /* Out of memory */
    }
    
    heap_end += incr;
    
    return (void *)prev_heap_end;
}

/* Stub implementations for other syscalls */
int _close(int file)
{
    return -1;
}

int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file)
{
    return 1;
}

int _lseek(int file, int ptr, int dir)
{
    return 0;
}

int _read(int file, char *ptr, int len)
{
    return 0;
}

int _write(int file, char *ptr, int len)
{
    return len;
}

void _exit(int status)
{
    while(1);
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

int _getpid(void)
{
    return 1;
}
