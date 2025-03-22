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
 * write - Writes data to a file descriptor.
 *
 * Description:
 *   Writes up to 'buflen' bytes to the file specified by 'fd', starting from
 *   the current seek position. The data is taken from the memory location
 *   pointed to by 'buf'. The file must be open for writing.
 *
 *   The seek position is advanced by the number of bytes successfully written.
 *
 *   Each write operation is atomic relative to other I/O operations on the
 *   same file. However, the kernel does not guarantee atomicity with respect
 *   to other threads accessing the I/O buffer during the write.
 *
 * Return Value:
 *   - On success, returns the number of bytes written (positive integer).
 *   - A return value of 0 indicates that nothing was written, but no error
 *     occurred (this typically happens at end-of-file on fixed-size objects).
 *   - On error, returns -1 and sets 'errno' appropriately.
 *
 * Error Codes:
 *   - EBADF:  'fd' is not a valid file descriptor or was not opened for writing.
 *   - EFAULT: The memory address pointed to by 'buf' is invalid.
 *   - ENOSPC: No free space remaining on the filesystem containing the file.
 *   - EIO:    A hardware I/O error occurred while writing.
 *
 */
int sys_write(int fd, userptr_t buf_ptr, size_t size)
{
    int i;
    char *p = (char *)buf_ptr;

    if (fd != STDOUT_FILENO && fd != STDERR_FILENO)
    {
        // TODO: Implement sys_write for other file descriptors
        kprintf("sys_write supported only to stdout\n");

        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        putch(p[i]);
    }

    return (int)size;
}
