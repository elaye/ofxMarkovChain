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
		int getState();
		int getStatesNumber();
		void setProbabilities(int i, vector<float> row);
		void draw(int x, int y);	
		void logTransitionMatrix();
};