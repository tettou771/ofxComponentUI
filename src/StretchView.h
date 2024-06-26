#pragma once
#include "ofxComponent.h"
#include "WindowComponent.h"

namespace ofxComponent {
    class StretchView : public View {
    public:
        enum Mode {
            NoCrop,
            Crop,
            Width,
            Height
        };

        StretchView();
        StretchView(Mode mode);
                
        // ofxComponentBase
        void onStart() override;
        void onLocalMatrixChanged() override;
        void onDestroy() override;

        // hanlder
        void onContentsLocalMatrixChanged();
        
        // View
        void onSetContents() override;

        // StreatchView
        void setMode(Mode _mode);
        Mode getMode() { return mode; }

    private:
        Mode mode;
        void updateContentsSize();
        bool onContentsLocalMatrixChangedResistored = false;
    };
}
