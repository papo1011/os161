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
 * _exit - Terminates the current process.
 *
 * Description:
 *   Causes the current process to exit immediately. The exit code 'exitcode'
 *   is reported to other processes via the 'waitpid()' system call. The process
 *   ID of the exiting process is not reused until all processes that need to
 *   collect the exit code with 'waitpid()' have done so.
 *
 *   Traditionally, exit codes are 7 bits wide (0-127), and values outside this
 *   range may be truncated. Portable code should avoid using exit codes outside
 *   this range. However, OS/161 supports a wider range of exit codes.
 *
 * Return Value:
 *   This function does not return.
 */
void sys__exit(int status) {
	/* get address space of current process and destroy */
	struct addrspace *as = proc_getas();
	as_destroy(as);
	/* thread exits. proc data structure will be lost */
	thread_exit();

	panic("thread_exit returned (should not happen)\n");
	(void)status; // TODO: status handling
}