#include "Window.h"

using namespace ofxComponent;

Window::Appearance Window::defaultAppearance;

void View::setContents(shared_ptr<ofxComponentBase> _contents) {
    if (!_contents) return;
    
    // if already exists, remove content
    if (contents) {
        removeChild(contents);
    }
    
    contents = _contents;
    onSetContents();
    
    // insert before scroll bars
    insertChild(contents, 0);
    
    contents->setWidth(getWidth());
    contents->setHeight(getHeight());
}

shared_ptr<Window> View::getParentWindow() {
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

	return nullptr;
}


Window::Window(string title, int x, int y, int w, int h) {
	Window(title, ofRectangle(x, y, w, h));
}

Window::Window(string title, ofRectangle _rect)
	:title(title) {
    appearance = defaultAppearance;
	auto withTitleBarRect = _rect;
	withTitleBarRect.height += appearance.titlebarHeight;
	setRect(withTitleBarRect);
    setMovable(true);
}

void Window::onStart() {
	homeRect = getRect();
    setAppearance(appearance);

	homeButton = make_shared<WindowHomeButton>();
	ofAddListener(homeButton->clickEvents, this, &Window::onHomeButton);
	addChild(homeButton);

    updateViewRect();
}

// draw before children
void Window::onDraw() {
    // background
    ofFill();
    ofSetColor(appearance.bgColor);
    ofDrawRectangle(0, 0, getWidth(), getHeight());
    
	// title bar
	ofSetColor(appearance.titlebarColor);
	ofDrawRectangle(0, 0, getWidth(), appearance.titlebarHeight);
	ofSetColor(appearance.titleColor);
	ofDrawBitmapString(title, 4, 14);
}

// draw after children
void Window::postDraw() {
	// window outline
	ofNoFill();
	ofSetColor(appearance.outlineColor);
	ofDrawRectangle(0.5, 0.5, getWidth()-1, getHeight()-1);

	// window resize handle
    if (appearance.resizable) {
        ofPushMatrix();
        float size = appearance.cornarHandle;
        ofTranslate(getWidth(), getHeight());
        ofFill();
        ofDrawTriangle(-size, 0, 0, -size, 0, 0);
        ofPopMatrix();
    }
}

void Window::onMousePressed(ofMouseEventArgs& mouse) {
	cornarDragging = false;

	if (!isMouseInside()) return;

	// in titlebar
	// grab titlebar
	if (getMouseY() < appearance.titlebarHeight) {
		// move most top
		auto p = getParent();
		if (p) {
			p->addChild(shared_from_this());
		}
	}

	// not titlebar
	else {
		setMoving(false);

		int cornarSize = appearance.cornarHandle;
		if (appearance.resizable && getMouseX() > getWidth() - cornarSize && getMouseY() > getHeight() - cornarSize) {
			cornarDragging = true;

			// move to most top
			auto p = getParent();
			if (p) {
				p->addChild(shared_from_this());
			}
		}
	}
}

void Window::onMouseDragged(ofMouseEventArgs& mouse) {
	if (cornarDragging) {
		auto move = getMousePos() - getPreviousMousePos();
        float minSize = 20;
		setWidth(MAX(getWidth() + move.x, minSize));
		setHeight(MAX(getHeight() + move.y, minSize + appearance.titlebarHeight));
    }
    else if (getMoving()) {
        auto p = getPos();
        if (p.x < 0 || p.y < 0) {
            setPos(MAX(0, p.x), MAX(0, p.y));
        }
    }
}

void Window::onMouseReleased(ofMouseEventArgs& mouse) {
	cornarDragging = false;
}

void Window::onLocalMatrixChanged() {
    updateViewRect();

	if (homeButton) {
		float margin = 4;
		homeButton->setRect(ofRectangle(getWidth() - appearance.titlebarHeight + margin, margin, appearance.titlebarHeight - margin * 2, appearance.titlebarHeight - margin * 2));
		homeButton->setActive(getRect() != homeRect);
	}

}

void Window::alignTo(Align direction, shared_ptr<Window> other) {
	if (!other) return;
	auto otherRect = other->getRect();
	ofVec2f p;

	switch (direction) {
	case Left:
		p.x = otherRect.x - getWidth();
		p.y = otherRect.y;
		break;
	case Right:
		p.x = otherRect.x + otherRect.width;
		p.y = otherRect.y;
		break;
	case Top:
		p.x = otherRect.x;
		p.y = otherRect.y - getHeight();
		break;
	case Bottom:
		p.x = otherRect.x;
		p.y = otherRect.y + otherRect.height;
		break;
	}

	setPos(p);
}

shared_ptr<View> Window::setView(shared_ptr<View> _view) {
    // if nullptr
    if (!_view) {
        // remove view
        if (view){
            view->destroy();
        }
        return nullptr;
    }
    
    // remove already added view
    if (view) {
        removeChild(view);
    }

    // set
    view = _view;
    addChild(view);

    updateViewRect();
    
    return view;
}

void Window::onHomeButton() {
	// move to home position
	setRect(homeRect);
	setMoving(false);
}

void Window::updateViewRect() {
	if (!view) return;

    // window frame
    int frameWidth = 1;
    
	ofRectangle r;
	r.x = frameWidth;
	r.y = appearance.titlebarHeight + frameWidth;
	r.width = getWidth() - frameWidth * 2;
	r.height = getHeight() - appearance.titlebarHeight - frameWidth * 2;
	view->setRect(r);
}

void WindowHomeButton::onDraw() {
	ofSetColor(120);
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), getHeight());
}

void WindowHomeButton::onMousePressed(ofMouseEventArgs& mouse) {
	if (isMouseInside()) {
		ofNotifyEvent(clickEvents);
	}
}
