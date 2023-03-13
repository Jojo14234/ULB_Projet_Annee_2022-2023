/**
 * Project Untitled
 */

#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractTerminal.hpp"


class AbstractTerminalView: public AbstractView, public AbstractTerminal {

public: 

	using AbstractView::AbstractView;

	virtual ~AbstractView()=default;

	virtual void draw()=0;

};