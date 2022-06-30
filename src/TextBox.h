#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
class TextBox : public ofxComponentBase {
public:
    // ofxComponentBase
    void onStart() override;
    void onDraw() override;
    void onLocalMatrixChanged() override;
    
    // TextBox
    void addString(string str, bool needLF = true);
    void clear();
    string pop(); // erase first line
    string popBack(); // erase last line
    void setMaxLines(int max); // -1 means infinity
    int getMax(){return maxLines;}
    
private:
    string text;
    int maxLines = -1;
    void updateTextBox();
};
}
