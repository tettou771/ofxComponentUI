#pragma once

#include "ofMain.h"
#include "ofxComponentUI.h"

using namespace ofxComponent;

class A : public View {
public:
	A() {}
	void onDraw() override {
		ofSetColor(200);
		ofNoFill();
		ofDrawRectangle(1, 1, getWidth()-1, getHeight()-1);
        ofDrawLine(1,1,getWidth()-1, getHeight()-1);
        ofDrawLine(1, getHeight()-1, getWidth()-1, 1);
        ofDrawCircle(getWidth()/2, getHeight()/2, MIN(getWidth(), getHeight())/2);
	}
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		shared_ptr<ofxComponent::ofxComponentManager> componentManager;
};
