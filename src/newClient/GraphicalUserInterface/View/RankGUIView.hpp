#pragma once

#include "AbstractGUIView.hpp"
#include "Objects.hpp"
#include "AssetsPath.hpp"
#include "configs.hpp"

class RankGUIController; // forward declaration

class RankGUIView: public AbstractGUIView {

	//Texts
	Text rank {ObjectInfo<>(WINDOW_WIDTH/4.f, WINDOW_WIDTH/4.f * 145.f/788.f, (WINDOW_WIDTH/2.f- ((WINDOW_WIDTH/4.f)/3)) , WINDOW_HEIGHT/10.f), "Ranking"};

		// top 5
	Text player1 {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f - 50), "Player12345678912345678", WHITE};
	Text player2 {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f + 30), "Player12345678912345678", WHITE};
	Text player3 {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f + 110), "Player12345678912345678", WHITE};
	Text player4 {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f + 190), "Player12345678912345678", WHITE};
	Text player5 {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f + 270), "Player12345678912345678", WHITE};
	Text score1 {ObjectInfo<>(WINDOW_WIDTH/60, WINDOW_WIDTH/60, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f - 45), "1234", WHITE};
	Text score2 {ObjectInfo<>(WINDOW_WIDTH/60, WINDOW_WIDTH/60, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f + 35), "123456", WHITE};
	Text score3 {ObjectInfo<>(WINDOW_WIDTH/60, WINDOW_WIDTH/60, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f + 115), "123456", WHITE};
	Text score4 {ObjectInfo<>(WINDOW_WIDTH/60, WINDOW_WIDTH/60, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f + 195), "123456", WHITE};
	Text score5 {ObjectInfo<>(WINDOW_WIDTH/60, WINDOW_WIDTH/60, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f + 275), "123456", WHITE};

		// my rank
	Text my_player {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f + 60, WINDOW_HEIGHT/2.f - 50), "PlayerMyRank", WHITE};
	Text my_score {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/2.f + 210, WINDOW_HEIGHT/2.f - 45), "1", WHITE};
	Text my_top {ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50, WINDOW_WIDTH/3.f - 15 , WINDOW_HEIGHT/2.f - 50), "100", BLACK};


	//Boxe
	Box box {ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_WIDTH/2.f - 50 , WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), WHITE};

	//Border
	Border box_border {box, 10, BLACK};
	
	//Image
	Image top_box{ObjectInfo<>(WINDOW_WIDTH/4.f + 200, WINDOW_WIDTH/4.f + 80, WINDOW_WIDTH/3.f - 30 , WINDOW_HEIGHT/3.f), RANK_PATH};
	Image my_rank_box{ObjectInfo<>(WINDOW_WIDTH/4.f + 200, WINDOW_WIDTH/8.f - 35, WINDOW_WIDTH/3.f - 30 , WINDOW_HEIGHT/3.f), MY_RANK_PATH};

	//Image Button
	ImageButton back_button{ObjectInfo<>(WINDOW_WIDTH/16.f, WINDOW_HEIGHT/16.f, 410,100), BACK_BUTTON_PATH};

	//TextButtons
	// (ObjectInfo<>(width, height, x, y) de la box, ObjectInfo<>(width, height, x, y) du texte, text, text_color, background_color
	TextButton top {ObjectInfo<>(WINDOW_WIDTH/15, WINDOW_WIDTH/40, WINDOW_WIDTH/3.f - 5 , WINDOW_HEIGHT/4.f-10), ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50 , WINDOW_WIDTH/3.f , WINDOW_HEIGHT/4.f - 10), "TOP 5", BLACK, RANK_COLOR}; 
	TextButton my_rank {ObjectInfo<>(WINDOW_WIDTH/12 + 5, WINDOW_WIDTH/40, WINDOW_WIDTH/2.f + 140 , WINDOW_HEIGHT/4.f-10), ObjectInfo<>(WINDOW_WIDTH/50, WINDOW_WIDTH/50 , WINDOW_WIDTH/2.f + 145 , WINDOW_HEIGHT/4.f - 10), "My Rank", BLACK, RANK_COLOR};

public:

	using AbstractGUIView::AbstractGUIView;
	
	~RankGUIView()=default;

	void drawTopBox() {
		top_box.draw(*window);

		player1.draw(*window);
		player2.draw(*window);
		player3.draw(*window);
		player4.draw(*window);
		player5.draw(*window);
		score1.draw(*window);
		score2.draw(*window);
		score3.draw(*window);
		score4.draw(*window);
		score5.draw(*window);
	}

	void drawMyRankBox() {
		
		my_rank_box.draw(*window);

		my_player.draw(*window);
		my_score.draw(*window);
		my_top.draw(*window);
	}

	void draw() override {
		box_border.draw(*window);
		box.draw(*window);
		rank.draw(*window);

		top.draw(*window);
		my_rank.draw(*window);
		
		back_button.draw(*window);


	}

	friend class RankGUIController;

};