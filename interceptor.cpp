#include <libsyscall_intercept_hook_point.h>
#include <syscall.h>
#include <errno.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <fmt/format.h>

extern "C" int
hook(long syscall_number,
			long arg0, long arg1,
			long arg2, long arg3,
			long arg4, long arg5,
			long *result)
{
    if (syscall_number == SYS_openat)
    {
        auto const path = reinterpret_cast<char*>(arg1);
        if (path != nullptr)
          fmt::print(stderr, "openat {} {} {} {} {} {}\n", arg0, path, arg2, arg3, arg4, arg5);
        else
          fmt::print(stderr, "openat {} {} {} {} {} {}\n", arg0, arg1, arg2, arg3, arg4, arg5);
        return 1;
    }
    else if (syscall_number == SYS_open)
    {
        auto const path = reinterpret_cast<char*>(arg1);
        if (path != nullptr)
          fmt::print(stderr, "open {} {} {} {} {} {}\n", arg0, path, arg2, arg3, arg4, arg5);
        else
          fmt::print(stderr, "open {} {} {} {} {} {}\n", arg0, arg1, arg2, arg3, arg4, arg5);
        return 1;
    }
    else {
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
    //fmt::print("hooking up\n");
	// Set up the callback function
	intercept_hook_point = hook;
}
