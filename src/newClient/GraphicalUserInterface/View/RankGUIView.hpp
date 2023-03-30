#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"
#include "Objects/TextButton.hpp"

class RankGUIController; // forward declaration

class RankGUIView: public AbstractGUIView {

	// Texts
	Text rank {ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 145.f/788.f, (WINDOW_WIDTH/2.f- ((WINDOW_WIDTH/4.f)/3)) , WINDOW_HEIGHT/10.f), "Ranking"};

	// Boxes
	Box box {ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f - 50 , WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), WHITE};
	Box top_box {ObjectInfo<>(WINDOW_WIDTH/3.f + 16, WINDOW_WIDTH/4.f + 50, WINDOW_WIDTH/3.f - 5 , WINDOW_HEIGHT/3.f), TOP_BOX_COLOR};

	// Borders
	Border box_border {box, 10, BLACK};
	Border top_box_border {top_box, 3, BLACK};
	
	

	// TextButtons
	// (ObjectInfo<>(width, height, x, y) de la box, ObjectInfo<>(width, height, x, y) du texte, text, text_color, background_color
	TextButton top {ObjectInfo<>(WINDOW_WIDTH/15, WINDOW_WIDTH/40, WINDOW_WIDTH/3.f - 5 , WINDOW_HEIGHT/4.f-10), ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50 , WINDOW_WIDTH/3.f , WINDOW_HEIGHT/4.f - 10), "TOP 5", BLACK, RANK_COLOR}; 
	TextButton my_rank {ObjectInfo<>(WINDOW_WIDTH/12 + 5, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f + 140 , WINDOW_HEIGHT/4.f-10), ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50 , WINDOW_WIDTH/2.f + 145 , WINDOW_HEIGHT/4.f - 10), "My Rank", BLACK, RANK_COLOR};

public:

	using AbstractGUIView::AbstractGUIView;
	
	~RankGUIView()=default;

	void draw() override {
		box_border.draw(*window);
		box.draw(*window);
		rank.draw(*window);

		top.draw(*window);
		my_rank.draw(*window);

		top_box_border.draw(*window);
		top_box.draw(*window);


	}

	friend class RankGUIController;

};