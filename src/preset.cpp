#include "preset.h"

DSP_manager l_dsp;

Preset::Preset(unsigned char id, char *prtName) {
    identify = id;
    presetName = prtName;

    effects.push_back(new Pre());
    effects.push_back(new Octaver());
    effects.push_back(new EnvelopeFilter());
    effects.push_back(new FuzzOd());
    effects.push_back(new CompTwoBand());
    effects.push_back(new Chorus());
    effects.push_back(new Compressor());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
    int j = 1; // for eq name eq1 eq2 ...
    for (int i = effects.size() - 4; i < effects.size(); i++) {
        effects[i]->name += j << 8;
        j++;
    }
}

String Preset::getPresetName() { return presetName; }

float Preset::getValueEffectPreset(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->value;
}

float Preset::getMinValueEffectPreset(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->min;
}

float Preset::getMaxValueEffectPreset(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->max;
}

float Preset::getIncFactor(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->incCoef;
}

unsigned int Preset::getLenghtPreset() {
    return sizeof(effects) - 2;
}

int Preset::getLenghtEffect(unsigned char page) {
    return effects[page]->properties.size();
}

void Preset::setPreseName(String s) { this->presetName = s; }

void Preset::setValueEffectPreset(unsigned char page, unsigned char parameter, float value) {
    if (value > effects[page]->properties[parameter]->max)
        effects[page]->properties[parameter]->value = effects[page]->properties[parameter]->max;
    else if (value < effects[page]->properties[parameter]->min)
        effects[page]->properties[parameter]->value = effects[page]->properties[parameter]->min;
    else
        effects[page]->properties[parameter]->value = value;

    l_dsp.setValueEffect(effects[page]);
}

void Preset::displayMenuPreset(unsigned char page, unsigned char parameter, presetDisplay display, Adafruit_ILI9341 *d) {

    int x_gauge = 0;
    int y_gauge = 120;

    if (display == allDisplay) // display new preset so preset title to
        drawPreset(this->identify, true, this->presetName, &d);
    else if (display == selectPresetAllDisplay)
        drawPreset(this->identify, false, this->presetName, &d);

    Property *ptr = effects[page]->properties[0];

    unsigned int numParamEffect = effects[page]->properties.size();

    if (display >= effectDisplay) { // display all gauge & effect title
        unsigned int pageEffect = parameter / 3 + 1;
        unsigned int numPageEffect = ((numParamEffect - 1) / 3) + 1;
        unsigned int presetLenght = getLenghtPreset();

        if (page == presetLenght) {
            drawEffect(effectLeftArrow, effects[page]->name, pageEffect, numPageEffect, &d);
        } else if (page == 0) {
            drawEffect(effectRightArrow, effects[page]->name, pageEffect, numPageEffect, &d);
        } else {
            drawEffect(effectTwoArrow, effects[page]->name, pageEffect, numPageEffect, &d);
        }

        if (numParamEffect - parameter == 1 && parameter + 3 >= numParamEffect) {
            ptr = effects[page]->properties[parameter];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 152, y_gauge, &d);

        } else if (numParamEffect - parameter == 2 && parameter + 3 >= numParamEffect) {
            ptr = effects[page]->properties[parameter++];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 103, y_gauge, &d);

            ptr = effects[page]->properties[parameter];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 201, y_gauge, &d);

        } else {
            ptr = effects[page]->properties[parameter++];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 54, y_gauge, &d);

            ptr = effects[page]->properties[parameter++];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 152, y_gauge, &d);

            ptr = effects[page]->properties[parameter];
            drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, 250, y_gauge, &d);
        }

    } else { // display 1 gauge
        if (parameter % 3 == 0) {
            if (numParamEffect - parameter == 1 && parameter + 3 >= numParamEffect)
                x_gauge = 152; // first gauge for display 1 gauge
            else if (numParamEffect - parameter == 2 && parameter + 3 >= numParamEffect)
                x_gauge = 103;
            else
                x_gauge = 54;
        }
        if (parameter % 3 == 1) {
            if (numParamEffect - (parameter - 1) == 2 && parameter + 3 >= numParamEffect)
                x_gauge = 201; // second gauge for display 1 gauge
            else
                x_gauge = 152;
        }
        if (parameter % 3 == 2)
            x_gauge = 250; // third gauge for display 1 gauge
        ptr = effects[page]->properties[parameter];
        drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, ptr->incCoef, x_gauge, y_gauge, &d);
    }

    d->fillRect(0, 230, 320, 10, ILI9341_RED);
}