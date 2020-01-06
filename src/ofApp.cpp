#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    b_drawGui = true;
    
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    
    gui.setup("Settings");
    gui.add(cycle.set("Cycle", 15, 0, 90));
    gui.add(fps.setup("Fps:", ""));
    
    instructionText.init("frabk.ttf", 20);
    instructionText.wrapTextX(ofGetWidth());
}

//--------------------------------------------------------------
void ofApp::update(){
//    if(++i > cycle){
//          addDrawingStep();
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(15, 16, 37), ofColor(11, 11, 10));
   
    if (b_drawGui){
        fps = ofToString(ofGetFrameRate());
        gui.draw();
        markov.draw(gui.getWidth() + 40, 20);
    }
    
    ofSetColor(ofColor::white);
    instructionText.wrapTextX(ofGetWidth()-10);
    // instructionText.wrapTextArea(ofGetWidth()-20, ofGetHeight()-20);
    instructionText.draw(10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case ' ':
            addDrawingStep();
            break;
            
        case 'g':
            b_drawGui = !b_drawGui;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::addDrawingStep(){
    // add a new step to list of drawing steps from Markov Chain matrix
    markov.update();
    Mark newMark(markov.getState());
    marks.push_back(newMark);
    
    string instructions;
    instructions =+ "draw a ";
    for(vector<Mark>::iterator b = marks.begin(); b != marks.end(); ++b){
        // b->draw();
        instructions += b->getMarkType() += " ";
    }
    
    instructionText.setText(instructions);
}
