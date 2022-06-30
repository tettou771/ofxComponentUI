#include "FitView.h"

using namespace ofxComponent;

FitView::FitView(){}

void FitView::onLocalMatrixChanged() {
    updateContentsSize();
}

void FitView::onSetContents() {
    updateContentsSize();
}

void FitView::updateContentsSize() {
    if (!contents) return;

    contents->setWidth(getWidth());
    contents->setHeight(getHeight());
}
