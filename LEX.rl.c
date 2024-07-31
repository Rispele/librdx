
#line 1 "LEX.rl"
#include "LEX.h"

enum {
    LEX=0,
    LEXname =LEX+1,
    LEXop =LEX+2,
    LEXclass =LEX+3,
    LEXstringA =LEX+4,
    LEXstringB =LEX+5,
    LEXentity =LEX+6,
    LEXexpr =LEX+7,
    LEXeq =LEX+8,
    LEXrulename =LEX+9,
    LEXline =LEX+10,
};

#define LEXmaxnest 32

fun ok64 popfails(u32* stack, u32* sp, u32 type) {
    while (*sp && stack[*sp]!=type) *sp -= 2;
    return *sp ? OK : LEXfail;
}

#define lexpush(t) { \
    if (sp>=LEXmaxnest) fail(LEXfail); \
    stack[++sp] = p - pb; \
    stack[++sp] = t; \
}
#define lexpop(t)  \
    if (stack[sp]!=t) call(popfails, stack, &sp, t); \
    tok[0] = *text+stack[sp-1]; \
    tok[1] = p; \
    sp -= 2;

ok64 _LEXname ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXop ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXclass ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXstringA ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXstringB ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXentity ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXexpr ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXrulename ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEXline ($cu8c text, $cu8c tok, LEXstate* state);
ok64 _LEX ($cu8c text, $cu8c tok, LEXstate* state);


#line 89 "LEX.rl"



#line 49 "LEX.rl.c"
static const char _LEX_actions[] = {
	0, 1, 14, 2, 1, 17, 2, 3, 
	13, 2, 19, 21, 2, 20, 21, 3, 
	1, 11, 2, 3, 1, 11, 13, 3, 
	1, 17, 14, 3, 3, 10, 0, 3, 
	3, 10, 4, 3, 3, 10, 6, 3, 
	3, 10, 8, 3, 5, 11, 2, 3, 
	5, 11, 13, 3, 7, 11, 2, 3, 
	7, 11, 13, 3, 9, 11, 2, 3, 
	9, 11, 13, 3, 15, 12, 2, 3, 
	15, 12, 13, 4, 19, 18, 16, 0, 
	4, 20, 18, 16, 0
};

static const short _LEX_key_offsets[] = {
	0, 0, 7, 18, 22, 31, 47, 49, 
	58, 60, 71, 88, 91, 102, 104, 113, 
	115, 126, 143, 152, 165, 171, 182, 191, 
	209, 212, 223, 225, 227, 238, 256, 259, 
	270, 279, 292, 298, 309, 318, 321, 333, 
	351, 355, 367, 385, 397, 407, 421, 428, 
	440, 443, 455, 466, 476, 495, 507, 517, 
	531, 538, 550, 561, 570, 583, 589, 600, 
	604, 617, 635, 648, 659, 674, 682, 695, 
	707, 724, 736, 747, 757, 771, 778, 790, 
	793, 805, 815, 834, 845, 865, 878, 888, 
	907, 919, 928, 946, 955, 973, 980, 996, 
	1000, 1007, 1016, 1025, 1035, 1045, 1054, 1065
};

