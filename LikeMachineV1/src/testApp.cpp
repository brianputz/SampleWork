#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){	 
	
	// this load font loads the non-full character set
	// (ie ASCII 33-128), at size "32"
	ofBackground(0, 0, 0);
	
	bebas.loadFont("BEBAs.TTF", 20);
	bebas.setLineHeight(36);
	bebas2.loadFont("BEBAs.TTF", 40);
	bebas3.loadFont("BEBAs.TTF", 30);
	bebas4.loadFont("BEBAs.TTF", 15);
	upImg.loadImage("images/upVote.png");
	downImg.loadImage("images/downVote.png");
	
	
	titleCount = 0;
	
	thumbX = ofGetWidth()/2+300;
	thumbY = 400;
	
	up.x = ofGetWidth()/2-50;
	up.y = 100;
	
	down.x = ofGetWidth()/2-50; 
	down.y = 445;
	
	upInt = 0;
	downInt = 0;
	
	blobIsIn = false;
	blobIsInToo = false;
	
	lastTime = ofGetElapsedTimef() - 5;
	
	
	
	url = "http://www.reddit.com/r/AskReddit/comments/gxvsm/if_you_could_name_an_art_piece_what_would_you/.json";
	


	
	// Now parse the JSON
	bool parsingSuccessful = result.open(url);
	if ( parsingSuccessful ) {
		
		cout << result.getRawString()<< endl;
		//cout <<	stamp.getRawString()<<endl
	} else {
	
		cout  << "Failed to parse JSON" << endl;
		
		cout << blobIsIn;

	}
	
	for(int i=0; i<result[1]["data"]["children"].size(); i++)
	{
		titles.push_back(  result[1]["data"]["children"][i]["data"]["body"].asString() );
		authors.push_back(  result[1]["data"]["children"][i]["data"]["author"].asString() );
		upVotes.push_back(upInt);
		downVotes.push_back(downInt);
	}
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);
#else
	vidPlayer.loadMovie("fingers.mov");
	vidPlayer.play();
#endif
	
    colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	
	
	bLearnBakground = true;
	threshold = 150;
	debugView = false;

	
}


//--------------------------------------------------------------

bool testApp::reddit_login(const char* username, const char* passwd)
{
	const char* url = "http://www.reddit.com/api/login";
    char* data = new char[255];
	username = "LikeMachine";
	passwd = "g00secock";
    sprintf(data, "user=%s&passwd=%s", username, passwd);
    
	string str = ofxJSONElement::post(url, data);
	
    cout << str << endl;
}
//--------------------------------------------------------------

//bool testApp::reddit_vote(const char* thing, int vote)
//{
//	const char* url = "http://www.reddit.com/api/vote";
//	char* data = new char[255];
//	
//	sprintf(data, "id=%s&dir=%d&vh=f0f0f0f0f&&uh=f0f0f0f0f0f0f0f0f0f0f0", thing, vote);
//}
//--------------------------------------------------------------
void testApp::update(){
	
//	
//	if(ofGetFrameNum() % (24*5) == 0) {

//		
//		
//	}
	
	ofSetFrameRate(24);
	
    bool bNewFrame = false;
	
#ifdef _USE_LIVE_VIDEO
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
#else
	vidPlayer.idleMovie();
	bNewFrame = vidPlayer.isFrameNew();
#endif
	
	if (bNewFrame){
		
#ifdef _USE_LIVE_VIDEO
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
#else
		colorImg.setFromPixels(vidPlayer.getPixels(), 320,240);
#endif
		colorImg.mirror(false, true);
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
			bLearnBakground = false;
		}
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		

		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);	// find holes
		
		
		

		float x_scale = ofGetWidth() / (float)grayDiff.width;
		float y_scale = ofGetHeight() / (float)grayDiff.height;
		
		for(int i=0; i<contourFinder.blobs.size(); i++)
		{
			ofFill();
			//ofSetColor(255, 0, 0);
			
			float x = contourFinder.blobs[i].centroid.x / grayDiff.width * ofGetWidth();
			float y = contourFinder.blobs[i].centroid.y / grayDiff.height * ofGetHeight();
			
			//ofCircle(x, y, 5);
			if(y > up.y && x > up.x && x < up.x + 100 && y < up.y + 100)
			{
				if(ofGetFrameNum()  %48 == 0)
				{
					
					upVotes[titleCount]++;
					titleCount++;
					
				}
				if(titleCount >= titles.size()){
					titleCount=0;	
				}
				
			}
			
			if(x < down.x + 100 && x > down.x && y < down.y + 100 && y > down.y)
			{
				if(ofGetFrameNum()  %48 == 0)
				{
					
					downVotes[titleCount]++;
					titleCount++;
					
				}
				if(titleCount >= titles.size()){
					titleCount=0;	
				}
				
			}
			
		}
 
		

	}
}

