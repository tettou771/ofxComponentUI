#include "StretchView.h"

using namespace ofxComponent;

StretchView::StretchView(){}
StretchView::StretchView(Mode mode):mode(mode){}

void ofxComponent::StretchView::onStart() {
    updateContentsSize();
}

void StretchView::onLocalMatrixChanged() {
    updateContentsSize();
}

void ofxComponent::StretchView::onDestroy() {
    if (onContentsLocalMatrixChangedResistored) {
        ofRemoveListener(contents->localMatrixChangedEvents, this, &StretchView::onContentsLocalMatrixChanged);
    }
}

void ofxComponent::StretchView::onContentsLocalMatrixChanged() {
    updateContentsSize();
}

void StretchView::updateContentsSize() {
    if (!contents) return;

    float widthScale = getWidth() / contents->getWidth();
    float heightScale = getHeight() / contents->getHeight();
    float scale;
    ofVec2f offset;

    bool useHeightScale;
    switch (mode) {
    case NoCrop:
        useHeightScale = widthScale >= heightScale;
        break;
    case Crop:
        useHeightScale = heightScale >= widthScale;
        break;
    case Width:
        useHeightScale = false;
        break;
    case Height:
        useHeightScale = true;
        break;
    }

    if (useHeightScale) {
        scale = heightScale;
        offset.x = (getWidth() - contents->getWidth() * scale) / 2;
        offset.y = 0;
    }
    else {
        scale = widthScale;
        offset.x = 0;
        offset.y = (getHeight() - contents->getHeight() * scale) / 2;
    }

    contents->setScale(scale);
    contents->setScaleAlignment(Cornar);
    contents->setPos(offset);
}

void StretchView::onSetContents() {
    ofAddListener(contents->localMatrixChangedEvents, this, &StretchView::onContentsLocalMatrixChanged);
    onContentsLocalMatrixChangedResistored = true;
    updateContentsSize();
}

void StretchView::setMode(Mode _mode) {
    mode = _mode;
    updateContentsSize();
}
