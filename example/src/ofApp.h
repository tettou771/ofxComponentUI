#pragma once

#include "ofMain.h"
#include "ofxComponentUI.h"

using namespace ofxComponent;

class A : public View {
public:
	A() {}
	void onDraw() override {
		// fill myself
		ofSetColor(0, 40, 100);
		ofDrawRectangle(0, 0, getWidth(), getHeight());

		// draw cross hatch
		ofSetColor(200);
		ofNoFill();
		ofSetLineWidth(3);
		ofDrawRectangle(1, 1, getWidth()-1, getHeight()-1);
        ofDrawLine(1,1,getWidth()-1, getHeight()-1);
        ofDrawLine(1, getHeight()-1, getWidth()-1, 1);
        ofDrawCircle(getWidth()/2, getHeight()/2, MIN(getWidth(), getHeight())/2);
	}
};

class MyListElement : public ListElement {
public:
	MyListElement(string t, ofRectangle r) {
		text = t;
		setRect(r);
		setDraggable(true);
	}
	string text;
	void onUpdate() override {
		if (getDragging()) {
			if (getPrevious() && getPrevious()->getPos().y > getPos().y) {
				moveUp();
			}
			else if (getNext() && getNext()->getPos().y < getPos().y) {
				moveDown();
			}
		}
	}
	void onDraw() override {
		// draw rect
		ofSetColor(200);
		ofNoFill();
		ofSetLineWidth(2);
		ofDrawRectangle(1, 1, getWidth() - 2, getHeight() - 2);

		// draw text
		string label = ofToString(getIndex()) + " " + text;
		ofDrawBitmapString(label, 4, 16);
	}
	void onMouseDragged(ofMouseEventArgs& mouse) override {
		if (getDragging()) moved = true;
	}
	void onMouseReleased(ofMouseEventArgs& mouse) override {
		if (moved) {
			moved = false;
			getParentBox()->updateList();
		}
	}
	bool moved = false;
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
