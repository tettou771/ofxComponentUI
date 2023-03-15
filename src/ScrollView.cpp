#include "ScrollView.h"
//#include "Window.h"

using namespace ofxComponent;

void ScrollBar::onDraw() {
    if (getWidth() <= 0 || getHeight() <= 0) return;

    ofFill();
    ofSetColor(200, 150);
    float r = MIN(getWidth(), getHeight()) / 2;
    ofDrawRectRounded(0, 0, getWidth(), getHeight(), r);
}

ScrollView::ScrollView() {
	fitMode = None;
	speed = 10;
	barHDragging = barVDragging = false;
	setConstrain(true);
}

ScrollView::ScrollView(FitMode _mode) {
    setFitMode(_mode);
    speed = 10;
    barHDragging = barVDragging = false;
    setConstrain(true);
}

void ScrollView::onStart() {
	barV = make_shared<ScrollBar>();
	barH = make_shared<ScrollBar>();
	addChild(barV);
	addChild(barH);
    onLocalMatrixChanged();
}

void ScrollView::onUpdate() {

}

void ScrollView::onDraw() {

}

void ScrollView::onMouseMoved(ofMouseEventArgs& mosue) {}
void ScrollView::onMousePressed(ofMouseEventArgs& mosue) {
	if (!barH || !barV) return;

	if (barH->getActive() && barH->isMouseInside()) {
		barHDragging = true;
	}
	// H & V is controlled exclusive
	else if (barV->getActive() && barV->isMouseInside()) {
		barVDragging = true;
	}
}

void ScrollView::onMouseDragged(ofMouseEventArgs& mosue) {
	if (!contents || !barH || !barV) return;

	ofVec2f move(ofGetMouseX() - ofGetPreviousMouseX(), ofGetMouseY() - ofGetPreviousMouseY());

	if (barHDragging || barVDragging) {
		if (barHDragging) {
			scrollX(-move.x * contents->getWidth() / getWidth());
		}

		if (barVDragging) {
			scrollY(-move.y * contents->getHeight() / getHeight());
		}
	}
}
void ScrollView::onMouseReleased(ofMouseEventArgs& mosue) {
	barHDragging = barVDragging = false;
}

void ScrollView::onMouseScrolled(ofMouseEventArgs& mouse) {
	if (fitMode == FitHeight) {
		// if this only have horizontal scroll, mouse wheel is horizontal
		scrollX(mouse.scrollY * speed);
	}
	else {
		scrollX(mouse.scrollX * speed);
		scrollY(mouse.scrollY * speed);
	}
}

void ScrollView::onLocalMatrixChanged() {
	if (!contents) return;

	switch (fitMode) {
    case None:
        break;
	case FitWidth:
		contents->setWidth(getWidth());
        break;
	case FitHeight:
		contents->setHeight(getHeight());
		break;
	}

	updateScrollBar();
}

void ScrollView::onSetContents() {
    onLocalMatrixChanged();
}

void ofxComponent::ScrollView::setScrollSpeed(float _speed) {
	speed = MAX(1, _speed);
}

void ScrollView::setFitMode(FitMode _mode) {
	fitMode = _mode;
	onLocalMatrixChanged();
	updateScrollBar();
}

void ScrollView::scrollX(float x) {
	if (!contents) return;

	auto contentsPos = contents->getPos();

	// horizontal scroll
	if (contents->getWidth() <= getWidth()) {
		contentsPos.x = 0;
	}
	else {
		contentsPos.x += x;

		// avoid overrun
		float maxPos = 0;
		float minPos = getWidth() - contents->getWidth();
		contentsPos.x = MIN(MAX(contentsPos.x, minPos), maxPos);
	}

	contents->setPos(contentsPos);

	updateScrollBar();
}

void ScrollView::scrollY(float y) {
	if (!contents) return;

	auto contentsPos = contents->getPos();

	// vertical scroll
	if (contents->getHeight() <= getHeight()) {
		contentsPos.y = 0;
	}
	else {
		contentsPos.y += y;

		// avoid overrun
		float maxPos = 0;
		float minPos = getHeight() - contents->getHeight();
		contentsPos.y = MIN(MAX(contentsPos.y, minPos), maxPos);
	}

	// dominant position
	contentsPos.x = round(contentsPos.x);
	contentsPos.y = round(contentsPos.y);

	contents->setPos(contentsPos);

	updateScrollBar();
}

void ScrollView::updateScrollBar() {
	if (!contents) return;
	if (!barH || !barV) return;

	float barWidth = 6;

	// horizontal
	if (contents->getWidth() <= getWidth()) {
		barH->setActive(false);
	}
	else {
		ofRectangle r;
		r.height = barWidth;
		r.y = getHeight() - barWidth - 1;
		r.width = getWidth() * getWidth() / contents->getWidth() + barWidth;
		r.x = (getWidth() - barWidth) * (-contents->getPos().x) / contents->getWidth();
		barH->setActive(true);
		barH->setRect(r);
	}

	// vertical
	if (contents->getHeight() <= getHeight()) {
		barV->setActive(false);
	}
	else {
		ofRectangle r;
		r.width = barWidth;
		r.x = getWidth() - barWidth - 1;
		r.height = getHeight() * getHeight() / contents->getHeight() + barWidth;
		r.y = (getHeight() - barWidth) * (-contents->getPos().y) / contents->getHeight();
		barV->setActive(true);
		barV->setRect(r);
	}
}
