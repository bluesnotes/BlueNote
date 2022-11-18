#ifndef PRESET_H
#define PRESET_H

#include "pin.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <string.h>

using namespace std;

class Pre {
  private:
    float gain = 0.00;   // 0.1 to 15.99 -> -20 to 24db
    float clip_up = 1;   // 0.1 to 10
    float clip_down = 1; // 0.1 to 10

  public:
    Pre() {}

    Pre(float g, float c_up, float c_down);

    float getPreGain();
    float getPreClipUp();
    float getPreClipDown();

    void setPre(float g, float c_up, float c_down);

    void setPreGain(float g);
    void setPreClipUp(float c_up);
    void setPreClipDown(float c_down);
};

class Compressor {
  private:
    float threshold = 0.0; // -90 / +6 [dB]
    float ratio = 1.0;     // 1 - 100 [:1]
    float rms_tc = 1.0;    // 1 - 500 [ms]
    float hold = 0.0;      // 0 - 500 [ms]
    float decay = 0.0;     // 0 - 2000 [ms]
    float postgain = 0.0;  // -30 / +24 [dB]

  public:
    Compressor() {}

    Compressor(float thresh, float rat, float rmst, float attack, float release,
               float make_up);

    float getThreshold();
    float getRatio();
    float getRMSTimeConstant();
    float getAttack();
    float getRelease();
    float getMake_Up();

    void setCompressor(float thresh, float rat, float rmst, float attack,
                       float release, float make_up);

    void setThreshold(float thresh);
    void setRatio(float rat);
    void setRMSTimeConstant(float rmst);
    void setAttack(float attack);
    void setRelease(float release);
    void setMake_Up(float make_up);
};

class Eq {
  private:
    float gain;    // Range +/-15 [dB]
    float freq;    // Range 20-20000 [Hz]
    float qFactor; // Parametric, Peaking, range 0-16

  public:
    Eq() {}

    Eq(float g, float f, float q);

    // Getters
    float getEqGain();
    float getEqFreq();
    float getEqQ();

    // Setters
    void setEq(float g, float f, float q);

    void setEqGain(float g);
    void setEqFreq(float f);
    void setEqQ(float q);
};

class Preset {
  private:
    int identify;
    String presetName;

    Eq eq1;
    Eq eq2;
    Eq eq3;
    Eq eq4;
    Compressor compressor;
    Pre pre;

    void drawCenterString(const String &buf, int x, int y, Adafruit_ILI9341 ***d);
    void drawPreset(int index, String &preset_name, Adafruit_ILI9341 **d);
    void drawEffect(const String &effect, Adafruit_ILI9341 **d);
    void drawCursor(float value, const String &parameter_name, const String &parameter_unit,
                    int min, int max, int center_x, int center_y, Adafruit_ILI9341 **d);

  public:
    Preset(int id, String prtName, Eq, Eq, Eq, Eq, Compressor, Pre);

    // Getters
    int getID();
    String getPresetName();

    Pre *getPre();

    Compressor *getComp();

    Eq *getEq1();
    Eq *getEq2();
    Eq *getEq3();
    Eq *getEq4();

    // Setters
    void setPreseName(String s);

    float getItemMenuPreset(unsigned char page, unsigned char parameter);

    void setItemPreset(unsigned char page, unsigned char parameter, float value);

    void displayMenuPreset(unsigned char page, unsigned char parameter, Adafruit_ILI9341 *d);

    friend int compare(const Preset &P1, const Preset &P2);
};

#endif