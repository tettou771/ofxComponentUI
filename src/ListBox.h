#pragma once
#include "ofxComponent.h"

namespace ofxComponent {
	class ListBox;

	class ListElement : public ofxComponentBase {
		friend ListBox;
	public:
		ListElement();
		shared_ptr<ListBox> getParentBox();
		shared_ptr<ListElement> getPrevious();
		shared_ptr<ListElement> getNext();
		void moveUp();
		void moveDown();
		int getIndex() { return index; }
	protected:
		int index;
		shared_ptr<ListElement> nextElement, previousElement;
	};

	class ListBox : public ofxComponentBase {
	public:
        enum Align {
            Left,
            Center,
            Right,
            FitWidth // resize element to fit width
        };

        ListBox(){}
        ListBox(Align _align) :align(_align){}
        void onStart() override;
		void onLocalMatrixChanged() override;

        void addElement(shared_ptr<ListElement> e);
		void insertElement(shared_ptr<ListElement> e, int index);
		void destroyElement(int index);
		void updateList();

		void setAlign(Align _align) {
			align = _align;
			updateList();
		}

	private:
		vector<shared_ptr<ListElement> > list;
		Align align;
	};
}