//--------------------------------------------------------------
void testApp::draw(){
	

	if (debugView==true) {
		grayImage.draw(ofGetWidth()/2-160,200);

		
		for (int i = 0; i < contourFinder.nBlobs; i++){
			contourFinder.blobs[i].draw(ofGetWidth()/2-160,200);
		}
		
		////////////////////////////////////////////////////////////////
		
		float x_scale = ofGetWidth() / (float)grayDiff.width;
		float y_scale = ofGetHeight() / (float)grayDiff.height;
		

		///////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////
		ofRect(up.x, up.y, 100, 100);
		ofRect(down.x, down.y, 100, 100);
	}
	
	
	//for(int i=0; i<contourFinder.blobs.size(); i++)
//	{
//		ofFill();
//		ofSetColor(255, 0, 0);
//		
//		float x = contourFinder.blobs[i].centroid.x / grayDiff.width * ofGetWidth();
//		float y = contourFinder.blobs[i].centroid.y / grayDiff.height * ofGetHeight();
//		
//		//ofCircle(x, y, 5);
//		if(y > up.y && x > up.x && x < up.x + 100 && y < up.y + 100)
//		{
//			blobIsIn = true;
//			continue;
//		}
//		else
//		{
//			if(blobIsIn==true)
//			{
//				
//				upVotes[titleCount]++;
//				titleCount++;
//				ofSetColor(255, 255, 255);
//				bebas3.drawString("Thank you, your vote has been counted", ofGetWidth()/2-400, ofGetHeight()/2+250);
//				
//				if(titleCount >= titles.size()){
//					titleCount=0;	
//				}
//				
//				
//			
//			}
//			blobIsIn = false;
//
//			
//		}
//
//		
//		if(x < down.x + 100 && x > down.x && y < down.y + 100 && y > down.y)
//		{
//			
//			blobIsInToo = true;
//			continue;
//		}
//			
//			else{
//				
//				if (blobIsInToo == true) {
//					downVotes[titleCount]++;
//					titleCount++;
//					ofSetColor(255, 255, 255);
//					bebas3.drawString("Thank you, your vote has been counted", ofGetWidth()/2-400, ofGetHeight()/2+250);
//					if(titleCount >= titles.size()){
//						titleCount=0;	
//				}
//
//			}
//				blobIsInToo = false;
//		}
		

//	}
 
	ofSetColor(255, 255, 255);
	
	
	bebas2.drawString(titles[titleCount], 10, 90);
	
	bebas.drawString("By " + authors[titleCount], 10, 150);
	bebas.drawString("Ups "+ofToString(upVotes[titleCount]), 1000, 600);
	bebas.drawString("Downs "+ofToString(downVotes[titleCount]), 1000, 650);
	bebas4.drawString("To vote, place a thumbs up or thumbs down in the corresponding hand for 2-3 seconds", 10, 650);
	


	
	ofEnableAlphaBlending();
	ofScale(.5, .5);
	upImg.draw(ofGetWidth()-50, 250);
	downImg.draw(ofGetWidth()-50, 950);
	ofDisableAlphaBlending();
	
	if (debugView==false) {
		ofScale(3.5, 3.5);
		//colorImg.mirror(false, true);
		colorImg.draw(ofGetWidth()/2-420,65);
		
	}
	

	
	ofEnableAlphaBlending();
	ofScale(.35, .35);
	upImg.draw(ofGetWidth()-275, 250);
	downImg.draw(ofGetWidth()-275, 750);
	ofDisableAlphaBlending();
	



	
}


//--------------------------------------------------------------
	void testApp::keyPressed  (int key){ 	switch (key){
			
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
			
	}
		
		if(key=='d')
		{
			debugView = !debugView;
		}
	
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	
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
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
