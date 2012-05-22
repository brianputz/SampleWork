#include "testApp.h"
#include "ofAppGlutWindow.h"
#include "ofMain.h"
#include "ofxFensterManager.h"

int main() {
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 640, 480, OF_FULLSCREEN);
    
    //ofSetupOpenGL(ofxFensterManager::get(), 640, 480, OF_WINDOW);
    
    //ofRunFensterApp(new testApp());
	ofRunApp(new testApp());
}

//#include "ofMain.h"
//#include "testApp.h"
//#include "ofxFensterManager.h"
//#include "ofAppGlutWindow.h"
//
////========================================================================
//int main( ){
//	ofSetupOpenGL(ofxFensterManager::get(), 640, 480, OF_WINDOW);			// <-------- setup the GL context
//    
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunFensterApp(new testApp());
//}


