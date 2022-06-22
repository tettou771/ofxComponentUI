#include "FitView.h"

using namespace ofxComponent;

FitView::FitView(){}
FitView::FitView(Mode mode):mode(mode){}

void FitView::onLocalMatrixChanged() {
    if (!contents) return;
    
    float widthScale = getWidth() / contents->getWidth();
    float heightScale = getHeight() / contents->getHeight();
    float scale;
    ofVec2f offset;
    
    bool heightFit;
    switch (mode) {
        case SmallFit:
            heightFit = widthScale >= heightScale;
            break;
        case CropFit:
            heightFit = heightScale >= widthScale;
            break;
    }
    
        if (heightFit) {
            scale = heightScale;
            offset.x = (getWidth() - contents->getWidth() * scale) / 2;
            offset.y = 0;
        } else{
            scale = widthScale;
            offset.x = 0;
            offset.y = (getHeight() - contents->getHeight() * scale) / 2;
        }
    
    contents->setScale(scale);
    contents->setScaleAlignment(Cornar);
    contents->setPos(offset);
}
