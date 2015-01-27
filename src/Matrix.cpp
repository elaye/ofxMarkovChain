#include "Matrix.h"

ofxMC::Matrix::Matrix()
{
}

#if OF_VERSION_MINOR == 8
	ofxMC::Matrix::Matrix(string filename){
		mat.clear();
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
			mat.push_back(row);
		}
		while(!buffer.isLastLine());
		log();
		if(!check()){
			ofLog(OF_LOG_ERROR) << "Bad transition matrix";
		}
	}
#elif OF_VERSION_MINOR > 8
	ofxMC::Matrix::Matrix(string filename){
		mat.clear();
		ofFile file;
		if(!file.open(ofToDataPath(filename))){
			ofLog(OF_LOG_ERROR) << "Cannot open \"" << filename << "\"";
		}
		ofBuffer buffer = file.readToBuffer();
		ofBuffer::Lines lines = buffer.getLines();
		for(ofBuffer::Line line = lines.begin(); line != lines.end(); ++line){
			vector<float> row;
			istringstream ss(*line);
			float val;
			while(ss >> val){
				row.push_back(val);
			}
			mat.push_back(row);
		}
		log();
		if(!check()){
			ofLog(OF_LOG_ERROR) << "Bad transition matrix";
		}
	}
#else
	ofLogError() << "Unsupported OF version";
#endif

ofxMC::Matrix::Matrix(vector<vector<float> > proba):
mat(proba)
{
	check();
}

bool ofxMC::Matrix::check(){
	int nCol = mat[0].size();
	for(int i = 1; i < mat.size(); ++i){
		if(mat[i].size() != nCol){
			ofLog(OF_LOG_ERROR) << "The transition matrix must be a square matrix";
			return false;	
		} 
		float sum = 0.0;
		for(int j = 0; j < mat[i].size(); ++j){
			sum += mat[i][j];
		}
		if(sum != 1.0){
			ofLog(OF_LOG_ERROR) << "The transition matrix must be stochastic\n(the sum of the coefficients in a row must be equal to 1.0)";
			return false;
		}
	}
	if(mat.size() != nCol){
		ofLog(OF_LOG_ERROR) << "The transition matrix must be a square matrix";
		return false;
	}
	else{
		return true;
	}
}

void ofxMC::Matrix::log(){
	stringstream ss;
	ss << "Transition matrix:\n";
	for(int i = 0; i < mat.size(); ++i){
		for(int j = 0; j < mat[i].size(); ++j){
			ss << mat[i][j] << "\t";
		}
		ss << "\n";
	}
	ofLog() << ss.str();
}

vector<float>& ofxMC::Matrix::operator[](int i){
	return mat[i];
}