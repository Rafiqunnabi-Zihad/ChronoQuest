#include "../include/game.h"
#include "../include/player.h"
#include "../include/combat.h"
#include "../include/savefile.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    Player player;
    int choice;
    const char *saveFile = "savegame.dat";

    srand(time(NULL));

    do {
        clearScreen();
        printf("===================================\n");
        printf("   CHRONOQUEST: REALM OF THE C     \n");
        printf("===================================\n");
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n'); // Clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                createCharacter(&player);
                saveGame(&player, saveFile);
                printf("\nNew game initialized and saved! Press Enter to start...");
                while(getchar() != '\n'); getchar();
                break;

            case 2:
                if (loadGame(&player, saveFile)) {
                    printf("\nGame loaded successfully! Welcome back, %s.\n", player.name);
                } else {
                    printf("\nNo save file found or failed to load.\n");
                }
                printf("Press Enter to continue...");
                while(getchar() != '\n'); getchar();
                break;

            case 3:
                printf("\nExiting ChronoQuest. Goodbye!\n");
                exit(0);

            default:
                printf("\nInvalid choice! Press Enter to retry...");
                while(getchar() != '\n'); getchar();
        }
    } while (1);

    return 0;
}
