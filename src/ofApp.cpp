#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(false);
    ofSetFrameRate(60);
    b_drawGui = true;
    b_autoSteps= false;
    iconWidth = 150;
    gutter = 20;
    i = 0;
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    
    gui.setup("Settings");
    gui.add(speed.set("Speed (ms)", 4000, 0, 10000));
    gui.add(b_autoSteps.set("autoSteps",false));
    // gui.add(fps.setup("Fps:", ""));
    
    instructionText.init("frabk.ttf", 30);
    instructionText.wrapTextX(ofGetWidth());
    ofBackground(ofColor::white);
    ofSetColor(ofColor::black);
    
    // random list of conjunction phrases to include between drawing instructions, add empty quotes "" to decrease occurrence of phrases
    conjunctions ={"then ", "then draw ", "and ", "follow with ", "followed by ", "add ", "adding ", "then add ", "continue with ", "next ", "next draw ", "", "", "", "", "",  "", "", "" };
    reset();
}

//--------------------------------------------------------------
void ofApp::update(){
    if (b_autoSteps){
        // add draw steps automatically at speed determined by gui speed slider value
        if(ofGetSystemTimeMillis() > now + speed){
            addDrawingStep();
            now = ofGetSystemTimeMillis();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int x = 0;
    int y = (ofGetHeight() /iconWidth) /2.0;
    for(vector<Mark>::iterator m = marks.begin(); m != marks.end(); ++m){
        m->draw( x  * (iconWidth + gutter), y * (iconWidth + gutter), iconWidth, iconWidth);
        x++;
        if (x * (iconWidth + gutter) > ofGetWidth()){
            x=0;
            y++;
            if (y * (iconWidth + gutter) > ofGetHeight() - iconWidth){
                if (b_autoSteps){
                    b_autoSteps = false; // if we have filled half the screen height with drawing icons then stop autoadding steps
                    string speaker = "Oliver";
                    string content = "and stop there" ;
                    string cmd = "say " + content + " -v " + speaker;
                    system(cmd.c_str());
                    instructions += "and stop there";
                    instructionText.setText(instructions);
                }
            }
        }
    }
    
    if (b_drawGui){
        // fps = ofToString(ofGetFrameRate());
        gui.draw();
        markov.draw(gui.getWidth() + 40, 20);
    }
    
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
            break;
            
        case 'a':
            b_autoSteps = !b_autoSteps;
            break;
            
        case 'p':
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::addDrawingStep(){
    // add a new step to list of drawing steps from Markov Chain matrix
    string newConjunction;
    
    markov.update();
    Mark newMark(markov.getState());
    marks.push_back(newMark);
    
    //for(vector<Mark>::iterator m = marks.begin(); m != marks.end(); ++m){
    if (marks.size() > 1) newConjunction =conjunctions[ofRandom(conjunctions.size())];
    instructions += newConjunction;
    instructions += newMark.getMarkType() += " ";
    // }
    instructionText.setText(instructions);
    
    string speaker = "Oliver";
    string content = newConjunction + newMark.getMarkType() ;
    string cmd = "say " + content + " -v " + speaker;
    system(cmd.c_str());
}

//--------------------------------------------------------------
void ofApp::reset(){
    marks.clear();
    string speaker = "Oliver";
    string content = "Take a piece of paper and a pen and draw " ;
    string cmd = "say " + content + " -v " + speaker;
    system(cmd.c_str());
    instructions = "";
    instructions = "Take a piece of paper and a pen and draw\n";
    instructionText.setText(instructions);
    
}
