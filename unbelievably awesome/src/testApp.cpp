#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(190, 220, 230 );
    vlc.setup("/Users/lia/vlc.sock"); 
    
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
    
    gridScaleX = 0; 
    gridScaleY = 0; 
    scaleFactor = 1; 
    degreesFactor = 0; 
    
    //set colors
    active.r = 255;
    active.b = 100; 
    active.g = 100;  
    
    inactive.r = 100;
    inactive.g = 100; 
    inactive.b = 100; 
    
    //set rotation off
    
    rotation=false;
    nowPlaying = "nothing" ;  
    
    //tuio--------------------------------//
    ofSetVerticalSync(true);
	
	//Connect to Port
	myTuio.connect(3333);
	
	
	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents.touchDown,this,&testApp::touchDown);
	ofAddListener(ofEvents.touchUp,this,&testApp::touchUp);
	ofAddListener(ofEvents.touchMoved,this,&testApp::touchMoved);
    
}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if (calibrateOn) drawGrid(); 
    if (calibrateOn) calibrate(); 
    drawText();
    
    
    //draw the cities------------------------------------------//
    ofPushMatrix(); 
    ofTranslate(gridX,gridY);
    ofScale(gridScaleX + scaleFactor, gridScaleY + scaleFactor);
    ofRotateZ(degreesFactor);
    ofEnableSmoothing();
    ofFill();

    for (int i = 0; i < 129; i++) {
        if (cities[i].isNear) {
            ofSetHexColor(0xe0be21);
        } else {
            ofSetColor(0);
        }
        cities[i].display(); 
    }
    ofFill();
    ofPopMatrix();
    
    
    //check distance------------------------------------------//
    for (int i = 0; i < 129; i++) {
        
        //we set the new coordinates of the cities to compare with mousePosition
        
        float loc_x_temp = cities[i].loc.x*(scaleFactor)+gridX;
        float loc_y_temp = cities[i].loc.y*(scaleFactor)+gridY;
        float d = ofDist(loc_x_temp, loc_y_temp,knob.x, knob.y); //magnitude
        
        
        if (rotation){
            ofVec2f locV(loc_x_temp,loc_y_temp);
            locV.rotate(degreesFactor);
            d= ofDist(locV.x, locV.y,knob.x, knob.y);
        }
        
        d = ofClamp(d, 0, 15);
        
        //add the station to the playlist. change later to "play"---------//
        if (d < 15) {
            int vol = ofMap(d, 0, 15, 100, 0);
            cities[i].volume = vol; 
            string setVol = "volume " + cities[i].volume; //for soundflower?
            
            cities[i].isNear = true;  
            
            if (!cities[i].isPlaying) {
                string command = "add " + cities[i].station;
                vlc.run(command); 
                nowPlaying = cities[i].name; 
                cities[i].isPlaying = true; 

            }
        } else {
            cities[i].isNear = false;  
            cities[i].isPlaying = false;              
        }
        
    }
    

    //tuio---------------------------//
    //render TUIO Cursors and Objects
	myTuio.drawCursors();
	myTuio.drawObjects();
    
    knob = myTuio.returnCursor();
    ofSetColor(100, 250, 100);
    ofCircle (knob.x, knob.y, 60); 
    

    
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
            scaleFactor = 1; 
            gridX = 0; 
            gridY = 0; 
        }
        
        if (key == OF_KEY_RIGHT) scaleFactor += 0.01; 
        if (key == OF_KEY_LEFT) scaleFactor -= 0.01; 
        
        if (key == OF_KEY_UP) {
            degreesFactor += 0.1; 
            rotation= true;
            
        }
        
        if (key == OF_KEY_DOWN){
            degreesFactor -= 0.1; 
            rotation= true;
            
        }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
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
    ofSetColor(0, 0, 0);
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
    //draw text
    
    
}

//--------------------------------------------------------------
void testApp::drawText(){
    
    
    
    ofSetColor(200, 50, 50);
    ofDrawBitmapString("NOW PLAYING: " + nowPlaying, 800 , 100);
    ofDrawBitmapString("c - toggle calibrate", 50,625); 
    ofDrawBitmapString("r - reset", 50,640); 
    ofDrawBitmapString("Up and Down - rotation", 50, 655); 
    ofDrawBitmapString("Left and Right- scale", 50, 670); 
    ofDrawBitmapString("Drag the red dot - location", 50, 685); 
    string textXY = "X Y coordinates: "+ofToString(gridX, 2) + " " + ofToString(gridY, 2);
    ofDrawBitmapString(textXY, 50,700);
    
    string textScale = "Scale: "+ofToString(scaleFactor,2);
    ofDrawBitmapString(textScale, 50,715);
    
    string textDegrees = "Degrees: "+ofToString(degreesFactor,2);
    ofDrawBitmapString(textDegrees, 50,730);
    
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

//-------------------------TUIO----------------//
void testApp::touchDown(ofTouchEventArgs & touch){
	cout << " cursor added: " + ofToString(touch.id)+
	" X: "+ofToString(touch.x)+
	" Y: "+ofToString(touch.y)
	<< endl;
    

}

void testApp::touchUp(ofTouchEventArgs & touch){
	cout << " cursor removed: " + ofToString(touch.id)+
    " X: "+ofToString(touch.x)+
    " Y: "+ofToString(touch.y)
    << endl;
	
}

void testApp::touchMoved(ofTouchEventArgs & touch){
	cout << " cursor updated: " + ofToString(touch.id)+
    " X: "+ofToString(touch.x)+
    " Y: "+ofToString(touch.y)
    << endl;


    
}