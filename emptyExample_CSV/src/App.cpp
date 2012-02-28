/***********************************************************************
 * -----------------------------------
 * 
 * Copyright (c) 2008, Memo Akten, www.memo.tv
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 	
 ***********************************************************************/


#include "App.h"
#include <fstream>

//--------------------------------------------------------------
void App::setup(){
	pm.init(0, MAX_PARTICLES);	// (maxSpeed, maxCount);
//	for(int c=0; c<MAX_PARTICLES; c++) pm.particles[c].init(ofRandom(0, WIDTH), ofRandom(0, HEIGHT), ofRandom(-WIDTH, WIDTH), ofRandom(0, 1), 20.0f);

	showConsole = true;
	mouseX = mouseY = mouseOldX = mouseOldY = mouseVelX = mouseVelY = 0;

	ofSeedRandom();
	ofSetFrameRate(30);
	ofSetBackgroundAuto(true);			// change this to false later
	ofBackground(0, 0, 0);

	glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void App::update(){
	//	printf("***************\nStarting UPDATE loop \n");
	
	mouseVelX = mouseX - mouseOldX;
	mouseVelY = mouseY - mouseOldY;
	
	static char szBuffer[150];
	sprintf(szBuffer, "%i.csv", ofGetFrameNum());
//	printf("%s \n", szBuffer);
	
	ifstream fileIn; 
    fileIn.open(ofToDataPath(szBuffer).c_str()); 
	if(fileIn) {
		float tx, ty, tz, ti;
		for(int c=0; c<MAX_PARTICLES; c++) {
			if(fileIn.good()) {
				fileIn.getline(szBuffer, 150);
				sscanf(szBuffer, "%f,%f,%f,%f\n", &tx, &ty, &tz, &ti);
				pm.particles[c].init(tx, ty, tz, ti/255.0f, 5.0f);
//				printf("%.3f, %.3f, %.3f, %.3f\n", tx, ty, tz, ti); 
			}
//			else pm.particles[c].kill();
		}
		fileIn.close();
	} else {
		printf(" *** ERROR OPENING FILE %s *** \n", szBuffer);
	}

	
	pm.update();
	
	//	printf("** ending UPDATE loop \n");
}

//--------------------------------------------------------------
void App::draw(){
	//	printf("Starting DRAW loop \n");
	glPushMatrix();
	
	glTranslatef(WIDTH * 0.5f - 150.0f, HEIGHT * 0.5f - 150.0f, 0.0f);		// center stage
	glRotatef((mouseX - 0.5f) * 360, 0, 1, 0);				
	glRotatef((mouseY - 0.5f) * -360, 1, 0, 0);	
	
	pm.render();
	
	glPopMatrix();
	if(showConsole) {
		glColor3f(1.0f, 1.0f, 1.0f);
		ofDrawBitmapString(		"fps: "+ofToString(ofGetFrameRate()), 20, 30);
	}
	
	mouseOldX = mouseX;
	mouseOldY = mouseY;
	//	printf("ending DRAW loop \n");
}


//--------------------------------------------------------------
void App::keyPressed  (int key){
	switch(key) {
		case 'f': ofToggleFullscreen();							break;
	}
}

//--------------------------------------------------------------
void App::keyReleased  (int key){
}

//--------------------------------------------------------------
void App::mouseMoved(int x, int y ){
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;
	if(mouseOldX == 0) mouseOldX = mouseX;
	if(mouseOldY == 0) mouseOldY = mouseY;
}

//--------------------------------------------------------------
void App::mouseDragged(int x, int y, int button){
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;
}

//--------------------------------------------------------------
void App::mousePressed(int x, int y, int button){
	mouseX = x * INV_WIDTH;
	mouseY = y * INV_HEIGHT;

	mouseDown = true;
}

//--------------------------------------------------------------
void App::mouseReleased(){
	mouseDown = false;
	
}
