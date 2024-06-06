#include "ofApp.h"

using namespace ofxComponent;

//--------------------------------------------------------------
void ofApp::setup(){
	auto componentManager = make_shared<ofxComponentManager>();

    // let's try change window appearance
    auto a = WindowComponent::getDefaultAppearance();
    // a.titleColor = ofColor(255,255,0);
    // a.titlebarColor = ofColor(0, 50, 100);
    // a.outlineColor = ofColor(200, 0, 0);
    // a.bgColor = ofColor(0, 100, 0, 100);
    // a.titlebarHeight = 30;
    // a.cornarHandle = 50;
    // a.movable = false;
    // a.resizable = false;
    WindowComponent::setDefaultAppearance(a);
    
    // Make StretchView (NoCrop) window
    {
        // Make contents instance
        // contents is child of view
        auto contents = make_shared<TestPatternView>();
        contents->setRect(ofRectangle(0, 0, 200, 200));

        // Make view instance
        // view is child of window
        auto view = make_shared<StretchView>(StretchView::NoCrop);
        // view has a contents
        view->setContents(contents);

        // Make window instance
        // window is child of componentManager
        ofRectangle rect(20, 40, 400, 300);
        auto window = make_shared<WindowComponent>("Stretch view NoCrop", rect);
        // window has a view
        window->setView(view);

        componentManager->addChild(window);
    }
    
    // Make StretchView (Crop) window
    {
        auto contents = make_shared<TestPatternView>();
        contents->setRect(ofRectangle(0, 0, 200, 200));

        auto view = make_shared<StretchView>(StretchView::Crop);
        view->setContents(contents);

        ofRectangle rect(440, 40, 400, 300);
        auto window = make_shared<WindowComponent>("Stretch view Crop", rect);
        window->setView(view);

        componentManager->addChild(window);
    }

    // Make Fit window
    {
        auto contents = make_shared<TestPatternView>();
        contents->setRect(ofRectangle(0, 0, 600, 400));

        auto view = make_shared<FitView>();
        view->setContents(contents);

        ofRectangle rect(860, 40, 400, 300);
        auto window = make_shared<WindowComponent>("Fit view", rect);
        window->setView(view);

        componentManager->addChild(window);
    }

    // Make ScrollView window
    {
        auto contents = make_shared<TestPatternView>();
        contents->setRect(ofRectangle(0, 0, 600, 400));

        auto view = make_shared<ScrollView>();
        view->setContents(contents);

        ofRectangle rect(20, 380, 400, 300);
        auto window = make_shared<WindowComponent>("Scroll view", rect);
        window->setView(view);

        componentManager->addChild(window);
    }

    // Make ScrollView window
    {
        auto contents = make_shared<TestPatternView>();
        contents->setRect(ofRectangle(0, 0, 600, 800));

        auto view = make_shared<ScrollView>();
        view->setContents(contents);
        //view->setFitMode(ScrollView::FitHeight);
        view->setFitMode(ScrollView::FitWidth);

        ofRectangle rect(440, 380, 400, 300);
        auto window = make_shared<WindowComponent>("Scroll view (fit width)", rect);
        window->setView(view);

        componentManager->addChild(window);
    }

    // Make scroll list view
    {
        auto listBox = make_shared<ListBox>();
        listBox->setRect(ofRectangle(0, 0, 600, 400));
//        listBox->setAlign(ListBox::Left);
//        listBox->setAlign(ListBox::Right);
//        listBox->setAlign(ListBox::Center);
        listBox->setAlign(ListBox::FitWidth);

        // make list
        for (int i = 0; i < 20; ++i) {
            string text = "element ";
            text += char(i + 'A');
            listBox->addElement(make_shared<MyListElement>(text, ofRectangle(0, 0, 200, 28)));
        }

        auto view = make_shared<ScrollView>();
        view->setContents(listBox);
        view->setFitMode(ScrollView::FitWidth);

        ofRectangle rect(860, 380, 400, 300);
        auto window = make_shared<WindowComponent>("Scroll view", rect);
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
    // draw help msg
    ofPushStyle();
    ofSetColor(200, 200, 0);
    ofDrawBitmapString("Move to drag window with titlebar  v", 20, 35);
    ofDrawBitmapString("Resize to drag right bottom cornar handle  ^", 70, 370);
    ofDrawBitmapString("Scroll to use mosue wheel  ^\nor drag scroll bars", 20, 710);
    ofDrawBitmapString("Move list elements to drag  ^\nClass of the elements is \"MyListObject\"\nThat is derived class of \"ListObject\"", 860, 710);
    ofPopStyle();
}
