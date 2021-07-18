#ifndef CONTROLLER
#define CONTROLLER
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
class SetBoardStrategy;

class Controller{
  size_t seed = 0;
 public:
  void setseed(size_t seed); // set the seed for random value;
  void loadStrategy(SetBoardStrategy sbs); // use stategy sbs to load the board
  void play();// start the game
};
#endif