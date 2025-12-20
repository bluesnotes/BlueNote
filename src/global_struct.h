#ifndef GLOBAL_STRUCT_H
#define GLOBAL_STRUCT_H

struct INOUTVAR {
    bool changeVariable = false;
    float temperature = 0;
    unsigned char MCP23008Inputs = 0;
    bool impedanceReturn = false;
    bool impedanceInst = false;
    bool padReturn = false;
    bool padInst = false;
    bool phantom = false;
    unsigned char volumeLineOut = 0;
    char lineOutRouting = 0;
};

#endif