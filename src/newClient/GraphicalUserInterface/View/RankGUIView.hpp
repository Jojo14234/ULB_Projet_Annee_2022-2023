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
	Text player1 {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/18.f), "", WHITE};
	Text player2 {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/30.f), "", WHITE};
	Text player3 {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/8.18f), "", WHITE};
	Text player4 {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/4.73f), "", WHITE};
	Text player5 {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/3.33f), "", WHITE};
	Text score1 {ObjectInfo<>(WINDOW_WIDTH/60.f, WINDOW_HEIGHT/33.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/20.f), "", WHITE};
	Text score2 {ObjectInfo<>(WINDOW_WIDTH/60.f, WINDOW_HEIGHT/33.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/25.71f), "", WHITE};
	Text score3 {ObjectInfo<>(WINDOW_WIDTH/60.f, WINDOW_HEIGHT/33.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/7.82f), "", WHITE};
	Text score4 {ObjectInfo<>(WINDOW_WIDTH/60.f, WINDOW_HEIGHT/33.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/4.61f), "", WHITE};
	Text score5 {ObjectInfo<>(WINDOW_WIDTH/60.f, WINDOW_HEIGHT/33.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/3.27f), "", WHITE};

		// my rank
	Text my_player {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f + WINDOW_WIDTH/26.6f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/18.f), "PlayerMyRank", WHITE};
	Text my_score {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/6.95f, WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/20.f), "1", WHITE};
	Text my_top {ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/3.f - WINDOW_WIDTH/228.57f , WINDOW_HEIGHT/2.f - WINDOW_HEIGHT/18.f), "100", BLACK};


	//Boxe
	Box box {ObjectInfo<>(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/3.f , WINDOW_WIDTH/4.f , WINDOW_HEIGHT/10.f), WHITE};

	//Border
	Border box_border {box, 10, BLACK};
	
	//Image
	Image top_box{ObjectInfo<>(WINDOW_WIDTH/4.f + WINDOW_WIDTH/8.f, WINDOW_HEIGHT/2.f + WINDOW_HEIGHT/30.f, WINDOW_WIDTH/3.f - WINDOW_WIDTH/53.33f , WINDOW_HEIGHT/3.f), RANK_PATH};
	Image my_rank_box{ObjectInfo<>(WINDOW_WIDTH/4.f + WINDOW_WIDTH/8.f, WINDOW_HEIGHT/6.f + WINDOW_HEIGHT/60.f, WINDOW_WIDTH/3.f - WINDOW_WIDTH/53.33f , WINDOW_HEIGHT/3.f), MY_RANK_PATH};

	//Image Button
	ImageButton back_button{ObjectInfo<>(WINDOW_WIDTH/10.f, WINDOW_HEIGHT/4.f, WINDOW_WIDTH/4.f + WINDOW_WIDTH/200.f ,WINDOW_HEIGHT/20.f), BACK_BUTTON_PATH};

	//TextButtons
	// (ObjectInfo<>(width, height, x, y) de la box, ObjectInfo<>(width, height, x, y) du texte, text, text_color, background_color
	TextButton top {ObjectInfo<>(WINDOW_WIDTH/15.f, WINDOW_HEIGHT/30.f + WINDOW_HEIGHT/90.f, WINDOW_WIDTH/3.f - WINDOW_WIDTH/320.f , WINDOW_HEIGHT/4.f-WINDOW_HEIGHT/90.f), ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f , WINDOW_WIDTH/3.f , WINDOW_HEIGHT/4.f - WINDOW_HEIGHT/90.f), "TOP 5", BLACK, RANK_COLOR}; 
	TextButton my_rank {ObjectInfo<>(WINDOW_WIDTH/12.f + WINDOW_WIDTH/320.f, WINDOW_HEIGHT/30.f + WINDOW_HEIGHT/90.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/11.42f , WINDOW_HEIGHT/4.f-WINDOW_HEIGHT/90.f), ObjectInfo<>(WINDOW_WIDTH/50.f, WINDOW_HEIGHT/28.f, WINDOW_WIDTH/2.f + WINDOW_WIDTH/11.03f , WINDOW_HEIGHT/4.f - WINDOW_HEIGHT/90.f), "My Rank", BLACK, RANK_COLOR};

	

	void hideTop();

	void showTop();

	void hideMyRank();

	void showMyRank();


public:

	explicit RankGUIView(sf::RenderWindow* window);
	~RankGUIView()=default;

	
	void drawTop();

	void drawMyRank();

	void draw() override;

	void setUpPlayer(int n, std::string username, int point);

	void setUpMyRank(int n, std::string username, int point);

	friend class RankGUIController;

};