#ifndef EFFECTS_H
#define EFFECTS_H

#include <WString.h>
#include <vector>

using namespace std;

enum effectName {
    pre,
    comp,
    eq
};

enum propertyName {
    gain,
    clip_up,
    clip_down,
    thresh,
    ratio,
    make_up,
    att,
    rel,
    rms,
    freq,
    q_fact
};

enum propertyUnit {
    noth,
    ms,
    hz,
    db,
    for_one
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

#endif