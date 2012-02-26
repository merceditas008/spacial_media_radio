#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(190, 220, 230 );

    
    vlc.setup("/Users/meR/vlc.sock"); 
     
    
    int yLoc = ofGetScreenHeight()/2;
    
    for (int i = 0; i < 3; i++) {
        cities[i].loc.x = 250*(i+1); 
        cities[i].loc.y = yLoc; 
        cities[i].isPlaying = false; 
        cities[0].station = "http://7279.live.streamtheworld.com:80/KAMPFMAAC_SC";
        cities[1].station = "http://2293.live.streamtheworld.com:80/KKGLFMAAC_SC";
        cities[2].station = "http://6693.live.streamtheworld.com:80/WTMJAMAAC_SC";
        
    }

}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i < 3; i++) {
        float d = ofDist(cities[i].loc.x, cities[i].loc.y,mouseLoc.x, mouseLoc.y); //magnitude
        d = ofClamp(d, 0, 150);
        

        if (d < 150) {
            int vol = ofMap(d, 0, 150, 100, 0);
            cities[i].volume = vol; 
            string setVol = "volume " + cities[i].volume;
            cout << setVol << endl; 
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
    

}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableSmoothing();
    ofFill();
    //ofSetColor(200);
	//ofSetHexColor(0xe0be21);
    for (int i = 0; i < 3; i++) {
        if (cities[i].isNear) {
            ofSetHexColor(0xe0be21);
        } else {
        ofSetColor(0);
        }
        cities[i].display(); 
    }
    
    
    
  
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
    mouseLoc.x = x;
    mouseLoc.y = y; 

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

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