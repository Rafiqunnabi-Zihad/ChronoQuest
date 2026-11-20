#include "../include/player.h"

void createCharacter(Player *p) {
    int classChoice;
    printf("\n--- CHARACTER CREATION ---\n");
    printf("Enter your hero's name: ");
    scanf("%49s", p->name);

    printf("Choose your Class:\n");
    printf("1. Warrior (High HP, High Attack)\n");
    printf("2. Mage (High Mana, Spellcasting)\n");
    printf("3. Rogue (Balanced, High Critical chance)\n");
    printf("Select class (1-3): ");
    scanf("%d", &classChoice);

    p->level = 1;
    p->xp = 0;
    p->gold = 50;
    p->currentFloor = 1;

    switch (classChoice) {
        case 1:
            strcpy(p->charClass, "Warrior");
            p->maxHp = 120; p->hp = 120;
            p->maxMana = 30; p->mana = 30;
            p->attack = 18; p->defense = 10;
            break;
        case 2:
            strcpy(p->charClass, "Mage");
            p->maxHp = 80; p->hp = 80;
            p->maxMana = 100; p->mana = 100;
            p->attack = 22; p->defense = 5;
            break;
        default:
            strcpy(p->charClass, "Rogue");
            p->maxHp = 100; p->hp = 100;
            p->maxMana = 50; p->mana = 50;
            p->attack = 15; p->defense = 8;
            break;
    }
}

void displayCharacter(const Player *p) {
    printf("\n=== HERO STATS ===");
    printf("\nName: %s (%s)", p->name, p->charClass);
    printf("\nLevel: %d | XP: %d", p->level, p->xp);
    printf("\nHP: %d/%d | Mana: %d/%d", p->hp, p->maxHp, p->mana, p->maxMana);
    printf("\nAttack: %d | Defense: %d", p->attack, p->defense);
    printf("\nGold: %d | Floor: %d\n", p->gold, p->currentFloor);
}