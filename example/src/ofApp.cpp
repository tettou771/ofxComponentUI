#include "ofApp.h"

using namespace ofxComponent;

//--------------------------------------------------------------
void ofApp::setup(){
	auto componentManager = make_shared<ofxComponentManager>();

    ofRectangle rect(100, 100, 500, 400);
	auto window1 = make_shared<Window>("Window 1", rect);
    //window1->setConstrain(true);
	window1->setDraggable(false);
    
    auto contentsA = make_shared<A>();
    contentsA->setRect(ofRectangle(0, 0, 300, 200));
    //auto view = make_shared<ScrollView>(ScrollView::Width);
    auto view = make_shared<FitView>(FitView::SmallFit);
    view->setContents(contentsA);
    window1->setView(view);
    
	componentManager->addChild(window1);
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
