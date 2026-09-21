#include "stateMachine.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <raylib.h>

typedef enum
{
    ASK_FIRST_NAME,
    ASK_LAST_NAME,
    START_GAME
} AppState;

char *cleanedString(char *s)
{
    s[strcspn(s, "\n")] = '\0';
    return s;
}

//static bool greetUser(char *fn, int fnSize, char *ln, int lnSize)
//{
//    for (;;)
//    {
//        DrawText("Hello, enter your first name", 190, 200, 20,
//                 LIGHTGRAY);
//
//        //if (fgets(fn, fnSize, stdin) == NULL)
//        //    return false;
//        //cleanedString(fn);
//
//        printf("Thank you, %s, now enter your last name: ", fn);
//        if (fgets(ln, lnSize, stdin) == NULL)
//            return false;
//        cleanedString(ln);
//
//        printf("Your name is: %s %s, is this true? [y] or [n]: ", fn, ln);
//
//        char choice[256];
//        if (fgets(choice, sizeof choice, stdin) == NULL)
//            return false;
//
//        if (choice[0] == 'y')
//            return true;
//    }
//}

static bool greetUser(AppState appState, char *buffer, Rectangle textBox,
                      char *firstName, char *lastName);


//void testDraw() { DrawText("Hello", 200, 170, 20, BLACK); }

#define MAX_INPUT_CHARS 9
#define MAX_NAME_CHARS 31
#define MAX_MESSAGES 5

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{

    AppState appState = ASK_FIRST_NAME;


    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "raylib [text] example - input box");

    SetExitKey(KEY_NULL);

    char buffer[MAX_INPUT_CHARS + 1] =
        "\0"; // NOTE: One extra space required for null terminator char '\0'
    char firstName[MAX_NAME_CHARS + 1] = "";
    char lastName[MAX_NAME_CHARS + 1] = "";

    int letterCount = 0;

    char messages[MAX_MESSAGES][MAX_INPUT_CHARS + 1] = {0};
    int messageCount = 0;

    Rectangle textBox = {50, screenHeight - 100,
                         225, 50};
    bool mouseOnText = false;

    int framesCounter = 0;



    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
   
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (CheckCollisionPointRec(GetMousePosition(), textBox))
            mouseOnText = true;
        else
            mouseOnText = false;

            // Set the window's cursor to the I-Beam
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

            // Get char pressed (unicode character) on the queue
            int key = GetCharPressed();

            // Check if more characters have been pressed on the same frame
            while (key > 0)
            {
                // NOTE: Only allow keys in range [32..125]
                if ((key >= 32) && (key <= 125) &&
                    (letterCount < MAX_INPUT_CHARS))
                {
                    //if (appState != START_GAME)
                    //{
                        buffer[letterCount] = (char)key;
                        letterCount++;
                        buffer[letterCount] = '\0';
                        // buffer[letterCount + 1] =
                        //     '\0'; // Add null terminator at the end of the
                        //     string             gives an access array out of
                        //     bounds error after
                        //     entering MAX_INPUT_CHARS - 1 (8 in the case that MAX_INPUT_CHARS is 9)
                    //}
                    
                }

                key = GetCharPressed(); // Check next character in the queue
            }

            if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
            {
                letterCount--;
                buffer[letterCount] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
            {
                if (appState == ASK_FIRST_NAME)
                {
                    memcpy(firstName, buffer, letterCount + 1);
                    appState = ASK_LAST_NAME;
                }
                else if (appState == ASK_LAST_NAME)
                {
                    memcpy(lastName, buffer, letterCount + 1);
                    appState = START_GAME;
                }

                if (messageCount == MAX_MESSAGES)
                {
                    memmove(messages[0], messages[1],
                             sizeof messages[0] * (MAX_MESSAGES - 1));

                    messageCount = MAX_MESSAGES - 1;
                }
                
                memcpy(messages[messageCount], buffer, (size_t)letterCount + 1U);
                messageCount++; 

                buffer[0] = '\0';
                letterCount = 0;
            }
        
            

        if (mouseOnText)
            framesCounter++;
        else
            framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        if (mouseOnText)
            DrawRectangleLines((int)textBox.x, (int)textBox.y,
                               (int)textBox.width, (int)textBox.height, RED);
        else
            DrawRectangleLines((int)textBox.x, (int)textBox.y,
                               (int)textBox.width, (int)textBox.height,
                               DARKGRAY);


        //if (appState == ASK_FIRST_NAME)
        //{
        //    DrawText("What is your first name?", textBox.x + 8, 50, 24, BLACK);
        //    DrawText(buffer,(int)textBox.x + 8, (int)textBox.y + 12, 30, MAROON);
        //}
        //else if (appState == ASK_LAST_NAME)
        //{
        //    DrawText("What is your last name?", textBox.x + 8, 50, 24, BLACK);
        //    DrawText(buffer, (int)textBox.x + 8, (int)textBox.y + 12, 30,
        //             MAROON);
        //}
        //else
        //{
        //    DrawText(TextFormat("Welcome, %s %s!", firstName, lastName), 50, 50 + 50,
        //             30, DARKBLUE);
        //}

        greetUser(appState, buffer, textBox, firstName, lastName);

        //if (mouseOnText)
        //{
            if (letterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter / 20) % 2) == 0)
                    DrawText("_", (int)textBox.x + 8 + MeasureText(buffer, 30),
                             (int)textBox.y + 12, 40, MAROON);
            }
            else
            {
                DrawText("Press BACKSPACE to delete chars...", 230, 300, 20,
                         GRAY);
            }
        //}

            for (int i = 0; i < messageCount; i++)
            {
                DrawText(messages[i], 50, 30 + i * 30, 24, DARKBLUE);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126))
        keyPressed = true;

    return keyPressed;
}

static bool greetUser(AppState appState, char *buffer, Rectangle textBox, char* firstName, char* lastName)
{
    if (appState == ASK_FIRST_NAME)
    {
        DrawText("What is your first name?", textBox.x, textBox.y - 50, 24, BLACK);
        DrawText(buffer, (int)textBox.x + 8, (int)textBox.y + 12, 30, MAROON);
    }
    else if (appState == ASK_LAST_NAME)
    {
        DrawText("What is your last name?", textBox.x, textBox.y - 50, 24,
                 BLACK);
        DrawText(buffer, (int)textBox.x, (int)textBox.y + 12, 30, MAROON);
    }
    else
    {
        DrawText(TextFormat("Welcome, %s %s!", firstName, lastName), 50,
                 50 + 50, 30, DARKBLUE);
    }
}