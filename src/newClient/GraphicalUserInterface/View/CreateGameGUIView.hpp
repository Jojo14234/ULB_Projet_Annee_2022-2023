#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"

class CreateGameGUIController; // forward declaration

class CreateGameGUIView: public AbstractGUIView {

	// Objects

	public:

	using AbstractGUIView::AbstractGUIView;
	
	~CreateGameGUIView()=default;

	void draw() override {

	}

	friend class CreateGameGUIController;

};