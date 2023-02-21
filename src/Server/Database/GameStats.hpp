#ifndef _SERVER_GAME_STATS_HPP
#define _SERVER_GAME_STATS_HPP


class GameStats {
	
	int score;
	int played;
	int wins;

public:

	GameStats(int score=0, int played=0, int wins=0): score(score), played(played), wins(wins) {}

	// To add Stats
	void operator+=(const GameStats& other) {
		score+=other.score;
		played+=other.played;
		wins+=other.wins;
	}

    // Calculate middle score
    int calculateMiddleScore() const {return this->score/this->played;}

    // GETTERS
    int getScore() const { return score; }
    int getPlayed() const { return played; }
    int getWins() const { return wins; }

	// To compare
	bool operator==(const GameStats &other) const { return score==other.score and played==other.played and wins==other.wins; }
	auto operator<=>(const GameStats &other) const { return score <=> other.score; }

	// Write Read
	void write(FILE* file) const {
		fwrite(&(this->score), sizeof(int), 1, file);
		fwrite(&(this->played), sizeof(int), 1, file);
		fwrite(&(this->wins), sizeof(int), 1, file);
	}

	void read(FILE* file) {
		fread(&(this->score), sizeof(int), 1, file);
		fread(&(this->played), sizeof(int), 1, file);
		fread(&(this->wins), sizeof(int), 1, file);
	}

};

#endif
