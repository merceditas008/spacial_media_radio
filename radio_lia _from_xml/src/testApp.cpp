#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(190, 220, 230 );
    vlc.setup("/Users/meR/vlc.sock"); 
    
    //we load the xml file with all the data from the cities : x,y,name city, radio station
    XML.loadFile("mySettings2.xml");
    
    //we load the array with the data from our xml file
    
    int num_cities=XML.getNumTags("PT:X");
    for (int i=0; i<num_cities; i++){
        cities[i].loc.x= XML.getValue("PT:X",0,i);
        cities[i].loc.y= XML.getValue("PT:Y",0,i);
        cities[i].isPlaying = false; 
        cities[i].name= XML.getValue("PT:CITY","",i);
        cities[i].station= XML.getValue("PT:Radio"," ",i);
                
    }

     
    
}

//--------------------------------------------------------------
void testApp::update(){
    for (int i = 0; i < 3; i++) {
        float d = ofDist(cities[i].loc.x, cities[i].loc.y,mouseLoc.x, mouseLoc.y); //magnitude
        d = ofClamp(d, 0, 150);
        

        if (d < 15) {
            int vol = ofMap(d, 0, 15, 100, 0);
            cities[i].volume = vol; 
            string setVol = "volume " + cities[i].volume;
            cout << setVol << endl; 
            cout << cities[i].name << endl;
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