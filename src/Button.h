#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
class Button : public ofxComponentBase {
public:
    Button();
    
    void onDraw() override;

    // please override this
    virtual void onDrawNormal(){;}
    virtual void onDrawHovered(){;}
    virtual void onDrawPressed(){;}
};
}
