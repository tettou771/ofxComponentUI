#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
    class WindowComponent;

    class View : public ofxComponentBase {
    public:
        View(){setConstrain(true);}
        void onDraw() override;
        void setContents(shared_ptr<ofxComponentBase> _contents);
        shared_ptr<ofxComponentBase> getContents() {return contents;};
        shared_ptr<WindowComponent> getParentWindow();
        virtual void onSetContents() {}
        
        void setBgColor(ofColor c){bgColor = c;};
        ofColor getBgColor(){return bgColor;}
    protected:
        shared_ptr<ofxComponentBase> contents;
        ofColor bgColor = ofColor(0, 0, 0, 0);
    };

    class WindowHomeButton : public ofxComponentBase {
    public:
        void onDraw() override;
        void onMousePressedOverComponent(ofMouseEventArgs& mouse) override;
        ofEvent<void> clickEvents;
    };

    /// <summary>
    /// Window has a component
    /// to use easy handling (drag move, and resize, and more)
    /// </summary>
    class WindowComponent : public ofxComponentBase {
    public:
        struct Appearance {
            // colors
            ofColor titleColor = ofColor(200);
            ofColor titlebarColor = ofColor(70);
            ofColor outlineColor = ofColor(120);
            ofColor bgColor = ofColor(0, 120);
            
            // geometry
            int titlebarHeight = 18;
            int cornarHandle = 10;
            
            // setting
            bool resizable = true;
            bool movable = true;
        };
        
        WindowComponent(string title, int x, int y, int w, int h);
        WindowComponent(string title, ofRectangle rect);

        // ofxComponentBase
        void onStart() override;
        void onDraw() override; // draw before children
        void postDraw() override; // draw after children
        void onMousePressed(ofMouseEventArgs& mouse) override;
        void onMouseDragged(ofMouseEventArgs& mouse) override;
        void onMouseReleased(ofMouseEventArgs& mouse) override;
        void onLocalMatrixChanged() override;

        // window
        void setTitle(const string& t) { title = t; }
        string getTitle() { return title; }
        void setResizable(bool _resizable) {appearance.resizable = _resizable;}
        bool getResizable() { return appearance.resizable;}
        void setAppearance(Appearance a) { appearance = a; setMovable(a.movable);}
        Appearance getAppearance() {return appearance;}
        
        // set home
        void setHomeRect(const float& x, const float& y, const float& width, const float& height);
        void setHomeRect(const ofRectangle rect);
        
        // set default appearance (setting)
        // to make same appearance window easy
        static void setDefaultAppearance(Appearance a) {defaultAppearance = a;}
        static Appearance getDefaultAppearance() {return defaultAppearance;}

        // align to other window
        enum Align {
            Left, Right, Top, Bottom
        };
        void alignTo(Align direction, shared_ptr<WindowComponent> other);
        
        shared_ptr<View> setView(shared_ptr<View> _view);
        shared_ptr<View> getView(){
            return view;
        }

    protected:
        string title;
        shared_ptr<View> view = nullptr;

        // setting
        Appearance appearance;
        
        bool cornarDragging = false;

        // size of start
        ofRectangle homeRect;
        shared_ptr<WindowHomeButton> homeButton = nullptr;
        void onHomeButton();

        void updateViewRect();
        
        // default setting
        // apply when make new window
        static Appearance defaultAppearance;
    };
}
