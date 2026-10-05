#define _GNU_SOURCE
#define _LARGEFILE64_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Pass the renderer's existing codec path to bundled libffmpeg.
 * libffmpeg loads the codec later, after Discord's normal download. */
__attribute__((constructor)) static void renderer_codec_path(void) {
    if (!getenv("SNAP"))
        return;

    const char *(*get_path)(void) =
        dlsym(RTLD_DEFAULT, "ff_libopenh264_get_library_path");
    void (*set_path)(const char *) =
        dlsym(RTLD_DEFAULT, "ff_libopenh264_set_library_path");

    /* Leave an already configured library alone. */
    if (!get_path || !set_path || get_path())
        return;

    char arguments[65536];
    int fd = open("/proc/self/cmdline", O_RDONLY | O_CLOEXEC);
    if (fd < 0)
        return;

    ssize_t length = read(fd, arguments, sizeof(arguments));
    close(fd);

    if (length <= 0 || length == (ssize_t)sizeof(arguments))
        return;

    const char prefix[] = "--openh264-library-path=";
    const char *codec = NULL;
    int renderer = 0;

    /* /proc separates arguments with NUL bytes. Reject a truncated one. */
    for (size_t offset = 0; offset < (size_t)length;) {
        const char *argument = arguments + offset;
        size_t remaining = (size_t)length - offset;
        size_t size = strnlen(argument, remaining);

        if (size == remaining)
            return;

        if (!strcmp(argument, "--type=renderer"))
            renderer = 1;
        if (!strncmp(argument, prefix, sizeof(prefix) - 1))
            codec = argument + sizeof(prefix) - 1;

        offset += size + 1;
    }

    /* The pinned setter copies the path; it does not retain this buffer. */
    if (renderer && codec && codec[0] == '/')
        set_path(codec);
}

/* The voice loader requests r+b, but only reads these two models. */
static const char *model_mode(const char *filename, const char *mode) {
    if (!filename || !mode ||
        (strcmp(mode, "r+") && strcmp(mode, "r+b") && strcmp(mode, "rb+")))
        return mode;

    const char *snap = getenv("SNAP");
    if (!snap || snap[0] != '/')
        return mode;

    const char *names[] = {
        "selfie_segmentation.tflite",
        "selfie_segmentation_landscape.tflite"
    };
    char expected[PATH_MAX];

    /* Match exact bundled paths; leave every other file and mode alone. */
    for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); ++i) {
        int length = snprintf(expected, sizeof(expected),
            "%s/usr/share/discord/resources/standalone_modules/discord_voice/%s",
            snap, names[i]);

        if (length > 0 && (size_t)length < sizeof(expected) &&
            !strcmp(filename, expected))
            return "rb";
    }

    return mode;
}

FILE *fopen(const char *filename, const char *mode) {
    FILE *(*next)(const char *, const char *) = dlsym(RTLD_NEXT, "fopen");

    if (!next) {
        errno = ENOSYS;
        return NULL;
    }

    return next(filename, model_mode(filename, mode));
}

FILE *fopen64(const char *filename, const char *mode) {
    FILE *(*next)(const char *, const char *) = dlsym(RTLD_NEXT, "fopen64");

    if (!next) {
        errno = ENOSYS;
        return NULL;
    }

    return next(filename, model_mode(filename, mode));
}
