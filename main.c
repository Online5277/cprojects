#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* cleanedString(char* s) {
  s[strlen(s) - 1] = '\0';
  return s;
}

char greetUser() {
  bool hasName = false;
  do {
    fflush(stdin);
  printf("Hello, enter your first name: ");
  char firstName[256];
  fgets(firstName, sizeof(firstName), stdin);
  fflush(stdin);

  printf("Thank you, %s, now enter your last name: ", cleanedString(firstName));
  char lastName[256];
  fgets(lastName, sizeof(lastName), stdin);
  fflush(stdin);

  printf("Your name is: %s %s, is this true? [y] or [n]: ", firstName, cleanedString(lastName));
  char choice[0];
  fgets(choice, sizeof(choice), stdin);

  fflush(stdin);
  printf("You chose %c\n", choice[0]);
  
  if (choice[0] == 'y') {
      hasName = true;
      // return firstName, lastName;
    } else {
      hasName = false;
      printf("Rerunning greetUser()...\n");
    }
  } while (!hasName); 
}


int main() {

  greetUser();




  return 0;
}
