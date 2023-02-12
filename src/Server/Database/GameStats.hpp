#ifndef _GAME_STATS_HPP
#define _GAME_STATS_HPP


class GameStats {
	
	int score;
	int played;
	int wins;

public:

	GameStats(int score=0, int played=0, int wins=0): score(score), played(played), wins(wins) {}

	void operator+=(const GameStats& other) {
		score+=other.score;
		played+=other.played;
		wins+=other.wins;
	}

	bool operator==(const GameStats &other) const { return score==other.score and played==other.played and wins==other.wins; }
	auto operator<=>(const GameStats &other) const { return score <=> other.score; }

	int getScore() const { return score; }
	int getPlayed() const { return played; }
	int getWins() const { return wins; }
	
};

#endif