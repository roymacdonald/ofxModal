//
//  somethingModal.h
//  ofxModalExample
//
//  Created by Roy Macdonald on 14-05-15.
//
//

#pragma once
#include "ofxModal.h"

class somethingModal: public ofxModal{
public:
	somethingModal(){
		width = ofGetWidth()* 0.8;//this sets the size of the modal panel.
		height = ofGetHeight()*0.8;
		ofRectangle r(0,0,ofGetWidth(), ofGetHeight());
		this->alignTo(r); //this will make the modal panel to be aligned at the center of the window.
	}
	void customDraw(){
		ofSetColor(255);
		ofNoFill();
		ofDrawRectangle(0, 0, width-2, height -2);
		ofSetColor(ofColor::red);
		ofSetLineWidth(5);
		line.draw();
		ofSetDrawBitmapMode(OF_BITMAPMODE_SIMPLE);
		ofDrawBitmapStringHighlight("press the ESC key to close this modal panel", 30, 30);
	}
	
	virtual bool mouseDragged(ofMouseEventArgs& args){
		if (inside(args.x, args.y)) {
			line.addVertex(args.x-mouseOffset.x, args.y -mouseOffset.y);
		}
		return true; //THIS IS VERY IMPORTANT as it make the mouse event to stop progagating. as the ofxModal class sets itself to have the highest priority no other class will receive this mouse event, thus avoiding any mouse interaction with elements drawn bellow the modal element.
	}
	virtual bool mousePressed(ofMouseEventArgs& args){
		if (inside(args.x, args.y)) {
			line.addVertex(args.x-mouseOffset.x, args.y -mouseOffset.y);
		}
		return true;
	}
	virtual bool keyReleased(ofKeyEventArgs& args){
		if (args.key == OF_KEY_ESC) {
			stopModal();
		}
		return true;
	}
	ofPolyline line;
};
