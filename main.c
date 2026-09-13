#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *cleanedString(char *s)
{
    s[strcspn(s, "\n")] = '\0';
    return s;
}

static void greetUser(char *fn, char *ln)
{
    bool hasName = false;
    do
    {
        printf("Hello, enter your first name: ");
        char firstName[256];
        if (fgets(firstName, sizeof(firstName), stdin) == NULL)
        {
            return;
        }

        printf("Thank you, %s, now enter your last name: ",
               cleanedString(firstName));
        char lastName[256];
        if (fgets(lastName, sizeof(lastName), stdin) == NULL)
        {
            return;
        }

        printf("Your name is: %s %s, is this true? [y] or [n]: ", firstName,
               cleanedString(lastName));
        char choice[256];
        if (fgets(choice, sizeof(choice), stdin) == NULL)
        {
            return;
        }

        printf("You chose %c\n", choice[0]);

        choice[0] == 'y' ? hasName = true : false;
        strcpy_s(fn, sizeof(firstName), firstName);
        strcpy_s(ln, sizeof(lastName), lastName);
    } while (!hasName);
}

int main(void)
{
    char firstName[256], lastName[256];
    // start of program
    greetUser(firstName, lastName);

    printf("%s %s", firstName, lastName);

    return 0;
}
