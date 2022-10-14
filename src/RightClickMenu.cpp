#include "RightClickMenu.h"

using namespace ofxComponent;

shared_ptr<RightClickMenu> RightClickMenu::singleton = nullptr;

// static methoc
void RightClickMenu::makeSingleton() {
    if (singleton != nullptr) return;
    singleton = make_shared<RightClickMenu>();
}

void RightClickMenu::makeMenu(RightClickMenuSettings &settings) {
    makeMenu(settings, ofGetMouseX(), ofGetMouseY());
}

void RightClickMenu::makeMenu(RightClickMenuSettings &settings, int x, int y) {
    if (settings.target == nullptr) {
        ofLogError() << "Error: RightClickMenu needs target, but this is nullptr";
    }
    
    makeSingleton();
    singleton->target = settings.target;
    
    // ignore this frame input
    // reenable in onStart()
    singleton->setKeyMouseEventEnabled(false);

    // find master manager
    shared_ptr<ofxComponentBase> t;
    t = settings.target;
    bool founded = false;
    while (true) {
        if (dynamic_pointer_cast<ofxComponentManager>(t) != nullptr) {
            founded = true;
            break;
        } else {
            t = t->getParent();
            if (t == nullptr) break;
        }
    }
    
    // make menu
    if (founded) {
        // controll with manager
        t->addChild(singleton);
        
        int w = 200; // menu width
        int h = 0; // height fit to list

        singleton->list = settings.list;
        for (auto l : singleton->list) {
            for (auto element : l) {
                h += listHeight;
            }
            h += bordarHeight;
        }

        singleton->setRect(ofRectangle(x, y, w, h));
    }
    // can not make menu
    else {
        ofLogError() << "Error: RightClickMenu needs ofxComponentManager, but target is not have it.";
    }
}

void RightClickMenu::onStart() {
    setKeyMouseEventEnabled(true);
}

void RightClickMenu::onDraw() {
    ofPushStyle();
    ofPushMatrix();
    
    int y = 0;
    
    // mouse pos
    int mx = getMouseX();
    int my = getMouseY();
    
    ofFill();
    ofSetColor(50);
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
    for (auto l : singleton->list) {
        for (auto element : l) {
            // if mouse hover, highlight
            if (0 <= mx && mx < getWidth()) {
                if (y <= my && my < y + listHeight) {
                    ofSetColor(100);
                    ofFill();
                    ofDrawRectangle(0, y, getWidth(), listHeight);
                }
            }
            
            
            ofSetColor(255);
            int fontHeight = 13.5;
            ofDrawBitmapString(element, 2, y + (fontHeight + listHeight) / 2);
            y += listHeight;
        }
        y += bordarHeight;
    }
    
    ofPopMatrix();
    ofPopStyle();
}

void RightClickMenu::onDestroy() {
    singleton = nullptr;
}

void RightClickMenu::onMousePressed(ofMouseEventArgs &mouse) {
    // If target is already destroyed, ignore
    if (!target || target->isDestroyed()) {
        destroy();
        return;
    }

    auto receivableTarget = dynamic_pointer_cast<RightClickMenuReceiver>(target);
    if (!receivableTarget) {
        destroy();
        return;
    }

    RightClickMenuEventArgs args;
    
    // out of range, canceled
    if (!isMouseInside()) {
        args.canceled = true;
        receivableTarget->onRightClickMenuClicked(args);
        destroy();
        return;
    } else {
        int y = 0;
        int my = getMouseY();
        for (auto l : singleton->list) {
            for (auto element : l) {
                // if mouse hover, highlight
                if (y <= my && my < y + listHeight) {
                    args.canceled = false;
                    args.selected = element;
                    receivableTarget->onRightClickMenuClicked(args);
                    destroy();
                    return;
                }
                y += listHeight;
            }
            y += bordarHeight;
        }
    }

    ofLog() << "Clicked, but here is no element.";
}
