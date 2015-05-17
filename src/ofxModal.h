//
//  ofxModal.h
//  ofxModalExample
//
//  Created by Roy Macdonald on 14-05-15.
//
//

#pragma once

#define USE_OFXTWEEN // Comment out this line to disable tweens.
//#define USE_TOUCH // UnComment this line if you need touch events (iOS, android)

#include "ofMain.h"
#ifdef USE_OFXTWEEN
#include "ofxTween.h"
#endif


class ofxModal : public ofRectangle {
public:
	ofxModal();
	virtual ~ofxModal();

	void runModal(bool bTween = true, int tweenDuration = 400); //DON'T OVERRIDE THIS METHOD.
	void stopModal(bool bTween = true);
	
	//CUSTOM METHODS. You should override these methods on your derived class
	virtual void customUpdate(){}
	virtual void customDraw(){}
	virtual void customExit(){}
	
	//KEY EVENTS
	virtual bool keyPressed(ofKeyEventArgs& args){return true;}
	virtual bool keyReleased(ofKeyEventArgs& args){return true;}
	
	//MOUSE EVENTS
	virtual bool mouseMoved(ofMouseEventArgs& args){return true;}
	virtual bool mouseDragged(ofMouseEventArgs& args){return true;}
	virtual bool mousePressed(ofMouseEventArgs& args){return true;}
	virtual bool mouseReleased(ofMouseEventArgs& args){return true;}
	virtual bool mouseScrolled(ofMouseEventArgs& args){return true;}
	virtual bool mouseEntered(ofMouseEventArgs& args){return true;}
	virtual bool mouseExited(ofMouseEventArgs& args){return true;}
	
	//WINDOW EVENTS
	virtual bool windowResized(ofResizeEventArgs& args){return false;}
	
	//MISC EVENTS
	virtual bool dragEvent(ofDragInfo& dragInfo){return false;}
	virtual bool gotMessage(ofMessage& msg){return false;}
	
#ifdef USE_TOUCH
	//TOUCH EVENTS
	virtual bool touchDown(ofTouchEventArgs& args){return true;}
	virtual bool touchUp(ofTouchEventArgs& args){return true;}
	virtual bool touchMoved(ofTouchEventArgs& args){return true;}
	virtual bool touchDoubleTap(ofTouchEventArgs& args){return true;}
	virtual bool touchCancelled(ofTouchEventArgs& args){return true;}
#endif
	
	//SETTERS
	//the following will overlay this color all over your window below your modal dialog.
	void setOverlayColor(ofColor c){overlayColor = c;}
	void setTweenDuration(unsigned int duration){tweenDuration = duration;}
	
	//GETTERS
	bool isTweening(){return bIsTweening;}
	unsigned int getTweenDuration(){return tweenDuration;}
	
protected:
#ifdef USE_OFXTWEEN
	virtual void tweenIn();
	virtual void tweenOut();
	virtual void tweenEnded(int& i);
	ofxTween tween;
	ofxEasingExpo easing;
#endif
	ofColor overlayColor;
	bool bIsTweening;
	
	void setMouseOffset();
	ofVec2f mouseOffset;
private:
	void update(ofEventArgs& a);//DON'T OVERRIDE THIS METHOD. Override customUpdate() instead
	void draw(ofEventArgs& a);//DON'T OVERRIDE THIS METHOD. Override customDraw() instead
	void exit(ofEventArgs& a);//DON'T OVERRIDE THIS METHOD. Override customExit() instead
	void run();
	void stop();
	bool bIsRunnig;
	bool bIsTweenIn;
	unsigned int tweenDuration;
};