#include "ImageView.h"
using namespace ofxComponent;

ImageView::ImageView() {
}

void ImageView::onUpdate() {
	// reload if file is updated
	int checkIntervalFrameNum = 60;
	if (ofGetFrameNum() % checkIntervalFrameNum == 0 && imgPath != "") {
		// reload image if file timestamp changed
		if (imgLastWriteTime != getFileTime(imgPath)) {
			load(imgPath);
		}
	}

	// load multi files
	loadFromQueueIfNotEmpty();
}

void ImageView::onDraw() {
	TextureView::onDraw();

	if (getTexture()) {
		if (isMouseInside()) {
			ofFill();
			ofSetColor(getPixelColorFromMouse());
			ofDrawCircle(getMouseX(), getMouseY(), 30);
		}
	}
	else {
		string msg = "Drag and Drop here";
		ofDrawBitmapStringHighlight(msg, getWidth() / 2 - msg.length() * 4, getHeight() / 2);
	}

	if (!loadQueue.empty()) {
		ofDrawBitmapStringHighlight("load picture remaining " + ofToString((int)loadQueue.size()), 4, 20);
	}
}

void ImageView::onDragEvent(ofDragInfo& info) {
	if (!isMouseInside()) return;

	for (auto path : info.files) {
		auto file = ofFile(path);
		if (file.isFile() && (
			file.getExtension() == "tif" ||
			file.getExtension() == "png" ||
			file.getExtension() == "jpg" ||
			file.getExtension() == "bmp"
			)
			) {

			loadQueue.push(file);
		}
	}
}

ofTexture* ImageView::getTexture() {
	if (img.isAllocated()) return &img.getTexture();
	else return nullptr;
}

ofFloatColor ImageView::getPixelColor(ofVec2f pos) {
	if (pos.x < 0 || img.getWidth() <= pos.x ||
		pos.y < 0 || img.getHeight() <= pos.y) {
		return ofFloatColor();
	}
	return img.getColor(pos.x, pos.y);
}

ofFloatColor ImageView::getPixelColorFromMouse() {
	ofVec2f p(
		getMouseX() * img.getWidth() / getWidth(),
		getMouseY() * img.getHeight() / getHeight()
	);
	return getPixelColor(p);
}

void ImageView::load(string path) {
	img.load(path);
	imgPath = path;
	imgLastWriteTime = getFileTime(imgPath);
	if (img.isAllocated()) {
		// delete opacity
		auto pixels = img.getPixels();
		int channels = pixels.getNumChannels();
		if (channels == 4) {
			for (int i = 3; i < pixels.size(); i += channels) {
				pixels[i] = 1.0;
			}
			img.update();
			img.setFromPixels(pixels);
		}

		if (fileInfo) {
			*fileInfo = imgPath;
		}

		notifyTextureChanged();
	}
	else {
		ofLogError() << "image file is not valid. " << path;
		imgPath = "";
		imgLastWriteTime = 0;
	}

    // show filename to titlebar
    auto w = getParentWindow();
    if (w) {
        string fileName = ofFile(path).getFileName();
        w->setTitleAttribute(fileName);
    }
}

long long ImageView::getFileTime(string path) {
#ifdef WIN32
	// how to get timestamp on windows
	// https://ameblo.jp/sgl00044/entry-12554456575.html

	FILETIME ftCreate, ftWrite, ftAccess, ftLocal;
	auto hFile = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		ofLogWarning() << "file not found " << path;
		return 0;
	}

	// get timestamp
	if (!(GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))) {
		ofLogWarning() << "file timestamp get fault " << path;
		CloseHandle(hFile);
		return 0;
	}
	CloseHandle(hFile);

	ULARGE_INTEGER intTime;
	intTime.HighPart = ftWrite.dwHighDateTime;
	intTime.LowPart = ftWrite.dwLowDateTime;

	return intTime.QuadPart;
#else
    return 0;
#endif
}

void ImageView::loadFromQueueIfNotEmpty() {
	if (!loadQueue.empty()) {
		load(loadQueue.front().getAbsolutePath());
		loadQueue.pop();
	}
}
