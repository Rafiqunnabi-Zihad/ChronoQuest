#include "../include/combat.h"

Enemy generateEnemy(int floor) {
    Enemy e;
    if (floor == 1) {
        strcpy(e.name, "Goblin Scout");
        e.hp = 40 + (floor * 5);
        e.attack = 10 + floor;
        e.defense = 3;
        e.xpReward = 20;
        e.goldReward = 15;
    } else {
        strcpy(e.name, "Dungeon Orc");
        e.hp = 60 + (floor * 5);
        e.attack = 15 + floor;
        e.defense = 5;
        e.xpReward = 35;
        e.goldReward = 30;
    }
    return e;
}

int startCombat(Player *p, Enemy *e) {
    int choice;
    printf("\nA wild %s appears!\n", e->name);

    while (p->hp > 0 && e->hp > 0) {
        printf("\n--- COMBAT TURN --- (%s: %d HP | %s: %d HP)\n", p->name, p->hp, e->name, e->hp);
        printf("1. Attack\n2. Run Away\nChoose action: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Player attacks enemy
            int damageToEnemy = (p->attack - e->defense > 0) ? (p->attack - e->defense) : 1;
            e->hp -= damageToEnemy;
            printf("You strike the %s for %d damage!\n", e->name, damageToEnemy);

            if (e->hp <= 0) {
                printf("You defeated the %s! Gained %d XP and %d gold.\n", e->name, e->xpReward, e->goldReward);
                p->xp += e->xpReward;
                p->gold += e->goldReward;
                return 1; // Victory
            }

            // Enemy retaliates
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