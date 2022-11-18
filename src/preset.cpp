#include "preset.h"
#include "FreeSans12pt7b.h"
#include "FreeSans18pt7b.h"
#include "FreeSans9pt7b.h"
#include "FreeSansBold12pt7b.h"
#include "FreeSansBold9pt7b.h"

/*************PreAmpSection**************/
// 0.1 to 15.99 -> -20 to 24dB
// 0.1 to 10
// 0.1 to 10

Pre::Pre(float g, float c_up, float c_down) {
    gain = g;
    clip_up = c_up;
    clip_down = c_down;
}

float Pre::getPreGain() { return gain; };
float Pre::getPreClipUp() { return clip_up; };
float Pre::getPreClipDown() { return clip_down; };

void Pre::setPre(float g, float c_up, float c_down) {
    if (g >= 0.1 && g <= 15.9)
        this->gain = g;
    if (c_up >= 0.1 && c_up <= 10)
        this->clip_up = c_up;
    if (c_down >= 0.1 && c_down <= 10)
        this->clip_down = c_down;
}

void Pre::setPreGain(float g) {
    if (g >= 0.1 && g <= 15.9)
        this->gain = g;
}
void Pre::setPreClipUp(float c_up) {
    if (c_up >= 0.1 && c_up <= 10)
        this->clip_up = c_up;
}
void Pre::setPreClipDown(float c_down) {
    if (c_down >= 0.1 && c_down <= 10)
        this->clip_down = c_down;
}

/*************Compressor**************/
// -90 / +6 [dB]
// 1 - 100 [:1]
// 1 - 500 [ms]
// 0 - 500 [ms]
// 0 - 2000 [ms]
// -30 / +24 [dB

Compressor::Compressor(float thresh, float rat, float rmst, float attack,
                       float release, float make_up) {
    if (thresh >= -90 && thresh <= 6)
        threshold = thresh;
    if (rat >= 1 && rat <= 100)
        ratio = rat;
    if (rmst >= 1 && rmst <= 500)
        rms_tc = rmst;
    if (attack >= 0 && attack <= 500)
        hold = attack;
    if (release >= 0 && release <= 2000)
        decay = release;
    if (make_up >= -30 && make_up <= 24)
        postgain = make_up;
}

float Compressor::getThreshold() { return threshold; };
float Compressor::getRatio() { return ratio; };
float Compressor::getRMSTimeConstant() { return rms_tc; };
float Compressor::getAttack() { return hold; };
float Compressor::getRelease() { return decay; };
float Compressor::getMake_Up() { return postgain; };

void Compressor::setCompressor(float thresh, float rat, float rmst,
                               float attack, float release, float make_up) {
    if (thresh >= -90 && thresh <= 6)
        this->threshold = thresh;
    if (rat >= 1 && rat <= 100)
        this->ratio = rat;
    if (rmst >= 1 && rmst <= 500)
        this->rms_tc = rmst;
    if (attack >= 0 && attack <= 500)
        this->hold = attack;
    if (release >= 0 && release <= 2000)
        this->decay = release;
    if (make_up >= -30 && make_up <= 24)
        this->postgain = make_up;
}

void Compressor::setThreshold(float thresh) {
    if (thresh >= -90 && thresh <= 6)
        this->threshold = thresh;
}
void Compressor::setRatio(float rat) {
    if (rat >= 1 && rat <= 100)
        this->ratio = rat;
}
void Compressor::setRMSTimeConstant(float rmst) {
    if (rmst >= 1 && rmst <= 500)
        this->rms_tc = rmst;
}
void Compressor::setAttack(float attack) {
    if (attack >= 0 && attack <= 500)
        this->hold = attack;
}
void Compressor::setRelease(float release) {
    if (release >= 0 && release <= 2000)
        this->decay = release;
}
void Compressor::setMake_Up(float make_up) {
    if (make_up >= -30 && make_up <= 24)
        this->postgain = make_up;
}

