#include "RDX.h"

#include <stdint.h>
#include <unistd.h>

#include "B.h"
#include "RDXJ.h"
#include "TEST.h"

pro(RDXtest1) {
    sane(1);
    aBpad(u8, pad, 0x1000);
    u8** into = Bu8idle(pad);
    $u8c hello = $u8str("Hello");
    aRDXid(id, 1, 2);
    call(RDXfeed, into, 'A', id, hello);
    same(10, $len(Bu8data(pad)));

    u8 const** from = Bu8cdata(pad);
    u8 t;
    id128 reid = {};
    $u8c rehello = {};
    call(RDXdrain, &t, &reid, rehello, from);
    same('A', t);
    same(0, $cmp(hello, rehello));
    same(0, id128cmp(&id, &reid));
    done;
}

pro(RDXid128test) {
    sane(1);
#define RDXIDINLEN 3
    u64 inputs[RDXIDINLEN][2] = {{0, 0}, {100, 200}, {UINT64_MAX, UINT64_MAX}};
    for (int i = 0; i < RDXIDINLEN; ++i) {
        aRDXid(in, inputs[i][0], inputs[i][1]);
        aBpad(u8, hex, 64);
        call(RDXid128feed, Bu8idle(hex), in);
        id128 in2 = {};
        call(RDXid128drain, &in2, Bu8cdata(hex));
        want(0 == id128cmp(&in, &in2));
    }
    done;
}

pro(RDXtest) {
    sane(1);
    call(RDXtest1);
    call(RDXid128test);
    done;
}

TEST(RDXtest);