static const unsigned char _LEX_trans_keys[] = {
	95u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	61u, 95u, 9u, 13u, 48u, 57u, 65u, 90u, 
	97u, 122u, 32u, 61u, 9u, 13u, 32u, 45u, 
	59u, 63u, 124u, 9u, 10u, 40u, 43u, 32u, 
	34u, 39u, 45u, 59u, 63u, 91u, 124u, 9u, 
	10u, 40u, 43u, 65u, 90u, 97u, 122u, 34u, 
	92u, 32u, 45u, 59u, 63u, 124u, 9u, 10u, 
	40u, 43u, 34u, 92u, 32u, 34u, 45u, 59u, 
	63u, 92u, 124u, 9u, 10u, 40u, 43u, 32u, 
	34u, 39u, 45u, 59u, 63u, 91u, 92u, 124u, 
	9u, 10u, 40u, 43u, 65u, 90u, 97u, 122u, 
	34u, 39u, 92u, 32u, 39u, 45u, 59u, 63u, 
	92u, 124u, 9u, 10u, 40u, 43u, 39u, 92u, 
	32u, 45u, 59u, 63u, 124u, 9u, 10u, 40u, 
	43u, 39u, 92u, 32u, 39u, 45u, 59u, 63u, 
	92u, 124u, 9u, 10u, 40u, 43u, 32u, 34u, 
	39u, 45u, 59u, 63u, 91u, 92u, 124u, 9u, 
	10u, 40u, 43u, 65u, 90u, 97u, 122u, 39u, 
	92u, 95u, 48u, 57u, 65u, 90u, 97u, 122u, 
	32u, 39u, 61u, 92u, 95u, 9u, 13u, 48u, 
	57u, 65u, 90u, 97u, 122u, 32u, 39u, 61u, 
	92u, 9u, 13u, 32u, 39u, 45u, 59u, 63u, 
	92u, 124u, 9u, 10u, 40u, 43u, 39u, 92u, 
	95u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	39u, 45u, 59u, 63u, 92u, 95u, 124u, 9u, 
	10u, 40u, 43u, 48u, 57u, 65u, 90u, 97u, 
	122u, 39u, 92u, 93u, 32u, 45u, 59u, 63u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 92u, 
	93u, 92u, 93u, 32u, 45u, 59u, 63u, 92u, 
	93u, 124u, 9u, 10u, 40u, 43u, 32u, 34u, 
	39u, 45u, 59u, 63u, 91u, 92u, 93u, 124u, 
	9u, 10u, 40u, 43u, 65u, 90u, 97u, 122u, 
	34u, 92u, 93u, 32u, 45u, 59u, 63u, 92u, 
	93u, 124u, 9u, 10u, 40u, 43u, 92u, 93u, 
	95u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	61u, 92u, 93u, 95u, 9u, 13u, 48u, 57u, 
	65u, 90u, 97u, 122u, 32u, 61u, 92u, 93u, 
	9u, 13u, 32u, 45u, 59u, 63u, 92u, 93u, 
	124u, 9u, 10u, 40u, 43u, 32u, 45u, 59u, 
	63u, 124u, 9u, 10u, 40u, 43u, 34u, 92u, 
	93u, 32u, 34u, 45u, 59u, 63u, 92u, 93u, 
	124u, 9u, 10u, 40u, 43u, 32u, 34u, 39u, 
	45u, 59u, 63u, 91u, 92u, 93u, 124u, 9u, 
	10u, 40u, 43u, 65u, 90u, 97u, 122u, 34u, 
	39u, 92u, 93u, 32u, 39u, 45u, 59u, 63u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 32u, 
	34u, 39u, 45u, 59u, 63u, 91u, 92u, 93u, 
	124u, 9u, 10u, 40u, 43u, 65u, 90u, 97u, 
	122u, 32u, 39u, 45u, 59u, 63u, 92u, 93u, 
	124u, 9u, 10u, 40u, 43u, 39u, 92u, 93u, 
	95u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	39u, 61u, 92u, 93u, 95u, 9u, 13u, 48u, 
	57u, 65u, 90u, 97u, 122u, 32u, 39u, 61u, 
	92u, 93u, 9u, 13u, 32u, 39u, 45u, 59u, 
	63u, 92u, 93u, 124u, 9u, 10u, 40u, 43u, 
	39u, 92u, 93u, 32u, 39u, 45u, 59u, 63u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 32u, 
	39u, 45u, 59u, 63u, 92u, 124u, 9u, 10u, 
	40u, 43u, 39u, 92u, 93u, 95u, 48u, 57u, 
	65u, 90u, 97u, 122u, 32u, 39u, 45u, 59u, 
	63u, 92u, 93u, 95u, 124u, 9u, 10u, 40u, 
	43u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	34u, 45u, 59u, 63u, 92u, 93u, 124u, 9u, 
	10u, 40u, 43u, 34u, 92u, 93u, 95u, 48u, 
	57u, 65u, 90u, 97u, 122u, 32u, 34u, 61u, 
	92u, 93u, 95u, 9u, 13u, 48u, 57u, 65u, 
	90u, 97u, 122u, 32u, 34u, 61u, 92u, 93u, 
	9u, 13u, 32u, 34u, 45u, 59u, 63u, 92u, 
	93u, 124u, 9u, 10u, 40u, 43u, 32u, 34u, 
	45u, 59u, 63u, 92u, 124u, 9u, 10u, 40u, 
	43u, 34u, 92u, 95u, 48u, 57u, 65u, 90u, 
	97u, 122u, 32u, 34u, 61u, 92u, 95u, 9u, 
	13u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	34u, 61u, 92u, 9u, 13u, 32u, 34u, 45u, 
	59u, 63u, 92u, 124u, 9u, 10u, 40u, 43u, 
	34u, 39u, 92u, 93u, 32u, 34u, 39u, 45u, 
	59u, 63u, 92u, 93u, 124u, 9u, 10u, 40u, 
	43u, 32u, 34u, 39u, 45u, 59u, 63u, 91u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 65u, 
	90u, 97u, 122u, 32u, 34u, 39u, 45u, 59u, 
	63u, 92u, 93u, 124u, 9u, 10u, 40u, 43u, 
	34u, 39u, 92u, 93u, 95u, 48u, 57u, 65u, 
	90u, 97u, 122u, 32u, 34u, 39u, 61u, 92u, 
	93u, 95u, 9u, 13u, 48u, 57u, 65u, 90u, 
	97u, 122u, 32u, 34u, 39u, 61u, 92u, 93u, 
	9u, 13u, 32u, 34u, 39u, 45u, 59u, 63u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 32u, 
	34u, 39u, 45u, 59u, 63u, 92u, 124u, 9u, 
	10u, 40u, 43u, 32u, 34u, 39u, 45u, 59u, 
	63u, 91u, 92u, 124u, 9u, 10u, 40u, 43u, 
	65u, 90u, 97u, 122u, 32u, 34u, 39u, 45u, 
	59u, 63u, 92u, 124u, 9u, 10u, 40u, 43u, 
	32u, 34u, 45u, 59u, 63u, 92u, 124u, 9u, 
	10u, 40u, 43u, 34u, 39u, 92u, 95u, 48u, 
	57u, 65u, 90u, 97u, 122u, 32u, 34u, 39u, 
	61u, 92u, 95u, 9u, 13u, 48u, 57u, 65u, 
	90u, 97u, 122u, 32u, 34u, 39u, 61u, 92u, 
	9u, 13u, 32u, 34u, 39u, 45u, 59u, 63u, 
	92u, 124u, 9u, 10u, 40u, 43u, 34u, 39u, 
	92u, 32u, 34u, 39u, 45u, 59u, 63u, 92u, 
	124u, 9u, 10u, 40u, 43u, 34u, 39u, 92u, 
	95u, 48u, 57u, 65u, 90u, 97u, 122u, 32u, 
	34u, 39u, 45u, 59u, 63u, 92u, 95u, 124u, 
	9u, 10u, 40u, 43u, 48u, 57u, 65u, 90u, 
	97u, 122u, 34u, 39u, 92u, 93u, 95u, 48u, 
	57u, 65u, 90u, 97u, 122u, 32u, 34u, 39u, 
	45u, 59u, 63u, 92u, 93u, 95u, 124u, 9u, 
	10u, 40u, 43u, 48u, 57u, 65u, 90u, 97u, 
	122u, 32u, 34u, 39u, 45u, 59u, 63u, 92u, 
	93u, 124u, 9u, 10u, 40u, 43u, 34u, 92u, 
	93u, 95u, 48u, 57u, 65u, 90u, 97u, 122u, 
	32u, 34u, 45u, 59u, 63u, 92u, 93u, 95u, 
	124u, 9u, 10u, 40u, 43u, 48u, 57u, 65u, 
	90u, 97u, 122u, 32u, 34u, 45u, 59u, 63u, 
	92u, 93u, 124u, 9u, 10u, 40u, 43u, 92u, 
	93u, 95u, 48u, 57u, 65u, 90u, 97u, 122u, 
	32u, 45u, 59u, 63u, 92u, 93u, 95u, 124u, 
	9u, 10u, 40u, 43u, 48u, 57u, 65u, 90u, 
	97u, 122u, 34u, 92u, 95u, 48u, 57u, 65u, 
	90u, 97u, 122u, 32u, 34u, 45u, 59u, 63u, 
	92u, 95u, 124u, 9u, 10u, 40u, 43u, 48u, 
	57u, 65u, 90u, 97u, 122u, 95u, 48u, 57u, 
	65u, 90u, 97u, 122u, 32u, 45u, 59u, 63u, 
	95u, 124u, 9u, 10u, 40u, 43u, 48u, 57u, 
	65u, 90u, 97u, 122u, 65u, 90u, 97u, 122u, 
	32u, 9u, 13u, 65u, 90u, 97u, 122u, 32u, 
	39u, 92u, 9u, 13u, 65u, 90u, 97u, 122u, 
	32u, 92u, 93u, 9u, 13u, 65u, 90u, 97u, 
	122u, 32u, 39u, 92u, 93u, 9u, 13u, 65u, 
	90u, 97u, 122u, 32u, 34u, 92u, 93u, 9u, 
	13u, 65u, 90u, 97u, 122u, 32u, 34u, 92u, 
	9u, 13u, 65u, 90u, 97u, 122u, 32u, 34u, 
	39u, 92u, 93u, 9u, 13u, 65u, 90u, 97u, 
	122u, 32u, 34u, 39u, 92u, 9u, 13u, 65u, 
	90u, 97u, 122u, 0
};

