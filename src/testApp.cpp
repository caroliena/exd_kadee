#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    flagBlob = false;
    
    openNIContext.setup();
	depthGenerator.setup(&openNIContext);
    irGenerator.setup(&openNIContext);
    
    blobImage.allocate(640, 480);
    ofSetBackgroundAuto(false);
	ofBackground(0, 0, 0);
    
    nearThreshold = 1500;
	farThreshold  = 2000;
     
}

//--------------------------------------------------------------
void testApp::update(){

    openNIContext.update();
    depthGenerator.update();
    irGenerator.update();
    
    irImage.setFromPixels( irGenerator.ir_pixels , 640, 480);
    irImage.threshold(150);
    
    // demo getting depth pixels directly from depth gen
    depthRangeMask.setFromPixels(depthGenerator.getDepthPixels(nearThreshold, farThreshold),
                                 depthGenerator.getWidth(), depthGenerator.getHeight(), OF_IMAGE_GRAYSCALE);
    
    //_______
    int numPixels = 640 * 480;
    
    unsigned char* blobPixels = blobImage.getPixels();
    unsigned char* irPixels = irImage.getPixels();
    
    
    /*
    for( int i = 0; i < numPixels ; i++ ){
        
        if( irPixels[i] <= 240){
            blobPixels[i] = 0;
        }else{
            blobPixels[i] = 255;
        }
    }
     */
    irImage.setFromPixels((const unsigned char*) irPixels, 640, 480);
    contourFinder.findContours(irImage, 50, numPixels/3, 1, false);
    
    ofLog() << "aantal blobs: " << contourFinder.nBlobs;
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    ofSetColor(255, 255, 255);
    
    //blobImage.draw(640,0,640,480);
    irImage.draw(0, 0, 640, 480);
    
	//depthRangeMask.draw(0, 480, 320, 240);	// can use this with openCV to make masks, find contours etc when not dealing with openNI 'User' like objects
    
    for(int i = 0; i < contourFinder.blobs.size();i++){
        
        contourFinder.blobs[i].draw(0,0);
    }

    
}
