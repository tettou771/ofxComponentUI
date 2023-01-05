#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
class Button : public ofxComponentBase {
public:
    Button();
    
    void onDraw() override;
    void onMousePressed(ofMouseEventArgs &mouse) override;
    void onMouseReleased(ofMouseEventArgs &mouse) override;

    // please override this
    virtual void onDrawNormal(){;}
    virtual void onDrawHovered(){;}
    virtual void onDrawPressed(){;}
    
    ofEvent<void> clickedEvents;
    bool mousePressing;
};
}
