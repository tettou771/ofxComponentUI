#include "Window.h"

using namespace ofxComponent;

void View::setContents(shared_ptr<ofxComponentBase> _contents) {
    if (!_contents) return;
    
    // if already exists, remove content
    if (contents) {
        removeChild(contents);
    }
    
    contents = _contents;
    
    // insert before scroll bars
    insertChild(contents, 0);
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
	auto withTitleBarRect = _rect;
	withTitleBarRect.height += titleBarHeight;
	setRect(withTitleBarRect);
}

void Window::onStart() {
	setDraggable(true);
	homeRect = getRect();

	homeButton = make_shared<WindowHomeButton>();
	ofAddListener(homeButton->clickEvents, this, &Window::onHomeButton);
	addChild(homeButton);

    updateViewRect();
}

// draw before children
void Window::onDraw() {
	// title bar
	ofSetColor(50);
	ofFill();
	ofDrawRectangle(0, 0, getWidth(), titleBarHeight);
	ofSetColor(200);
	if (titleAttribute == "") {
		ofDrawBitmapString(title, 4, 14);
	}
	else {
		ofDrawBitmapString(title + " - " + titleAttribute, 4, 14);
	}
}

// draw after children
void Window::postDraw() {
	// window outline
	ofNoFill();
	ofSetColor(100);
	ofDrawRectangle(0.5, 0.5, getWidth()-1, getHeight()-1);

	// window scale handle
	ofPushMatrix();
	float margin = 4;
	float size = titleBarHeight - margin * 2;
	ofTranslate(getWidth() - margin, getHeight() - margin);
	ofNoFill();
	ofDrawTriangle(-size, 0, 0, -size, 0, 0);
	ofPopMatrix();
}

void Window::onMousePressed(ofMouseEventArgs& mouse) {
	cornarDragging = false;

	if (!isMouseInside()) return;

	// in titlebar
	// grab titlebar
	if (getMouseY() < titleBarHeight) {
		// move most top
		auto p = getParent();
		if (p) {
			p->addChild(shared_from_this());
		}
	}

	// not titlebar
	else {
		setDragging(false);

		int cornarSize = titleBarHeight;
		if (getMouseX() > getWidth() - cornarSize && getMouseY() > getHeight() - cornarSize) {
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
		setHeight(MAX(getHeight() + move.y, minSize + titleBarHeight));
    }
    else if (getDragging()) {
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
		homeButton->setRect(ofRectangle(getWidth() - titleBarHeight + margin, margin, titleBarHeight - margin * 2, titleBarHeight - margin * 2));
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

void Window::setView(shared_ptr<View> _view) {
    // ignore if nullptr
    if (!_view) return;

    // remove already added view
    if (view) {
        removeChild(view);
    }

    // set
    view = _view;
    addChild(view);

    updateViewRect();
}

void Window::onHomeButton() {
	// move to home position
	setRect(homeRect);
	setDragging(false);
}

void Window::updateViewRect() {
	if (!view) return;

	ofRectangle r;
	r.x = 0;
	r.y = titleBarHeight;
	r.width = getWidth();
	r.height = getHeight() - titleBarHeight;
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
