/**
 * Project Untitled
 */

#pragma once

#include <vector>
#include <initializer_list>

#include "AbstractView.hpp"


template <typename StateType>
class MainView {

	std::vector<AbstractView*> views;

	AbstractView* getView(StateType state) {
		return views[static_cast<short>(state)];
	}

public:

	MainView()=default;

	~MainView() { for (auto elem : views) delete elem; }

	void draw(StateType &state) { this->getView(state)->draw(); }

	void setViews(std::initializer_list<AbstractView*> list) { this->views = list; }

};