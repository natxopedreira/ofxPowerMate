//
//  ofxPowerMate.cpp
//  example_simple
//
//  Created by Natxo Pedreira gonzalez on 24/11/14.
//
//

#include "ofxPowerMate.h"


ofxPowerMate::ofxPowerMate(){
    //
    data.direccion = 0;
    data.presionado = 0;
    data.intensidad = 0;
    
    //
    ofAddListener(ofEvents().update, this, &ofxPowerMate::update);
}

//--------------------------------------------------------------
ofxPowerMate::~ofxPowerMate(){
    ofRemoveListener(ofEvents().update, this, &ofxPowerMate::update);
}

//--------------------------------------------------------------
void ofxPowerMate::conecta(){
    
    // Open the device using the VID, PID,
    // and optionally the Serial number.
    handle = hid_open(0x077d, 0x0410, NULL);
    
    // Read the Manufacturer String
    res = hid_get_manufacturer_string(handle, wstr, 6);
    printf("Manufacturer String: %ls\n", wstr);
    
    // Set the hid_read() function to be non-blocking.
    hid_set_nonblocking(handle, 1);
    
   
}

//--------------------------------------------------------------
void ofxPowerMate::setBrillo(int brillo){
    // valor entre 0 - 255 ¿?¿
    
    buf[0] = 0x00;
    buf[1] = 0x41;
    buf[2] = 0x01;
    buf[3] = 0x04;	// command type
    buf[4] = 0x00;	// select table
    buf[5] = brillo;
    
    res = hid_write(handle, buf, sizeof(buf));
}

//--------------------------------------------------------------
void ofxPowerMate::update(ofEventArgs & args){
    res = hid_read(handle, buf, sizeof(buf));
    
    
    
    if(res>0){
        //hay datos
        
        data.direccion = buf[1];
        //hack en direccion porque no mantiene el valor
        if(data.direccion>200)
            data.direccion = 255;
        else
            data.direccion = 1;
        
        
        data.presionado = buf[0];
        data.intensidad = buf[3];
        
        ofNotifyEvent(tengoInfo, data);
    }

}