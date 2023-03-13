/**
 * Project Untitled
 */

#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractUI.hpp"
#include "../configs.hpp"


class AbstractUIView: public AbstractView, public AbstractUI {

public:
	
	using AbstractView::AbstractView;

	virtual ~AbstractUIView()=default;

	virtual void draw()=0;

};