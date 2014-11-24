//
//  ofxPowerMate.h
//  example_simple
//
//  Created by Natxo Pedreira gonzalez on 24/11/14.
//
//

#ifndef __example_simple__ofxPowerMate__
#define __example_simple__ofxPowerMate__

#include "ofMain.h"
#include "hidapi.h"

class powerData {
    
public:
    int direccion;
    int presionado;
    int intensidad;
};

class ofxPowerMate {
    
public:
    ofxPowerMate();
    ~ofxPowerMate();
    
    void conecta();
    void update();
    void setBrillo(int brillo);
    void apaga();
    void enciende();
    
    ofEvent<powerData> tengoInfo;
private:
    
   
    wchar_t wstr[6];
    unsigned char buf[6];
    int res;
    hid_device *handle;

    float elapsed;
    powerData data;
};

#endif /* defined(__example_simple__ofxPowerMate__) */