static const char _LEX_single_lengths[] = {
	0, 1, 3, 2, 5, 8, 2, 5, 
	2, 7, 9, 3, 7, 2, 5, 2, 
	7, 9, 3, 5, 4, 7, 3, 8, 
	3, 7, 2, 2, 7, 10, 3, 7, 
	3, 5, 4, 7, 5, 3, 8, 10, 
	4, 8, 10, 8, 4, 6, 5, 8, 
	3, 8, 7, 4, 9, 8, 4, 6, 
	5, 8, 7, 3, 5, 4, 7, 4, 
	9, 10, 9, 5, 7, 6, 9, 8, 
	9, 8, 7, 4, 6, 5, 8, 3, 
	8, 4, 9, 5, 10, 9, 4, 9, 
	8, 3, 8, 3, 8, 1, 6, 0, 
	1, 3, 3, 4, 4, 3, 5, 4
};

static const char _LEX_range_lengths[] = {
	0, 3, 4, 1, 2, 4, 0, 2, 
	0, 2, 4, 0, 2, 0, 2, 0, 
	2, 4, 3, 4, 1, 2, 3, 5, 
	0, 2, 0, 0, 2, 4, 0, 2, 
	3, 4, 1, 2, 2, 0, 2, 4, 
	0, 2, 4, 2, 3, 4, 1, 2, 
	0, 2, 2, 3, 5, 2, 3, 4, 
	1, 2, 2, 3, 4, 1, 2, 0, 
	2, 4, 2, 3, 4, 1, 2, 2, 
	4, 2, 2, 3, 4, 1, 2, 0, 
	2, 3, 5, 3, 5, 2, 3, 5, 
	2, 3, 5, 3, 5, 3, 5, 2, 
	3, 3, 3, 3, 3, 3, 3, 3
};

