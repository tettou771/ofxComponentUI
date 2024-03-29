#pragma once

#include "ofMain.h"
#include "ofxComponentUI.h"

using namespace ofxComponent;

// this is custom View component
class TestPatternView : public View {
public:
	TestPatternView() {}
    void onSetup() override {
        // Sets the default size.
        // If the view setting is FitView, ScrollView, the size may be automatically changed accordingly
        setWidth(600);
        setHeight(600);
    }
    
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

// this is custom ListElement
class MyListElement : public ListElement {
public:
	MyListElement(string t, ofRectangle r) {
		text = t;
		setRect(r);
		setMovable(true);
	}
	string text;
	void onUpdate() override {
		if (getMoving()) {
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
    
    // This methods makes it draggable
	void onMouseDragged(ofMouseEventArgs& mouse) override {
		if (getMoving()) moved = true;
	}
	void onMouseReleased(ofMouseEventArgs& mouse) override {
        // Update list order if it moved by mouse
		if (moved) {
			moved = false;
			getParentBox()->updateList();
		}
	}
    // True if mouse dragged
	bool moved = false;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        // ofxComponent needs this instance
		shared_ptr<ofxComponent::ofxComponentManager> componentManager;
};
