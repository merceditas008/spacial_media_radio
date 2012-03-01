#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
    map.loadImage("radio_2.png");
    int tagNum=0;

}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
    map.draw(0,0);

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){

		//no data gets saved unless you hit the s key
		if(key == 's'){
			XML.saveFile("mySettings.xml");
			message ="settings saved to xml!";
		}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){


}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
        //now we will add a pt tag - with two
		//children - X and Y*/
        
		int tagNum = XML.addTag("PT");
        XML.setValue("PT:city ", tagNum, tagNum);
		XML.setValue("PT:X", x, tagNum);
		XML.setValue("PT:Y", y, tagNum);
        tagNum++;
        printf("%i", tagNum);
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

