#include "ToggleButton.h"

using namespace ofxComponent;

ToggleButton::ToggleButton(string _name) {
    setName(_name);
}

void ToggleButton::onStart(){
    
}

void ToggleButton::onDraw(){
    ofDisableAntiAliasing();
    
    string onoffstr;
    if (enabled) {
        ofSetColor(255, 0, 0, 100);
        ofFill();
        ofDrawRectangle(0, 0, getWidth(),getHeight());
        onoffstr = " ON";
    }else{
        onoffstr = " OFF";
    }
    ofSetColor(200);
    ofNoFill();
    ofDrawRectangle(0, 0, getWidth(),getHeight());
    ofDrawBitmapString(name + onoffstr, 4, (getHeight() + 10) / 2);
    
    ofEnableAntiAliasing();
}

void ToggleButton::onMousePressed(ofMouseEventArgs &mouse){
    if (isMouseInside()) {
        enabled = !enabled;
        ofNotifyEvent(buttonPressedEvent, enabled);
    }
}

void ToggleButton::setName(string _name) {
    name = _name;
}

string ToggleButton::getName() {
    return name;
}

void ToggleButton::setEnabled(bool _enabled) {
    enabled = _enabled;
    ofNotifyEvent(buttonPressedEvent, enabled);
}

bool ToggleButton::getEnabled(){
    return enabled;
}
