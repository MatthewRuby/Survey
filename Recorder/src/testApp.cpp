/**
 *  testApp.cpp
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
 *	This code is distributed under an MIT license you can use it
 *	for whatever you'd like, if you make improvements consider sharing
 *	them back
 */

#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofEnableSmoothing();
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
    
	
	camWidth = CAM_WIDTH;	// try to grab at this size. 
	camHeight = CAM_HEIGHT;
	
    //	ofSetLogLevel(OF_LOG_VERBOSE);
	
    //	vidGrabber.listVideoDevices();
    //	vidGrabber.listAudioDevices();
	vidGrabber.setVideoDeviceID("Logitech Camera");
	vidGrabber.setAudioDeviceID(1);
	vidGrabber.setVideoCodec("QTCompressionOptions240SizeH264Video");
	vidGrabber.setAudioCodec("QTCompressionOptionsVoiceQualityAACAudio");
	
	vidGrabber.setUseAudio(true);
	vidGrabber.initGrabber(camWidth, camHeight);
	vidGrabber.initRecording();
	
	
    //	vidGrabber.setDesiredFrameRate(30);
	
	ofTrueTypeFont::setGlobalDpi(72);
	fontXSm.loadFont("DIN.otf", 36);
	fontSm.loadFont("DIN.otf", 48);
	fontLrg.loadFont("DIN.otf", 120);
	
	
	questions[0] = "How Old Are You?";
    questions[1] = "What Do You Do?";
    questions[2] = "Do You Own A House?";
	questions[3] = "Are You Married?";
    questions[4] = "Do You Have Children?";
    questions[5] = "Are You Happy?";
	q_index = 0;
	
	age = "";
	
	b_SessionStarted = false;
	b_SessionFinished = false;
	b_Idle = true;
	
	
	for (int i = 0; i < NUM_QUESTIONS; i++) {
		countdown[i].setTime(5.0);
		countdown[i].fontSm = &fontSm;
		countdown[i].fontLrg = &fontLrg;
	}
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	vidGrabber.update();
	
	if (b_SessionStarted && b_SessionFinished == false) {
		
		countdown[q_index].update();
		
		if (countdown[q_index].bFinished) {
			
			q_index++;
			
			if (q_index < NUM_QUESTIONS) {
				
				countdown[q_index].startTimer();
				
			}
			
			if (q_index >= NUM_QUESTIONS) {
				
				q_index = 0;
				b_SessionStarted = false;
				b_SessionFinished = true;
				b_Idle = true;
				
				age = "";
				
				for (int i = 0; i < NUM_QUESTIONS; i++) {
					countdown[i].resetTimer();
				}
				
			}
            
		}
		
	}
    
	
	if (countdown[q_index].bRunning) {
		
		if (!vidGrabber.isRecording()) {
			vidGrabber.startRecording("videos/" + ofToString(vid_id) + "/" + ofToString(q_index) + ".mov"); // dumps to data folder
		}
		
	} else {
		
		vidGrabber.stopRecording();
		
	}
    
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(0, 0, 0);
    
	
	ofSetColor(255,255,255);
//	float x = (ofGetWidth() / 2) - (768 / 2);
    
//	vidGrabber.draw(x, 0, 768, 576);
    
    
    float x = (ofGetWidth() / 2) - (1024 / 2);
    
    vidGrabber.draw(x, 200, 1024, 768);
    
	
	ofSetColor(240,50,50);
    
	if (b_Idle == true) {

        ofPushMatrix();
        ofTranslate(-7, 175);
        
		fontXSm.drawString("You are about to be asked", 20, 75);
        fontXSm.drawString("a series of questions.", 20, 125);
		
		for (int i = 0; i < NUM_QUESTIONS; i++) {
			
			fontXSm.drawString(" - " + questions[i], 20, 175 + (i * 50));
			
		}
		
		fontXSm.drawString("The questions will be asked automatically", 20, 175 + (NUM_QUESTIONS * 50));
		fontXSm.drawString("the answers will be recorded, stored in a", 20, 175 + (NUM_QUESTIONS * 50) + 50);
		fontXSm.drawString("database and played back in this installation.",20, 175 + (NUM_QUESTIONS * 50) + 100);
        
        fontSm.drawString("Please Look into the camera", 20, 175 + (NUM_QUESTIONS * 50) + 175);
        fontSm.drawString("and state your answer clearly.", 20, 175 + (NUM_QUESTIONS * 50) + 225);
		
		fontSm.drawString("Press Enter to Continue.", 20, 200 + (NUM_QUESTIONS * 50) + 275);
		
        ofPopMatrix();
        
	} else {
		
		if (b_SessionStarted == false) {
			
			ofRectangle bounds = fontSm.getStringBoundingBox("Please enter your age? " + age, 0, 0);
			fontSm.drawString("Please enter your age? " + age, ofGetWidth()/2 - bounds.width/2, 400);
			
		} else {
			
			ofRectangle bounds = fontSm.getStringBoundingBox(questions[q_index], 0, 0);
			fontSm.drawString(questions[q_index], ofGetWidth()/2 - bounds.width/2, 175);
            
            countdown[q_index].draw(ofGetWidth() / 2, 50, 600);

		}
		
	}
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	// numeric pad key = 3
    
	
	if (!b_SessionStarted && b_Idle == false) {
		
		if (key != OF_KEY_RETURN || key != 3){
            
            if(age.size() <= 1 && key >= 48 && key <= 57) {
                
                age += key;
                
            }
            
		}
		
        if(!b_SessionStarted) {
            
            if (key == OF_KEY_RETURN || key == 3){
                
                vid_id = "";
                vid_id += age + "_" + ofGetTimestampString("%Y%m%d%H%M%S");
                
                dir.open("videos/" + vid_id);
                dir.create();
                
                b_SessionStarted = true;
                b_SessionFinished = false;
                
                countdown[0].startTimer();
                
            }
			
		}
		
	}
	
	
	if (key == OF_KEY_RETURN || key == 3) {
		
        if (b_Idle == true) {
            
            b_Idle = false;
            
        }
		
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
