#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class FitView : public View {
    public:
        enum Mode {
            SmallFit,
            CropFit
        };

        FitView();
        FitView(Mode mode);
                
        // ofxComponentBase
        void onLocalMatrixChanged() override;
        
    private:
        Mode mode;
    };
}
