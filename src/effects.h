#ifndef EFFECTS_H
#define EFFECTS_H

#include <WString.h>
#include <vector>

using namespace std;

enum effectName {
    pre,
    oct,
    env_filter,
    fuzz_od,
    chorus,
    comp_2b,
    comp,
    eq
};

enum propertyName {
    active,
    gain,
    clip_up,
    clip_down,
    thresh,
    threshLP,
    threshHP,
    ratio,
    make_up,
    att,
    rel,
    rms,
    freq,
    q_fact,
    strength,
    decay_freq,
    dry_freq,
    wet_freq,
    sel,
    bias,
    vol,
    t_offset,
    bld
};

enum propertyUnit {
    noth,
    ms,
    hz,
    db,
    for_one,
    on_off,
    od_type,
    waveforms,
    filter_type,
    knee_type
};

enum propertyValueBypass {
    off,
    on,
};

enum propertyValueDrive {
    octa,
    od,
    fuzz
};

enum propertyValueWaveforms {
    sine,
    triangular,
    square
};

enum propertyValueFilterType : unsigned char {
    peaking,
    low_shelving,
    high_shelving,
    low_shelving_first,
    high_shelving_first,
    low_pass,
    high_pass,
    low_pass_first,
    high_pass_first,
    notch,
    band_stop,
    none
};

enum popertyValueKneeType {
    hard_knee,
    soft_knee1,
    soft_knee2,
    soft_knee3
};

class Property {
  public:
    Property() {}
    int name;
    float value;
    int unit;
    float min;
    float max;
    float incCoef;
    Property(int name, float value, int unit, float min, float max,
             float incCoef) {
        this->name = name;
        this->value = value;
        this->unit = unit;
        this->min = min;
        this->max = max;
        this->incCoef = incCoef;
    }
};

class Effects : public Property {
  public:
    Effects();
    int name;
    vector<Property *> properties;
};

class Pre : public Effects {
  public:
    Pre();
};

class Octaver : public Effects {
  public:
    Octaver();
};

class EnvelopeFilter : public Effects {
  public:
    EnvelopeFilter();
};

class FuzzOd : public Effects {
  public:
    FuzzOd();
};

class CompTwoBand : public Effects {
  public:
    CompTwoBand();
};

class Chorus : public Effects {
  public:
    Chorus();
};

class Compressor : public Effects {
  public:
    Compressor();
};

class Eq : public Effects {
  public:
    Eq();
};

String effectNameToStr(int n);
String propertyNameToStr(int n);
String unitToStr(int n);
String valueToStr(float value, int unit);

#endif