#include "FitView.h"

using namespace ofxComponent;

FitView::FitView(){}

void FitView::onStart() {
    updateContentsSize();
}

void FitView::onLocalMatrixChanged() {
    updateContentsSize();
}

void ofxComponent::FitView::onDestroy() {
    if (onContentsLocalMatrixChangedResistored) {
        ofRemoveListener(contents->localMatrixChangedEvents, this, &FitView::onContentsLocalMatrixChanged);
    }
}

void ofxComponent::FitView::onContentsLocalMatrixChanged() {
    updateContentsSize();
}

void FitView::onSetContents() {
    ofAddListener(contents->localMatrixChangedEvents, this, &FitView::onContentsLocalMatrixChanged);
    onContentsLocalMatrixChangedResistored = true;
    updateContentsSize();
}

void FitView::updateContentsSize() {
    if (!contents) return;

    contents->setWidth(getWidth());
    contents->setHeight(getHeight());
}
