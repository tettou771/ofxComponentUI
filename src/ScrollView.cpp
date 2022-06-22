#include "ScrollView.h"
//#include "Window.h"

using namespace ofxComponent;

ScrollView::ScrollView() {}
ScrollView::ScrollView(ResizeMode mode) : resizeMode(mode){}

void ScrollView::onStart() {
    setConstrain(true);
}

void ScrollView::onUpdate() {
    
}

void ScrollView::onDraw() {
    
}

void ScrollView::onMouseMoved(ofMouseEventArgs &mosue) {}
void ScrollView::onMousePressed(ofMouseEventArgs &mosue) {}
void ScrollView::onMouseDragged(ofMouseEventArgs &mosue) {}
void ScrollView::onMouseReleased(ofMouseEventArgs &mosue) {}

void ScrollView::onMouseScrolled(ofMouseEventArgs &mouse) {
    if (!contents) return;
    
    // can not scroll
    if (resizeMode == Both) return;

    float scrollSpeed = 5;
    
    auto contentsPos = contents->getPos();
    
    // horizontal scroll
    if (isHorizontalScrollEnabled()) {
        if (contents->getWidth() <= getWidth()) {
            contentsPos.x = 0;
        }
        else {
            contentsPos.x += mouse.scrollX * scrollSpeed;
            
            // avoid overrun
            float maxPos = 0;
            float minPos = getWidth() - contents->getWidth();
            contentsPos.x = MIN(MAX(contentsPos.x, minPos), maxPos);
        }

    }
    
    // vertical scroll
    if (isVerticalScrollEnabled()) {
        if (contents->getHeight() <= getHeight()) {
            contentsPos.y = 0;
        }
        else {
            contentsPos.y += mouse.scrollY * scrollSpeed;
            
            // avoid overrun
            float maxPos = 0;
            float minPos = getHeight() - contents->getHeight();
            contentsPos.y = MIN(MAX(contentsPos.y, minPos), maxPos);
        }
    }

    contents->setPos(contentsPos);
}

void ScrollView::onLocalMatrixChanged() {
    if (!contents) return;
    
    if (resizeMode == Both || resizeMode == Width) {
        contents->setWidth(getWidth());
    }
    if (resizeMode == Both || resizeMode == Height) {
        contents->setHeight(getHeight());
    }
    
    updateScrollBar();
}

 void ScrollView::updateScrollBar() {
 //    if ();
 }

/*
shared_ptr<Window> ScrollView::getParentWindow() {
    shared_ptr<Window> w = nullptr;
    auto child = static_pointer_cast<ofxComponentBase>(shared_from_this());
    while(true) {
        auto p = child->getParent();
        if (!p) return nullptr;
        
        auto w = dynamic_pointer_cast<Window>(p);
        if (w) {
            return w;
        } else {
            child = p;
        }
    }
    
    //return nullptr;
}
*/


