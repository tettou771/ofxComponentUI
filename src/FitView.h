#pragma once
#include "ofxComponent.h"
#include "Window.h"

namespace ofxComponent {
    class FitView : public View {
    public:
        FitView();
                
        // ofxComponentBase
        void onStart();
        void onLocalMatrixChanged() override;
        void onDestroy() override;

        // hanlder
        void onContentsLocalMatrixChanged();
        
        // View
        void onSetContents() override;
        
    protected:
        void updateContentsSize();
        bool onContentsLocalMatrixChangedResistored = false;
    };
}
