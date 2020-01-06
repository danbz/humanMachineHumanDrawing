#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    b_drawGui = true;
    iconWidth = 100;
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    
    gui.setup("Settings");
    gui.add(cycle.set("Cycle", 15, 0, 90));
    gui.add(fps.setup("Fps:", ""));
    
    instructionText.init("frabk.ttf", 30);
    instructionText.wrapTextX(ofGetWidth());
    ofBackground(ofColor::white);
    
    reset();
}

//--------------------------------------------------------------
void ofApp::update(){
    //    if(++i > cycle){
    //          addDrawingStep();
    //    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string instructions;
    instructions =+ "Take a piece of paper and a pen and draw ";
    int x = 0;
    int y = (ofGetHeight() /iconWidth) /2.0;
    for(vector<Mark>::iterator m = marks.begin(); m != marks.end(); ++m){
        m->draw( x  * iconWidth, y * iconWidth, iconWidth, iconWidth);
        instructions += m->getMarkType() += " ";
        x++;
        if (x * iconWidth > ofGetWidth()){
            x=0;
            y++;
        }
    }
    
    instructionText.setText(instructions);
    
    if (b_drawGui){
        fps = ofToString(ofGetFrameRate());
        gui.draw();
        markov.draw(gui.getWidth() + 40, 20);
    }
    
    ofSetColor(ofColor::black);
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
            break;
            
        case 'r':
            reset();
            
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
    
    string speaker = "Samantha";
    string content = newMark.getMarkType() ;
    string cmd = "say " + content + " -v " + speaker;
    system(cmd.c_str());
}

//--------------------------------------------------------------


void ofApp::reset(){
    marks.clear();
    string speaker = "Samantha";
    string content = "Take a piece of paper and a pen and draw " ;
    string cmd = "say " + content + " -v " + speaker;
    system(cmd.c_str());
}
