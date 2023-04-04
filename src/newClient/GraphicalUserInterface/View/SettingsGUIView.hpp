#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"

class SettingsGUIController; // forward declaration

class SettingsGUIView: public AbstractGUIView {

	// Objects

	public:

	using AbstractGUIView::AbstractGUIView;
	
	~SettingsGUIView()=default;

	void draw() override {

	}

	friend class SettingsGUIController;

};