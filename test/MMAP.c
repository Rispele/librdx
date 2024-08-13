#include "MMAP.h"

#include "INT.h"
#include "PRO.h"
#include "TEST.h"

pro(MMAPtest1) {
    Bu8 buf8 = {};
    call(MMAPopen, (void$)buf8, 4096);
    aB(u32, buf32);
    sane(Bnil(buf32));
    call(Bmmap, buf32, 1024);
    sane(Bsize(buf8) == Bsize(buf32));

    Bat(buf8, 0) = 0xaa;
    Bat(buf8, 1) = 0xbb;
    Bat(buf8, 2) = 0xcc;
    Bat(buf8, 3) = 0xdd;
    $copy(Bidle(buf32), Bidle(buf8));
    sane(Bat(buf32, 0) == 0xddccbbaa);

    call(Bremap2, buf8);
    call(Bmayremap, buf32, 2048);
    sane(Bsize(buf8) == Bsize(buf32));

    Bat(buf8, 8188) = 0xaa;
    Bat(buf8, 8189) = 0xbb;
    Bat(buf8, 8190) = 0xcc;
    Bat(buf8, 8191) = 0xee;
    $copy(Bidle(buf32), Bidle(buf8));
    sane(Bat(buf32, 2047) == 0xeeccbbaa);
    sane(Bat(buf32, 0) == 0xddccbbaa);

    call(MMAPclose, (void$)buf8);
    call(Bunmap, buf32);
    done;
}

pro(MMAPtest) {
    call(MMAPtest1);
    done;
}

TEST(MMAPtest);
