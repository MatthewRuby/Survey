/*
 *  Countdown.cpp
 *  survey_0.1
 *
 *  Created by Matt Ruby on 1/29/12.
 *  Copyright 2012. All rights reserved.
 *
 */

#include "Countdown.h"


//------------------------------------------------------------------
Countdown::Countdown() {
	
	time = 0;
	timerAmount = 0;
	startTime = 0;
	preTimer = 3.0;
	
	bStart = false;
	bPre = false;
	bRunning = false;
	bFinished = false;
	
	preTimer = 3.0;
	
}

//------------------------------------------------------------------
void Countdown::setTime(float t) {
	timerAmount = t;
}

//------------------------------------------------------------------
void Countdown::startTimer() {
	
	if (bStart == false) {
		bStart = true;
		startTime = ofGetElapsedTimef() + preTimer;
	}
	
}

//------------------------------------------------------------------
void Countdown::resetTimer() {

	time = 0;
	startTime = 0;
	preTimer = 3.0;
	
	bStart = false;
	bPre = false;
	bRunning = false;
	bFinished = false;
	
}

//------------------------------------------------------------------
void Countdown::update() {
	
	if (bStart) {
		
		if (startTime > ofGetElapsedTimef() && preTimer > 0) {
			
			bPre = true;
			
			preTimer = (startTime - ofGetElapsedTimef());
			
		} else if (startTime + timerAmount > ofGetElapsedTimef() && startTime < ofGetElapsedTimef()) {
			
			bPre = false;
			bRunning = true;

			time = timerAmount - (ofGetElapsedTimef() - startTime);

		} else {
			
			bRunning = false;
			
		}
		
		if (startTime + timerAmount < ofGetElapsedTimef()) {
			bFinished = true;
		}


	}
	
	
}

//------------------------------------------------------------------
void Countdown::draw(float x, float y, float w) {
	
	ofNoFill();
	ofSetColor(255, 255, 255);
	ofRect(x - (w / 2 - 5), y, w - 10, 50);
	
	if(bRunning){
		
		ofFill();
		ofSetColor(255, 0, 0, 100);
		ofSetLineWidth(2);
		float bar = ofMap(timerAmount - time, 0, timerAmount, 0, w - 20);
		ofRect(x - (w / 2 - 10), y + 5, bar, 40);
		
	}
	
	
	ofSetColor(255, 0, 0);
/*	
	if (bRunning) {
		string drawTime = ofToString(time, 0);
		ofRectangle bounds = fontSm->getStringBoundingBox(drawTime, 0, 0);
		fontSm->drawString(drawTime, (x + w/2) - (bounds.width + 50), y - 20);
	}
*/	
	if (bPre) {
		
		ofSetColor(255, 255, 255);
		
		string pTime = ofToString(preTimer,0);
		ofRectangle bounds = fontLrg->getStringBoundingBox(pTime, 0, 0);
		fontLrg->drawString(pTime, x - bounds.width/2, y + 360);
		
	}

	
}

