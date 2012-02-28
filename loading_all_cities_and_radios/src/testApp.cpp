#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(190, 220, 230 );
    vlc.setup("/Users/meR/vlc.sock"); 
    
    //we load the xml file with all the data from the cities : x,y,name city, radio station
    XML.loadFile("new_radios.xml");
    
    //we load the array with the data from our xml file
    
    XML.pushTag("document");
    int num_cities=XML.getNumTags("row");
    cout <<num_cities<<endl;
    for (int i=0; i<num_cities; i++){
        cities[i].loc.x= XML.getValue("row:X",0,i);
        cout <<cities[i].loc.x<<endl;
        cities[i].loc.y= XML.getValue("row:Y",0,i);
        cout <<cities[i].loc.y<<endl;
        cities[i].isPlaying = false; 
        cities[i].name= XML.getValue("row:name"," ",i);
        cout <<cities[i].name<<endl;
        cities[i].station= XML.getValue("row:radio"," ",i);
        cout <<cities[i].station<<endl;
    }
    XML.popTag();
    /*int num_cities=XML.getNumTags("PT:X");
    cout <<num_cities<<endl;
    for (int i=0; i<num_cities; i++){
        cities[i].loc.x= XML.getValue("PT:X",0,i);
        cout <<cities[i].loc.x<<endl;
        cities[i].loc.y= XML.getValue("PT:Y",0,i);
        cout <<cities[i].loc.y<<endl;
        cities[i].isPlaying = false; 
        cities[i].name= XML.getValue("PT:CITY","",i);
        cout <<cities[i].name<<endl;
        cities[i].station= XML.getValue("PT:Radio"," ",i);
        cout <<cities[i].station<<endl;
        
    }*/
    
    //setup calibration
    gridWidth = 720; 
    gridHeight =480; 
    gridX = 0; 
    gridY = 0; 
    buttonSize = 20; 
    
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
    for (int i = 0; i < 129; i++) {
        float d = ofDist(cities[i].loc.x, cities[i].loc.y,mouseLoc.x, mouseLoc.y); //magnitude
        d = ofClamp(d, 0, 150);
        

        if (d < 15) {
            int vol = ofMap(d, 0, 15, 100, 0);
            cities[i].volume = vol; 
            string setVol = "volume " + cities[i].volume;
            //cout << setVol << endl; 
           // cout << cities[i].name << endl;
            //vlc.run(setVol);
            
            
           cities[i].isNear = true;  
           
            if (!cities[i].isPlaying) {
                string command = "add " + cities[i].station;
                vlc.run(command); 
                cities[i].isPlaying = true; 
            }
             } else {
            cities[i].isNear = false;  
            //vlc.run("stop"); 
            cities[i].isPlaying = false;              
        }

    }
    
    if (calibrateOn) calibrate(); 
    

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (calibrateOn) drawGrid(); 
    
    ofPushMatrix(); 
    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    ofRotateZ(degreesFactor);
    
    //cities
    ofEnableSmoothing();
    ofFill();
    //ofSetColor(200);
	//ofSetHexColor(0xe0be21);
    for (int i = 0; i < 129; i++) {
        if (cities[i].isNear) {
            ofSetHexColor(0xe0be21);
        } else {
        ofSetColor(0);
        }
        cities[i].display(); 
    }
    
    
    ofPopMatrix();
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if (key == 'c') {
        if (!calibrateOn) {
        calibrateOn = true; 
        } else {
            calibrateOn = false; 
        }
    }

    if (calibrateOn) {
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
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    mouseLoc.x = x;
    mouseLoc.y = y; 
    
    //match these variables later
    mouseX = x; 
    mouseY = y; 

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if (calibrateOn) {
    if (buttonCornerOn) {
        gridX = x; 
        gridY = y; 
    }
    }
}

//--------------------------------------------------------------
void testApp::calibrate() {

    ofPushMatrix(); 
    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    ofRotateZ(degreesFactor);
    
    if (mouseX < gridX + buttonSize + 100 && mouseX > gridX - buttonSize - 100 && mouseY < gridY + buttonSize + 100 && mouseY > gridY - buttonSize - 100) {
        buttonCornerOn = true; 
    } else {
        buttonCornerOn = false; 
    }
    ofPopMatrix(); 
}

//--------------------------------------------------------------
void testApp::drawGrid(){
    
    ofPushMatrix(); 
    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    ofRotateZ(degreesFactor);
    ofNoFill(); 
    ofRect (0, 0, gridWidth, gridHeight); 
    
    for (int i = 0; i < gridWidth ; i += 20) {
        ofLine(i, 0, i, gridHeight);
    }
    
    for (int i = 0; i < gridHeight; i +=20) {
        ofLine(0, i, gridWidth, i);
    }
    
    ofFill(); 
    //buttonCorner
    if (buttonCornerOn) {
        ofSetColor(active);
    } else {
        ofSetColor(inactive);
    }
    ofCircle(0, 0, buttonSize);
    
    ofPopMatrix(); 
    
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