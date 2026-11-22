#include "../include/game.h"
#include "../include/player.h"
#include "../include/combat.h"
#include "../include/savefile.h"

void clearScreen(void) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void waitForEnter(void) {
    char buf[16];
    printf("Press Enter to continue...");
    fflush(stdout);
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        printf("\n[Input stream closed / EOF detected]\n");
    }
}

void gameSession(Player *player, const char *saveFile) {
    char input[64];
    int choice;

    do {
        clearScreen();
        displayCharacter(player);
        printf("\n--- ADVENTURE MENU ---\n");
        printf("1. Explore Dungeon (Battle on Floor %d)\n", player->currentFloor);
        printf("2. Descend to Next Floor (Floor %d)\n", player->currentFloor + 1);
        printf("3. Save Progress\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            return;
        }
        if (sscanf(input, "%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1: {
                Enemy enemy = generateEnemy(player->currentFloor);
                int result = startCombat(player, &enemy);
                if (result == 1) {
                    saveGame(player, saveFile);
                    printf("\nProgress auto-saved!\n");
                } else if (result == 0) {
                    player->hp = player->maxHp;
                    printf("\nYou woke back up at camp.\n");
                }
                waitForEnter();
                break;
            }
            case 2:
                saveGame(player, saveFile);
                printf("\nGame saved to '%s'!\n", saveFile);
                waitForEnter();
                break;
            case 3:
                return;
            default:
                printf("\nInvalid choice!\n");
                waitForEnter();
                break;
        }
    } while (1);
}

int main(void) {
    Player player;
    char input[64];
    int choice;
    const char *saveFile = "savegame.dat";

    srand((unsigned int)time(NULL));

    do {
        clearScreen();
        printf("===================================\n");
        printf("   CHRONOQUEST: REALM OF THE C     \n");
        printf("===================================\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            return 0;
        }

        if (sscanf(input, "%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            waitForEnter();
            continue;
        }

        switch (choice) {
            case 1:
                createCharacter(&player);
                saveGame(&player, saveFile);
                printf("\nNew game initialized and saved!\n");
                waitForEnter();
                gameSession(&player, saveFile);
                break;

            case 2:
                if (loadGame(&player, saveFile)) {
                    printf("\nGame loaded successfully! Welcome back, %s.\n", player.name);
                    waitForEnter();
                    gameSession(&player, saveFile);
                } else {
                    printf("\nNo save file found or failed to load.\n");
                    waitForEnter();
                }
                break;

            case 3:
                printf("\nExiting ChronoQuest. Goodbye!\n");
                return 0;

            default:
                printf("\nInvalid choice!\n");
                waitForEnter();
                break;
        }
    } while (1);

    return 0;
}