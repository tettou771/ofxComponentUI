#pragma once

#include "ofMain.h"
#include "ofxComponentUI.h"

using namespace ofxComponent;

class A : public ofxComponentBase {
public:
	A() {}
	void onDraw() override {
		ofSetColor(200);
		ofNoFill();
		ofDrawRectangle(0, 0, getWidth(), getHeight());
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
