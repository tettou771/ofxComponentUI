#include "ListBox.h"

using namespace ofxComponent;

ofxComponent::ListElement::ListElement() {
	nextElement = nullptr;
	previousElement = nullptr;
	index = 0;
}

shared_ptr<ListBox> ofxComponent::ListElement::getParentBox() {
	shared_ptr<ListBox> w = nullptr;
	auto child = static_pointer_cast<ofxComponentBase>(shared_from_this());
	while (true) {
		auto p = child->getParent();
		if (!p) return nullptr;

		auto w = dynamic_pointer_cast<ListBox>(p);
		if (w) {
			return w;
		}
		else {
			child = p;
		}
	}

	return nullptr;
}

shared_ptr<ListElement> ofxComponent::ListElement::getPrevious() {
	return previousElement;
}

shared_ptr<ListElement> ofxComponent::ListElement::getNext() {
	return nextElement;
}

void ListElement::moveUp() {
	shared_ptr<ListBox> p;
	if (p = getParentBox()) {
		p->insertElement(static_pointer_cast<ListElement>(shared_from_this()), index - 1);
	}
}

void ListElement::moveDown() {
	shared_ptr<ListBox> p;
	if (p = getParentBox()) {
		p->insertElement(static_pointer_cast<ListElement>(shared_from_this()), index + 1);
	}
}

void ListBox::onLocalMatrixChanged() {
	updateList();
}

void ListBox::addElement(shared_ptr<ListElement> e) {
	insertElement(e, list.size());
}

void ListBox::insertElement(shared_ptr<ListElement> e, int index) {
	if (index < 0) index = 0;
	if (index > list.size()) index = list.size();

	// check is this already listed. if listed, erase it
	auto itr = find(list.begin(), list.end(), e);
	if (itr != list.end()) {
		list.erase(itr);
	}

	list.insert(list.begin() + index, e);
	updateList();
}

void ListBox::destroyElement(int index) {
	if (index < 0 || list.size() <= index) return;
	auto e = list[index];
	if (e) e->destroy();
	updateList();
}

void ListBox::updateList() {
	float maxWidth = 0;
	float y = 0;
	for (int i = 0; i < list.size(); ++i) {
		auto& e = list[i];
		// if destroyed, remove it
		if (e->isDestroyed()) {
			list.erase(list.begin() + i);
			--i;
		}
		else {
			e->index = i;
			addChild(e);
			maxWidth = MAX(maxWidth, e->getWidth());

			// calc position
			ofRectangle r = e->getRect();
			r.y = y;
			switch (align) {
			case Left: r.x = 0; break;
			case Center: r.x = (getWidth() - r.width) / 2; break;
			case Right: r.x = getWidth() - r.width; break;
			case FitWidth: r.x = 0; r.width = getWidth(); break;
			}
			e->setRect(r);

			// increment position to next element
			y += e->getHeight();

			// set next and previous element pointer
			if (i == 0) {
				list[i]->previousElement = nullptr;
			}
			else {
				list[i - 1]->nextElement = e;
				list[i]->previousElement = list[i - 1];
			}
			if (i == list.size() - 1) {
				list[i]->nextElement = nullptr;
			}
		}
	}

	// fit to list
	setHeight(y);
}
