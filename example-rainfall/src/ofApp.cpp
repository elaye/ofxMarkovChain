#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(false);
	ofSetFrameRate(60);

	i = 0;

	ofxMC::Matrix mat("transitionMatrix.txt");
	markov.setup(mat, 0);

	gui.setup("Settings");
	gui.add(cycle.set("Cycle", 15, 0, 90));
	gui.add(fps.setup("Fps:", ""));

}

//--------------------------------------------------------------
void ofApp::update(){
	if(++i > cycle){
		markov.update();
		if(markov.getState() != 0){
			Ball b(markov.getState());
			balls.push_back(b);
		}
		i = 0;
	}

	for(vector<Ball>::iterator b = balls.begin(); b != balls.end(); ++b){
		b->update();
		if(!b->isAlive()){
			balls.erase(b);
			--b;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(15, 16, 37), ofColor(11, 11, 10));

	for(vector<Ball>::iterator b = balls.begin(); b != balls.end(); ++b){
		b->draw();
	}

	if(i == 0){
		ofSetColor(ofColor::red);
		ofRect(gui.getWidth()+15, 15, 10, 10);	
	}
	fps = ofToString(ofGetFrameRate());
	gui.draw();

	markov.draw(gui.getWidth() + 40, 20);

	ofSetColor(ofColor::white);
	ofDrawBitmapString("You can change the \ntransition matrix in \n'data/transitionMatrix.txt'", 10, gui.getHeight() + 30);
}
