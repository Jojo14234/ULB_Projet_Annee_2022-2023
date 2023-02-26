#ifndef _CONNECTION_VIEW_HPP
#define _CONNECTION_VIEW_HPP

#include "AbstractView.hpp"
#include "Object/InputBox.hpp"
#include "Object/HiddenInputBox.hpp"


class ConnectionView : public AbstractView {

	InputBox username{ObjectInfo{2, 20, 5, (COLS-20)/2}};
	HiddenInputBox password{ObjectInfo{2, 20, 10, (COLS -20)/2}};

public:

	using AbstractView::AbstractView;
	
	void draw() override {
		// TODO: implement
		username.draw();
		password.draw();
	}

};

#endif
