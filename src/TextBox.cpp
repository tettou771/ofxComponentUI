#include "TextBox.h"
using namespace ofxComponent;

void TextBox::onStart() {
    updateTextBox();
}

void TextBox::onDraw() {
    ofDrawBitmapString(text, 2, 13.5);
}

void TextBox::onLocalMatrixChanged() {
    updateTextBox();
}

void TextBox::addString(string str, bool needLF) {
    text += str;
    if (needLF) text += '\n';
    updateTextBox();
}

string TextBox::pop() {
    string rt = "";
    
    if (text == "") {
        rt = "";
    } else {
        int appear = text.find_first_of('\n');
        
        // if no LF, erase all
        if (appear == 0) {
            rt = text;
            text = "";
        }
        
        else {
            rt = text.substr(0, appear);
            text = text.substr(appear + 1, text.length() - appear - 1);
        }
    }

    updateTextBox();
    return rt;
}

string TextBox::popBack() {
    string rt = "";
    
    if (text == "") {
        rt = "";
    } else {
        int appear = text.find_last_of('\n');
        
        // if no LF, erase all
        if (appear == 0) {
            rt = text;
            text = "";
        }
        
        else {
            rt = text.substr(appear + 1, text.length() - appear - 1);
            text = text.substr(0, text.length() - appear);
        }
    }

    updateTextBox();
    return rt;
}

void TextBox::setMaxLines(int max) {
    maxLines = max;
}

void TextBox::updateTextBox() {
    // check height
    int lineCount = 1;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '\n') {
            ++lineCount;
        }
    }
    if (maxLines < lineCount) {
        for (int i = maxLines; i < lineCount; ++i) {
            // delete oldest text
            int appear = text.find_first_of('\n');
            
            // if no LF, erase all
            if (appear == 0) {
                text = "";
            }
            else {
                text = text.substr(appear + 1, text.length() - appear - 1);
            }
        }
        lineCount = maxLines;
    }
    
    // check width
    int maxCharCount = 0;
    int charCount;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '\n') {
            maxCharCount = MAX(maxCharCount, charCount);
            charCount = 0;
        }
        else ++charCount;
    }

    // set width/height
    float charWidth = 8;
    setWidth(maxCharCount * charWidth + 2);
    float lineHeight = 13;
    setHeight(lineCount * lineHeight);
    
    auto p = getParent();
    if (p) p->onLocalMatrixChanged();
}
