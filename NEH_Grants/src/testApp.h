#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "particle.h"



class grant {
    
public: 
    int zipCode;
    int year;
    int origAmount;

    

};


class testApp : public ofSimpleApp{
	
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
    
    bool loaded;
    

    ofxXmlSettings grantsData;
    vector <particle> particles;
   ofTrueTypeFont  bebas;

    
    int zipCode;
    int year;
    float origAmount;
    
    int blahZip;
    int blahYear;
    float blahAmount;
    
    float radRepulse;
    
    //string ballTotal;
    
    //vector <int> zipCodes;
    //vector <int> years;
    //vector <float> origAmounts;
	
	vector < grant > grants;
    
    
    map < int , vector < grant > > grantMap;
    //map < int , vector < grant > > grantMap2;
    
    //grantMap[90210]. 
    
    
    
};

#endif

