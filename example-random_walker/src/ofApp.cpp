#include "ofApp.h"

void ofApp::setup(){
	// Transition matrix: 4 states (up, right, down, left)
	// each state as the same probability (0.25)

	vector<vector<float> > vals(4, vector<float>(4, 0.25));
	ofxMC::Matrix mat(vals);
	mc.setup(mat, 0);

	// Origin of the random walker at the center of the window
	line.addVertex(ofGetWidth()/2.0, ofGetHeight()/2.0);

	ofBackground(ofColor::white);
}

void ofApp::update(){
	mc.update();
	int s = mc.getState();
	ofPoint prevPoint = line[line.size() - 1];
	switch(s){
		// Go up
		case 0:
			line.lineTo(prevPoint.x, prevPoint.y + 1);
			break;
		// Go right
		case 1:
			line.lineTo(prevPoint.x + 1, prevPoint.y);
			break;
		// Go down
		case 2:
			line.lineTo(prevPoint.x, prevPoint.y - 1);
			break;
		// Go left
		case 3:
			line.lineTo(prevPoint.x - 1, prevPoint.y);
			break;
		default:
			break;
	}
}

void ofApp::draw(){
	ofSetColor(ofColor(0, 0, 0, 60));
	line.draw();
}