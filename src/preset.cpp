#include "preset.h"

Preset::Preset(int id, char *prtName) {
    identify = id;
    presetName = prtName;

    effects.push_back(new Pre());
    effects.push_back(new Compressor());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
    effects.push_back(new Eq());
}

String Preset::getPresetName() { return presetName; }

void Preset::setPreseName(String s) { this->presetName = s; }

float Preset::getValueEffectPreset(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->value;
}

float Preset::getIncFactor(unsigned char page, unsigned char parameter) {
    return effects[page]->properties[parameter]->incCoef;
}

int Preset::getLenghtEffect(unsigned char page) {
    return effects[page]->properties.capacity();
}

void Preset::setValueEffectPreset(unsigned char page, unsigned char parameter, float value) {
    if (value <= effects[page]->properties[parameter]->max && value >= effects[page]->properties[parameter]->min) {
        effects[page]->properties[parameter]->value = value;
    }
}
void Preset::displayMenuPreset(unsigned char page, unsigned char parameter, Adafruit_ILI9341 *d) {
    int x_gauge = 0;
    int y_gauge = 120;
    if (parameter % 3 == 0)
        x_gauge = 54;
    if (parameter % 3 == 1)
        x_gauge = 152;
    if (parameter % 3 == 2)
        x_gauge = 250;

    if (parameter == 254)
        drawPreset(this->identify, this->presetName, &d);

    Property *ptr = effects[page]->properties[0];

    if (parameter > 252) {
        drawEffect(effects[page]->name, &d);
        ptr = effects[page]->properties[0];
        drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, 54, y_gauge, &d);

        ptr = effects[page]->properties[1];
        drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, 152, y_gauge, &d);

        ptr = effects[page]->properties[2];
        drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, 250, y_gauge, &d);
    } else {
        ptr = effects[page]->properties[parameter];
        drawCursor(ptr->value, ptr->name, ptr->unit, ptr->min, ptr->max, x_gauge, y_gauge, &d);
    }

    d->fillRect(0, 230, 320, 10, ILI9341_RED);
}