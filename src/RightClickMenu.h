#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
    struct RightClickMenuElement {
        string name;
        int shotrcutKey;
        function<void()> event;
    };

    struct RightClickMenuSettings {
        vector<RightClickMenuElement> list;
    };

    class RightClickMenu : public ofxComponentBase {
    public:
        RightClickMenu(){};
        
        void onStart() override;
        void onDraw() override;
        void onUpdate() override;
        void onDestroy() override;
        void onMousePressed(ofMouseEventArgs& mouse) override;

        // make menu. if it exists, add menu
        static void makeMenu(RightClickMenuSettings &settings);
        static void makeMenu(RightClickMenuSettings &settings, int x, int y);

    private:
        static shared_ptr<RightClickMenu> singleton;
        static void makeSingleton();
        static const int borderHeight = 10;
        static const int listHeight = 16;
        
        // list of list
        // between list and list is separated
        vector<vector<RightClickMenuElement> > metaList;
        
        bool ignoreThisFrame = true;
    };
}