static const short _LEX_index_offsets[] = {
	0, 0, 5, 13, 17, 25, 38, 41, 
	49, 52, 62, 76, 80, 90, 93, 101, 
	104, 114, 128, 135, 145, 151, 161, 168, 
	182, 186, 196, 199, 202, 212, 227, 231, 
	241, 248, 258, 264, 274, 282, 286, 297, 
	312, 317, 328, 343, 354, 362, 373, 380, 
	391, 395, 406, 416, 424, 439, 450, 458, 
	469, 476, 487, 497, 504, 514, 520, 530, 
	535, 547, 562, 574, 583, 595, 603, 615, 
	626, 640, 651, 661, 669, 680, 687, 698, 
	702, 713, 721, 736, 745, 761, 773, 781, 
	796, 807, 814, 828, 835, 849, 854, 866, 
	869, 874, 881, 888, 896, 904, 911, 920
};

static const unsigned char _LEX_indicies[] = {
	0, 0, 0, 0, 1, 2, 3, 0, 
	2, 0, 0, 0, 1, 4, 5, 4, 
	1, 6, 6, 7, 6, 6, 6, 6, 
	1, 8, 9, 10, 8, 11, 8, 13, 
	8, 8, 8, 12, 12, 1, 15, 16, 
	14, 17, 17, 18, 17, 17, 17, 17, 
	1, 19, 16, 14, 20, 15, 20, 21, 
	20, 16, 20, 20, 20, 14, 22, 23, 
	24, 22, 25, 22, 27, 16, 22, 22, 
	22, 26, 26, 14, 29, 30, 31, 28, 
	33, 34, 33, 35, 33, 36, 33, 33, 
	33, 32, 34, 36, 32, 37, 37, 38, 
	37, 37, 37, 37, 1, 39, 36, 32, 
	40, 34, 40, 41, 40, 36, 40, 40, 
	40, 32, 42, 43, 44, 42, 45, 42, 
	47, 36, 42, 42, 42, 46, 46, 32, 
	34, 36, 48, 48, 48, 48, 32, 49, 
	34, 50, 36, 48, 49, 48, 48, 48, 
	32, 51, 34, 52, 36, 51, 32, 53, 
	34, 53, 54, 53, 36, 53, 53, 53, 
	32, 34, 36, 55, 55, 55, 55, 32, 
	56, 34, 56, 57, 56, 36, 55, 56, 
	56, 56, 55, 55, 55, 32, 59, 60, 
	61, 58, 63, 63, 64, 63, 65, 66, 
	63, 63, 63, 62, 65, 66, 62, 65, 
	67, 62, 68, 68, 69, 68, 65, 66, 
	68, 68, 68, 62, 70, 71, 72, 70, 
	73, 70, 13, 65, 66, 70, 70, 70, 
	74, 74, 62, 76, 77, 78, 75, 79, 
	79, 80, 79, 65, 66, 79, 79, 79, 
	62, 65, 66, 81, 81, 81, 81, 62, 
	82, 83, 65, 66, 81, 82, 81, 81, 
	81, 62, 84, 85, 65, 66, 84, 62, 
	86, 86, 87, 86, 65, 66, 86, 86, 
	86, 62, 88, 88, 89, 88, 88, 88, 
	88, 1, 90, 77, 91, 75, 92, 76, 
	92, 93, 92, 77, 78, 92, 92, 92, 
	75, 94, 95, 96, 94, 97, 94, 27, 
	77, 78, 94, 94, 94, 98, 98, 75, 
	100, 101, 102, 103, 99, 104, 59, 104, 
	105, 104, 60, 61, 104, 104, 104, 58, 
	106, 107, 108, 106, 109, 106, 47, 60, 
	61, 106, 106, 106, 110, 110, 58, 111, 
	59, 111, 112, 111, 60, 61, 111, 111, 
	111, 58, 59, 60, 61, 113, 113, 113, 
	113, 58, 114, 59, 115, 60, 61, 113, 
	114, 113, 113, 113, 58, 116, 59, 117, 
	60, 61, 116, 58, 118, 59, 118, 119, 
	118, 60, 61, 118, 118, 118, 58, 120, 
	60, 121, 58, 122, 59, 122, 123, 122, 
	60, 61, 122, 122, 122, 58, 124, 34, 
	124, 125, 124, 36, 124, 124, 124, 32, 
	59, 60, 61, 126, 126, 126, 126, 58, 
	127, 59, 127, 128, 127, 60, 61, 126, 
	127, 127, 127, 126, 126, 126, 58, 129, 
	76, 129, 130, 129, 77, 78, 129, 129, 
	129, 75, 76, 77, 78, 131, 131, 131, 
	131, 75, 132, 76, 133, 77, 78, 131, 
	132, 131, 131, 131, 75, 134, 76, 135, 
	77, 78, 134, 75, 136, 76, 136, 137, 
	136, 77, 78, 136, 136, 136, 75, 138, 
	15, 138, 139, 138, 16, 138, 138, 138, 
	14, 15, 16, 140, 140, 140, 140, 14, 
	141, 15, 142, 16, 140, 141, 140, 140, 
	140, 14, 143, 15, 144, 16, 143, 14, 
	145, 15, 145, 146, 145, 16, 145, 145, 
	145, 14, 147, 148, 102, 149, 99, 150, 
	100, 101, 150, 151, 150, 102, 103, 150, 
	150, 150, 99, 152, 153, 154, 152, 155, 
	152, 157, 102, 103, 152, 152, 152, 156, 
	156, 99, 158, 100, 101, 158, 159, 158, 
	102, 103, 158, 158, 158, 99, 100, 101, 
	102, 103, 160, 160, 160, 160, 99, 161, 
	100, 101, 162, 102, 103, 160, 161, 160, 
	160, 160, 99, 163, 100, 101, 164, 102, 
	103, 163, 99, 165, 100, 101, 165, 166, 
	165, 102, 103, 165, 165, 165, 99, 167, 
	29, 30, 167, 168, 167, 31, 167, 167, 
	167, 28, 169, 170, 171, 169, 172, 169, 
	157, 31, 169, 169, 169, 173, 173, 28, 
	174, 29, 30, 174, 175, 174, 31, 174, 
	174, 174, 28, 176, 15, 176, 177, 176, 
	16, 176, 176, 176, 14, 29, 30, 31, 
	178, 178, 178, 178, 28, 179, 29, 30, 
	180, 31, 178, 179, 178, 178, 178, 28, 
	181, 29, 30, 182, 31, 181, 28, 183, 
	29, 30, 183, 184, 183, 31, 183, 183, 
	183, 28, 185, 186, 31, 28, 187, 29, 
	30, 187, 188, 187, 31, 187, 187, 187, 
	28, 29, 30, 31, 189, 189, 189, 189, 
	28, 190, 29, 30, 190, 191, 190, 31, 
	189, 190, 190, 190, 189, 189, 189, 28, 
	100, 101, 102, 103, 192, 192, 192, 192, 
	99, 193, 100, 101, 193, 194, 193, 102, 
	103, 192, 193, 193, 193, 192, 192, 192, 
	99, 195, 100, 101, 195, 196, 195, 102, 
	103, 195, 195, 195, 99, 76, 77, 78, 
	197, 197, 197, 197, 75, 198, 76, 198, 
	199, 198, 77, 78, 197, 198, 198, 198, 
	197, 197, 197, 75, 200, 76, 200, 201, 
	200, 77, 78, 200, 200, 200, 75, 65, 
	66, 202, 202, 202, 202, 62, 203, 203, 
	204, 203, 65, 66, 202, 203, 203, 203, 
	202, 202, 202, 62, 15, 16, 205, 205, 
	205, 205, 14, 206, 15, 206, 207, 206, 
	16, 205, 206, 206, 206, 205, 205, 205, 
	14, 208, 208, 208, 208, 1, 209, 209, 
	210, 209, 208, 209, 209, 209, 208, 208, 
	208, 1, 211, 211, 1, 212, 212, 213, 
	213, 1, 214, 34, 36, 214, 215, 215, 
	32, 216, 65, 66, 216, 217, 217, 62, 
	218, 59, 60, 61, 218, 219, 219, 58, 
	220, 76, 77, 78, 220, 221, 221, 75, 
	222, 15, 16, 222, 223, 223, 14, 224, 
	100, 101, 102, 103, 224, 225, 225, 99, 
	226, 29, 30, 31, 226, 227, 227, 28, 
	0
};

