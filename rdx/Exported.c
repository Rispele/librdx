#include "JDR.h"
#include "RDXY.h"

uint8_t _pro_depth = 0;

ok64 FromJDR($u8 tlv, $u8c rdxj) {
    return JDRdrain(tlv, rdxj);
}

ok64 ToJDR($u8 rdxj, $u8c tlv, u8 prnt) {
    return _JDRfeed(rdxj, tlv, prnt);
}

ok64 MergeRDX($u8 into, $$u8c from) {
    return RDXY(into, from);
}