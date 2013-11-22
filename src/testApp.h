#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxOpenNi.h"

#define USE_IR

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        ofxOpenNIContext openNIContext;
        ofxDepthGenerator depthGenerator;
        ofxIRGenerator irGenerator;
        ofImage depthRangeMask, irRangeMask;
    
        ofxCvGrayscaleImage irImage;
    
        int nearThreshold, farThreshold;
 
    private:
        bool flagBlob;
        ofxCvGrayscaleImage blobImage;
        ofxCvContourFinder contourFinder;
	
};

