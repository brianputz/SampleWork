#include "particle.h"
#include "ofMain.h"
#include "testApp.h"

//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0,0,0,0,0);
	damping = 0.05f;
	bFixed = false;
    bebas.loadFont("BEBAs.TTF", 15);
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a fofVec2force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addRepulsionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
        diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce(float x, float y, float radius, float scale){
    
	// ----------- (1) make a vector of where this position is: 
	
	ofVec2f posOfForce;
	posOfForce.set(x,y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addRepulsionForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce(particle & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}

//------------------------------------------------------------
void particle::addClockwiseForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.y * scale * pct;
        frc.y = frc.y + diff.x * scale * pct;
		p.frc.x = p.frc.x + diff.y * scale * pct;
        p.frc.y = p.frc.y - diff.x * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addCounterClockwiseForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.y * scale * pct;
        frc.y = frc.y - diff.x * scale * pct;
		p.frc.x = p.frc.x - diff.y * scale * pct;
        p.frc.y = p.frc.y + diff.x * scale * pct;
		
    }
}


//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy, int size, int col, int location, int amount){
    pos.set(px,py);
	vel.set(vx,vy);
    rad = size;
    Amount = amount;
    
    Color = col;
    
    Location = location;
}

//------------------------------------------------------------
void particle::update(){	
	if (bFixed == false){
		vel = vel + frc;
		pos = pos + vel;
	}
}

void particle::ballHitState(int mouseX, int mouseY){
    
    ofPoint mouse;
    
    mouse.set(mouseX, mouseY);
    
    //ofPoint 
    if((pos-mouse).length() < rad){
        
        hit = true;
        //ofSetColor(255, 255, 255);
        
    }
    else{
        hit = false;
    }
    
}

//------------------------------------------------------------
void particle::draw(int mouseX, int mouseY){
    
    //for( map<int, vector <grant > >::iterator i=grantMap.begin(); i!=grantMap.end(); ++i){

    ofSetColor(Color, 50, Color, 50);
    ofCircle(pos.x, pos.y, rad);


}

void particle::draw2(){
    
    if(hit == true && pos.x < 1200 && pos.y < 630){
        
        ofSetColor(0, 0, 0, 50);
        ofRect(pos.x, pos.y, 300, 180);
        ofSetColor(255, 255, 255);
        string Location2;
        string Amount2;
        Location2 = ofToString(Location);
        Amount2 = ofToString(Amount);
        //ofDrawBitmapString(Location2, 100, 100);
        bebas.drawString("Location by Zip:", pos.x +30, pos.y+30);
        bebas.drawString(Location2, pos.x + 30, pos.y+ 60);
        bebas.drawString("Number of Grants received:", pos.x + 30, pos.y + 90);
        bebas.drawString(Amount2, pos.x + 30, pos.y + 120);
        
    }
    
    if(hit == true && pos.x > 1200 && pos.y <630){
        
        ofSetColor(0, 0, 0, 50);
        ofRect(pos.x-300, pos.y, 300, 180);
        ofSetColor(255, 255, 255);
        string Location2;
        string Amount2;
        Location2 = ofToString(Location);
        Amount2 = ofToString(Amount);
        //ofDrawBitmapString(Location2, 100, 100);
        bebas.drawString("Location by Zip:", pos.x -270, pos.y+30);
        bebas.drawString(Location2, pos.x -270, pos.y+ 60);
        bebas.drawString("Number of Grants received:", pos.x -270, pos.y + 90);
        bebas.drawString(Amount2, pos.x -270, pos.y + 120);
        
    }
    
    if(hit == true  && pos.y > 630 && pos.x > 300){
        
        ofSetColor(0, 0, 0, 50);
        ofRect(pos.x-300, pos.y-180, 300, 180);
        ofSetColor(255, 255, 255);
        string Location2;
        string Amount2;
        Location2 = ofToString(Location);
        Amount2 = ofToString(Amount);
        //ofDrawBitmapString(Location2, 100, 100);
        bebas.drawString("Location by Zip:", pos.x -270, pos.y-150);
        bebas.drawString(Location2, pos.x -270, pos.y-120);
        bebas.drawString("Number of Grants received:", pos.x -270, pos.y -90);
        bebas.drawString(Amount2, pos.x -270, pos.y -60);
        
    }
    
    if(hit == true  && pos.y > 630 && pos.x <300){
        
        ofSetColor(0, 0, 0, 50);
        ofRect(pos.x, pos.y-180, 300, 180);
        ofSetColor(255, 255, 255);
        string Location2;
        string Amount2;
        Location2 = ofToString(Location);
        Amount2 = ofToString(Amount);
        //ofDrawBitmapString(Location2, 100, 100);
        bebas.drawString("Location by Zip:", pos.x+30, pos.y-150);
        bebas.drawString(Location2, pos.x+30, pos.y-120);
        bebas.drawString("Number of Grants received:", pos.x+30, pos.y -90);
        bebas.drawString(Amount2, pos.x+30, pos.y -60);
        
    }
    
    
}


//------------------------------------------------------------
void particle::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -1;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -1;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
