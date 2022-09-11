# ofxComponentUI

This is in developping project.

ofxComponentUI is extention of [ofxComponent](http://github.com/tettou771/ofxComponent/)

I wanna make window system easily, and growing this addon.

## Features

- Window class, that is Draggable window.
- View class, that is draw area of window (inside of window frame).
- Scroll view, Resizable view, etc
- (TODO) Right click menu

## Usage

Window has a view, but View class is blank normally.

To show your contents, make derived class of View to draw what you wanna, and set to window with Window::setView().

Please read the example for details.
"A" class (defined in ofApp.h) is derived class of View.

![example](/example/screenshot.png)

## Depend addons
- [ofxComponent](http://github.com/tettou771/ofxComponent/)

## Author
[tettou771](http://github.com/tettou771/)
