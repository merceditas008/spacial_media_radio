#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    int gridX, gridY, gridWidth, gridHeight; 

    ofColor active, inactive; 
    int buttonSize; 
    
    bool buttonCornerOn; 
    bool buttonScaleOn; 
    
    int mouseX, mouseY; 
    
    int gridMoveX, gridMoveY; 
    int gridScaleX, gridScaleY;
    
    float scaleFactor; 
    float degreesFactor; 
    
};
