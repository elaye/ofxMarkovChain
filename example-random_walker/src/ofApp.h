#pragma once

#include "ofMain.h"

#include "ofxMarkovChain.h"

class ofApp : public ofBaseApp{

	ofxMC::MarkovChain mc;
	ofPolyline line;
	float w;

	public:
		void setup();
		void update();
		void draw();
};
