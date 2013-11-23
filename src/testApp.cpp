#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    prevBlob = 0;
    rotations = 0;
    prevSeconden = 0;
    
    openNIContext.setup();
	depthGenerator.setup(&openNIContext);
    irGenerator.setup(&openNIContext);
    
    blobImage.allocate(640, 480);
    ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);
    
    threshold = 100;
    nearThreshold = 2000;
	farThreshold  = 2250;
     
}

//--------------------------------------------------------------
void testApp::update(){

    openNIContext.update();
    depthGenerator.update();
    irGenerator.update();
    
    irImage.setFromPixels( irGenerator.ir_pixels , 640, 480);
    irImage.threshold(threshold);
    
    // demo getting depth pixels directly from depth gen
    // depthRangeMask.setFromPixels(depthGenerator.getDepthPixels(nearThreshold, farThreshold),
                                 //depthGenerator.getWidth(), depthGenerator.getHeight(), OF_IMAGE_GRAYSCALE);
    
    //_______
    int numPixels = 640 * 480;
    
    unsigned char* blobPixels = blobImage.getPixels();
    unsigned char* irPixels = irImage.getPixels();
    
    irImage.setFromPixels((const unsigned char*) irPixels, 640, 480);
    contourFinder.findContours(irImage, 100, numPixels/3, 1, false);
    
    // om te zien of er geroteerd wordt
    if( prevBlob != contourFinder.nBlobs ){
        rotations++;
        prevBlob = contourFinder.nBlobs;
        prevSeconden = ofGetElapsedTimeMillis();
    }
    
    // Zien of dat de hoepel ni gevallen is
    if( ( ofGetElapsedTimeMillis() - prevSeconden ) >= 3000 ){
        ofLog() << "hoepel gevallen";
    }
    
    ofLog() << "aantal blobs: " << contourFinder.nBlobs;
    ofLog() << "aantal rotaties: " << rotations;
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 255, 255);
    irImage.draw(0, 0, 640, 480);
    
    //depthRangeMask.draw(0, 0, 640, 480);
    
    for(int i = 0; i < contourFinder.blobs.size();i++){
        contourFinder.blobs[i].draw(0,0);
    }

    ofSetColor(255, 255, 255);
	stringstream reportStream;
    reportStream.str(std::string());
    reportStream << "num blobs found " << contourFinder.nBlobs<< endl;
    ofDrawBitmapString(reportStream.str(), 20, 652);
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == OF_KEY_UP) {
		irImage.threshold(++threshold);
		
	} else if(key == OF_KEY_DOWN) {
		irImage.threshold(--threshold);
	}
}
