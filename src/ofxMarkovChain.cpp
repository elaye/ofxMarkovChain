#include "ofxMarkovChain.h"

void ofxMC::MarkovChain::setup(ofxMC::Matrix mat, int _state){
	transMat = mat;
	state = _state;
}

void ofxMC::MarkovChain::update(){
	float f = ofRandom(1.0);
	float sum = 0.0;
	int new_state = -1;
	vector<float> row = transMat[state];
	if(f < row[0]){
		new_state = 0;
	}
	else{
		for(uint i = 0; i < row.size()-1; ++i){
			sum += row[i];
			if(f > sum && f < sum+row[i+1]){
				new_state = i+1;
			}
		}		
	}
	if(new_state == -1){
		new_state = row.size()-1;
	}
	state = new_state;
}

ofxMC::Matrix ofxMC::MarkovChain::getTransitionMatrix(){
	return transMat;
}

int ofxMC::MarkovChain::getState(){
	return state;
}

int ofxMC::MarkovChain::getStatesNumber(){
	return transMat.size();
}

void ofxMC::MarkovChain::setStateProbabilities(int i, vector<float> row){
	if(row.size() != transMat[i].size()){
		ofLog(OF_LOG_ERROR) << "Bad size for state transition probabilites assignment";
		return;
	}
	transMat[i] = row;
	transMat.check();
}

void ofxMC::MarkovChain::draw(int x, int y){
	for(int i = 0; i < (int) transMat.size(); ++i){
		if(state == i){
			ofSetColor(ofColor(231, 44, 44, 255));
		}
		else{
			ofSetColor(ofColor(44, 231, 44, 255));
		}
		ofDrawCircle(x + 25*i, y, 10);
		ofSetColor(ofColor::black);
		ofDrawBitmapString(ofToString(i), x+25*i-4, y+4);
	}
}
