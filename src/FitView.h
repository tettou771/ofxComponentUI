#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class FitView : public View {
    public:
        FitView();
                
        // ofxComponentBase
        void onLocalMatrixChanged() override;
    };
}
