#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define BOXES 15
#define SHUFFLES 137
#define BOX_ROW 5
#define PADDING 12
#define BOXES_TO_OFFER 4

#define HOR 205
#define VER 186
#define TOP_LEFT 201
#define TOP_RIGHT 187
#define BOT_LEFT 200
#define BOT_RIGHT 188
#define TOP_MID 203
#define BOT_MID 202
#define MID_LEFT 204
#define MID_RIGHT 185

// Prints all boxes
void displayBoxes(unsigned boxes[], unsigned opened[], unsigned length,  int playerBox, unsigned sums[]) {
    // Pre header - All sums
    char preHeader[] = {
        TOP_LEFT, HOR, 65, 108, 108, ' ', 115, 117, 109, 115,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, TOP_RIGHT, '\0' };
    printf("%s\n", preHeader);
    printf("%c  ", VER);

    for (int i = 0; i < BOXES; i++) {
        printf("%d   ", sums[i]);
    }
    printf("   %c\n", VER);

    // Header - Boxes and Player box
    char header[] = {
        MID_LEFT, HOR, 66, 111, 120, 101, 115,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, TOP_MID,
        HOR, 89, 111, 117, 114, ' ', 98, 111, 120,
        HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, MID_RIGHT,
        '\0' };
    printf("%s\n", header);
    printf("%c                                                                                %c                    %c\n%c     ", VER, VER, VER, VER);
    for (int i = 0, row = 1, boxCount = 1; i < length; i++, boxCount++) {
        bool playerBoxChosen = playerBox > -1;
        // Skip the player box (printed separately)
        if (playerBoxChosen && i == playerBox) {
            i++;
        }

        if (i < length) {
            // Print current box
            if (opened[i] == 0) {
                printf("%2d[______]     ", i+1);
            } else {
                printf("%2d[%6d]     ", i+1, boxes[i]);
            }
        } else {
            // Early break from the loop if the player chose the last box
            break;
        }

        // Print new row and borders
        if (boxCount % BOX_ROW == 0 || (playerBoxChosen && boxCount == length-1)) {
            // Print the player's box
            if (playerBoxChosen && row == 2) {
                if (opened[playerBox] == 0) {
                    printf("%c     %2d[______]     ", VER, playerBox+1);
                } else {
                    printf("%c     %2d[%6d]     ", VER, playerBox+1, boxes[playerBox]);
                }
            } else if (playerBoxChosen && boxCount >= length-1) {
                // boxCount >= length-1 covers both cases -> playerBox != length-1 and playerBox == length-1
                // Extra spaces in place of the last box
                // when the player has selected and taken one of the boxes
                printf("               %c                    ", VER);
            } else {
                printf("%c                    ", VER);
            }

            printf("%c\n%c                                                                                %c                    %c\n", VER, VER, VER, VER);

            // Next row indent (only if there will be a next row)
            if (boxCount < length-1) {
                // boxCount < length-1 covers both cases -> playerBox != length-1 and playerBox == length-1
                printf("%c     ", VER);
            }

            row++;
        }
    }

    char footer[] = {
        BOT_LEFT, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, BOT_MID, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, HOR, HOR,
        HOR, HOR, HOR, HOR, HOR, BOT_RIGHT,
        '\0' };
    printf("%s\n\n", footer);
};

void pressToContinue() {
    printf("\n[==  Press ENTER to Continue  ==]\n\n");
    scanf("");
    char c;
    // Consume chars until a newline is read to prevent
    // invalid or accidental inputs to propagate to the next scanf/getchar
    do {
        c = getchar();
    } while (c != '\n');
}

// Reads user input until a valid value is entered
int readInput(int min, int max) {
    bool inputAgain = false;
    int input = -1;
    do {
        scanf("%d", &input);
        getchar(); // Consume the newline
        if (input < min || input > max) {
            printf("Invalid input. Valid input is %d <= X <= %d.\n\n", min, max);
            pressToContinue();
            printf("\n> ");
            inputAgain = true;
        } else {
            inputAgain = false;
        }
    } while(inputAgain);

    return input;
}

