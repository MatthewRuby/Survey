#include "testApp.h"

static int batchNum;

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(255,255,255);
	
	buildVideoList();
	
	currentMovie = 0;
	
	batchNum = 0;
	
}

//--------------------------------------------------------------
void testApp::update(){
	
	for (int i = 0; i < movies.size(); i++) {
		if (movies[i].isPlaying()) {
			
			movies[i].idleMovie();
			
		}
	}
	
	if (movies.size() > 0) {
		
		if (movies[currentMovie].isPlaying() == false) {
			movies[currentMovie].play();
		}
		
		
		
		
		if (movies[currentMovie].getIsMovieDone() == true) {
			
			if (currentMovie < movies.size()) {
				
				currentMovie++;
				
			}
			
			if (currentMovie >= movies.size()) {
				
				currentMovie = 0;
				
				buildVideoList();
				
			}
			
		}
		
	}
	
	
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofBackground(0, 0, 0);
    
	ofSetHexColor(0xFFFFFF);
	
	if (movies.size() > 0) {
		
        float x = 1280 / 2;
        float w = 1024 / 2;
		movies[currentMovie].draw(x - w, 0, 1024, 768);
		
	} else {
		
		ofSetColor(0, 0, 0);
		
		ofRect(0, 0, ofGetWidth(), ofGetHeight());
		
	}
	
	ofSetHexColor(0x000000);
	ofDrawBitmapString(ofToString(currentMovie), 10, ofGetHeight() - 10);
	
}

//--------------------------------------------------------------
void testApp::buildVideoList(){
	
	vidDirectory = "../../../Recorder/bin/data/videos/";
	
	dir.listDir(vidDirectory);

	
	int numMoviesCreated = 0;
	
	
	movies.clear();
	
	while (numMoviesCreated < BATCH_LENGTH * NUM_QUESTIONS) {
			
		for (int j = batchNum * BATCH_LENGTH; j < (batchNum * BATCH_LENGTH) + BATCH_LENGTH; j++) {
			
			for (int k = 0; k < NUM_QUESTIONS; k++) {
				
				for (int i = 0; i < dir.size(); i++) {
					
					string tempPath = vidDirectory + dir.getName(i) ;
					
					ofDirectory d;
					d.listDir(tempPath);
					
					if (d.size() == NUM_QUESTIONS) {
						
						string ageA = "";
						ageA += dir.getName(i)[0];
						ageA += dir.getName(i)[1];
						int a = ofToInt(ageA);
						
						if (a == j) {
							
							string path = vidDirectory + dir.getName(i) + "/" + ofToString(k, 0) + ".mov";
							
							cout << path << endl;
							
							ofVideoPlayer v;
							v.loadMovie(path);
							v.setLoopState(OF_LOOP_NONE);
							movies.push_back(v);
							
							numMoviesCreated++;
							
						}
						
					}
					
				}
				
			}
			
		}
		
		batchNum++;
		
		if (batchNum > 100 / BATCH_LENGTH) {
			
			batchNum = 0;
		}
		
	}
	
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){
	
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

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}
