//
//  city.h
//  emptyExample
//
//  Created by Lia Martinez on 2/22/12.
//  Copyright (c) 2012 liamartinez.com. All rights reserved.
//

#ifndef emptyExample_city_h
#define emptyExample_city_h
#include "ofMain.h"


using namespace std;

class City {

    public:
    City ();
    ofVec2f loc; 
    string station;
    string name;
    
    void adjustVol(); 
    void display(); 
    ofPoint getLocation(); 
    
    void play(); 
    bool isNear; 
    bool isPlaying; 
    
    int volume; 
    
    float scaleFactor; 
    float scaleTotalX, scaleTotalY; 
    float degreesFactor; 
    int gridX, gridY; 
    

};

#endif
