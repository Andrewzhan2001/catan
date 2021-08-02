#include <string>
#include <fstream>
#include <memory>
#include "SetBoardStrategy.h"
#include "Controller.h"
#include "GameModel.h"

using namespace std;

Controller::Controller(): gm{make_unique<GameModel>()}{}

void Controller::setseed(size_t seed) {
  this->seed = seed;
  gm->setSeed(seed);
}

void Controller::loadStrategy(SetBoardStrategy *sbs) {
  sbs->loadBoard(gm.get());
}

void Controller::saveFile(std::string fname) {
  gm->saveFile(fname);
}

bool Controller::play() {
  // at beginning of game, assign each player with two basements
  gm->initial();
  gm->printBoard();
  while (!gm->ifWin()) {
    cout << "Builder " << gm->getCurColor() << "'s turn." << endl;
    gm->printTurn();
    while (true) {
      std::string cmd;
      if(!(gm->getCurPlayer()->chooseCommand(cmd))) {
        saveFile();
        return false;
      } else if (cmd == "load" || cmd == "fair") {
        gm->getCurPlayer()->setDice(cmd);
      } else if (cmd == "roll") {
        gm->rollDice();
        // This ends the "Beginning of the turn".
        break;
      } else {
        cout << "Invalid command." << endl;
      }
    }
    gm->update();
    while (true) {
      std::string cmd;
      if (!(gm->getCurPlayer()->chooseCommand(cmd))) {
        saveFile();
        return false;
      }
      if (cmd == "board") {
        gm->printBoard();
      } else if (cmd == "status") {
        gm->printPlayers();
      } else if (cmd == "residences") {
        gm->printBuildings();
      } else if (cmd == "build-road") {
        int idx;
        if(!(gm->getCurPlayer()->chooseRoad(idx, gm->getBoard()))) {
          saveFile();
          return false;
        }
        if (idx >= gm->getBoard()->getRoadNum() || idx < 0) {
          std::cout << "Invalid road number! Please input again!" << std::endl;
        } else {
          gm->buildRoad(idx);
        }
      } else if (cmd == "build-res") {
        int idx;
        if (!(gm->getCurPlayer()->chooseVertex(idx, gm->getBoard()))) {
          saveFile();
          return false;
        }
        gm->buildBasement(idx);
      } else if (cmd == "improve") {
        int idx;
        if(!(gm->getCurPlayer()->chooseVertex(idx, gm->getBoard()))) {
          saveFile();
          return false;
        }
        gm->upgrade(idx);
      } else if (cmd == "trade") {
        std::string color;
        std::string give;
        std::string take;
        std::vector<std::string> v;
        for (int i = 0; i < gm->getNum(); ++i) {
          if (i != gm->getCurrentTurn()) {
            v.emplace_back(gm->getPlayer(i)->getColor());
          }
        }
        cout << "Player " << gm->getCurPlayer()->getColor();
        cout << " could choose from [";
        for (unsigned int j = 0; j < v.size(); ++j) {
          cout << gm->getPlayer(j)->getColor();
          if (j != v.size() - 1);
          cout << ",";
        }
        cout << "]" << endl;
        if (gm->getCurPlayer()->chooseColor(color, v)) {
          saveFile();
          return false;
        }
        if (gm->getCurPlayer()->chooseResource(give)) {
          saveFile();
          return false;
        }
        if (gm->getCurPlayer()->chooseResource(take)) {
          saveFile();
          return false;
        }
        gm->exchange(color, give, take);
      } else if (cmd == "next") {
        gm->switches();
        break;
      } else if (cmd == "save") {
        std::string name;
        cin >> name;
        if (cin.eof()) {
          saveFile();
          return false;
        }
        saveFile(name);
        return false;
      } else if (cmd == "help") {
        cout << "Valid commands:" << endl;
        cout << "board" << endl;
        cout << "status" << endl;
        cout << "residences" << endl;
        cout << "build-road <edge#>" << endl;
        cout << "build-res <housing#>" << endl;
        cout << "improve <housing#>" << endl;
        cout << "trade <colour> <give> <take>" << endl;
        cout << "next" << endl;
        cout << "save <file>" << endl;
        cout << "help" << endl;
      } else {
        cout << "Invalid Command." << endl;
      }
    }
  }
  cout << "Would you like to play again?" << endl;
  std::string cmd2;
  if (!(gm->getCurPlayer()->answer(cmd2))) {
    saveFile();
    return false; 
  }
  if (cmd2 == "yes") {
    return true;
  } else if (cmd2 == "no") {
    return false;
  } 
}

void Controller::print() {
  Board *bb = gm->getBoard();
  bb->printBoard(std::cout);
}