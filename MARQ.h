#ifndef ABC_MARQ_H
#define ABC_MARQ_H

#include "01.h"
#include "FILE.h"
#include "INT.h"
#include "LEX.h"

con ok64 MARQfail = 0x30b65a8251b296;
#define MARQenum 16

// max 8 bits
typedef enum {
    MARQ_MARKUP = 0,
    MARQ_CODE = 1,
    MARQ_LINK = 2,
    MARQ_STRONG = 3,
    MARQ_EMPH = 4,
} MARQfmt;

typedef u64 link64;

#define MARQ_MAX_OPEN_BRACKETS 31

typedef enum {
    MARK_MODE_HTML,
    MARK_MODE_ANSI,
} MARKmode;

typedef struct {
    MARKmode mode;

    $u8c text;
    $u8 fmt;

    // 0 ~ nothing
    u64 brackets[MARQ_MAX_OPEN_BRACKETS + 1];
} MARQstate;

ok64 MARQlexer(MARQstate* state);
#endif