static const char _LEX_trans_targs[] = {
	2, 0, 3, 4, 3, 4, 5, 96, 
	5, 6, 13, 96, 93, 26, 6, 7, 
	8, 5, 96, 9, 10, 101, 10, 9, 
	11, 101, 91, 30, 11, 12, 74, 79, 
	13, 17, 14, 97, 15, 5, 96, 16, 
	17, 97, 17, 11, 16, 97, 22, 24, 
	19, 20, 21, 20, 21, 17, 97, 23, 
	17, 97, 24, 25, 48, 50, 26, 29, 
	98, 27, 36, 28, 29, 98, 29, 30, 
	24, 98, 89, 30, 31, 37, 58, 29, 
	98, 33, 34, 35, 34, 35, 29, 98, 
	5, 96, 38, 88, 39, 100, 39, 38, 
	40, 100, 86, 40, 41, 53, 63, 71, 
	42, 99, 42, 40, 43, 99, 51, 42, 
	99, 45, 46, 47, 46, 47, 42, 99, 
	43, 49, 42, 99, 17, 97, 52, 42, 
	99, 39, 100, 55, 56, 57, 56, 57, 
	39, 100, 10, 101, 60, 61, 62, 61, 
	62, 10, 101, 64, 66, 85, 65, 102, 
	65, 64, 66, 102, 83, 40, 65, 102, 
	68, 69, 70, 69, 70, 65, 102, 72, 
	103, 72, 73, 80, 103, 81, 72, 103, 
	10, 101, 76, 77, 78, 77, 78, 72, 
	103, 73, 80, 72, 103, 82, 72, 103, 
	84, 65, 102, 65, 102, 87, 39, 100, 
	39, 100, 90, 29, 98, 92, 10, 101, 
	94, 5, 96, 1, 96, 1, 97, 18, 
	98, 32, 99, 44, 100, 54, 101, 59, 
	102, 67, 103, 75
};

