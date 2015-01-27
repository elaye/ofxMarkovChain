#pragma once

#include "ofMain.h"

namespace ofxMC {

	class Matrix {

		vector<vector<float> > mat;

		public:
			Matrix();
			Matrix(string filename);
			Matrix(vector<vector<float> > mat);
			bool check();
			void log();
			vector<float>& operator[](int i);

			uint size(){ return mat.size(); }	
	};

}