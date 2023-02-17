#pragma once
#include "ofxComponent.h"
#include "ClickableComponent.h"

namespace ofxComponent {
class Button : public ClickableComponent {
public:
    Button();
    
    void onDraw() override;

    // please override this
    virtual void onDrawNormal(){;}
    virtual void onDrawHovered(){;}
    virtual void onDrawPressed(){;}
};
}
