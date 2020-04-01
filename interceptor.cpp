#include <libsyscall_intercept_hook_point.h>
#include <syscall.h>
#include <errno.h>

#include <fmt/format.h>

extern "C" int
hook(long syscall_number,
			long arg0, long arg1,
			long arg2, long arg3,
			long arg4, long arg5,
			long *result)
{
	if (syscall_number == SYS_getdents) {
		/*
		 * Prevent the application from
		 * using the getdents syscall. From
		 * the point of view of the calling
		 * process, it is as if the kernel
		 * would return the ENOTSUP error
		 * code from the syscall.
		 */
		return 1;
		*result = -ENOTSUP;
		return 0;
    }
    else if (syscall_number == SYS_openat)
    {
        fmt::print("hei\n");
        return 1;
    }
    else{
		/*
		 * Ignore any other syscalls
		 * i.e.: pass them on to the kernel
		 * as would normally happen.
		 */
		return 1;
	}
}

extern "C" __attribute__((constructor)) void
init(void)
{
    fmt::print("hooking up\n");
	// Set up the callback function
	intercept_hook_point = hook;
}
