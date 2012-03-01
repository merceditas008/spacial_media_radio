#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);

	//-----------
	
    
    XML.loadFile("mySettings2.xml");
    int numPtTagsx = XML.getNumTags("PT:X");
    printf("%i \n", numPtTagsx);
    for (int i=0; i<numPtTagsx ; i++){
        int x= XML.getValue("PT:X",0,i);
        cout << x << endl;
        int y= XML.getValue("PT:Y",0,i);
        cout << y << endl;
        string  city= XML.getValue("PT:CITY","",i);
        cout << city << endl;
        string radio= XML.getValue("PT:Radio"," ",i);
        cout <<radio << endl;

    }
        
    
}

//--------------------------------------------------------------
void testApp::update(){
	//we change the background color here based on the values
	//affected by the mouse position
	ofBackground((int)red,(int)green,(int)blue);

}

//--------------------------------------------------------------
void testApp::draw(){

/*	//---------
	//Lets draw the stroke as a continous line
	ofSetHexColor(0x222222);
	ofNoFill();
	ofBeginShape();
	for(int i = 0; i < pointCount; i++){
		ofVertex(dragPts[i].x, dragPts[i].y);
	}
	ofEndShape(false);

    ofFill();

	//--------
	//we make a black area on the left
	//which we can print the xml text on
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 200);
	ofRect(0, 0, 160, ofGetHeight());
	ofDisableAlphaBlending();

	//our text that shows how the <STROKE> data looks in the xml file
	ofSetColor(240, 240, 240);

	string drawString = "How the data is stored:\n\n";
	if(xmlStructure.size() > 0) drawString += xmlStructure+"</STROKE>";
	TTF.drawString(drawString, 5, 40);

	//the message bars at the top and bottom of the app
	//ofSetHexColor(0xDDDDDD);
	ofEnableAlphaBlending();
	ofSetColor(0, 0, 0, 200);

	ofRect(160, 0, ofGetWidth()-160, 20);
	ofRect(160, ofGetHeight()-20, ofGetWidth()-160, 20);

	//we draw our status message at the top
	//ofSetColor(210, 90, 100);
	ofSetColor(240, 240, 240);
	TTF.drawString("Save settings to XML hit 's' key     status: "+message, 170, 12);

	//instructions at the bottom
	TTF.drawString("mouse drag changes background color and records stroke", 168, ofGetHeight() - 9);*/
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

	//-------
	//we change the background color based on
	//the two mouse coords coming in
	float xpct = (float)x / ofGetWidth();
	float ypct = (float)y / ofGetHeight();
	red			= xpct * 255.0;
	green		= ypct * 255.0;
	blue		= (int)(red - green) % 255;


	//-------------
	//we also want to record the stroke

	//lets store the drag of the user.
	//we will push into the most recent
	//<STROKE> tag - add the mouse points
	//then pop out
	if( XML.pushTag("STROKE", lastTagNumber) ){

		//now we will add a pt tag - with two
		//children - X and Y

		int tagNum = XML.addTag("PT");
		XML.setValue("PT:X", x, tagNum);
		XML.setValue("PT:Y", y, tagNum);

		XML.popTag();
	}

	//-------------
	//here we make a string of text that looks like how the xml data
	//is stored in the settings file - this is just so people can
	//visually see how the data is stored.

	//if the text is about to go off screen
	if(lineCount > 64){
		//we find the first <PT> tag with the
		//x and y data and we remove it from the begining
		//this way the displayed text always shows the newest data
		//without going offscreen.
		int pos = xmlStructure.find("</PT>");
		xmlStructure = xmlStructure.substr(pos+6);
	}

	//here we add the most recent point to our fake xml string
	xmlStructure += "    <PT>\n        <X>"+ofToString(x)+"</X>\n        <Y>"+ofToString(y)+"</Y>\n    </PT>\n";
	lineCount+=4; //we have added 4 lines so increment by 4

	//------------
	//we also record the x y points into an array - so we can draw it
	if(pointCount < NUM_PTS -1){
		dragPts[pointCount].set(x, y);
		pointCount++;
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

