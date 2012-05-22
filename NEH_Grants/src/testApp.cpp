#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup(){	
    
    
    ofBackground(255,255,255);
    bebas.loadFont("BEBAs.TTF", 15);
    
    
    grantsData.loadFile("NEH_Grants2000s.xml");
    
    loaded = true;
    
    if( !grantsData.loadFile("NEH_Grants2000s.xml")){
        grantsData.saveFile("NEH_Grants2000s.xml");
        loaded = false;
    }
    
    grantsData.pushTag("Grants"); 
    int numTags = grantsData.getNumTags("Grant");  
    grantsData.popTag();  
    
    
    grantsData.pushTag("Grants");  
    for( int i = 0; i < numTags; i++ )  
    {  
     
        
        grantsData.pushTag("Grant", i); 
        
        grant tempGrant;
        
        
        blahZip = grantsData.getValue("InstPostalCode", 0,0); 
        blahYear = grantsData.getValue("YearAwarded", 0,0);
        blahAmount = grantsData.getValue("OriginalAmount", 0,0);
        
        grantsData.popTag();
        
//        printf("%i \n", blahZip);
        
        tempGrant.zipCode = blahZip;
        tempGrant.year = blahYear;
        tempGrant.origAmount = blahAmount;
       
        
        grants.push_back(tempGrant);
          

        
        
    }  
    
    
    grantsData.popTag(); 
	

    printf("--------------------- \n");
	
    for (int i = 0; i < grants.size(); i++){
        grantMap[ grants[i].zipCode ].push_back(grants[i]);
        
        //grantMap[ grants[i].origAmount].push_back(grants[i]);
    }
    
    for( map<int, vector <grant > >::iterator i=grantMap.begin(); i!=grantMap.end(); ++i){
        
       // cout << (*i).first << ": " << (*i).second.size()<< endl;

        
        particle myParticle;
        myParticle.setInitialCondition(ofRandom(0, ofGetWidth()),ofRandom(0,ofGetHeight()),0,0,(*i).second.size(),(*i).second.size(), (*i).first, (*i).second.size());
        particles.push_back(myParticle);
        
        //radRepulse = (*i).first;
        
    }
    
    ofSetWindowTitle("NEH Grants 2000-2010");

    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    for (int i = 1; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		
		particles[i].addAttractionForce(mouseX, mouseY, 200, 1.4);
		
		for (int j = 0; j < i; j++){
			particles[i].addRepulsionForce(particles[j], 80, .99);
			particles[i].addAttractionForce(particles[j], 500, 0.005);
            
		}
	}
	
	
	for (int i = 1; i < particles.size(); i++){
		particles[i].addDampingForce();
		particles[i].update();
        particles[i].ballHitState(mouseX, mouseY);
        particles[i].bounceOffWalls();
        
        
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    



    for (int i = 1; i < particles.size(); i++){
		
        particles[i].draw(mouseX, mouseY);
        
	}
  
    for (int i = 1; i < particles.size(); i++){
		
        particles[i].draw2();
        
	}

    
 


	

    
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    

    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(){
}
