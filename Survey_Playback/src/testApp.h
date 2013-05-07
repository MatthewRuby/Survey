#pragma once

#include "ofMain.h"

#define NUM_QUESTIONS 6
#define BATCH_LENGTH 15

class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();
	
		void buildVideoList();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

	
		vector <ofVideoPlayer>	movies;
	
		ofDirectory				dir;
	
		string					vidDirectory;
		
		int						currentMovie;
	
};

