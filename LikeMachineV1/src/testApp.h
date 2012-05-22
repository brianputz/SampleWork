#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxJSONElement.h"
#include "ofxOpenCv.h"
#include "ofxHttpTypes.h"
#include "ofxHttpEvents.h"
#include "ofxHttpUtils.h"


#define _USE_LIVE_VIDEO	


class testApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		
		
		ofTrueTypeFont  bebas;
		ofTrueTypeFont bebas2;
	ofTrueTypeFont bebas3;
	ofTrueTypeFont bebas4;
	
		ofxJSONElement result;
		ofxJSONElement reddit;
		ofxJSONElement reddit2;
	
	string url;
	
		ofImage thumb;
	ofImage upImg;
	ofImage downImg;
	
#ifdef _USE_LIVE_VIDEO
	ofVideoGrabber 		vidGrabber;
#else
	ofVideoPlayer 		vidPlayer;
#endif
	
	ofxCvColorImage		colorImg;
	
	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	
	ofxCvContourFinder 	contourFinder;
	
	int 				threshold;
	bool				bLearnBakground, blobIsIn, blobIsInToo;
	bool debugView;
	int titleCount;
	int thumbX;
	int thumbY;
	
	ofPoint up;
	ofPoint down;
	
	int upX;
	int downX;
	int upY;
	int downY;
	
	vector<string> titles;
	vector<string> authors;
	vector<int> upVotes;
	vector<int> downVotes;
	
	int upInt;
	int downInt;
	
	float lastTime;
	
	bool reddit_login(const char* username, const char* passwd);
    bool reddit_vote(const char* thing, int vote);
	static int writeData(char *data, size_t size, size_t nmemb, std::string *buffer);

};

#endif	

