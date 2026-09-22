#include "stateMachine.h"
#include <raylib.h>
#include <stdbool.h>

typedef enum
{
    STATE_IDLE,
    STATE_ATTACH_BAIT,
    STATE_CASTING,
    STATE_REELING,
    STATE_COOKING
} GameState;

static GameState state;
static bool rodHasBait;
static int baitCount;
static int fishInventory;
static double fishBitesAt;

void fishingGameInit(void)
{
    state = STATE_IDLE;
    rodHasBait = false;
    baitCount = 10;
    fishInventory = 0;
    fishBitesAt = 0.0;
}

void fishingGameUpdate(void)
{
    switch (state)
    {
    case STATE_IDLE:
        if (IsKeyPressed(KEY_B))
            state = STATE_ATTACH_BAIT;

        if (IsKeyPressed(KEY_C))
        {
            state = STATE_CASTING;
            if (rodHasBait)
                fishBitesAt = GetTime() + GetRandomValue(1, 3);
        }
        // add settings menu to change name and stuff
        break;

    case STATE_ATTACH_BAIT:
        if (rodHasBait || baitCount == 0)
        {
            if (IsKeyPressed(KEY_ENTER))
                state = STATE_IDLE;
        }
        else if (IsKeyPressed(KEY_Y))
        {
            rodHasBait = true;
            baitCount--;
            state = STATE_IDLE;
        }
        else if (IsKeyPressed(KEY_N))
        {
            state = STATE_IDLE;
        }
        break;

    case STATE_CASTING:
        if (!rodHasBait)
        {
            if (IsKeyPressed(KEY_ENTER))
                state = STATE_IDLE;
        }
        else if (GetTime() >= fishBitesAt)
        {
            state = STATE_REELING;
        }
        break;

    case STATE_REELING:
        if (IsKeyPressed(KEY_ENTER))
        {
            fishInventory++;
            rodHasBait = false;
            state = STATE_IDLE;
        }
        break;

    case STATE_COOKING:
        break;
    }
}

void fishingGameDraw(void)
{
    switch (state)
    {
    case STATE_IDLE:
        DrawText("[B] Attach bait", 50, 150, 24, BLACK);
        DrawText("[C] Cast rod", 50, 185, 24, BLACK);
        break;

    case STATE_ATTACH_BAIT:
        if (rodHasBait)
            DrawText("Your rod already has bait. Press Enter.", 50, 150, 24,
                     BLACK);
        else if (baitCount == 0)
            DrawText("You have no bait left. Press Enter.", 50, 150, 24,
                     BLACK);
        else
            DrawText("Attach bait? [Y] Yes  [N] No", 50, 150, 24, BLACK);
        break;

    case STATE_CASTING:
        if (!rodHasBait)
            DrawText("Your rod has no bait! Press Enter.", 50, 150, 24,
                     BLACK);
        else
            DrawText("Waiting for a fish...", 50, 150, 24, DARKBLUE);
        break;

    case STATE_REELING:
        DrawText("Fish on the line! Press Enter!", 50, 150, 24, RED);
        break;

    case STATE_COOKING:
        DrawText("Cooking...", 50, 150, 24, ORANGE);
        break;
    }

    DrawText(TextFormat("Bait: %d", baitCount), 600, 30, 20, BLACK);
    DrawText(TextFormat("Fish: %d", fishInventory), 600, 60, 20, BLACK);
}
