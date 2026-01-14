#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define cls "\033[1;1H\033[2J" // clears the terminal on linux, won't work on windows if virtual terminal is not enabled

void writeNew(const char *toWrite)
{
    FILE *src = fopen("DATA", "r");
    FILE *dest = fopen("DATA.tmp", "w");

    char line[1024];

    if (src)
    {
        while (fgets(line, sizeof(line), src))
        {
            fputs(line, dest);
        }
        fclose(src);
    }

    fprintf(dest, "%s\n", toWrite); //write to the last line

    fclose(dest);

    remove("DATA");
    rename("DATA.tmp", "DATA");
}

int findUser(char *name)
{
    FILE *src = fopen("DATA", "r");
    int i = 0;
    char line[1024];
    while (fgets(line, sizeof(line), src))
    {
        size_t len = strcspn(line, ":"); // stops at first ':', which is the name
        i++;
        if (strncmp(line, name, len) == 0 && name[len] == '\0')
        {
            fclose(src);
            return i; // found
        }
    }

    fclose(src);
    return -1; // not found
}

void deleteUser(int lineToDelete)
{
    FILE *src = fopen("DATA", "r");
    FILE *dest = fopen("DATA.tmp", "w");
    int i = 0;
    char line[1024];
    if (src)
    {
        while (fgets(line, sizeof(line), src))
        {
            i++;
            if (i == lineToDelete){
                continue;
            }
            fputs(line, dest);
        }
        fclose(src);
    }

    fclose(dest);
    remove("DATA");
    rename("DATA.tmp", "DATA");
}

void updateUser(int lineToUpdate, char* newLine)
{
    FILE *src = fopen("DATA", "r");
    FILE *dest = fopen("DATA.tmp", "w");
    int i = 0;
    char line[1024];
    if (src)
    {
        while (fgets(line, sizeof(line), src))
        {
            i++;
            if (i == lineToUpdate){
                fputs(newLine,dest);
                continue;
            }
            fputs(line, dest);
        }
        fclose(src);
    }

    fclose(dest);
    remove("DATA");
    rename("DATA.tmp", "DATA");
}

int listUser()
{
    FILE *src = fopen("DATA", "r");
    char line[1024];
    int i = 1;
    if (src)
    {
        while (fgets(line, sizeof(line), src))
        {
            line[strcspn(line, "\n")] = 0;

            size_t len = strcspn(line, ":");

            char user[256]; snprintf(user, sizeof(user), "%.*s", (int)len, line); //write only name
            printf("%d. %s\n", i, user);
            i++;
        }
        fclose(src);

        if (i == 1) return -1;
    }
    return 0;
}

int main()
{
    int selection;
    char *arr[] = {"Add User", "Delete User", "Update User", "List all", "Quit", NULL};

    printf(cls); // clear screen (escape code ascii)
    printf("Welcome to Student manager. What do you want to do?\n\n1. Add User\n2. Delete User\n3. Update User\n4. List all\n\n5. Quit\n\n>> ");

    scanf("%d", &selection);
    selection--; // because we start to count from 1 but computer counts from 0, he's dumb

    char name[256];
    char surname[256];
    int age;
    char toWrite[256];

    printf(cls);
    if (selection == 3){
        printf("-- List Users --\n\n");
        if (listUser() == -1){ printf("No users."); return 0;}
        return 0;
    }
    if (selection == 4) { return 0;}
    printf(selection == 1 ? "\n -- %s --\n\n1. Name (Case sensitive): ":" -- %s --\n\n1. Name: ", arr[selection]);
    scanf("%255s", name);
   
    if(selection == 1){ //Delete user
        if(findUser(name) == -1){printf("No such user found."); return 1;}
        deleteUser(findUser(name));
        printf("\n%s have been removed.\n",name);
        return 0;
    }

    if(selection == 2){ //Update user
        if(findUser(name) == -1){printf("No such user found."); return 1;}

        printf(cls); printf("\n -- Update User --\n\n1. Name: "); scanf("%s255",&name);
        printf("2. Surname: "); scanf("%s255",&surname);
        printf("3. Age: "); scanf("%d",&age);

        snprintf(toWrite, sizeof(toWrite), "%s:%s:%d", name, surname, age);
        updateUser(findUser(name),toWrite);
        printf("\n%s have been updated.",name);
        return 0;

    }

    printf("2. Surname: ");
    scanf("%255s", surname);
    printf("3. Age: ");
    scanf("%d", &age);


    if (selection == 0)
    {
        snprintf(toWrite, sizeof(toWrite), "%s:%s:%d", name, surname, age);
        writeNew(toWrite);
    }



}


