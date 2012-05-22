#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"


class particle
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
			
        particle();
		virtual ~particle(){};

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
		
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
		void addClockwiseForce(particle &p, float radius, float scale);
		void addCounterClockwiseForce(particle &p, float radius, float scale);
    void ballHitState(int mouseX, int mouseY);
	
		
		void addDampingForce();
        
		void setInitialCondition(float px, float py, float vx, float vy, int size, int col, int location, int amount);
        void update();
        void draw(int mouseX, int mouseY);
    void draw2();
	
		void bounceOffWalls();
    
    int rad;
    float Color;
    
    int Location;
    int Amount;
    ofPoint mouse;
    ofTrueTypeFont  bebas;

    bool hit;
		bool  bFixed;
	
		float damping;

    protected:
    private:
};

#endif // PARTICLE_H