// Same as readInput() but for boxes specifically
int readBoxInput(int min, int max, unsigned opened[], int playerBox) {
    bool inputAgain = false;
    int input = -1;
    do {
        scanf("%d", &input);
        getchar(); // Consume the newline
        // Decrement to match the zero-indexed array
        input--;
        if (input+1 < min || input+1 > max) {
            printf("Invalid input. Valid input is %d <= X <= %d.\n\n", min, max);
            pressToContinue();
            printf("\n> ");
            inputAgain = true;
        } else if (opened[input] == 1) {
            printf("This box has been opened already. Choose another box.\n\n");
            pressToContinue();
            printf("\n> ");
            inputAgain = true;

        } else if (input == playerBox) {
            printf("Can't open your own box, mate. It beats the purpose of the game.\n\n");
            pressToContinue();
            printf("\n> ");
            inputAgain = true;
        } else {
            inputAgain = false;
        }
    } while(inputAgain);

    return input;
}

void openAndDisplayAllBoxes(unsigned boxes[], unsigned opened[], unsigned length,  int playerBox, unsigned sums[]) {
        // Open all boxes
        for (int i = 0; i < length; i++) {
            opened[i] = 1;
        }

        // Clear the screen
        system("cls");

        // Display the boxes
        displayBoxes(boxes, opened, length, playerBox, sums);
}

void takeDeal (unsigned offer, unsigned boxes[], unsigned opened[], int playerBox, unsigned sums[]) {
    int previousBox = 0;
    if (offer == 0) {
        printf("But let's not be too hasty, right? \nIt's not over just yet. \nOne last tough decision left.\n\n");
        printf("Choose which box to swap yours with:\n> ");

        // Read and process the input
        int boxToChange = readBoxInput(1, BOXES, opened, playerBox);
        int previousBox = playerBox;

        // Change the boxes
        playerBox = boxToChange;

        printf("\nSwitching the boxes...\n");
        pressToContinue();

        // Clear the screen
        system("cls");

        // Display the boxes
        displayBoxes(boxes, opened, BOXES, playerBox, sums);

        printf("Well.. What's done is done! \nDecisions were made, boxes were switched.\nLet's find out what that deal earned you, shall we?\n\n");
        pressToContinue();

        openAndDisplayAllBoxes(boxes, opened, BOXES, playerBox, sums);

        printf("YOUR NEW BOX GOT YOU [%6d]!!\n\n", boxes[playerBox]);

        printf("Want to know how much you had in your original box?\n\n");
        pressToContinue();

        printf("Your original box contained [%6d]!\n", boxes[previousBox]);
    } else {
        printf("YOUR DEAL GOT YOU [%6d]!!\n\n", offer);

        printf("Want to know how much you had in your box?\n\n");
        pressToContinue();

        openAndDisplayAllBoxes(boxes, opened, BOXES, playerBox, sums);

        printf("Your box contained [%6d]!\n\n", boxes[playerBox]);

        printf("And you won [%6d]! \nCongrats!\n\n", offer);
    }

    // If you took the offer and it's bigger than your box OR if you changed and your box value is bigger than the offer
    if ((offer > 0 && offer > boxes[playerBox]) || (offer == 0 && boxes[playerBox] > boxes[previousBox])) {
        printf("What a game ya pulled there! \nWell done.\n\n");
    } else {
        printf("Not the best outcome but, oh well..\nThat's life for ya.\n\n");
    }

    pressToContinue();
}

