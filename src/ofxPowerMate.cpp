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
    
    elapsed = ofGetElapsedTimeMillis();
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
    //hid_set_nonblocking(handle, 1);
    unsigned char bufBrillo[8];
    bufBrillo[0] = 0x41;
    bufBrillo[1] = 0x01;
    bufBrillo[2] = 0x01;
    bufBrillo[3] = 0x00;	// command type
    bufBrillo[4] = brillo;	// select table
    bufBrillo[5] = 0x00;
     bufBrillo[6] = 0x00;
     bufBrillo[7] = 0x00;
    res = hid_send_feature_report(handle, bufBrillo, sizeof(bufBrillo));
    
    
    //res = hid_write(handle, buf, bufbuf);
    
}


//--------------------------------------------------------------
void ofxPowerMate::update(ofEventArgs & arg){

    res = hid_read(handle, buf,  sizeof(buf));
   
   
    if(res>0 && ofGetElapsedTimeMillis() > elapsed+40){
        //hay datos
        
        data.presionado = buf[0];
        data.direccion = buf[1];
        
        if(data.direccion>200)
            data.direccion = 255;
        else
            data.direccion = 1;
        
        
        
        
        ofNotifyEvent(tengoInfo, data);
        
        elapsed = ofGetElapsedTimeMillis();
    }

}