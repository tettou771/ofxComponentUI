#include "ofApp.h"

using namespace ofxComponent;

//--------------------------------------------------------------
void ofApp::setup(){
	auto componentManager = make_shared<ofxComponentManager>();

    // make StretchView (NoCrop) window
    {
        auto contents = make_shared<A>();
        contents->setRect(ofRectangle(0, 0, 200, 200));

        auto view = make_shared<StretchView>(StretchView::NoCrop);
        view->setContents(contents);

        ofRectangle rect(50, 50, 400, 300);
        auto window = make_shared<Window>("Stretch view NoCrop", rect);
        window->setDraggable(false);
        window->setView(view);

        componentManager->addChild(window);
    }
    
    // make StretchView (Crop) window
    {
        auto contents = make_shared<A>();
        contents->setRect(ofRectangle(0, 0, 200, 200));

        auto view = make_shared<StretchView>(StretchView::Crop);
        view->setContents(contents);

        ofRectangle rect(500, 50, 400, 300);
        auto window = make_shared<Window>("Stretch view Crop", rect);
        window->setDraggable(false);
        window->setView(view);

        componentManager->addChild(window);
    }

    // make Fit window
    {
        auto contents = make_shared<A>();
        contents->setRect(ofRectangle(0, 0, 600, 400));

        auto view = make_shared<FitView>();
        view->setContents(contents);

        ofRectangle rect(50, 400, 400, 300);
        auto window = make_shared<Window>("Fit view", rect);
        window->setDraggable(false);
        window->setView(view);

        componentManager->addChild(window);
    }

    // make ScrollView window
    {
        auto contents = make_shared<A>();
        contents->setRect(ofRectangle(0, 0, 600, 400));

        auto view = make_shared<ScrollView>();
        view->setContents(contents);

        ofRectangle rect(500, 400, 400, 300);
        auto window = make_shared<Window>("Scroll view", rect);
        window->setDraggable(false);
        window->setView(view);

        componentManager->addChild(window);
    }
    
    componentManager->setup();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
