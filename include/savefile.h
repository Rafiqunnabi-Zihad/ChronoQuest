#ifndef SAVEFILE_H
#define SAVEFILE_H

#include "game.h"

void saveGame(const Player *p, const char *filename);
int loadGame(Player *p, const char *filename);

#endif