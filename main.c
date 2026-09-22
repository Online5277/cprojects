#include "stateMachine.h"
#include "fileHelper.h"
#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAX_INPUT_CHARS 31

typedef enum
{
    ASK_FIRST_NAME,
    ASK_LAST_NAME,
    START_GAME
} AppState;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const Rectangle textBox = {50.0f, 350.0f, 700.0f, 50.0f};

    AppState appState = ASK_FIRST_NAME;
    char buffer[MAX_INPUT_CHARS + 1] = "";
    char firstName[MAX_INPUT_CHARS + 1] = "";
    char lastName[MAX_INPUT_CHARS + 1] = "";
    int letterCount = 0;
    int framesCounter = 0;

    if (checkName(firstName, sizeof firstName, lastName, sizeof lastName))
        {
            appState = START_GAME;
        }

    InitWindow(screenWidth, screenHeight, "cprojects");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    fishingGameInit();

    while (!WindowShouldClose())
    {
        // file helper logic

        if (appState != START_GAME)
        {
            int key = GetCharPressed();
            while (key > 0)
            {
                if (key >= 32 && key <= 125 && letterCount < MAX_INPUT_CHARS)
                {
                    buffer[letterCount] = (char)key;
                    letterCount++;
                    buffer[letterCount] = '\0';
                }

                key = GetCharPressed();
            } // get key inputs for strings (Goes inside of the buffer)

            if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
            {
                letterCount--;
                buffer[letterCount] = '\0';
            } // decrement letterCount because we deleted a letter.
	      // set buffer at letterCount to '\0' since raylib
	      // reads strings until '\0'

            if (IsKeyPressed(KEY_ENTER) && letterCount > 0)// check if letterCount is more than 0 to not return save empty string
            {
                if (appState == ASK_FIRST_NAME)
                {
		  memcpy(firstName, buffer, (size_t)letterCount + 1U); // (size_t) + 1U[unsigned]) makes memcpy safe 
		  appState = ASK_LAST_NAME; // saved firstName, transition to lastName
                }
                else // no `else if` since we only get first and last name
                {
                    memcpy(lastName, buffer, (size_t)letterCount + 1U);

                    jsonInit(firstName, lastName);
                    appState = START_GAME;

                }

                buffer[0] = '\0'; // set buffer[0] to '\0' so that raylib doesn't read it maybe?
                letterCount = 0; // no more letters to show.
            }
        }
        else // appState = START_GAME so we call fishingGameUpdate()
        {
            fishingGameUpdate();
        }

        bool mouseOnText = appState != START_GAME /*<----  probably AI slop*/ &&
                           CheckCollisionPointRec(GetMousePosition(), textBox);
        SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        framesCounter++;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (appState == ASK_FIRST_NAME)
        {
            DrawText("What is your first name?", 50, 50, 24, BLACK);
        }
        else if (appState == ASK_LAST_NAME)
        {
            DrawText("What is your first name?", 50, 50, 24, DARKGRAY);
            DrawText(firstName, 50, 85, 30, DARKBLUE);
            DrawText("What is your last name?", 50, 140, 24, BLACK);
        }
        else if (appState == START_GAME)
        {
            DrawText(TextFormat("Welcome, %s %s!", firstName, lastName), 50,
                     35, 30, DARKBLUE);

            fishingGameDraw();
        }

        if (appState != START_GAME)
        {
            DrawRectangleRec(textBox, LIGHTGRAY);
            DrawRectangleLines((int)textBox.x, (int)textBox.y,
                               (int)textBox.width, (int)textBox.height,
                               mouseOnText ? RED : DARKGRAY);
            DrawText(buffer, (int)textBox.x + 8, (int)textBox.y + 10, 30,
                    MAROON);

            if (letterCount < MAX_INPUT_CHARS &&
                ((framesCounter / 20) % 2) == 0)
            {
                DrawText("_", (int)textBox.x + 8 + MeasureText(buffer, 30),
                         (int)textBox.y + 10, 30, MAROON);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
