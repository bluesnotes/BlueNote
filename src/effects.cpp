#include "effects.h"

Effects::Effects() {}
/*************PreAmpSection**************/
// Gain 0.1 to 15.99 -> -20 to 24dB
// Clip Up 0.1 to 10
// Clip Down 0.1 to 10
// on - off
Pre::Pre() {
    name = pre;
    properties.push_back(new Property(gain, 0, db, -20, 24, 0.1));
    properties.push_back(new Property(clip_up, 5, noth, 1, 9, 0.1));
    properties.push_back(new Property(clip_down, 5, noth, 1, 9, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************OctaverSection**************/
// Blend 0.001 to 1 -> -60 to 0dB
// on - off
Octaver::Octaver() {
    name = oct;
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************EnvelopeFilterSection**************/
// Strength 0.1 to 15.99 ->
// Decay Stop Freq. 76 to 1.3kHz
// QFactor 0.1 to 20
// Frequency dry filter 20 to 20kHz
// Blend 0.001 to 1 -> -60 to 0dB
// on - off
EnvelopeFilter::EnvelopeFilter() {
    name = env_filter;
    properties.push_back(new Property(strength, 0, noth, -20, 24, 0.1));
    properties.push_back(new Property(decay_freq, 500, hz, 76, 1300, -1));
    properties.push_back(new Property(q_fact, 10, noth, 0.1, 20, 0.1));
    properties.push_back(new Property(dry_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************FuzzOdSection**************/
// Gain 0.1 to 15.99 -> -20 to 80dB
// Select drive Od/Fuzz/Octa
// Bias -1 to 1
// Post Eq
// Volume 0.001 to 10-> -60 to 20dB
// Blend 0.001 to 1 -> -60 to 0dB
// on - off
FuzzOd::FuzzOd() {
    name = fuzz_od;
    properties.push_back(new Property(gain, 0, db, -20, 80, 0.1));
    properties.push_back(new Property(sel, 0, od_type, 0, 2, 1));
    properties.push_back(new Property(bias, 0, noth, -1, 1, 0.1));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 60, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 400, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 800, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(vol, 0, db, -60, 20, 0.1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************TeSmxSection**************/
// Threshold HP comp 0.01 to 15.99 -> -40 to 24dB
// Threshold LP comp 0.01 to 15.99 -> -40 to 24dB
// Blend 0.001 to 1 -> -60 to 0dB
// on - off
CompTwoBand::CompTwoBand() {
    name = comp_2b;
    properties.push_back(new Property(threshHP, 0, db, -40, 24, 0.1));
    properties.push_back(new Property(threshLP, 0, db, -40, 24, 0.1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************ChorusSection**************/
// Select Sine Square or triangle
// Offset 0.1 to 30 ms
// Strenght (gain of lfo)
// FC dry
// FC Wet
// Blend
// on - off
Chorus::Chorus() {
    name = chorus;
    properties.push_back(new Property(sel, 0, waveforms, 0, 2, 1));
    properties.push_back(new Property(t_offset, 15, ms, 0, 30, 0.1));
    properties.push_back(new Property(strength, 1, ms, 0.1, 15, 0.1));
    properties.push_back(new Property(freq, 0.2, hz, 0.1, 2, 0.1));
    properties.push_back(new Property(wet_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(dry_freq, 20000, hz, 20, 20000, -1));
    properties.push_back(new Property(bld, -6, db, -60, 0, 0.1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************CompressorSection**************/
// threshold -80 / +6 [dB]
// ratio 1 - 100 [:1]
// make-up-30 / +24 [dB]
// attack 0 - 500 [ms]
// release 0 - 2000 [ms]
// rms 0 - 2000 [ms]
// on - off
Compressor::Compressor() {
    name = comp;
    properties.push_back(new Property(thresh, 0, db, -80, 6, 0.5));
    properties.push_back(new Property(ratio, 1.1, for_one, 1.1, 100, -1));
    properties.push_back(new Property(make_up, 0, db, -30, 24, 0.1));
    properties.push_back(new Property(att, 10, ms, 0, 500, 1));
    properties.push_back(new Property(rel, 100, ms, 0, 2000, 1));
    properties.push_back(new Property(sel, 0, knee_type, 0, 3, 1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}
/*************EQ**************/
// Range +/-15 [dB]
// Range 20-20000 [Hz]
// QFactor
// Filter type (peaking, low shelving...)
// on - off
Eq::Eq() {
    name = eq;
    properties.push_back(new Property(gain, 0, db, -15, 15, 0.1));
    properties.push_back(new Property(freq, 200, hz, 20, 20000, -1));
    properties.push_back(new Property(q_fact, 1.41, noth, 0, 16, 0.01));
    properties.push_back(new Property(sel, 0, filter_type, 0, 2, 1));
    properties.push_back(new Property(active, 0, on_off, 0, 1, 1));
}

String effectNameToStr(int n) {
    switch (n & 255) {
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
    }
    return "err";
}

String propertyNameToStr(int n) {
    switch (n) {
    case active:
        return "active";
        break;
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
    case on_off:
        return "";
        break;
    case od_type:
        return "";
        break;
    case waveforms:
        return "";
        break;
    case filter_type:
        return "";
        break;
    }

    return "err";
}

String valueToStr(float value, int unit) {
    if (unit < on_off) {
        return String(value);
    } else if (unit == on_off) {
        switch ((int)value) {
        case off:
            return "Off";
            break;
        case on:
            return "On";
            break;
        }
        return "err";
    } else if (unit == od_type) {
        switch ((int)value) {
        case octa:
            return "octa";
            break;
        case od:
            return "OD";
            break;
        case fuzz:
            return "fuzz";
            break;
        }
        return "err";
    } else if (unit == waveforms) {
        switch ((int)value) {
        case sine:
            return "sine";
            break;
        case triangular:
            return "triang.";
            break;
        case square:
            return "square";
            break;
        }
        return "err";
    } else if (unit == filter_type) {
        switch ((int)value) {
        case peaking:
            return "peaking";
            break;
        case low_shelving:
            return "low shel.";
            break;
        case high_shelving:
            return "hi shel.";
            break;
        case low_shelving_first:
            return "lo sh.1st";
            break;
        case high_shelving_first:
            return "hi sh.1st";
            break;
        case low_pass:
            return "low pass";
            break;
        case high_pass:
            return "hi pass";
            break;
        case low_pass_first:
            return "lp 1st";
            break;
        case high_pass_first:
            return "hp 1st";
            break;
        case notch:
            return "notch";
            break;
        case band_stop:
            return "bnd stop";
            break;
        }
        return "err";
    } else if (unit == knee_type) {
        switch ((int)value) {
        case hard_knee:
            return "hard";
            break;
        case soft_knee1:
            return "soft I";
            break;
        case soft_knee2:
            return "soft II";
            break;
        case soft_knee3:
            return "soft III";
            break;
        }
        return "err";
    }
}