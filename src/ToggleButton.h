#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
class ToggleButton : public ofxComponentBase {
public:
    ToggleButton(string _name);
    void onStart() override;
    void onDraw() override;
    void onMousePressed(ofMouseEventArgs& mouse) override;
    
    void setName(string _name);
    string getName();
    void setEnabled(bool _enabled);
    bool getEnabled();
    
    ofEvent<bool> buttonPressedEvent;
    
private:
    bool enabled = false;
    string name;
};
}
