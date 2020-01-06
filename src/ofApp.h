#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMarkovChain.h"
#include "ofxTextSuite.h"

class Mark {
        string markType;
public:
    Mark(int state){
        switch(state){
            case 0:
                markType = "lineup";
                break;
                
            case 1:
                markType = "linedown";
                break;
                
            case 2:
                markType = "lineleft";
                break;
                
            case 3:
                markType = "lineright";
                break;
                
            case 4:
                markType = "arcup";
                break;
                
            case 5:
                markType = "arcdown";
                break;
                
            case 6:
                markType = "arcleft";
                break;
                
            case 7:
                markType = "arcright";
                break;
                
            default:
                break;
        }
    }
    
    string getMarkType(){
        return markType;
    }
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void addDrawingStep();
    
    bool b_drawGui;
    
    ofParameter<int> cycle;
    
    ofxMC::MarkovChain markov;
    
    ofxLabel fps;
    ofxPanel gui;
    
    vector<Mark> marks;
    
    ofxTextBlock instructionText;
    
};
