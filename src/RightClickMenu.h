#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
    struct RightClickMenuEventArgs {
        bool canceled = false;
        string selected = "";
    };

    class RightClickMenuReceiver {
    public:
        virtual void onRightClickMenuClicked(RightClickMenuEventArgs &args){};
    };

    struct RightClickMenuSettings {
        shared_ptr<ofxComponentBase> target;
        
        // vector in vector
        // list is separated with bordar
        vector<vector<string> > list;
    };

    class RightClickMenu : public ofxComponentBase {
    public:
        RightClickMenu(){};
        
        void onStart() override;
        void onDraw() override;
        void onDestroy() override;
        void onMousePressed(ofMouseEventArgs& mouse) override;

        static void makeMenu(RightClickMenuSettings &settings);
        static void makeMenu(RightClickMenuSettings &settings, int x, int y);

    private:
        static shared_ptr<RightClickMenu> singleton;
        static void makeSingleton();
        static const int bordarHeight = 10;
        static const int listHeight = 16;
        
        shared_ptr<ofxComponentBase> target = nullptr;
        vector<vector<string> > list;
    };
}
