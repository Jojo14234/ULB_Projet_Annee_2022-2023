#pragma once

#include "../../View/AbstractView.hpp"
#include "../AbstractCUI.hpp"
#include "../../Model/Client.hpp"


class AbstractCUIView: public AbstractView, public AbstractCUI {

public: 

	AbstractCUIView(): AbstractView(), AbstractCUI(){}

	virtual ~AbstractCUIView()=default;

	virtual void draw()=0;

};