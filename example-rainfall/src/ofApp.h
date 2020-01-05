#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "ofxMarkovChain.h"

class Ball {

	ofPoint p;
	float radius;
	ofColor c;

	public:
		Ball(int k){
			switch(k){
				case 1:
					c = ofColor(225, 20, 10, 200);
					break;
				case 2:
					c = ofColor(10, 225, 20, 200);
					break;
				case 3:
					c = ofColor(20, 10, 225, 200);
					break;
				default:
					break;
			}
			radius = ofRandom(10, 50);
			p.x = ofRandomWidth();
			p.y = 0;
		}
		void update(){
			p.y += 10;
		}
		void draw(){
			ofSetColor(c);
			ofDrawCircle(p, radius);
		}
		bool isAlive(){
			return (p.y - radius) < ofGetHeight();
		}	
};

class ofApp : public ofBaseApp{

	int i;
	ofParameter<int> cycle;

	ofxMC::MarkovChain markov;

	ofxLabel fps;
	ofxPanel gui;

	vector<Ball> balls;

	public:
		void setup();
		void update();
		void draw();
		
};
