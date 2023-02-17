#include "Button.h"

using namespace ofxComponent;

Button::Button() {
}

void Button::onDraw() {
    if (isMostFront()) {
        if (mousePressing) onDrawPressed();
        else onDrawHovered();
    }
    else {
        onDrawNormal();
    }
}
