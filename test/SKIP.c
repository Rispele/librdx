
#include "SKIP.h"

#include <stdint.h>
#include <unistd.h>

#include "01.h"
#include "B.h"
#include "COMB.h"
#include "FILE.h"
#include "HEX.h"
#include "PRO.h"
#include "TEST.h"

#define X(M, name) M##bl04##name
#define SKIPoff_t u8
#include "SKIPx.h"
#undef X

// Avg skip record: 2 entries, 4+1 bytes,
// OVerhead 1% => gap 1<<9=512
#define X(M, name) M##bl09##name
#include "SKIPx.h"
#undef X

pro(SKIP0) {
    sane(1);
    SKIPbl09 skips = {};
    testeq(0, SKIPbl09pos(&skips, 0));
    testeq(0, SKIPbl09pos(&skips, 1));
    testeq(0, SKIPbl09pos(&skips, 2));
    SKIPbl09 skips2 = {.pos = 1025};
    testeq(512, SKIPbl09pos(&skips2, 0));
    testeq(0, SKIPbl09pos(&skips2, 1));
    SKIPbl09 skips4 = {.pos = 2049, .off = {23}};
    testeq(1024 + 512 + 23, SKIPbl09pos(&skips4, 0));
    testeq(1024, SKIPbl09pos(&skips4, 1));
    testeq(0, SKIPbl09pos(&skips4, 2));
    SKIPbl09 skips5 = {.pos = 2048 + 512 + 1};
    skips5.off[1] = 9;
    testeq(2048, SKIPbl09pos(&skips5, 0));
    testeq(1024 + 9, SKIPbl09pos(&skips5, 1));
    testeq(0, SKIPbl09pos(&skips5, 2));
    done;
}

pro(SKIPcheck, Bu8 buf, Bu8 checked, SKIPbl04 const* k) {
    sane(1);
    for (int h = k->len - 1; h >= 0; --h) {
        if (k->off[h] == 0xff) continue;
        SKIPbl04 hop = {};
        ok64 o = SKIPbl04hop(&hop, buf, k, h);
        if (o != OK) {
            if (o == SKIPbof) continue;
            fail(o);
        } else if (!Bitat(checked, hop.pos)) {
            Bitset(checked, hop.pos);
            call(SKIPcheck, buf, checked, &hop);
        }
    }
    done;
}

pro(SKIP1) {
    sane(1);
    aBcpad(u8, pad, MB);
    aBcpad(u8, check, MB);
    SKIPbl04 k = {};
    for (u64 u = 0; u < MB / 16; ++u) {
        $u8feed64(padidle, &u);
        call(SKIPbl04mayfeed, padbuf, &k);
    }
    // aBcpad(u8, hex, PAGESIZE * 2);
    // HEXfeedall(hexidle, paddata);
    SKIPbl04 k2 = {};
    call(SKIPbl04drain, &k2, padbuf, k.pos);
    call(SKIPcheck, padbuf, checkbuf, &k2);
    done;
}

pro(SKIP2) {
#define SKIP2LEN (1 << 14)
    sane(1);
    $u8c path = $u8str("/tmp/SKIP2.txt");
    FILEunlink(path);
    aB(u8, pad);
    aBcpad(u8, check, SKIP2LEN);
    call(FILEmapre, (voidB)padbuf, path, SKIP2LEN);
    COMBinit(padbuf);
    SKIPbl04 k = {};
    for (u64 i = 0; i < 8; ++i) {
        for (u64 u = 0; u < SKIP2LEN / 16; ++u) {
            $u8feed64(padidle, &u);
            call(SKIPbl04mayfeed, padbuf, &k);
        }
        call(SKIPbl04term, padbuf, &k);
        size_t ds = Bdatalen(padbuf);
        size_t bs = Busysize(padbuf);
        COMBsave(padbuf);
        call(FILEunmap, (voidB)padbuf);
        call(FILEmapre, (voidB)padbuf, path, SKIP2LEN * (i + 2));
        COMBload(padbuf);
        testeq(ds, Bdatalen(padbuf));
        testeq(bs, Busysize(padbuf));
        testeq(SKIP2LEN * (i + 2), Bsize(padbuf));
        zero(k);
        call(SKIPbl04load, &k, padbuf);
    }
    SKIPbl04 k2 = {};
    call(SKIPbl04drain, &k2, padbuf, k.pos);
    call(SKIPcheck, padbuf, checkbuf, &k2);
    call(FILEunlink, path);
    done;
}

pro(SKIPtest) {
    sane(1);
    call(SKIP0);
    call(SKIP1);
    call(SKIP2);
    done;
}

TEST(SKIPtest);
