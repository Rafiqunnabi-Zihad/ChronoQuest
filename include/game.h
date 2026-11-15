#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct for Player Character
typedef struct {
    char name[50];
    char charClass[20]; // Warrior, Mage, Rogue
    int level;
    int hp;
    int maxHp;
    int mana;
    int maxMana;
    int attack;
    int defense;
    int gold;
    int xp;
    int currentFloor;
} Player;

// Struct for Enemy
typedef struct {
    char name[50];
    int hp;
    int attack;
    int defense;
    int xpReward;
    int goldReward;
} Enemy;

#endif