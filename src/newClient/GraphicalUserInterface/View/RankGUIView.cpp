#include "RankGUIView.hpp"

void RankGUIView::hideTop() {
	top_box.setHidden();
	player1.setHidden();
	player2.setHidden();
	player3.setHidden();
	player4.setHidden();
	player5.setHidden();
	score1.setHidden();
	score2.setHidden();
	score3.setHidden();
	score4.setHidden();
	score5.setHidden();
}

void RankGUIView::showTop() {
	top_box.setVisible();
	player1.setVisible();
	player2.setVisible();
	player3.setVisible();
	player4.setVisible();
	player5.setVisible();
	score1.setVisible();
	score2.setVisible();
	score3.setVisible();
	score4.setVisible();
	score5.setVisible();
}

void RankGUIView::hideMyRank() {
	my_rank_box.setHidden();
	my_player.setHidden();
	my_score.setHidden();
	my_top.setHidden();
}


void RankGUIView::showMyRank() {
		my_rank_box.setVisible();
		my_player.setVisible();
		my_score.setVisible();
		my_top.setVisible();
}

RankGUIView::RankGUIView(sf::RenderWindow* window) : AbstractGUIView(window) {
		this->hideMyRank();
}

void RankGUIView::drawTop() {
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

void RankGUIView::drawMyRank() {
	my_rank_box.draw(*window);
	my_player.draw(*window);
	my_score.draw(*window);
	my_top.draw(*window);
}

void RankGUIView::draw() {
	box_border.draw(*window);
	box.draw(*window);
	rank.draw(*window);
	top.draw(*window);
	my_rank.draw(*window);
	back_button.draw(*window);

	drawTop();
	drawMyRank();
}

void RankGUIView::setUpPlayer(int n, std::string username, int point) {
	switch (n) {
		case 1: this->player1.setString(username); this->score1.setString(std::to_string(point)); break;
		case 2: this->player2.setString(username); this->score2.setString(std::to_string(point)); break;
		case 3: this->player3.setString(username); this->score3.setString(std::to_string(point)); break;
		case 4: this->player4.setString(username); this->score4.setString(std::to_string(point)); break;
		case 5: this->player5.setString(username); this->score5.setString(std::to_string(point)); break;
		default : break;
	}
}

void RankGUIView::setUpMyRank(int n, std::string username, int point) {
	this->my_player.setString(username);
	this->my_top.setString(std::to_string(n));
	this->my_score.setString(std::to_string(point));
}