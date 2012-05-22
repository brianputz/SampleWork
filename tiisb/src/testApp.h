#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Clone.h"
#include "ofMain.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofxCvHaarFinder.h"
#include "ofEvents.h"




class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void dragEvent(ofDragInfo dragInfo);
  //  void mouseMoved(int x, int y, ofxFenster* win);
	void loadFace(string face);
    void faceLoader();
    //void gotMessage(ofMessage msg);
	void mouseMovedEvent(ofMouseEventArgs &args);
	
	void keyPressed(int key);

	ofxFaceTrackerThreaded camTracker;
	ofVideoGrabber cam;
	
	ofxFaceTracker srcTracker;
	ofImage src;
    //arduino
    ofArduino	ard;
    bool		bSetupArduino;
    
	vector<ofVec2f> srcPoints;
    
    vector<string> imageLoad;
    vector<string> txtLoad;
    vector<string> imageCaption;
    
    
    vector<ofImage> images;
    
    vector<ofImage> txtImgs;
    
    ofTrueTypeFont impact;
    
	ofVec2f mousePos;
	bool cloneReady, faceOn;
	Clone clone;
	ofFbo srcFbo, maskFbo;
    
//    ofxCvHaarFinder finder;
    
//    ofVideoGrabber 		vidGrabber;
//    
//    ofxCvColorImage			colorImg;
//    
//    ofxCvGrayscaleImage 	grayImage;
    
//    ofImage meme;
    
  //  ofxFenster* test;

	ofDirectory faces;
	int currentFace;
    int imgLoadNum;
};