static const char _LEX_trans_actions[] = {
	0, 0, 3, 23, 0, 1, 67, 71, 
	0, 35, 39, 6, 27, 31, 0, 0, 
	0, 51, 55, 0, 51, 55, 0, 35, 
	39, 6, 27, 31, 0, 0, 0, 0, 
	0, 51, 0, 55, 0, 59, 63, 0, 
	59, 63, 0, 35, 39, 6, 27, 31, 
	0, 3, 23, 0, 1, 67, 71, 0, 
	15, 19, 0, 0, 0, 0, 0, 59, 
	63, 0, 0, 0, 43, 47, 0, 35, 
	39, 6, 27, 0, 0, 0, 0, 51, 
	55, 0, 3, 23, 0, 1, 67, 71, 
	43, 47, 0, 0, 51, 55, 0, 35, 
	39, 6, 27, 0, 0, 0, 0, 0, 
	51, 55, 0, 35, 39, 6, 27, 59, 
	63, 0, 3, 23, 0, 1, 67, 71, 
	0, 0, 43, 47, 43, 47, 0, 15, 
	19, 59, 63, 0, 3, 23, 0, 1, 
	67, 71, 43, 47, 0, 3, 23, 0, 
	1, 67, 71, 0, 0, 0, 51, 55, 
	0, 35, 39, 6, 27, 31, 59, 63, 
	0, 3, 23, 0, 1, 67, 71, 43, 
	47, 0, 35, 39, 6, 27, 51, 55, 
	59, 63, 0, 3, 23, 0, 1, 67, 
	71, 0, 0, 59, 63, 0, 15, 19, 
	0, 15, 19, 43, 47, 0, 15, 19, 
	43, 47, 0, 15, 19, 0, 15, 19, 
	0, 15, 19, 80, 0, 75, 0, 75, 
	0, 75, 0, 75, 0, 75, 0, 75, 
	0, 75, 0, 75
};