/*************EQ**************/
// Range +/-15 [dB]
// Range 20-20000 [Hz]
// Parametric, Peaking, range 0-16

Eq::Eq(float g, float f, float q) {
    gain = g;
    freq = f;
    qFactor = q;
}

float Eq::getEqGain() { return gain; };
float Eq::getEqFreq() { return freq; };
float Eq::getEqQ() { return qFactor; };

void Eq::setEq(float g, float f, float q) {
    if (g >= -15 && g <= 15)
        this->gain = g;
    if (f >= 20 && f <= 20000)
        this->freq = f;
    if (q >= 0 && q <= 16)
        this->qFactor = q;
}

void Eq::setEqGain(float g) {
    if (g >= -15 && g <= 15)
        this->gain = g;
}
void Eq::setEqFreq(float f) {
    if (f >= 20 && f <= 20000)
        this->freq = f;
}
void Eq::setEqQ(float q) {
    if (q >= 0 && q <= 16)
        this->qFactor = q;
}

/*************PRESET**************/

Preset::Preset(int id, String prtName, Eq eq1, Eq eq2, Eq eq3, Eq eq4, Compressor compressor,
               Pre pre) {
    identify = id;
    presetName = prtName;
    this->eq1 = eq1;
    this->eq2 = eq2;
    this->eq3 = eq3;
    this->eq4 = eq4;
    this->compressor = compressor;
    this->pre = pre;
}

int Preset::getID() { return identify; }

String Preset::getPresetName() { return presetName; }

Pre *Preset::getPre() { return &this->pre; }

Compressor *Preset::getComp() { return &this->compressor; }

Eq *Preset::getEq1() { return &this->eq1; }
Eq *Preset::getEq2() { return &this->eq2; }
Eq *Preset::getEq3() { return &this->eq3; }
Eq *Preset::getEq4() { return &this->eq4; }

void Preset::setPreseName(String s) { this->presetName = s; }

void Preset::drawCenterString(const String &buf, int x, int y, Adafruit_ILI9341 ***d) {
    int16_t x1, y1;
    uint16_t w, h;
    (***d).getTextBounds(buf, 0, y, &x1, &y1, &w, &h); // calc width of new string
    (***d).setCursor(x - w / 2, y);
    (***d).print(buf);
}

void Preset::drawPreset(int index, String &preset_name, Adafruit_ILI9341 **d) {
    (**d).fillRect(0, 0, 320, 50, ILI9341_LIGHTGREY);
    (**d).fillRoundRect(7, 7, 63, 40, 10, 0x018c);

    (**d).setCursor(10, 38);
    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans18pt7b);
    (**d).print(index);

    (**d).setCursor(90, 38);
    (**d).setTextColor(ILI9341_BLACK);
    (**d).setFont(&FreeSans18pt7b);
    (**d).print(preset_name);
}

void Preset::drawEffect(const String &effect, Adafruit_ILI9341 **d) {
    (**d).fillRect(0, 50, 320, 30, 0x018c);

    (**d).setCursor(65, 72);
    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans12pt7b);
    //(**d).print(effect);
    drawCenterString(effect, 160, 72, &d);
}

void Preset::drawCursor(float value, const String &parameter_name, const String &parameter_unit,
                        int min, int max, int center_x, int center_y, Adafruit_ILI9341 **d) {

    int radius = 29;

    float percent = ((value + abs(min)) / (max - min)) * 100;

    (**d).fillRect(center_x - 40, center_y - 32, 80, 140, ILI9341_BLACK);

    (**d).drawCircle(center_x, center_y, 30, ILI9341_LIGHTGREY);
    (**d).drawCircle(center_x, center_y, 31, ILI9341_LIGHTGREY);

    for (int i = -20; i < 21; i++) {
        float angle_needle = (((percent + (i * 0.1)) * 0.01745331 * 2.9) - 4.19);
        int needle_x = (center_x + ((radius)*cos(angle_needle)));
        int needle_y = (center_y + ((radius)*sin(angle_needle)));
        (**d).drawLine(center_x, center_y, needle_x, needle_y, 0X4c94);
    }

    (**d).setTextColor(ILI9341_WHITE);
    (**d).setFont(&FreeSans9pt7b);
    drawCenterString(parameter_name, center_x, center_y + 60, &d);

    String str = String(value + parameter_unit);
    if (str.length() > 6) {
        str = String(value);
        (**d).setTextColor(ILI9341_WHITE);
        (**d).setFont(&FreeSansBold9pt7b);
        drawCenterString(str, center_x, center_y + 80, &d);
        drawCenterString(parameter_unit, center_x, center_y + 100, &d);
    } else {
        (**d).setTextColor(ILI9341_WHITE);
        (**d).setFont(&FreeSansBold9pt7b);
        drawCenterString(str, center_x, center_y + 80, &d);
    }
}

