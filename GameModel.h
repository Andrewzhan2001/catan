#ifndef GAMEMODEL
#define GAMEMODEL
#include <string>
#include <vector>
#include "Board.h"
#include "Player.h"

class GameModel {
	int number; // total number of players
	size_t seed = 0; // for random generator
	std::default_random_engine rng{ seed };
	std::vector<std::unique_ptr<Player>> players;
	std::unique_ptr<Board> b;
	int currentTurn = 0;
	int diceNum = 0;

public:
	GameModel(std::string players);
	int getNum() const;
	int getCurrentTurn() const;
	void rollDice();
	void setSeed(size_t n);
	Player* getPlayer(int idx);
	std::string getCurColor();
	Player* getCurPlayer();
	Board* getBoard() const;
	size_t getSeed() const;
	void setTurn(int turn);
	// constructor
	// each player chooses two places for basement
	void initial();
	// switches turn from 1,2,3,4
	void switches();
	// create a residence/road at location x
	/* void create(int x, std::string type); */
	// prints current turn
	void printTurn();
	void printPlayers();
	void printBuildings();
	bool buildRoad();
	bool buildBasement();
	bool upgrade();
	void update();
	void exchange(std::string type, std::string type1, std::string type2);
	bool ifWin();
	// void printData();
	void saveFile(std::string filename = "backup.sv");
	void printBoard() const;
};
#endif