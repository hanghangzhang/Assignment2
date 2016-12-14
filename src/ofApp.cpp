#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetWindowTitle("Noise 1D Example");
    ofBackground(215,215,215);
    ofSetVerticalSync(true);
    ofSetCircleResolution(256);
    
    setupSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::setupSignedNoiseDemo(){
    // Setup and allocate resources used in the signed noise demo.
    
    nSignedNoiseData = 400; // we'll store a history of 400 numbers
    signedNoiseData = new float[nSignedNoiseData];
    for (int i=0; i<nSignedNoiseData; i++){
        signedNoiseData[i] = 0;
    }
    
    // Some coordinates...
    radialNoiseDemoY = 200;
    radialNoiseDemoR0 = 50;
    radialNoiseDemoR = 100;
    radialNoiseDemoR1 = 150;
    radialNoiseDemoR2 = 200;
    radialNoiseDemoR3 = 250;
    radialNoiseDemoR4 = 300;
    radialNoiseDemoR5 = 350;
    radialNoiseDemoR6 = 350;
    radialNoiseDemoR7 = 400;
    radialNoiseDemoR8 = 450;
    
    radialNoiseDemoX = ofGetWidth()/2 - radialNoiseDemoR;
    
    // These 2 sliders control the noise waveform at the top.
    radialNoiseStepSlider.setup(ofGetWidth()/2 + 250,   radialNoiseDemoY+520, 200,16, 0.010, 0.150, 0.05, false,true);
    radialNoiseAmountSlider.setup(ofGetWidth()/2 + 250, radialNoiseDemoY+540, 200,16, 0.000, 1.000, 0.40, false,true);
    
    radialNoiseStepSlider.setLabelString(  "Noise Step");
    radialNoiseAmountSlider.setLabelString("Noise Amount");
    radialNoiseStepSlider.setNumberDisplayPrecision(3);
    radialNoiseCursor = 0.0;
}

//--------------------------------------------------------------
void ofApp::update(){
    updateSignedNoiseDemo();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient( ofColor(0), ofColor(10), OF_GRADIENT_CIRCULAR);
    renderSignedNoiseDemo();
    renderNoisyRobotArmDemo();
}



//--------------------------------------------------------------
void ofApp::updateSignedNoiseDemo (){
    
    // Shift all of the old data forward through the array
    for (int i=(nSignedNoiseData-1); i>0; i--){
        signedNoiseData[i] = signedNoiseData[i-1];
    }
    
    // Compute the latest data, and insert it at the head of the array.
    // Here is where ofSignedNoise is requested.
    float noiseStep    = radialNoiseStepSlider.getValue();
    float noiseAmount  = radialNoiseAmountSlider.getValue();
    
    signedNoiseData[0] = noiseAmount * ofSignedNoise( radialNoiseCursor );
    radialNoiseCursor += noiseStep;
}


//--------------------------------------------------------------
void ofApp::renderNoisyRobotArmDemo(){
   }


//--------------------------------------------------------------
void ofApp::drawNoisyArmRect (float w, float h){
    }



//--------------------------------------------------------------
void ofApp::renderSignedNoiseDemo(){
    
        float signedNoiseTextX = radialNoiseDemoX - radialNoiseDemoR;
    float signedNoiseTextY = radialNoiseDemoY + radialNoiseDemoR * 2.0 + 16;
    renderRadialSignedNoiseDemo();
    renderLinearSignedNoiseDemo();
}