int main()
{
    unsigned sums[BOXES] = {
        1, 2, 5, 10, 100, 200, 500, 1000,
        2500, 5000, 7500, 10000,
        25000, 50000, 100000
    };
    unsigned boxes [BOXES] = {
        1, 2, 5, 10, 100, 200, 500, 1000,
        2500, 5000, 7500, 10000,
        25000, 50000, 100000
    };
    unsigned opened[BOXES] = {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0
    };
    int playerBox = -1; //rand() % 15;

    // Initialiaze RNG
    time_t t;
    srand((unsigned) time(&t));

    // Greeting
    printf("=== WELCOME TO \"DEAL OR NO DEAL\" THE MOST EXCITING GAME IN THE WORLD!!! === \n\n");
    // printf("Read to play Deal or No Deal?\n");

    // Shuffle
    printf("Shuffling boxes...\n");
    for (int i = 0; i < SHUFFLES; i++) {
        unsigned rand1 = rand() % 15;
        unsigned rand2 = rand() % 15;
        if (rand1 == rand2) {
            // printf("MATCHING INDEXES\n");
            continue;
        }
        // printf("Swapping %d(%d) and %d(%d)\n", rand1+1, boxes[rand1], rand2+1, boxes[rand2]);
        unsigned swap = boxes[rand1];
        boxes[rand1] = boxes[rand2];
        boxes[rand2] = swap;
    }
    printf("Boxes shuffled. \nCarpet rolled out. \nCurtains raised. \nTime for action!\n\n");
    pressToContinue();

    // Clear the screen
    system("cls");

    // Display boxes
    displayBoxes(boxes, opened, BOXES, playerBox, sums);

    // Player selects their box
    printf("First you need a box. \nAny box can be yours but only one holds the big prize of 100,000! \nChoose wisely.\n> ");
    playerBox = readInput(1, BOXES);
    // Decrement to match the zero-based array
    playerBox--;

    // Clear the screen
    system("cls");

    // Main loop
    bool loop = true;
    unsigned openedBoxes = 0;
    unsigned totalSumOfOpenedBoxes = 0;
    bool offerGiven = true;
    bool hasTakenADeal = false;
    unsigned takenDeal = 0;

    do {
        // Display the boxes
        displayBoxes(boxes, opened, BOXES, playerBox, sums);

        // Check if it's time for an offer
        if (!offerGiven) {
            // Bank offer

            unsigned offer = 0;
            // Last offer is always Change of boxes and has different dialogue
            if (openedBoxes < 12) {
                printf("Well well, would you look at the time.\nIt's offer time! \nThe Bank will give you a special offer to get your box. \n\n");
                pressToContinue();
                printf("It's so exciting! \nI wonder what it's going to be...\n\n");
                pressToContinue();

                // Calculate offer
                if (totalSumOfOpenedBoxes < 10000) {
                    offer = rand() % 14000 + 14000; // from 14000 to 28000
                } else if (totalSumOfOpenedBoxes > 10000 && totalSumOfOpenedBoxes < 30000) {
                    // 33% pseudo-chance to offer Change of boxes
                    if (rand() % 3 == 1) {
                        // if offer == 0 => change of boxes
                        offer = 0;
                    } else {
                        offer = rand() % 6000 + 4000; // from 4000 to 10000
                    }
                } else {
                    offer = rand() % 6000 + 1000; // from 1000 to 7000
                }

                if (offer > 0) {
                    printf("The Bank is offering [%6d] for that box of yours.\n", offer);
                } else {
                    printf("The Bank is full of suprises.\nThe offer is a [Change of Boxes].\n\n");
                }
                printf("\nThe moment to ask the question has come, friend.\nDeal or No Deal?\n\n");

                printf("1) Deal!\n2) No deal!\n\n> ");

                // Read the player's input
                int choice = readInput(1, 2);

                // Process the choice
                if (choice == 1) {
                    // Clear the screen
                    system("cls");

                    // Display the boxes
                    displayBoxes(boxes, opened, BOXES, playerBox, sums);

                    printf("\nWE HAVE A DEAL!! \nCONGRATULATIONS!! \n\n");
                    pressToContinue();
                    hasTakenADeal = true;
                    takenDeal = offer;

                    takeDeal(offer, boxes, opened, playerBox, sums);
                    // End Game
                    break;

                } else {
                    printf("\nNot giving up that easily, eh? \nI like that. \nLet's see where it takes you.\n\n");
                    offerGiven = true;
                    printf("You gotta open four boxes.\n\n");
                }
            } else {
                // Last change to change boxes
                printf("\nYou did it, buddy. \nYou weren't tempted by the offers at all. \nYou declined them all and now only two boxes remain. \nYou probably know what this means.\n\n");
                pressToContinue();

                printf("\nA choice is to be made. \nIt's all in your hands. \nOne last chance to change your box with one of the others.\n\n");
                pressToContinue();

                printf("\nWhat will it be then? \nChange? No change? \nYou know I'm just waiting to ask the question. \nDeal or no deal?\n\n");
                printf("1) Deal!\n2) No deal!\n\n> ");

                // Set the offer (0 = Change of boxes)
                offer = 0;

                // Read the player's input
                int choice = readInput(1, 2);

                if (choice == 1) {
                    // Clear the screen
                    system("cls");

                    // Display the boxes
                    displayBoxes(boxes, opened, BOXES, playerBox, sums);

                    printf("\nWE HAVE A DEAL!! \nCONGRATULATIONS!! \n\n");
                    pressToContinue();
                    hasTakenADeal = true;
                    takenDeal = offer;

                    takeDeal(offer, boxes, opened, playerBox, sums);
                } else {
                    // The player kept their box until the end
                    printf("\nYou really don't want to let that box go, huh. \nDetermined to the very end. \nI can respect that. \n\n");
                    pressToContinue();

                    // Clear the screen
                    system("cls");

                    // Display the boxes
                    displayBoxes(boxes, opened, BOXES, playerBox, sums);

                    printf("Well, two boxes are still in the game so let me open them for you.\n\n");
                    pressToContinue();

                    printf("Suspense..\n\n");
                    pressToContinue();

                    // Open the remaining two boxes
                    for (int i = 0, flag = 0; i < BOXES; i++) {
                        if (opened[i] == 0 && i != playerBox) {
                            if (flag == 0) {
                                printf("Box %d was hiding a [%6d].\n\n", i+1, boxes[i]);
                                pressToContinue();
                                opened[i] = 1;
                                flag = 1;
                            } else {
                                printf("And box %d was going to give you [%6d].\n\n", i+1, boxes[i]);
                                pressToContinue();
                                opened[i] = 1;
                            }
                        }
                    }

                    printf("Time for the big reveal then. \nYour box...\n\n");
                    pressToContinue();

                    printf("The box you chose in the very beginning of this game and never let go of..\n\n");
                    pressToContinue();

                    printf("That box... contains...\n\n");
                    pressToContinue();

                    openAndDisplayAllBoxes(boxes, opened, BOXES, playerBox, sums);

                    printf("It contains [%6d]!!! \n\n", boxes[playerBox]);
                    printf("Wow. \nJust wow. \nWhat a game!\n\n");
                    pressToContinue();

                    printf("This why they call it the greatest game ever made!\n\n");
                    pressToContinue();

                    printf("I believe it's time for our ways to part, friend. \nBut worry not! \nI'll remember you and this awesome game!\n\n");
                    pressToContinue();
                }

                break;
            }

            pressToContinue();

        } else {
            // Player chooses a box to open
            printf("Choose a box to open:\n> ");
            int boxToOpen = readBoxInput(1, BOXES, opened, playerBox);

            // Open box
            opened[boxToOpen] = 1;
            openedBoxes++;
            totalSumOfOpenedBoxes += boxes[boxToOpen];
            printf("\n Box %d contains [%6d]!\n\n", boxToOpen+1, boxes[boxToOpen]);
            if (boxes[boxToOpen] >= 10000) {
                printf("Nooo! \nIt's one of the big ones..\n\n");
            } else if (boxes[boxToOpen] < 1000) {
                printf("Ah, a lucky shot! \nIt's a small one!\n\n");
            } else {
                printf("Oh well, could be better but could be a lot worse too so that's fine.\n\n");
            }
            pressToContinue();

            if (openedBoxes != 0 && openedBoxes % 4 == 0) {
                offerGiven = false;
            }
        }

        // Clear the screen
        system("cls");
    } while (loop);

    printf("Don't forget to come back, friend. \nThe greatest game in the universe will be waiting for you! \n'Til next time.\n\n==================END====================\n\n");

    return 0;
}
