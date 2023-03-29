#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractCUI.hpp"


class AbstractCUIView: public AbstractView, public AbstractCUI {

public: 

	using AbstractView::AbstractView;

	virtual ~AbstractCUIView()=default;

	virtual void draw()=0;

};