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


#pragma once

#include "ofxVectorMath.h"


/********************* Particle ***********************/
class Particle {
	friend class ParticleManager;
public:	
	Particle() {
		intensity = 0;
		size = 0;
	}
	
	void init(float initX, float initY, float initZ, float initIntensity, float initSize) {
		pos.set(initX, initY, initZ);
		intensity = initIntensity;
		size = initSize;
	}
	
	void kill() {
		intensity = 0;
	}
	
	void setManager(ParticleManager *_manager) {
		manager = _manager;
	}
	
	
protected:
	/****** main *******/
	ofxVec3f pos;			// current position
	float intensity;			// color of particle
	float size;	
	
	void update() {
	}
	
	void render() {
//		printf("Particle::render()\n");
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);
		glScalef(size, size, size);
		glColor3f(intensity, intensity, intensity);
		glBegin( GL_QUADS );
		glVertex3f(-0.5f, -0.5f, 0);
		glVertex3f( 0.5f, -0.5f, 0);
		glVertex3f( 0.5f,  0.5f, 0);
		glVertex3f(-0.5f,  0.5f, 0);
		glEnd();
		glPopMatrix();
	}
	
	ParticleManager *manager;
	
	float maxSpeed;	
	
};



/********************* Particle Manager ***********************/
class ParticleManager /*: public MSAThread*/ {
public:
	Particle *particles;
	
	ParticleManager() {
		particles = NULL;
	}
	
	~ParticleManager() {
		if(particles) delete particles;
	}
	
	void init(float _maxSpeed, int _maxCount) {
		maxSpeed		= _maxSpeed;
		maxCount		= _maxCount;
		particles		= new Particle[maxCount];
	}
	
	void update() {
		for(int c=0; c<maxCount; c++) {
			if(particles[c].intensity) {
				particles[c].update();
			}
		}
	}
	
	void render() {
//		printf("ParticleManager::render()\n");
		for(int c=0; c<maxCount; c++) {
			if(particles[c].intensity) {
				particles[c].render();
			}
		}
	}
	
	
protected:
	float			maxSpeed;
	int				maxCount;
	
};

