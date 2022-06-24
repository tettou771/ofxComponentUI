#include "FitView.h"

using namespace ofxComponent;

FitView::FitView(){}

void FitView::onLocalMatrixChanged() {
    if (!contents) return;

    contents->setWidth(getWidth());
    contents->setHeight(getHeight());
}