float Preset::getItemMenuPreset(unsigned char page, unsigned char parameter) {
    float tab[7][3]{
        {this->pre.getPreGain(), this->pre.getPreClipUp(), this->pre.getPreClipDown()},
        {this->compressor.getThreshold(), this->compressor.getRatio(), this->compressor.getMake_Up()},
        {this->compressor.getAttack(), this->compressor.getRelease(), this->compressor.getRMSTimeConstant()},
        {this->getEq1()->getEqGain(), this->getEq1()->getEqFreq(), 0},
        {this->getEq2()->getEqGain(), this->getEq2()->getEqFreq(), this->getEq2()->getEqQ()},
        {this->getEq3()->getEqGain(), this->getEq3()->getEqFreq(), this->getEq3()->getEqQ()},
        {this->getEq4()->getEqGain(), this->getEq4()->getEqFreq(), 0}};
    return tab[page][parameter];
}

void Preset::setItemPreset(unsigned char page, unsigned char parameter, float value) {

    if (page == 0) {
        if (parameter == 0)
            this->pre.setPreGain(value);
        if (parameter == 1)
            this->pre.setPreClipUp(value);
        if (parameter == 2)
            this->pre.setPreClipDown(value);
    }
    if (page == 1) {
        if (parameter == 0)
            this->compressor.setThreshold(value);
        if (parameter == 1)
            this->compressor.setRatio(value);
        if (parameter == 2)
            this->compressor.setMake_Up(value);
    }
    if (page == 2) {
        if (parameter == 0)
            this->compressor.setAttack(value);
        if (parameter == 1)
            this->compressor.setRelease(value);
        if (parameter == 2)
            this->compressor.setRMSTimeConstant(value);
    }
    if (page == 3) {
        if (parameter == 0)
            this->getEq1()->setEqGain(value);
        if (parameter == 1)
            this->getEq1()->setEqFreq(value);
    }
    if (page == 4) {
        if (parameter == 0)
            this->getEq2()->setEqGain(value);
        if (parameter == 1)
            this->getEq2()->setEqFreq(value);
        if (parameter == 2)
            this->getEq2()->setEqQ(value);
    }
    if (page == 5) {
        if (parameter == 0)
            this->getEq3()->setEqGain(value);
        if (parameter == 1)
            this->getEq3()->setEqFreq(value);
        if (parameter == 2)
            this->getEq3()->setEqQ(value);
    }
    if (page == 6) {
        if (parameter == 0)
            this->getEq4()->setEqGain(value);
        if (parameter == 1)
            this->getEq4()->setEqFreq(value);
    }
}

