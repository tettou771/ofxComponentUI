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
    // if menu exists, not make and add
    bool addMenu = false;
    
    if (singleton == nullptr || singleton->isDestroyed()) {
        makeSingleton();
    }else{
        addMenu = true;
    }
    
    // ignore this frame input
    singleton->ignoreThisFrame = true;
    
    // make menu
    if (ofxComponentManager::singleton) {
        // controll with manager
        ofxComponentManager::singleton->addChild(singleton);
        
        int w = 200; // menu width
        int h = 0; // height fit to list

        singleton->metaList.push_back(settings.list);
        
        // check height
        for (auto l : singleton->metaList) {
            for (auto element : l) {
                h += listHeight;
            }
            h += bordarHeight;
        }
        
        // if add menu, don't move the menu
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

void RightClickMenu::onUpdate() {
    if (ignoreThisFrame) {
        ignoreThisFrame = false;
        return;
    }
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
    
    for (auto l : singleton->metaList) {
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
            ofDrawBitmapString(element.name, 2, y + (fontHeight + listHeight) / 2);
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
    if (ignoreThisFrame) return;
    
    // didn't touched, cancel
    if (!isMouseOver()) {
        destroy();
        return;
    } else {
        int y = 0;
        int my = getMouseY();
        for (auto l : singleton->metaList) {
            for (auto element : l) {
                // if mouse hover, highlight
                if (y <= my && my < y + listHeight) {
                    ofLogVerbose("RightClickMenu") << element.name << " is selected";
                    element.event();
                    destroy();
                    return;
                }
                y += listHeight;
            }
            y += bordarHeight;
        }
    }

    ofLogVerbose("RightClickMenu") << "Clicked, but here is no element.";
}
