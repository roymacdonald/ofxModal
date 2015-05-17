//
//  ofxModal.cpp
//  ofxModalExample
//
//  Created by Roy Macdonald on 14-05-15.
//
//

#include "ofxModal.h"
//-------------------------------------------------------------
ofxModal::ofxModal():bIsRunnig(false), ofRectangle(0,0,ofGetWidth(), ofGetHeight()), bIsTweening(false), bIsTweenIn(false){}
//-------------------------------------------------------------
ofxModal::~ofxModal(){
	stop();
}
//-------------------------------------------------------------
void ofxModal::update(ofEventArgs& a){
	setMouseOffset();//this is a bit redundant. could be more ellegant.
	customUpdate();
}
//-------------------------------------------------------------
void ofxModal::draw(ofEventArgs& a){
	ofPushStyle();
	float tweenVal = tween.update();
	if (overlayColor.a > 0) {
		ofSetColor(overlayColor, ofMap(tweenVal, 0, 1, 0, overlayColor.a));
		ofFill();
		ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
	}
	ofSetColor(255);
	ofPushStyle();
	ofPushMatrix();
	ofPushView();
	ofRectangle r = *this;
	if (bIsTweening) {
		r.scaleFromCenter(tweenVal);
		ofViewport(r);
		ofSetupScreen();
		ofScale(tweenVal, tweenVal);
	}else{
		ofViewport(*this);
		ofSetupScreen();
	}
	customDraw();
	ofPopMatrix();
	ofPopStyle();
	ofPopView();
	ofPopStyle();
	
	ofDrawBitmapStringHighlight("rect: " + ofToString((ofRectangle)*this), 100,100 );
}
//-------------------------------------------------------------
void ofxModal::exit(ofEventArgs& a){
	customExit();
	stop();
}
//-------------------------------------------------------------
void ofxModal::tweenIn(){
	tween.setParameters(easing, ofxTween::easeOut, 0, 1, tweenDuration, 0);
	ofAddListener(tween.end_E, this, &ofxModal::tweenEnded);
	bIsTweenIn = true;
	bIsTweening = true;
	tween.start();
	run();
}
//-------------------------------------------------------------
void ofxModal::tweenOut(){
	tween.setParameters(easing, ofxTween::easeIn, 1, 0, tweenDuration, 0);
	ofAddListener(tween.end_E, this, &ofxModal::tweenEnded);
	bIsTweenIn = false;
	bIsTweening = true;
	tween.start();
}
//-------------------------------------------------------------
void ofxModal::tweenEnded(int& i){
	if (bIsTweening) {
		ofRemoveListener(tween.end_E, this, &ofxModal::tweenEnded);
		if (!bIsTweenIn) {
			stop();
		}
	}
	bIsTweenIn = false;
	bIsTweening = false;
}
//-------------------------------------------------------------
void ofxModal::runModal(bool bTween, int tweenDuration){
	if (!bIsRunnig) {
		this->tweenDuration = tweenDuration;
#ifdef USE_OFXTWEEN
		if(bTween){
			tweenIn();
		}else{
			run();
		}
#else
		run();
#endif
	}
}
//-------------------------------------------------------------
void ofxModal::run(){
	ofRegisterDragEvents(this, OF_EVENT_ORDER_BEFORE_APP);
	ofRegisterGetMessages(this, OF_EVENT_ORDER_BEFORE_APP);
	ofRegisterKeyEvents(this, OF_EVENT_ORDER_BEFORE_APP);
	ofRegisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);

	ofAddListener(ofEvents().windowResized, this, &ofxModal::windowResized, OF_EVENT_ORDER_BEFORE_APP);
	ofAddListener(ofEvents().draw, this, &ofxModal::draw, OF_EVENT_ORDER_AFTER_APP);
	ofAddListener(ofEvents().update, this, &ofxModal::update, OF_EVENT_ORDER_AFTER_APP);
	ofAddListener(ofEvents().exit, this, &ofxModal::exit, OF_EVENT_ORDER_AFTER_APP);
#ifdef USE_TOUCH
	ofRegisterTouchEvents(this, OF_EVENT_ORDER_BEFORE_APP);
#endif
	bIsRunnig = true;
}
//-------------------------------------------------------------
void ofxModal::stopModal(bool bTween){
	if (bIsRunnig) {
		
#ifdef USE_OFXTWEEN
		if (bTween) {
			tweenOut();
		}else{
			stop();
		}
#else
		stop();
#endif
	}
}
//-------------------------------------------------------------
void ofxModal::stop(){
	if (bIsRunnig) {
		ofUnregisterDragEvents(this, OF_EVENT_ORDER_BEFORE_APP);
		ofUnregisterGetMessages(this, OF_EVENT_ORDER_BEFORE_APP);
		ofUnregisterKeyEvents(this, OF_EVENT_ORDER_BEFORE_APP);
		ofUnregisterMouseEvents(this, OF_EVENT_ORDER_BEFORE_APP);
	
		ofRemoveListener(ofEvents().windowResized, this, &ofxModal::windowResized, OF_EVENT_ORDER_BEFORE_APP);
		ofRemoveListener(ofEvents().draw, this, &ofxModal::draw, OF_EVENT_ORDER_AFTER_APP);
		ofRemoveListener(ofEvents().update, this, &ofxModal::update, OF_EVENT_ORDER_AFTER_APP);
		ofRemoveListener(ofEvents().exit, this, &ofxModal::exit, OF_EVENT_ORDER_AFTER_APP);
#ifdef USE_TOUCH
		ofUnregisterTouchEvents(this);
#endif
		bIsRunnig = false;
	}
}
//-------------------------------------------------------------
void ofxModal::setMouseOffset(){
	mouseOffset.set(x, y);
}