static const char _LEX_eof_actions[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 12, 
	9, 9, 9, 9, 9, 9, 9, 9
};

static const int LEX_start = 95;
static const int LEX_first_final = 95;
static const int LEX_error = 0;

static const int LEX_en_main = 95;


#line 92 "LEX.rl"

pro(LEXlexer, $u8c text, LEXstate* state) {
    test(text!=nil && *text!=nil, LEXfail);

    int cs, res = 0;
    u8c *p = (u8c*) text[0];
    u8c *pe = (u8c*) text[1];
    u8c *eof = pe;
    u8c *pb = p;

    u32 stack[LEXmaxnest] = {0, LEX};
    u32 sp = 1;
    $u8c tok = {p, p};

    
#line 485 "LEX.rl.c"
	{
	cs = LEX_start;
	}

#line 107 "LEX.rl"
    
#line 488 "LEX.rl.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const unsigned char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _LEX_trans_keys + _LEX_key_offsets[cs];
	_trans = _LEX_index_offsets[cs];

	_klen = _LEX_single_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (unsigned int)(_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _LEX_range_lengths[cs];
	if ( _klen > 0 ) {
		const unsigned char *_lower = _keys;
		const unsigned char *_mid;
		const unsigned char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += (unsigned int)((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	_trans = _LEX_indicies[_trans];
	cs = _LEX_trans_targs[_trans];

	if ( _LEX_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _LEX_actions + _LEX_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 52 "LEX.rl"
	{ lexpush(LEXname); }
	break;
	case 1:
#line 53 "LEX.rl"
	{ lexpop(LEXname); call(_LEXname, text, tok, state); }
	break;
	case 2:
#line 54 "LEX.rl"
	{ lexpush(LEXop); }
	break;
	case 3:
#line 55 "LEX.rl"
	{ lexpop(LEXop); call(_LEXop, text, tok, state); }
	break;
	case 4:
#line 56 "LEX.rl"
	{ lexpush(LEXclass); }
	break;
	case 5:
#line 57 "LEX.rl"
	{ lexpop(LEXclass); call(_LEXclass, text, tok, state); }
	break;
	case 6:
#line 58 "LEX.rl"
	{ lexpush(LEXstringA); }
	break;
	case 7:
#line 59 "LEX.rl"
	{ lexpop(LEXstringA); call(_LEXstringA, text, tok, state); }
	break;
	case 8:
#line 60 "LEX.rl"
	{ lexpush(LEXstringB); }
	break;
	case 9:
#line 61 "LEX.rl"
	{ lexpop(LEXstringB); call(_LEXstringB, text, tok, state); }
	break;
	case 10:
#line 62 "LEX.rl"
	{ lexpush(LEXentity); }
	break;
	case 11:
#line 63 "LEX.rl"
	{ lexpop(LEXentity); call(_LEXentity, text, tok, state); }
	break;
	case 12:
#line 64 "LEX.rl"
	{ lexpush(LEXexpr); }
	break;
	case 13:
#line 65 "LEX.rl"
	{ lexpop(LEXexpr); call(_LEXexpr, text, tok, state); }
	break;
	case 14:
#line 66 "LEX.rl"
	{ lexpush(LEXeq); }
	break;
	case 15:
#line 67 "LEX.rl"
	{ lexpop(LEXeq); call(_LEXeq, text, tok, state); }
	break;
	case 16:
#line 68 "LEX.rl"
	{ lexpush(LEXrulename); }
	break;
	case 17:
#line 69 "LEX.rl"
	{ lexpop(LEXrulename); call(_LEXrulename, text, tok, state); }
	break;
	case 18:
#line 70 "LEX.rl"
	{ lexpush(LEXline); }
	break;
	case 19:
#line 71 "LEX.rl"
	{ lexpop(LEXline); call(_LEXline, text, tok, state); }
	break;
	case 20:
#line 72 "LEX.rl"
	{ lexpush(LEX); }
	break;
#line 624 "LEX.rl.c"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _LEX_actions + _LEX_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 19:
#line 71 "LEX.rl"
	{ lexpop(LEXline); call(_LEXline, text, tok, state); }
	break;
	case 20:
#line 72 "LEX.rl"
	{ lexpush(LEX); }
	break;
	case 21:
#line 73 "LEX.rl"
	{ lexpop(LEX); call(_LEXroot, text, tok, state); }
	break;
#line 648 "LEX.rl.c"
		}
	}
	}

	_out: {}
	}

#line 108 "LEX.rl"

    test(cs >= LEX_first_final, LEXfail);

    nedo(
        text[0] = p;
    );
}

