#pragma once
#include "ofxComponent.h"
namespace ofxComponent {
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
        Window(string title, int x, int y, int w, int h, shared_ptr<ofxComponentBase> contents);
        Window(string title, ofRectangle rect, shared_ptr<ofxComponentBase> contents);

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

    private:
        string title, titleAttribute;
        shared_ptr<ofxComponentBase> contents;
        bool cornarDragging = false;

        // initial size
        ofRectangle homeRect;
        shared_ptr<WindowHomeButton> homeButton = nullptr;
        void onHomeButton();

        void updateContentsRect();
    };
}