#include "Button.h"

using namespace ofxComponent;

Button::Button() {
}

void Button::onDraw() {
    if (isMouseOver()) {
        if (isMousePressedOverComponent()) onDrawPressed();
        else onDrawHovered();
    }
    else {
        onDrawNormal();
    }
}
