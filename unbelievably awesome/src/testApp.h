#pragma once

#include "ofMain.h"
#include "ofxVLCRemote.h"
#include "city.h"
#include "ofxXmlSettings.h"
#include "ofxTuioClient.h"


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
    
    City cities[129]; 
    ofPoint mouseLoc; 
    
    //vlc
    ofxVLCRemote vlc; 
    
    //XML
    ofxXmlSettings XML;
    
    //calibration
    bool calibrateOn; 
    bool rotation;
    void calibrate(); 
    void drawGrid(); 
    int gridWidth, gridHeight; 
    int gridX, gridY; 
    int gridScaleX, gridScaleY;
    int buttonSize; 
    bool buttonCornerOn; 
    ofColor active, inactive; 
    int mouseX, mouseY; 
    ofVec2f knob; 
    
    float scaleFactor; 
    float degreesFactor; 
    
    void drawText(); 
    string nowPlaying; 
    
    //tuio
    ofxTuioClient myTuio;
	
	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
    
};