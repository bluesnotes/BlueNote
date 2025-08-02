#include "effects.h"

Effects::Effects() {}
/*************PreAmpSection**************/
// Gain 0.1 to 15.99 -> -20 to 24dB
// Clip Up 0.1 to 10
// Clip Down 0.1 to 10
Pre::Pre() {
    name = pre;
    properties.push_back(new Property(gain, 0, db, -20, 24, 0.1));
    properties.push_back(new Property(clip_up, 5, noth, 0.1, 10, 0.1));
    properties.push_back(new Property(clip_down, 5, noth, 0.1, 10, 0.1));
}
/*************OctaverSection**************/
// Blend 0.001 to 1 -> -60 to 0dB
Octaver::Octaver() {
    name = oct;
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
}
/*************EnvelopeFilterSection**************/
// Strength 0.1 to 15.99 ->
// Decay Stop Freq. 76 to 1.3kHz
// QFactor 0.1 to 20
// Frequency dry filter 20 to 20kHz
// Blend 0.001 to 1 -> -60 to 0dB
EnvelopeFilter::EnvelopeFilter() {
    name = env_filter;
    properties.push_back(new Property(strength, 0, noth, -20, 24, 0.1));
    properties.push_back(new Property(decay_freq, 5, hz, 76, 1300, 0.1));
    properties.push_back(new Property(q_fact, 10, noth, 0.1, 20, 0.1));
    properties.push_back(new Property(dry_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
}
/*************FuzzOdSection**************/
// Gain 0.1 to 15.99 -> -20 to 24dB
// Select Fuzz or Od
// Bias 0.1 to 10
// Post Eq
// Volume 0.001 to 10-> -60 to 20dB
// Blend 0.001 to 1 -> -60 to 0dB
FuzzOd::FuzzOd() {
    name = fuzz_od;
    properties.push_back(new Property(gain, 0, db, -20, 80, 0.1));
    properties.push_back(new Property(sel, 0, noth, 0, 1, 1));
    properties.push_back(new Property(bias, 5, noth, 0.1, 10, 0.1));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(vol, 0, db, -60, 20, 0.1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
}
/*************TeSmxSection**************/
// Threshold HP comp 0.01 to 15.99 -> -40 to 24dB
// Threshold LP comp 0.01 to 15.99 -> -40 to 24dB
// Blend 0.001 to 1 -> -60 to 0dB
CompTwoBand::CompTwoBand() {
    name = comp_2b;
    properties.push_back(new Property(threshHP, 0, db, -90, 6, 0.1));
    properties.push_back(new Property(threshLP, 0, db, -90, 6, 0.1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
}
/*************ChorusSection**************/
// Select Sine Square or triangle
// Offset auto or 0.1 to 10
// Strenght (gain of lfo)
// FC dry
// FC Wet
// Blend
Chorus::Chorus() {
    name = chorus;
    properties.push_back(new Property(sel, 0, noth, 0, 2, 1));
    properties.push_back(new Property(t_offset, 15, ms, 0, 30, 0.1));
    properties.push_back(new Property(strength, 1, noth, 0.1, 10, 0.1));
    properties.push_back(new Property(wet_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(dry_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
}
/*************CompressorSection**************/
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
    case oct:
        return "Octaver";
        break;
    case env_filter:
        return "Enveloppe filter";
        break;
    case fuzz_od:
        return "Fuzz & OD";
        break;
    case comp_2b:
        return "Comp 2 band";
        break;
    case chorus:
        return "Chorus";
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
    case threshLP:
        return "thresh.HP";
        break;
    case threshHP:
        return "thresh.LP";
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
    case strength:
        return "strength";
        break;
    case decay_freq:
        return "decay sp fr";
        break;
    case dry_freq:
        return "dry FC LP";
        break;
    case wet_freq:
        return "wet FC LP";
        break;
    case sel:
        return "select";
        break;
    case bias:
        return "bias";
        break;
    case t_offset:
        return "time offset";
        break;
    case vol:
        return "volume";
        break;
    case bld:
        return "blend";
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