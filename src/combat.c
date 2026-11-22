#include "../include/combat.h"

Enemy generateEnemy(int floor) {
    Enemy e;
    int tier = (floor < 1) ? 1 : floor;
    int roll = rand() % 3;

    if (tier == 1) {
        if (roll == 0) {
            strcpy(e.name, "Cave Rat");
            e.hp = 35;
            e.attack = 8;
            e.defense = 2;
            e.xpReward = 15;
            e.goldReward = 10;
        } else {
            strcpy(e.name, "Goblin Scout");
            e.hp = 45;
            e.attack = 11;
            e.defense = 3;
            e.xpReward = 22;
            e.goldReward = 15;
        }
    } else if (tier <= 3) {
        if (roll == 0) {
            strcpy(e.name, "Dungeon Orc");
            e.hp = 60 + (tier - 2) * 15;
            e.attack = 15 + (tier - 2) * 3;
            e.defense = 5 + (tier - 2) * 2;
            e.xpReward = 35 + (tier - 2) * 10;
            e.goldReward = 28 + (tier - 2) * 10;
        } else {
            strcpy(e.name, "Shadow Stalker");
            e.hp = 55 + (tier - 2) * 15;
            e.attack = 18 + (tier - 2) * 3;
            e.defense = 4 + (tier - 2) * 2;
            e.xpReward = 40 + (tier - 2) * 10;
            e.goldReward = 32 + (tier - 2) * 10;
        }
    } else {
        // Floor 4+ scaling
        strcpy(e.name, (roll == 0) ? "Abyssal Knight" : "Obsidian Drake");
        e.hp = 95 + (tier - 4) * 25;
        e.attack = 22 + (tier - 4) * 5;
        e.defense = 8 + (tier - 4) * 3;
        e.xpReward = 65 + (tier - 4) * 20;
        e.goldReward = 55 + (tier - 4) * 15;
    }

    return e;
}

void advanceFloor(Player *p) {
    p->currentFloor++;
    printf("\nYou descend deeper into the dungeon! Now on Floor %d.\n", p->currentFloor);
}

int startCombat(Player *p, Enemy *e) {
    int choice;
    printf("\nA wild %s (Floor %d) appears!\n", e->name, p->currentFloor);

    while (p->hp > 0 && e->hp > 0) {
        printf("\n--- COMBAT TURN --- (%s: %d HP | %s: %d HP)\n", p->name, p->hp, e->name, e->hp);
        printf("1. Attack\n2. Run Away\nChoose action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int damageToEnemy = (p->attack - e->defense > 0) ? (p->attack - e->defense) : 1;
            e->hp -= damageToEnemy;
            printf("You strike the %s for %d damage!\n", e->name, damageToEnemy);

            if (e->hp <= 0) {
                printf("You defeated the %s! Gained %d XP and %d gold.\n", e->name, e->xpReward, e->goldReward);
                p->xp += e->xpReward;
                p->gold += e->goldReward;
                return 1; // Victory
            }

            int damageToPlayer = (e->attack - p->defense > 0) ? (e->attack - p->defense) : 1;
            p->hp -= damageToPlayer;
            printf("The %s hits you back for %d damage!\n", e->name, damageToPlayer);

            if (p->hp <= 0) {
                printf("You have been slain in combat...\n");
                return 0; // Defeat
            }
        } else {
            printf("You fled from combat safely!\n");
            return -1;
        }
    }
    return 0;
}