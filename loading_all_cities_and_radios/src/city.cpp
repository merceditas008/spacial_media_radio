//
//  city.cpp
//  emptyExample
//
//  Created by Lia Martinez on 2/22/12.
//  Copyright (c) 2012 liamartinez.com. All rights reserved.
//

#include <iostream>
#include "city.h"
#include "testApp.h"

using namespace std; 


City::City () {
    
}

void City::display() {
    

    ofCircle( loc, 5);

}

void City::play() {


}

ofPoint City::getLocation () {
    
    ofPoint locay = loc; 
    return locay; 
    
}

