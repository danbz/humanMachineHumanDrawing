#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMarkovChain.h"


class Mark {

    ofPoint p;
    float radius;
    ofColor c;
    string markType;
    public:
        Mark(int k){
            switch(k){
                case 1:
                    c = ofColor(225, 20, 10, 200);
                    markType = "lineup";
                    break;
                case 2:
                    c = ofColor(10, 225, 20, 200);
                    markType = "linedown";

                    break;
                case 3:
                    c = ofColor(20, 10, 225, 200);
                    markType = "lineleft";
                    break;
                default:
                    break;
            }
            radius = ofRandom(10, 50);
            //p.x = ofRandomWidth();
            p.x = 10;
            p.y = 0;
        }
        void update(){
            p.y += 3;
        }
        void draw(){
            ofSetColor(255);
            //ofDrawCircle(p, radius);
            ofDrawBitmapString(markType, p.x, p.y);
        }
        bool isAlive(){
            return (p.y - radius) < ofGetHeight();
        }
    
        string getMarkType(){
            return markType;
        }
};

class ofApp : public ofBaseApp{

    int i;
    ofParameter<int> cycle;

    ofxMC::MarkovChain markov;

    ofxLabel fps;
    ofxPanel gui;

    vector<Mark> marks;
    
	public:
		void setup();
		void update();
		void draw();

		
		
};