//--------------------------------------------------------------
void ofApp::renderRadialSignedNoiseDemo (){
    
    float centerX = radialNoiseDemoX;
    float centerY = radialNoiseDemoY;
    ofSetLineWidth(1);
 
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofNoFill();
    
    // Draw a faint plain circle, so that we can better understand
    // the radial displacements caused by the signed noise later on.
    ofSetColor(255,0,255, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR0*2,radialNoiseDemoR0*2);

    
    
    ofSetColor(255,0,0, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR*2,radialNoiseDemoR*2);
    
    
    ofSetColor(0,255,0, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR1*2,radialNoiseDemoR1*2);
    
    
    ofSetColor(0,0,255, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR2*2,radialNoiseDemoR2*2);
    
    ofSetColor(0,255,255, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR3*2,radialNoiseDemoR3*2);
    
    ofSetColor(255,255,0, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR4*2,radialNoiseDemoR4*2);
    
    ofSetColor(255,0,255, 64);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR5*2,radialNoiseDemoR5*2);
    
    ofSetColor(100,0,0, 160);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR6*2,radialNoiseDemoR6*2);
    
    ofSetColor(0,0,200, 160);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR7*2,radialNoiseDemoR7*2);

    
    
    ofSetColor(0,180,0, 160);
    ofSetCircleResolution(256);
    ofDrawEllipse(0,0, radialNoiseDemoR8*2,radialNoiseDemoR8*2);

    

    // Let's use the signed noise as a radial displacement to a circle.
    // We render out the points stored in the X and Y arrays.
    ofMesh wigglyMeshLine; // yes, technically, it's a "mesh"
    wigglyMeshLine.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px = 0, py = 0;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,-TWO_PI) - HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine.addColor(ofFloatColor(255,0,0, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius = radialNoiseDemoR;
        wigglyRadius +=  radialNoiseDemoR * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px = wigglyRadius * cos( angle );
        py = wigglyRadius * sin( angle );
        wigglyMeshLine.addVertex(ofVec2f(px,py));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(255,0,0, 160);
    ofDrawEllipse(px,py, 7,7);
   //----------------------------------------------------------------------
    
    ofMesh wigglyMeshLine1; // yes, technically, it's a "mesh"
    wigglyMeshLine1.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px1 = ofGetWidth(), py1 = 0;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,+TWO_PI) + HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine1.addColor(ofFloatColor(0,255,0, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius1 = radialNoiseDemoR1;
        wigglyRadius1 +=  radialNoiseDemoR1 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px1 = wigglyRadius1 * cos( angle );
        py1 = wigglyRadius1 * sin( angle );
        wigglyMeshLine1.addVertex(ofVec2f(px1,py1));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine1.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(0,255,0, 160);
    ofDrawEllipse(px1,py1, 7,7);
    
//    -----------------------------------------------------------------------------------------------
    
    ofMesh wigglyMeshLine2; // yes, technically, it's a "mesh"
    wigglyMeshLine2.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px2 = ofGetWidth(), py2 = 50;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,-TWO_PI) - HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine2.addColor(ofFloatColor(0,0,255, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius2 = radialNoiseDemoR2;
        wigglyRadius2 +=  radialNoiseDemoR2 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px2 = wigglyRadius2 * cos( angle );
        py2 = wigglyRadius2 * sin( angle );
        wigglyMeshLine2.addVertex(ofVec2f(px2,py2));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine2.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(0,0,255, 160);
    ofDrawEllipse(px2,py2, 7,7);

//-------------------------------------------------------------------------------------------------
    
    ofMesh wigglyMeshLine3; // yes, technically, it's a "mesh"
    wigglyMeshLine3.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px3 = ofGetWidth(), py3 = 100;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,+TWO_PI) + HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine3.addColor(ofFloatColor(0,255,255, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius3 = radialNoiseDemoR3;
        wigglyRadius3 +=  radialNoiseDemoR3 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px3 = wigglyRadius3 * cos( angle );
        py3 = wigglyRadius3 * sin( angle );
        wigglyMeshLine3.addVertex(ofVec2f(px3,py3));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine3.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(0,255,255, 160);
    ofDrawEllipse(px3,py3, 7,7);
//-------------------------------------------------------------------------------------------------------------
    ofMesh wigglyMeshLine4; // yes, technically, it's a "mesh"
    wigglyMeshLine4.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px4 = ofGetWidth(), py4 = 150;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,-TWO_PI) - HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine4.addColor(ofFloatColor(255,255,0, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius4 = radialNoiseDemoR4;
        wigglyRadius4 +=  radialNoiseDemoR4 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px4 = wigglyRadius4 * cos( angle );
        py4 = wigglyRadius4 * sin( angle );
        wigglyMeshLine4.addVertex(ofVec2f(px4,py4));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine4.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(255,255,0, 160);
    ofDrawEllipse(px4,py4, 7,7);
//--------------------------------------------------------------------------------------------------------
    ofMesh wigglyMeshLine5; // yes, technically, it's a "mesh"
    wigglyMeshLine5.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px5 = ofGetWidth(), py5 = 200;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,+TWO_PI) + HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine5.addColor(ofFloatColor(255,0,255, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius5 = radialNoiseDemoR5;
        wigglyRadius5 +=  radialNoiseDemoR5 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px5 = wigglyRadius5 * cos( angle );
        py5 = wigglyRadius5 * sin( angle );
        wigglyMeshLine5.addVertex(ofVec2f(px5,py5));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine5.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(255,0,255, 160);
    ofDrawEllipse(px5,py5, 7,7);
//    -----------------------------------------------------------------------------------------
    ofMesh wigglyMeshLine0; // yes, technically, it's a "mesh"
    wigglyMeshLine0.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px0 = ofGetWidth(), py0 = 0;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,+TWO_PI) + HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine0.addColor(ofFloatColor(255,0,255, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius0 = radialNoiseDemoR0;
        wigglyRadius0 +=  radialNoiseDemoR0 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px0 = wigglyRadius0 * cos( angle );
        py0 = wigglyRadius0 * sin( angle );
        wigglyMeshLine0.addVertex(ofVec2f(px0,py0));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine0.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(150,0,255, 160);
    ofDrawEllipse(px0,py0, 7,7);
//    ------------------------------------------------------------------------------------------------
    ofMesh wigglyMeshLine6; // yes, technically, it's a "mesh"
    wigglyMeshLine6.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px6 = ofGetWidth(), py6 = 250;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,+TWO_PI) + HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine6.addColor(ofFloatColor(100,0,0, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius6 = radialNoiseDemoR6;
        wigglyRadius6 +=  radialNoiseDemoR6 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px6 = wigglyRadius6 * cos( angle );
        py6 = wigglyRadius6 * sin( angle );
        wigglyMeshLine6.addVertex(ofVec2f(px6,py6));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine6.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(100,0,0, 160);
    ofDrawEllipse(px6,py6, 7,7);
    
// -----------------------------------------------------------------------------
    
    
    ofMesh wigglyMeshLine7; // yes, technically, it's a "mesh"
    wigglyMeshLine7.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px7 = ofGetWidth(), py7 = 300;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,- TWO_PI) - HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine7.addColor(ofFloatColor(0,0,200, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius7 = radialNoiseDemoR7;
        wigglyRadius7 +=  radialNoiseDemoR7 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px7 = wigglyRadius7 * cos( angle );
        py7 = wigglyRadius7 * sin( angle );
        wigglyMeshLine7.addVertex(ofVec2f(px7,py7));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine7.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(0,0,200, 160);
    ofDrawEllipse(px7,py7, 7,7);
    
    
//    -----------------------------------------------------------------------------------------------------
    ofMesh wigglyMeshLine8; // yes, technically, it's a "mesh"
    wigglyMeshLine8.setMode(OF_PRIMITIVE_LINE_STRIP);
    float px8 = ofGetWidth(), py8 = 300;
    for (int i=(nSignedNoiseData-1); i>=0; i--){
        
        // From the 'i' iterator, use ofMap to compute both
        // an angle (around a circle) and an alpha value.
        float angle   = ofMap(i, 0,nSignedNoiseData-1, 0,- TWO_PI) - HALF_PI;
        float alph    = ofMap(i, 0,nSignedNoiseData-1, 1,0);
        wigglyMeshLine8.addColor(ofFloatColor(0,180,0, alph));
        
        // Cpmpute the displaced radius
        float wigglyRadius8 = radialNoiseDemoR8;
        wigglyRadius8 +=  radialNoiseDemoR8 * signedNoiseData[i];
        
        // Good old-fashioned trigonometry: y = cos(t), x = sin(t)
        px8 = wigglyRadius8 * cos( angle );
        py8 = wigglyRadius8 * sin( angle );
        wigglyMeshLine8.addVertex(ofVec2f(px8,py8));
    }
    
    // draw the "mesh" (line)
    ofEnableSmoothing();
    wigglyMeshLine8.draw();
    
    // draw a little ball at the end
    ofFill();
    ofSetColor(0,180,0, 160);
    ofDrawEllipse(px8,py8, 7,7);
    




    ofPopMatrix();
    
    
    
}

//--------------------------------------------------------------
void ofApp::renderLinearSignedNoiseDemo(){
    
    
}

// In case you're wondering, the simpleSliders get their mouse info through event handlers.
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
