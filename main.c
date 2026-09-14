#include "stateMachine.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *cleanedString(char *s)
{
    s[strcspn(s, "\n")] = '\0';
    return s;
}

static bool greetUser(char *fn, int fnSize, char *ln, int lnSize)
{
    for (;;)
    {
        printf("Hello, enter your first name: ");
        if (fgets(fn, fnSize, stdin) == NULL)
            return false;
        cleanedString(fn);

        printf("Thank you, %s, now enter your last name: ", fn);
        if (fgets(ln, lnSize, stdin) == NULL)
            return false;
        cleanedString(ln);

        printf("Your name is: %s %s, is this true? [y] or [n]: ", fn, ln);

        char choice[256];
        if (fgets(choice, sizeof choice, stdin) == NULL)
            return false;

        if (choice[0] == 'y')
            return true;
    }
}

int main(void)
{
    char firstName[256], lastName[256];
    srand((unsigned)time(NULL));
    // start of program
    if (!greetUser(firstName, sizeof firstName, lastName, sizeof lastName))
        return 1;

    //    printf("%s %s", firstName, lastName);
    fishingGame(firstName, lastName);

    return 0;
}
