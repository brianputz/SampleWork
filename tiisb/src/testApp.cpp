#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
       
    
//#ifdef TARGET_OSX
//	ofSetDataPathRoot("../data/");
//#endif
    
    //cam.setDeviceID(9);
	ofSetVerticalSync(true);
    ofSetFrameRate(30);
	cloneReady = false;
	cam.initGrabber(640, 480);
	clone.setup(cam.getWidth(), cam.getHeight());
	ofFbo::Settings settings;
	settings.width = cam.getWidth();
	settings.height = cam.getHeight();
	maskFbo.allocate(settings);
	srcFbo.allocate(settings);
	camTracker.setup();
	srcTracker.setup();
	srcTracker.setIterations(25);
	srcTracker.setAttempts(4);
    
       
  //Vector for String path  
    
    impact.loadFont("Impact.TTF", 12);
    

    
    for(int i =0; i < 9; i++){
        
        string bleh = ofToString(i)+".jpg";
        imageLoad.push_back(bleh);
        
        images.push_back(imageLoad[i]);
        
        images[i].loadImage(imageLoad[i]);
        
        string bleh2= ofToString(i)+".png";
        txtLoad.push_back(bleh2);
        
        txtImgs.push_back(txtLoad[i]);
        
        
        txtImgs[i].loadImage(txtLoad[i]);

        
    }
    

    
    impact.loadFont("Impact.TTF", 30);
    
    imgLoadNum = 0;
    
    
	faces.allowExt("jpg");
	faces.allowExt("png");
	faces.listDir("faces");
	currentFace = 0;
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
    
    faceOn = false;
    
}

void testApp::update() {
    
    //image loading from data folder
 
    if(camTracker.getFound()){
        
        faceOn = true;
    }
    
    else{
        
        faceOn = false;
    }
    
    //timer
    
    if(faceOn == false){
        
        imgLoadNum++;
    }
    
    
    //-----------------------------------------------
    if(imgLoadNum >= imageLoad.size()){
        
        imgLoadNum = 0;
    }
    
    if(imgLoadNum == 0){
        imgLoadNum = 0;
    }
    loadFace(imageLoad[imgLoadNum]);
   
	cam.update();
	if(cam.isFrameNew()) {
		camTracker.update(toCv(cam));
		
		cloneReady = camTracker.getFound();
		if(cloneReady) {
			ofMesh camMesh = camTracker.getImageMesh();
			camMesh.clearTexCoords();
			camMesh.addTexCoords(srcPoints);
			
			maskFbo.begin();
			ofClear(0, 255);
			camMesh.draw();
			maskFbo.end();
			
			srcFbo.begin();
			ofClear(0, 255);
			src.bind();
			camMesh.draw();
			src.unbind();
			srcFbo.end();
			
			clone.setStrength(16);
			clone.update(srcFbo.getTextureReference(), cam.getTextureReference(), maskFbo.getTextureReference());
		}
	}

}



//--------------------------------------------------------------


//--------------------------------------------------------------

void testApp::draw() {
    

    
    ofSetColor(255);

    ofScale(2, 2);

	
	if(src.getWidth() > 0 && cloneReady) {
		clone.draw(40, 0);
        ofEnableAlphaBlending();
        txtImgs[imgLoadNum].draw(40, -20);
        ofDisableAlphaBlending();
	} else {
		cam.draw(40, 0);
	}

// debug purposes for finding faces	
    
/*	if(!camTracker.getFound()) {
		drawHighlightString("camera face not found", 10, 10);
	}
	if(src.getWidth() == 0) {
		drawHighlightString("drag an image here", 10, 30);
        //drawHighlightString(ofToString(currentFace), 10, 40);
	} else if(!srcTracker.getFound()) {
		drawHighlightString("image face not found", 10, 30);
        
	}
 */

    
    ofSetColor(0, 0, 0, .5);
     ofRect(0, 700, ofGetWidth(), 200);
    ofSetColor(255);
    
    //drawHighlightString(ofToString(imgLoadNum), 10, 50);
    

    
}

void testApp::loadFace(string face){
    
    ofScale(2,2);
	src.loadImage(face);
	if(src.getWidth() > 0) {
		srcTracker.update(toCv(src));
		srcPoints = srcTracker.getImagePoints();
	}
}

void testApp::dragEvent(ofDragInfo dragInfo) {

}


void testApp::keyPressed(int key){
	switch(key){
	case OF_KEY_UP:
		currentFace++;
		break;
	case OF_KEY_DOWN:
		currentFace--;
		break;
            

	}
    
    if(key == ' '){
        imgLoadNum++;
    }
    if(key == 'h'){
        
        imgLoadNum--;
    }
    //ofScale(2,2);
	currentFace = ofClamp(currentFace,0,faces.size());
	if(faces.size()!=0){
		loadFace(faces.getPath(currentFace));
	}
}
