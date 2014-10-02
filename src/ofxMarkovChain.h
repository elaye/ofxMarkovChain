#pragma once

#include "ofMain.h"

typedef vector<vector<float> > transitionMatrix;

class MarkovChain {

	transitionMatrix transMat;
	int state;

	public:
		void setup(transitionMatrix mat, int state);
		void load(string filename);
		bool checkTransitionMatrix();
		void update();
		void draw(int x, int y);	
		void logTransitionMatrix();
};