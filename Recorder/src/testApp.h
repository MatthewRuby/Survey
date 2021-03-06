#ifndef _TEST_APP
#define _TEST_APP

/**
 
 THANK YOU
 
 *  testApp.h
 *
 *	ofxQTKitveVideoGrabber example project
 *
 *  Created by James George ( http://www.jamesgeorge.org ) on 6/15/10.
 *  In collaboration with FlightPhase ( http://www.flightphase.com )
 *
 *  Copyright (c) 2010 
 *
 * Video & Audio sync'd recording + named device id's 
 * added by gameover [matt gingold] (c) 2011 http://gingold.com.au
 * with the support of hydra poesis http://hydrapoesis.net
 *
 */

#include "ofMain.h"
#include "ofxQTKitVideoGrabber.h"
#include "Countdown.h"

#define CAM_WIDTH 640
#define CAM_HEIGHT 480
#define NUM_QUESTIONS 6

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
    
    ofxQTKitVideoGrabber	vidGrabber;	
    int 				camWidth;
    int 				camHeight;
    
    ofTrueTypeFont fontXSm;
    ofTrueTypeFont fontSm;
    ofTrueTypeFont fontLrg;
    
    ofDirectory dir;
    string currentDir;
	
    string vid_id;
    
    string age;
    string questions[NUM_QUESTIONS];
    int q_index;
    
    bool b_SessionStarted;
    bool b_SessionFinished;
    bool b_Idle;
    
    Countdown countdown[NUM_QUESTIONS];
	
};

#endif	
