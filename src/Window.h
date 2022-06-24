#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
    class Window;

    class View : public ofxComponentBase {
    public:
        View(){setConstrain(true);}
        void setContents(shared_ptr<ofxComponentBase> _contents);
        shared_ptr<ofxComponentBase> getContents() {return contents;};
        shared_ptr<Window> getParentWindow();
    protected:
        shared_ptr<ofxComponentBase> contents;
    };

    class WindowHomeButton : public ofxComponentBase {
    public:
        void onDraw() override;
        void onMousePressed(ofMouseEventArgs& mouse) override;
        ofEvent<void> clickEvents;
    };

    /// <summary>
    /// Window has a component
    /// to use easy handling (drag move, and resize, and more)
    /// </summary>
    class Window : public ofxComponentBase {
    public:
        Window(string title, int x, int y, int w, int h);
        Window(string title, ofRectangle rect);

        // ofxComponentBase
        void onStart() override;
        void onDraw() override; // draw before children
        void postDraw() override; // draw after children
        void onMousePressed(ofMouseEventArgs& mouse) override;
        void onMouseDragged(ofMouseEventArgs& mouse) override;
        void onMouseReleased(ofMouseEventArgs& mouse) override;
        void onLocalMatrixChanged() override;

        // window
        void setTitle(string& t) { title = t; }
        string getTitle() { return title; }
        void setTitleAttribute(string& a) { titleAttribute = a; }
        string getTitleAttribute() { return titleAttribute; }

        // align to other window
        enum Align {
            Left, Right, Top, Bottom
        };
        void alignTo(Align direction, shared_ptr<Window> other);

        static const int titleBarHeight = 20;
        
        void setView(shared_ptr<View> _view);
        shared_ptr<View> getView(){
            return view;
        }

    private:
        string title, titleAttribute;
        shared_ptr<View> view;

        bool cornarDragging = false;

        // initial size
        ofRectangle homeRect;
        shared_ptr<WindowHomeButton> homeButton = nullptr;
        void onHomeButton();

        void updateViewRect();
    };
}
