#ifndef LIBRDX_OK_H
#define LIBRDX_OK_H
#include <errno.h>
#include <stdint.h>

#include "$.h"
#include "01.h"

typedef uint64_t ok64;
typedef ok64 ok;

#define OK 0
#define FAIL 0xffffffffffffffffUL

con ok64 FAILsanity = 0xf78b7297755228f;
con ok64 notimplyet = 0xe29f70d31b78cf2;
con ok64 OKnoroom = 0x614cb3db3cf1;
con ok64 OKbadtext = 0x18526968e29f38;

con char *_base_ron64 =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~";

con u8 BASEron64rev[256] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x0,  0x1,  0x2,  0x3,  0x4,  0x5,  0x6,  0x7,  0x8,  0x9,  0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xa,  0xb,  0xc,  0xd,  0xe,  0xf,  0x10,
    0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c,
    0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0xff, 0xff, 0xff, 0xff, 0x24,
    0xff, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b,
    0x3c, 0x3d, 0x3e, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff,
};

// todo thread local
static char _ok64_tmp[16];

fun ok64 OKprint(ok64 o, uint8_t **into) {
    if (o == 0) {
        if (into[1] < into[0] + 2) return OKnoroom;
        **into = 'O';
        ++*into;
        **into = 'K';
        ++*into;
        return OK;
    }
    while (o && !$empty(into)) {
        **into = _base_ron64[o & 63];
        o >>= 6;
        ++*into;
    }
    return o ? OKnoroom : OK;
}

fun ok64 OKscan(ok64 *o, uint8_t const **from) {
    ok64 res = 0;
    int shift = 0;
    for (uint8_t const *p = from[0]; p < from[1]; ++p) {
        uint64_t v = BASEron64rev[*p];
        if (v == 0xff) return OKbadtext;
        res |= v << shift;
        shift += 6;
    }
    *o = res;
    return OK;
}

fun const char *ok64str(ok64 o) {
    char *tmp[2] = {_ok64_tmp, _ok64_tmp + sizeof(_ok64_tmp)};
    OKprint(o, (uint8_t **)tmp);
    **tmp = 0;
    return _ok64_tmp;
}

fun const char *okstr(ok64 o) { return ok64str(o); }

fun int ok64is(ok64 val, ok64 root) {
    return val == root || (val >> 6) == root || (val >> 12) == root ||
           (val >> 18) == root || (val >> 24) == root;
}

fun ok64 errnok() {
    ok64 e = errno;
    e &= 63;
    e <<= 54;
    return e;
}

#endif
