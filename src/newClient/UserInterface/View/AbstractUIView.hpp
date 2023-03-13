/**
 * Project Untitled
 */

#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractUI.hpp"
#include "../configs.hpp"


class AbstractUIView: public AbstractView<STATE>, public AbstractUI {

public:
	
	using AbstractView<STATE>::AbstractView;

	virtual ~AbstractView()=default;

	virtual void draw()=0;

};