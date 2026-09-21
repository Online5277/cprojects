#include <raylib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define MAX_INPUT_CHARS 31
#define MAX_MESSAGES 5

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
    char messages[MAX_MESSAGES][MAX_INPUT_CHARS + 1] = {{0}};
    int letterCount = 0;
    int messageCount = 0;
    int framesCounter = 0;

    InitWindow(screenWidth, screenHeight, "Fishing Game");
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    while (!WindowShouldClose())
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
                memcpy(firstName, buffer, (size_t)letterCount + 1U);
                appState = ASK_LAST_NAME;
            }
            else if (appState == ASK_LAST_NAME)
            {
                memcpy(lastName, buffer, (size_t)letterCount + 1U);
                appState = START_GAME;
            }
            else
            {
                if (messageCount == MAX_MESSAGES)
                {
                    memmove(messages[0], messages[1],
                            sizeof messages[0] * (MAX_MESSAGES - 1U));
                    messageCount--;
                }

                memcpy(messages[messageCount], buffer,
                       (size_t)letterCount + 1U);
                messageCount++;
            }

            buffer[0] = '\0';
            letterCount = 0;
        }

        bool mouseOnText =
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
        else
        {
            DrawText(TextFormat("Welcome, %s %s!", firstName, lastName), 50,
                     35, 30, DARKBLUE);
            DrawText("Type a message and press Enter:", 50, 80, 20,
                     DARKGRAY);

            for (int i = 0; i < messageCount; i++)
                DrawText(messages[i], 50, 120 + i * 36, 24, BLACK);
        }

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

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
