#include "ext4_utils/key_control.h"

#include <stdarg.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/keyctl.h>

static long keyctl(int cmd, ...)
{
    va_list va;
    unsigned long arg2, arg3, arg4, arg5;

    va_start(va, cmd);
    arg2 = va_arg(va, unsigned long);
    arg3 = va_arg(va, unsigned long);
    arg4 = va_arg(va, unsigned long);
    arg5 = va_arg(va, unsigned long);
    va_end(va);
    return syscall(__NR_keyctl, cmd, arg2, arg3, arg4, arg5);
}

key_serial_t add_key(const char *type,
                     const char *description,
                     const void *payload,
                     size_t plen,
                     key_serial_t ringid)
{
    return syscall(__NR_add_key, type, description, payload, plen, ringid);
}

long keyctl_unlink(key_serial_t key, key_serial_t keyring)
{
    return keyctl(KEYCTL_UNLINK, key, keyring);
}

long keyctl_setperm(key_serial_t id, int permissions)
{
    return keyctl(KEYCTL_SETPERM, id, permissions);
}

long keyctl_search(key_serial_t ringid, const char *type,
                   const char *description, key_serial_t destringid)
{
    return keyctl(KEYCTL_SEARCH, ringid, type, description, destringid);
}
