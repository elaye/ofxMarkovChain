#pragma once

#include "ofMain.h"

#include "Matrix.h"

namespace ofxMC {
	class MarkovChain {

		ofxMC::Matrix transMat;
		int state;

		public:
			void setup(ofxMC::Matrix mat, int state);
			void update();
			int getState();
			int getStatesNumber();
			ofxMC::Matrix getTransitionMatrix();
			void setStateProbabilities(int i, vector<float> row);
			void draw(int x, int y);
	};
}