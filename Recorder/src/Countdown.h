/*
 *  Countdown.h
 *  survey_0.1
 *
 *  Created by Matt Ruby on 1/29/12.
 *  Copyright 2012. All rights reserved.
 *
 */
#ifndef _Countdown
#define _Countdown


#include "ofMain.h"


class Countdown {
	
	public:
		
		Countdown();

		void setTime(float t);
		void startTimer();
		void resetTimer();
	
		void update();
		void draw(float x, float y, float w);

		ofTrueTypeFont *	fontSm;
		ofTrueTypeFont *	fontLrg;
	
		float time;
		float timerAmount;
		double startTime;
		float preTimer;
	
		bool bStart;
		bool bPre;
		bool bRunning;
		bool bFinished;
	
};

#endif
