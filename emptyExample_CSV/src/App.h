#pragma once

//#define OF_ADDON_USING_OFXOPENCV
//#define OF_ADDON_USING_OFXOBJLOADER
//#define OF_ADDON_USING_OFXDIRLIST
#define OF_ADDON_USING_OFXVECTORMATH
//#define OF_ADDON_USING_OFXNETWORK
//#define OF_ADDON_USING_OFXVECTORGRAPHICS
//#define OF_ADDON_USING_OFXOSC
//#define OF_ADDON_USING_OFXTHREAD
//#define OF_ADDON_USING_OFXXMLSETTINGS

 	
#include "ofMain.h"
#include "ofAddons.h"
#include "Particles.h"

#define		WIDTH		640
#define		HEIGHT		480

#define		INV_WIDTH	(1.0f/WIDTH)
#define		INV_HEIGHT	(1.0f/HEIGHT)

#define		MAX_PARTICLES				12500							// seems to cover all files
	

class App : public ofSimpleApp {
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased (int key);

		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
	
	private:
		float mouseX, mouseY, mouseOldX, mouseOldY, mouseVelX, mouseVelY;
		bool mouseDown;
		
		ParticleManager pm;
		bool showConsole;
};

