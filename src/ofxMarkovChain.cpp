#include "ofxMarkovChain.h"

void MarkovChain::setup(transitionMatrix mat, int _state){
	transMat = mat;
	state = _state;
}

void MarkovChain::load(string filename){
	ofFile file;
	if(!file.open(ofToDataPath(filename))){
		ofLog(OF_LOG_ERROR) << "Cannot open \"" << filename << "\"";
	}
	ofBuffer buffer = file.readToBuffer();
	string line;
	do{
		vector<float> row;
		line = buffer.getNextLine();
		istringstream ss(line);
		float val;
		while(ss >> val){
			row.push_back(val);
		}
		transMat.push_back(row);
	}
	while(!buffer.isLastLine());
	logTransitionMatrix();
	if(!checkTransitionMatrix()){
		ofLog(OF_LOG_ERROR) << "Bad transition matrix";
	}
}

bool MarkovChain::checkTransitionMatrix(){
	int nCol = transMat[0].size();
	for(int i = 1; i < transMat.size(); ++i){
		if(transMat[i].size() != nCol){
			ofLog(OF_LOG_ERROR) << "The transition matrix must be a square matrix";
			return false;	
		} 
		float sum = 0.0;
		for(int j = 0; j < transMat[i].size(); ++j){
			sum += transMat[i][j];
		}
		if(sum != 1.0){
			ofLog(OF_LOG_ERROR) << "The transition matrix must be stochastic\n(the sum of the coefficients in a row must be equal to 1.0)";
			return false;
		}
	}
	if(transMat.size() != nCol){
		ofLog(OF_LOG_ERROR) << "The transition matrix must be a square matrix";
		return false;
	}
	else{
		return true;
	}
}

void MarkovChain::update(){
	float f = ofRandom(1.0);
	float sum = 0.0;
	int new_state = -1;
	vector<float> row = transMat[state];
	if(f < row[0]){
		new_state = 0;
	}
	else{
		for(int i = 0; i < row.size()-1; ++i){
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

int MarkovChain::getState(){
	return state;
}

void MarkovChain::draw(int x, int y){
	for(int i = 0; i < transMat.size(); ++i){
		if(state == i){
			ofSetColor(ofColor(231, 44, 44, 255));
		}
		else{
			ofSetColor(ofColor(44, 231, 44, 255));
		}
		ofCircle(x + 25*i, y, 10);
		ofSetColor(ofColor::black);
		ofDrawBitmapString(ofToString(i), x+25*i-4, y+4);
	}
}

void MarkovChain::logTransitionMatrix(){
	stringstream ss;
	ss << "Transition matrix:\n";
	for(int i = 0; i < transMat.size(); ++i){
		for(int j = 0; j < transMat[i].size(); ++j){
			ss << transMat[i][j] << "\t";
		}
		ss << "\n";
	}
	ofLog() << ss.str();
}