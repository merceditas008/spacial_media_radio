#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(100, 100, 100);
    
    gridX = 0; 
    gridY = 0; 
    gridWidth = 500;
    gridHeight = 500; 
    
    buttonSize = 20; 
    gridMoveX = 0; 
    gridMoveY  = 0; 
    
    gridScaleX = 1; 
    gridScaleY = 1; 
    scaleFactor = 0; 
    degreesFactor = 0; 
    
    //set colors
    active.r = 255;
    active.b = 100; 
    active.g = 100;  
    
    inactive.r = 100;
    inactive.g = 100; 
    inactive.b = 100; 
    


}

//--------------------------------------------------------------
void testApp::update(){
    
    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    
    if (mouseX < gridX + buttonSize + 100 && mouseX > gridX - buttonSize - 100 && mouseY < gridY + buttonSize + 100 && mouseY > gridY - buttonSize - 100) {
        buttonCornerOn = true; 
    } else {
        buttonCornerOn = false; 
    }
    
    if (mouseX < gridWidth + buttonSize + 100 && mouseX > gridWidth - buttonSize - 100 && mouseY < gridHeight + buttonSize + 100 && mouseY > gridHeight - buttonSize - 100) {
        buttonScaleOn = true; 
    } else {
        buttonScaleOn = false; 
    }
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    

    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    //ofRotate(degreesFactor, gridWidth/2, gridHeight/2, 0);
    ofRotateZ(degreesFactor);
    
    ofSetColor(255, 255, 255);
    //ofRect (gridX, gridY, gridWidth, gridHeight);
    ofRect (0, 0, gridWidth, gridHeight);

    //ofRect(100, 200, 500, 500);
    
    //cities
    ofSetColor(100, 100, 190);
    ofCircle(200,300, 10);
    ofCircle(300, 250, 10);
    ofCircle(220, 280, 10);
    ofCircle(400, 420, 10);
    ofCircle(450, 420, 10);
    
    //buttonScale
    if (buttonScaleOn) {
        ofSetColor(active);
    } else {
        ofSetColor(inactive);
    }
    ofCircle(gridWidth, gridHeight, buttonSize);
    

    //buttonCorner
    if (buttonCornerOn) {
    ofSetColor(active);
    } else {
     ofSetColor(inactive);
    }
    ofCircle(0, 0, buttonSize);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'r') {
    scaleFactor = 0; 
    gridX = 0; 
    gridY = 0; 
    }
    
    if (key == OF_KEY_RIGHT) scaleFactor += 0.01; 
    if (key == OF_KEY_LEFT) scaleFactor -= 0.01; 

    if (key == OF_KEY_UP) degreesFactor += 0.1; 
    if (key == OF_KEY_DOWN) degreesFactor -= 0.1; 
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    mouseX = x; 
    mouseY = y; 

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    if (buttonCornerOn) {
        gridX = x; 
        gridY = y; 
    }
    
    if (buttonScaleOn) {
        //map the distance between mouseX and buttonScale to Scale Values
        float d = ofDist(0, x, 0, y); //get the distance between mouse and origin //it should be distance between last spot and new spot
        cout << "distance " << d << endl; 
        scaleFactor = ofMap(d, 100, 200, 1, 2); 
        cout << "scaleFactor " << scaleFactor << endl; 
    }
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}