#include "stateMachine.h"
#include "sleep.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    STATE_IDLE,
    STATE_ATTACH_BAIT,
    STATE_CASTING,
    STATE_REELING,
    STATE_COOKING,
    STATE_QUIT
} GameState;

void fishingGame(char *firstName, char *lastName)
{
    GameState state = STATE_IDLE;
    char input[32];

    bool rodHasBait = false;
    int baitCount = 10;
    int fishInventory = 0;
    int fishingExperience = 0;
    int cookingExperience = 0;

    printf("Hello, %s %s. It's time to fish.\n", firstName, lastName);

    while (state != STATE_QUIT)
    {
        switch (state)
        {
        case STATE_IDLE:
            printf("\nYou are idle... Shouldn't you be fishing in a fishing "
                   "game?\n\n[b] Attach bait to fishing rod\n[c] Cast fishing "
                   "rod\n[g] Grill some fish\n[q] Quit the game\n");

            fgets(input, sizeof(input), stdin);
            if (input[0] == 'q')
            {
                state = STATE_QUIT;
                break;
            }
            else if (input[0] == 'b')
            {
                state = STATE_ATTACH_BAIT;
            }
            else if (input[0] == 'g')
                state = STATE_COOKING;
            else if (input[0] == 'c')
            {
                if (rodHasBait == true)
                {
                    state = STATE_CASTING;
                }
                else
                {
                    printf("You need bait first!\n");
                    printf("Press Enter to continue.");
                    getchar();
                }
            }
            break;

        case STATE_ATTACH_BAIT:
            if (rodHasBait == false)
            {
                printf("You have %d worms\nWould you like to attach one to "
                       "your rod? [y] or [n]: ",
                       baitCount);
                fgets(input, sizeof input, stdin);

                if (input[0] == 'y')
                {
                    if (baitCount > 0)
                    {
                        rodHasBait = true;
                        baitCount--;
                        state = STATE_IDLE;
                    }
                }
            }
            else
            {
                printf("You already have bait on your hook!\n");
                state = STATE_IDLE;
            }
            break;
        case STATE_CASTING:
            puts("You cast your rod!");
            int upper_bound = 3;
            int lower_bound = 1;

            sleepSeconds((unsigned)(rand() % (upper_bound - lower_bound + 1) +
                                    lower_bound));
            puts("A fish is on the line. Press \'enter\' to reel it in!");
            getchar();
            state = STATE_REELING;
            break;
        case STATE_REELING:
            //            printf("Insert logic for fish minigame here\n");
            printf("You have caught a fish!\n");
            fishInventory++;
            fishingExperience += 10;
            printf("Fishing XP: %d\n", fishingExperience);
            rodHasBait = false;
            state = STATE_IDLE;
            break;

        case STATE_COOKING:
            if (fishInventory == 0)
                puts("What did you even plan on cooking? Get to fishing!");

            if (fishInventory > 0)
            {
                puts("You put the fish on the grill");
                sleepSeconds(1);
                puts("It sizzles...");
                sleepSeconds(1);
                puts("Done! You have cooked a fish on the grill. [+10 Cooking "
                     "XP]\n");
                fishInventory--;
                cookingExperience += 10;
                printf("Cooking XP: %d\n", cookingExperience);
            }
            state = STATE_IDLE;
            break;
        case STATE_QUIT:
            break;
        }
    }
}