void Preset::displayMenuPreset(unsigned char page, unsigned char parameter, Adafruit_ILI9341 *d) {
    // this is just a processor for when you exit the top level menu

    String strAct = this->presetName;
    if (parameter == 4)
        drawPreset(this->identify, strAct, &d);

    int value = 100;
    int y_gauge = 120;

    if (page == 0) {
        if (parameter > 2)
            drawEffect("Pre-Amp >", &d);
        if (parameter > 2 || parameter == 0)
            drawCursor(this->pre.getPreGain(), "gain", "dB", -40, 24, 54, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->pre.getPreClipUp(), "clip up", "", 0.1, 10, 152, y_gauge, &d);
        if (parameter > 2 || parameter == 2)
            drawCursor(this->pre.getPreClipDown(), "clip dn", "", 0.1, 10, 250, y_gauge, &d);
    }
    if (page == 1) {
        if (parameter > 2)
            drawEffect("<  Compressor  >", &d);
        if (parameter > 2 || parameter == 0)
            drawCursor(this->compressor.getThreshold(), "thresh.", "dB", -100, 0, 54, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->compressor.getRatio(), "ratio", ":1", 1, 100, 152, y_gauge, &d);
        if (parameter > 2 || parameter == 2)
            drawCursor(this->compressor.getMake_Up(), "make-up", "dB", -30, 24, 250, y_gauge, &d);
    }
    if (page == 2) {
        if (parameter > 2) {
            drawEffect("<  Compressor  >", &d);
            (*d).fillRect(0, 80, 320, 150, ILI9341_BLACK);
        }
        if (parameter > 2 || parameter == 0)
            drawCursor(this->compressor.getAttack(), "att.", "ms", 0, 500, 54, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->compressor.getRelease(), "rel.", "ms", 0, 500, 152, y_gauge, &d);
        if (parameter > 2 || parameter == 2)
            drawCursor(this->compressor.getRMSTimeConstant(), "rms tc", "ms", 1, 500, 250, y_gauge, &d);
    }
    if (page == 3) {
        if (parameter > 2) {
            drawEffect("<  Eq. low freq.  >", &d);
            (*d).fillRect(0, 80, 320, 150, ILI9341_BLACK);
        }
        if (parameter > 2 || parameter == 0)
            drawCursor(this->getEq1()->getEqGain(), "gain", "dB", -15, 15, 105, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->getEq1()->getEqFreq(), "freq.", "Hz", 20, 2000, 210, y_gauge, &d);
    }
    if (page == 4) {
        if (parameter > 2) {
            drawEffect("<  Eq. par. 1  >", &d);
            (*d).fillRect(0, 80, 320, 150, ILI9341_BLACK);
        }
        if (parameter > 2 || parameter == 0)
            drawCursor(this->getEq2()->getEqGain(), "gain", "dB", -15, 15, 54, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->getEq2()->getEqFreq(), "freq.", "Hz", 20, 20000, 152, y_gauge, &d);
        if (parameter > 2 || parameter == 2)
            drawCursor(this->getEq2()->getEqQ(), "Q", "", 0, 16, 250, y_gauge, &d);
    }
    if (page == 5) {
        if (parameter > 2) {
            drawEffect("<  Eq. par. 2  >", &d);
            (*d).fillRect(0, 80, 320, 150, ILI9341_BLACK);
        }
        if (parameter > 2 || parameter == 0)
            drawCursor(this->getEq3()->getEqGain(), "gain", "dB", -15, 15, 54, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->getEq3()->getEqFreq(), "freq.", "Hz", 20, 20000, 152, y_gauge, &d);
        if (parameter > 2 || parameter == 2)
            drawCursor(this->getEq3()->getEqQ(), "Q", "", 0, 16, 250, y_gauge, &d);
    }
    if (page == 6) {
        if (parameter > 2) {
            drawEffect("<  Eq. high freq.", &d);
            (*d).fillRect(0, 80, 320, 150, ILI9341_BLACK);
        }
        if (parameter > 2 || parameter == 0)
            drawCursor(this->getEq4()->getEqGain(), "gain", "dB", -15, 15, 105, y_gauge, &d);
        if (parameter > 2 || parameter == 1)
            drawCursor(this->getEq4()->getEqFreq(), "freq.", "Hz", 200, 20000, 210, y_gauge, &d);
    }

    d->fillRect(0, 230, 320, 10, ILI9341_RED);
}

int compare(const Preset &P1, const Preset &P2) {
    if (P1.identify > P2.identify)
        return P1.identify;
    else
        return P2.identify;
}
