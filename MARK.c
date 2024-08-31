#include "MARK.h"

#include "01.h"
#include "B.h"
#include "INT.h"
#include "MARQ.h"
#include "PRO.h"

char MARKdivascii[] = " 1234~`_.-[>";

$u8c DIVTAGS[][3] = {{},
                     {
                         $u8str("<h1>"),
                         $u8str("</h1><h1>"),
                         $u8str("</h1>\n"),
                     },
                     {
                         $u8str("<h2>"),
                         $u8str("</h2><h2>"),
                         $u8str("</h2>\n"),
                     },
                     {
                         $u8str("<h3>"),
                         $u8str("</h3><h3>"),
                         $u8str("</h3>\n"),
                     },
                     {
                         $u8str("<h4>"),
                         $u8str("</h4><h4>"),
                         $u8str("</h4>\n"),
                     },
                     {
                         $u8str("<hr>"),
                         $u8str("</hr><hr>"),
                         $u8str("</hr>\n"),
                     },
                     {
                         $u8str("<pre>"),
                         $u8str(""),
                         $u8str("</pre>\n"),
                     },
                     {},
                     {
                         $u8str("<ol><li>"),
                         $u8str("</li><li>"),
                         $u8str("</li></ol>\n"),
                     },
                     {
                         $u8str("<ul><li>"),
                         $u8str("</li><li>"),
                         $u8str("</li></ul>\n"),
                     },
                     {
                         $u8str("<a>"),
                         $u8str(""),
                         $u8str("</a>\n"),
                     },
                     {
                         $u8str("<blockquote>"),
                         $u8str(""),
                         $u8str("</blockquote>\n"),
                     }};

fun ok64 tagopen($u8 $into, u8 tag) { return $u8feed($into, DIVTAGS[tag][0]); }
fun ok64 tagredo($u8 $into, u8 tag) { return $u8feed($into, DIVTAGS[tag][1]); }
fun ok64 tagclose($u8 $into, u8 tag) { return $u8feed($into, DIVTAGS[tag][2]); }

fun b8 pable(u64 stack) {
    u8 l = u64bytelen(stack);
    if (l == 0) return YES;
    u8 b = u64byte(stack, l - 1);
    return b == MARK_OLIST || b == MARK_ULIST || b == MARK_QUOTE;
}

fun b8 samediv(u64 stack, u64 div) {
    u8 al = u64bytelen(stack);
    u8 bl = u64bytelen(div);
    if (al != bl) return NO;
    for (u8 i = 0; i < al; ++i) {
        switch (u64byte(div, i)) {
            case MARK_INDENT:
                break;
            case MARK_QUOTE:
                if (u64byte(stack, i) != MARK_QUOTE) return NO;
                break;
            default:
                return NO;
        }
    }
    return YES;
}

