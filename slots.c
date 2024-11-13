#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(seconds) Sleep((seconds) * 1000)
#else
    #include <unistd.h>
    #define SLEEP(seconds) sleep(seconds)
#endif

const char *symbols[] = {"7", "$", "£", "#", "X"};
const int numSymbols = sizeof(symbols) / sizeof(symbols[0]);

int sevenCount = 0;

const char* spinReel() {
    const char *selected_sym = symbols[rand() % numSymbols];

    if (strcmp(selected_sym, "7") == 0) {
        sevenCount++;
    }

    if (sevenCount == 2) {
        selected_sym = symbols[rand() % numSymbols];
        sevenCount == 0;
    }

    return selected_sym;
}


int calculatePrize(const char *reel1, const char *reel2, const char *reel3) {
    if (reel1 == reel2 && reel2 == reel3) {
        if (reel1 == "7") return 500;
        if (reel1 == "$") return 50;
        if (reel1 == "£") return 10;
        if (reel1 == "#") return 5;
        if (reel1 == "X") return 1;
    }
    return 0;
}

int main() {
    const char *reel1, *reel2, *reel3;
    char choice;
    int rolls, money = 0;
    int costPerRoll = 1;

    srand(time(NULL));

    rolls = rand() % 50;
    rolls = (rolls == 0) ? rolls += 3 : rolls;

    system("clear");
    printf("Rolling for starting amount of rolls...\n");
    SLEEP(1.5);
    
    system("clear");
    printf("You start with %d rolls!\n", rolls);
    SLEEP(1);

    do {
        system("clear");

        if (rolls == 0 && money > 5) {
            printf("You have no rolls and no money. You lost the game!\n");
            SLEEP(2);
            break;
        }
    
        printf("\n--- Slot Machine Menu ---\n");
        printf("1. Play\n");
        printf("2. Shop (Buy rolls)\n");
        printf("3. Check Balance\n");
        printf("4. Exit\n");
        printf("\nRolls remaining: %d\n", rolls);
        printf("Choose an option: ");
        scanf(" %c", &choice);
        system("clear");

        switch (choice) {
            case '1':
                if (rolls > 0) {
                    int rollsToPlay;
                    printf("How many times would you like to roll? (You have %d rolls remaining.): ", rolls);
                    scanf("%d", &rollsToPlay);

                    if (rollsToPlay > rolls) {
                        printf("You don't have enough rolls! You can only roll up to %d times.\n", rolls);
                        SLEEP(1);
                    } else {
                        for (int i = 0; i < rollsToPlay; i++) {
                            system("clear");
                            printf("Spinning...\n\n");

                            reel1 = spinReel();
                            reel2 = spinReel();
                            reel3 = spinReel();
                            sevenCount = (sevenCount > 0) ? 0 : sevenCount; 

                            printf("---------------\n");
                            printf("--   %s", reel1);
                            printf(" %s ", reel2);
                            printf("%s   --\n", reel3);
                            printf("---------------\n");
                            SLEEP(1);

                            int prize = calculatePrize(reel1, reel2, reel3);
                            if (prize > 0) {
                                if (reel1 == "$" && reel2 == "$" && reel3 == "$") {
                                    system("clear");
                                    printf("!!! JACKPOT!!! You win $%d !!!\n", prize);
                                } else {
                                    system("clear");
                                    printf("!!! You win $%d !!!\n", prize);
                                }
                                SLEEP(1);
                                money += prize;
                            } else {
                                system("clear");
                                printf("No match, better luck next time!\n");
                            }

                            rolls--;
                            printf("Rolls remaining: %d\n", rolls);
                            SLEEP(1);
                            system("clear");
                        }
                    }
                } else {
                    system("clear");
                    printf("You have no rolls left! Visit the shop to buy more.\n");
                    SLEEP(1);
                }
                break;

            case '2':
                while (1) {
                    printf("\n--- Shop ---\n");
                    printf("1. Buy rolls ($%d per roll)\n", costPerRoll);
                    printf("2. Back\n");
                    printf("Choose an option: ");
                    int shopChoice;
                    scanf("%d", &shopChoice);

                    if (shopChoice == 1) {
                        printf("Enter the number of rolls you want to buy: ");
                        int rollsToBuy;
                        scanf("%d", &rollsToBuy);

                        int totalCost = rollsToBuy * costPerRoll;

                        if (money >= totalCost) {
                            rolls += rollsToBuy;
                            money -= totalCost;
                            system("clear");
                            printf("You bought %d rolls for $%d. Rolls remaining: %d\n", rollsToBuy, totalCost, rolls);
                            SLEEP(1);
                        } else {
                            system("clear");
                            printf("Not enough money. You need $%d but only have $%d.\n", totalCost, money);
                            SLEEP(1);
                        }
                    } else if (shopChoice == 2) {
                        system("clear");
                        printf("Returning to the main menu...\n");
                        SLEEP(1);
                        break;
                    } else {
                        system("clear");
                        printf("Invalid option. Please try again.\n");
                        SLEEP(1);
                    }
                }
                break;

            case '3':
                system("clear");
                printf("Balance: $%d\n", money);
                SLEEP(2);
                break;

            case '4':
                system("clear");
                printf("Thank you for playing!\n");
                SLEEP(1);
                break;

            default:
                system("clear");
                printf("Invalid option. Please try again.\n");
                SLEEP(1);
                break;
        }
    } while (choice != '4');

    return 0;
}
