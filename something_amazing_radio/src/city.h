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
    ofPoint loc; 
    string station;
    string name;
    
    void adjustVol(); 
    void display(); 
    void play(); 
    bool isNear; 
    bool isPlaying; 
    
    int volume; 
    

};

#endif