fun b8 u8ws(u8 c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

pro(eatline, $u8c line, $u8c dline, u64* room) {
    sane($ok(line));
    b8 wasws = NO;
    u64 len = 0;
    u8c* p = *line;
    u8c* last = p;
    u64 lastroom = *room;
    while (p < line[1] && len < *room) {
        ++len;
        b8 isws = u8ws(*p);
        if (!wasws && isws) {
            last = p;
            lastroom = *room - len;
        }
        wasws = isws;
        ++p;
    }
    if (p == line[1] && !wasws && len < *room) {
        last = p;
        lastroom = *room - len;
    }
    dline[0] = line[0];
    dline[1] = last;
    line[0] = last;
    while (line[0] < line[1] && u8ws(**line)) ++line[0];
    *room = lastroom;
    done;
}

/**
    MARK_H1 = 1,
    MARK_H2 = 2,
    MARK_H3 = 3,
    MARK_H4 = 4,
    MARK_HLINE = 5,
    MARK_CODE = 6,
    MARK_INDENT = 7,
    MARK_OLIST = 8,
    MARK_ULIST = 9,
    MARK_LINK = 10,
    MARK_QUOTE = 11,
*/
$u8c MARKdivcanon[] = {
    $u8str(",,,,"), $u8str("  # "), $u8str(" ## "), $u8str("### "),
    $u8str("####"), $u8str("~~~~"), $u8str("````"), $u8str("____"),
    $u8str("00. "), $u8str("  - "), $u8str("[ ]:"), $u8str("  > "),
};

pro(feedbullet, $u8 $into, u64 stack, b8 head) {
    sane($ok($into));
    u8 depth = u64bytelen(stack);
    test($len($into) >= depth * 4, MARKnoroom);
    for (u8 d = 0; d < depth; ++d) {
        u8 b = u64byte(stack, d);
        test(b < MARK_END, MARKbadrec);
        b8 indent = !(head && d + 1 == depth) && (b != MARK_QUOTE);
        if (head && d + 1 == depth || b == MARK_QUOTE) {
            call($u8feed, $into, MARKdivcanon[b]);
        } else {
            call($u8feed, $into, MARKdivcanon[0]);
        }
    }
    done;
}

fun pro(MARKlinetext, $u8c name, u64 lno, MARKstate const* state) {
    sane(state != nil);
    $mv(name, state->lines[0] + lno);
    u64 div = Bat(state->divs, lno);
    u8 depth = u64bytelen(div);
    test($len(name) >= depth * 4, MARKmiss);
    name[0] += depth * 4;
    done;
}

pro(MARKANSIdiv, $u8 $into, u64 lfrom, u64 ltill, u64 stack, u32 width,
    MARKstate const* state) {
    sane($ok($into) && state != nil);
    u64 depth = u64bytelen(stack);
    test(width > depth * 4, MARKnoroom);
    u64 lno = lfrom;
    $u8c line = {};
    b8 head = YES;
    call(MARKlinetext, line, lno, state);
    while (!$empty(line)) {
        $u8c wrap = {};
        u64 room = width - depth * 4;
        call(eatline, line, wrap, &room);
        call(feedbullet, $into, stack, head);
        head = NO;
        $u8c wfmt = {};
        range64 mark = {};
        call($u8mark, state->text, wrap, &mark);
        call($u8rewind, (u8c**)state->fmt, wfmt, mark);
        call(MARQANSI, $into, wrap, wfmt);
        call($u8feed1, $into, '\n');
        if ($empty(line) && lno + 1 < ltill) {
            ++lno;
            call(MARKlinetext, line, lno, state);
            // TODO if empty (gap)
        }
    }
    done;
}

pro(MARKANSI, $u8 $into, u32 width, MARKstate const* state) {
    sane($ok($into) && state != nil && !Bempty(state->divs));
    u64$ divs = Bu64data(state->divs);
    u8cp$ lines = Bu8cpdata(state->lines);
    u64 divlen = 0;
    u64 spent = 0;
    b8 hadgap = NO;
    size_t llen = $len(divs) - 1;
    u64$ ps = Bu64data(state->ps);
    for (u64 p = 0; p + 1 < $len(ps); ++p) {
        u64 from = Bat(ps, p);
        u64 till = Bat(ps, p + 1);
        u64 div = $at(divs, from);
        call(MARKANSIdiv, $into, from, till, div, width, state);
    }
    /*for (u64 lno = 0; lno < llen; ++lno) {
        u64 div = $at(divs, lno);
        u8c$ line = MARKline(state, lno);
        if (samediv(stack, div)) {
            ++divlen;
            hadgap = NO;
        } else if (!hadgap && div == 0 && $len(line) == 1) {
            ++divlen;
            hadgap = YES;
        } else if (divlen > 0) {
            call(MARKANSIdiv, $into, lno - divlen, lno, stack, width, state);
            divlen = 0;
            hadgap = NO;
        }
    }
    if (divlen > 0) {
        call(MARKANSIdiv, $into, llen - divlen, llen, stack, width, state);
    }*/
    done;
}

pro(MARKMARQdiv, u64 from, u64 till, MARKstate* state) {
    sane(1);
    MARQstate marq = {};
    u8c* tb = state->text[0];
    u8* fb = state->fmt[0];
    size_t boff = Bat(state->lines, from) - tb;
    size_t eoff = Bat(state->lines, till) - tb;
    marq.text[0] = tb + boff;
    marq.text[1] = tb + eoff;
    marq.fmt[0] = fb + boff;
    marq.fmt[1] = fb + eoff;
    call(MARQlexer, &marq);
    done;
}

pro(MARKMARQ, MARKstate* state) {
    sane(state != nil && !Bempty(state->divs));
    u64$ divs = Bu64data(state->divs);
    u8cp$ lines = Bu8cpdata(state->lines);
    u64$ blocks = Bu64data(state->ps);
    for (u64 b = 0; b + 1 < $len(blocks); ++b) {
        call(MARKMARQdiv, $at(blocks, b), $at(blocks, b + 1), state);
    }
    done;
}

pro(htmlp, $u8 $into, u64 line, u64 len, u8 depth, MARKstate const* state) {
    sane($ok($into) && state != nil && line + len <= $len(state->lines));
    u8c* text0 = state->text[0];
    u8c* fmt0 = state->fmt[0];
    for (u64 l = line; l < line + len; ++l) {
        u8c$ line = MARKline(state, l);
        a$str(haha, ">>>");
        $print(haha);
        $print(line);
        line[0] += depth * 4;
        size_t f = line[0] - text0;
        size_t t = line[1] - text0;
        $u8c fmt = {fmt0 + f, fmt0 + t};
        call(MARQHTML, $into, line, fmt);
    }
    done;
}

pro(MARKHTML, $u8 $into, MARKstate const* state) {
    sane($ok($into) && state != nil);
    u64 stack = 0;
    u64 plen = 0;
    $u64 divs;
    $u8cp lines;
    $mv(divs, Bu64data(state->divs));
    $mv(lines, Bu8cpdata(state->lines));
    $for(u64, div, divs) {
        u64 d = *div;
        u8 depth = u64bytelen(stack);
        u8 newdepth = u64bytelen(d);
        u8 keep = 0;
        for (; keep < depth && keep < newdepth; ++keep) {
            u8 n = u64byte(d, keep);
            u8 x = u64byte(stack, keep);
            if (n == MARK_INDENT) {
                continue;
            } else if (n == MARK_QUOTE) {
                if (x == MARK_QUOTE) {
                    continue;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
        if (keep < depth) {
            size_t at = div - *divs;
            call(htmlp, $into, at - state->_plen - 1, state->_plen + 1, depth,
                 state);
            // maybe close p
            for (u8 c = depth - 1; c >= keep; --c) {
                call(tagopen, $into, u64byte(d, c));
            }
            stack = u64lowbytes(stack, keep);
        } else if (keep == depth && u64topbyte(d) != MARK_INDENT && d != 0) {
            call(tagredo, $into, u64topbyte(d));
        } else {  // maybe open things
            for (u8 o = keep; o < newdepth; ++o) {
                u8 b = u64byte(d, o);
                call(tagclose, $into, b);
                stack = u64setbyte(stack, b, o);
            }
        }
        ++*lines;
    }
    u8 depth = u64bytelen(stack);
    size_t at = $len(Bdata(state->lines));  // FIXME
    call(htmlp, $into, at - state->_plen - 1, state->_plen + 1, depth, state);
    done;
}

fun ok64 pushdiv(MARKstate* state, u8 div) {
    u8 l = u64bytelen(state->_div);
    if (l < 8) {
        state->_div = u64setbyte(state->_div, div, l);
    }
    printf("pushdiv %c=%lu\n", div, state->_div);
    return OK;
}

ok64 MARKonHLine($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_HLINE);
}
ok64 MARKonOList($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_OLIST);
}
ok64 MARKonUList($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_ULIST);
}
ok64 MARKonLink($cu8c tok, MARKstate* state) { return OK; }
ok64 MARKonRoot($cu8c tok, MARKstate* state) { return OK; }
ok64 MARKonDiv($cu8c tok, MARKstate* state) { return OK; }
ok64 MARKonH1($cu8c tok, MARKstate* state) { return pushdiv(state, MARK_H1); }
ok64 MARKonH2($cu8c tok, MARKstate* state) { return pushdiv(state, MARK_H2); }
ok64 MARKonH3($cu8c tok, MARKstate* state) { return pushdiv(state, MARK_H3); }
ok64 MARKonH4($cu8c tok, MARKstate* state) { return pushdiv(state, MARK_H4); }
ok64 MARKonIndent($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_INDENT);
}
ok64 MARKonQuote($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_QUOTE);
}

ok64 MARKonCode($cu8c tok, MARKstate* state) {
    return pushdiv(state, MARK_CODE);
}

pro(MARKonLine, $cu8c tok, MARKstate* state) {
    sane($ok(tok) && state != nil);
    b8 end = tok[1] == state->text[1];
    if (Bempty(state->ps) ||
        !samediv(Blast(state->divs), state->_div)) {  // FIXME gaps
        call(Bu64feed1, state->ps, Bdatalen(state->lines));
    }
    call(Bu64feed1, state->divs, state->_div);
    call(Bu8cpfeed1, state->lines, tok[0]);
    if (tok[1] == state->text[1]) {
        call(Bu64feed1, state->ps, Bdatalen(state->lines));
        call(Bu8cpfeed1, state->lines, tok[1]);
        call(Bu64feed1, state->divs, 0);
    }
    state->_div = 0;
    done;
}
