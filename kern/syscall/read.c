#include <types.h>
#include <kern/unistd.h>
#include <clock.h>
#include <copyinout.h>
#include <syscall.h>
#include <lib.h>
#include <proc.h>
#include <thread.h>
#include <addrspace.h>

/*
 * read - Reads data from a file descriptor.
 *
 * Description:
 *   Reads up to 'buflen' bytes from the file specified by 'fd', starting from
 *   the current seek position, and stores them in the memory location pointed
 *   to by 'buf'. The file must be open for reading.
 *
 *   The seek position is advanced by the number of bytes successfully read.
 *
 *   Each read operation is atomic relative to other I/O operations on the same
 *   file. However, the kernel does not guarantee atomicity with respect to other
 *   threads accessing the I/O buffer during the read.
 *
 * Return Value:
 *   - On success, returns the number of bytes read (positive integer).
 *   - A return value of 0 indicates end-of-file.
 *   - On error, returns -1 and sets 'errno' appropriately.
 *
 * Error Codes:
 *   - EBADF:  'fd' is not a valid file descriptor or was not opened for reading.
 *   - EFAULT: The memory address pointed to by 'buf' is invalid.
 *   - EIO:    A hardware I/O error occurred while reading.
 */
int sys_read(int fd, userptr_t buf_ptr, size_t size)
{
    int i;
    char *p = (char *)buf_ptr;

    if (fd != STDIN_FILENO)
    {
        // TODO: Implement sys_read for other file descriptors
        kprintf("sys_read supported only to stdin\n");
        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        p[i] = getch();
        if (p[i] < 0)
            return i;
    }

    return (int)size;
}
