#include "effects.h"

Effects::Effects() {}
/*************PreAmpSection**************/
// 0.1 to 15.99 -> -20 to 24dB
// 0.1 to 10
// 0.1 to 10
Pre::Pre() {
    name = pre;
    properties.push_back(new Property(gain, 0, db, -20, 24, 1));
    properties.push_back(new Property(clip_up, 5, noth, 0.1, 10, 0.1));
    properties.push_back(new Property(clip_down, 5, noth, 0.1, 10, 0.1));
}
/*************Compressor**************/
// -90 / +6 [dB]
// 1 - 100 [:1]
// 1 - 500 [ms]
// 0 - 500 [ms]
// 0 - 2000 [ms]
// -30 / +24 [dB
Compressor::Compressor() {
    name = comp;
    properties.push_back(new Property(thresh, 0, db, -90, 6, 0.1));
    properties.push_back(new Property(ratio, 1, for_one, 1, 100, -1));
    properties.push_back(new Property(make_up, 0, db, -30, 24, 0.1));
    properties.push_back(new Property(att, 10, ms, 0, 500, 1));
    properties.push_back(new Property(rel, 100, ms, 0, 2000, 1));
    properties.push_back(new Property(rms, 100, ms, 0, 500, 1));
}
/*************EQ**************/
// Range +/-15 [dB]
// Range 20-20000 [Hz]
// Parametric, Peaking, range 0-16
Eq::Eq() {
    name = eq;
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
}

String effectNameToStr(int n) {
    switch (n) {
    case pre:
        return "Pre";
        break;
    case comp:
        return "Compressor";
        break;
    case eq:
        return "Eq";
        break;

    default:
        break;
    }
    return "err";
}

String propertyNameToStr(int n) {
    switch (n) {
    case gain:
        return "gain";
        break;
    case clip_up:
        return "clip up";
        break;
    case clip_down:
        return "clip down";
        break;
    case thresh:
        return "thresh.";
        break;
    case ratio:
        return "ratio";
        break;
    case make_up:
        return "make up";
        break;
    case att:
        return "att.";
        break;
    case rel:
        return "rel.";
        break;
    case rms:
        return "rms tc";
        break;
    case freq:
        return "freq.";
        break;
    case q_fact:
        return "Q";
        break;

    default:
        break;
    }
    return "err";
}

String unitToStr(int n) {
    switch (n) {
    case noth:
        return "";
        break;
    case ms:
        return "ms";
        break;
    case hz:
        return "Hz";
        break;
    case db:
        return "dB";
        break;
    case for_one:
        return ":1";
        break;

    default:
        break;
    }
    return "err";
}