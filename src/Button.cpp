#include "Button.h"

using namespace ofxComponent;

Button::Button() {
}

void Button::onDraw() {
    if (isMouseInside()) {
        if (mousePressing) onDrawPressed();
        else onDrawHovered();
    }
    else {
        onDrawNormal();
    }
}

void Button::onMousePressed(ofMouseEventArgs &mouse) {
    if (isMouseInside()) {
        ofNotifyEvent(clickedEvents);
        mousePressing = true;
    }
}
            
void Button::onMouseReleased(ofMouseEventArgs &mouse) {
    mousePressing = false;
}
