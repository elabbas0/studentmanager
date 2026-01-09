#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int size(char **param)
{
    int i = 0;
    while (param[i] != NULL)
    {
        i++;
    }
    return i;
}

int getLineCount()
{
    FILE *fp = fopen("DATA", "r");
    if (!fp)
        return 0;

    int lines = 0;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        lines++;
    fclose(fp);
    return lines;
}

char *lineContent(int line)
{
    FILE *fp = fopen("DATA", "r");
    if (!fp)
        return NULL;

    char buffer[1024];
    int currentLine = 0;
    char *result = NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        currentLine++;
        if (currentLine == line)
        {
            result = malloc(strlen(buffer) + 1);
            if (result)
                strcpy(result, buffer);
            break;
        }
    }

    fclose(fp);
    return result;
}

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

void trimSpaces(char *str)
{
    char *start = str;
    while (*start == ' ' || *start == '\t')
        start++;
    char *end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t'))
        *end-- = '\0';
    memmove(str, start, strlen(start) + 1);
}

int main(void)
{
    FILE *fp = fopen("DATA", "a+"); // Append mode, evvelki datani silmir. (w+ silir)
    if (!fp)
    {
        perror("fopen failed:");
        return 1;
    }

    char *prompts[] = {"Add user", "Delete user", "List user", "Update user", "\nQuit", NULL};
    int selection = 0;

    while (1)
    {
        printf("\033[H\033[J");
        printf("Welcome to the student manager. What do you want to do?\n\n");
        for (int i = 0; i < size(prompts); i++)
        {
            printf("%s%s\n", prompts[i], (selection == i) ? " <" : "");
        }

        char ch = _getch();
        if (ch == 's' || ch == 'S' && selection < size(prompts) - 1)
            selection++;
        else if (ch == 'w' || ch == 'W' && selection > 0)
            selection--;
        else if (ch == '\r')
            break;
    }

    if (selection == 0) // Add User
    {
        int newLine = getLineCount() + 1;
        printf("\033[H\033[J-- ADD USER --\n\n");
        char *AddUser[] = {"Name", "Surname", "Age", "Group", NULL};
        char userInput[4][256]; // 4 input

        for (int i = 0; i < 4; i++)
        {
            while (1)
            {
                printf("%s: ", AddUser[i]);
                if (!fgets(userInput[i], sizeof(userInput[i]), stdin))
                {
                    printf("Input error. Try again.\n");
                    continue;
                }

                trimNewline(userInput[i]);
                trimSpaces(userInput[i]);

                if (strlen(userInput[i]) == 0)
                {
                    printf("Input cannot be empty. Please enter %s.\n", AddUser[i]);
                    continue;
                }
                break;
            }

            fprintf(fp, "%s;", userInput[i]);
        }

        fprintf(fp, "\n"); // line sonu
        fflush(fp);

        char *written = lineContent(newLine);
        if (written)
        {
            size_t sep = strcspn(written, ";");
            printf("\n\nSaved User: %.*s\n", (int)sep, written);
            free(written);
        }
        else
        {
            printf("Failed to read saved user.\n");
        }
    }

    if (selection == 1) // Delete user
    {
        printf("\033[H\033[J-- DELETE USER --\n\n");
        char username[256];

        while (1)
        {
            printf("Enter Username: ");
            if (!fgets(username, sizeof(username), stdin))
            {
                printf("\nExiting..\n"); // eof ctrl+d
                break;
            }

            trimNewline(username);
            trimSpaces(username);

            if (strlen(username) == 0)
            {
                printf("Username cannot be empty.\n");
                continue;
            }

            FILE *fp = fopen("DATA", "r");
            if (!fp)
            {
                perror("fopen failed");
                break;
            }

            FILE *temp = fopen("DATA.tmp", "w");
            if (!temp)
            {
                perror("fopen temp failed");
                fclose(fp);
                break;
            }

            char buffer[1024];
            int found = 0;

            while (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                char lineCopy[1024];
                strcpy(lineCopy, buffer);
                char *firstField = strtok(lineCopy, ";");
                if (firstField && strcmp(firstField, username) == 0)
                {
                    found = 1; // skip this line
                }
                else
                {
                    fputs(buffer, temp);
                }
            }

            fclose(fp);
            fclose(temp);

            if (!found)
            {
                printf("Username '%s' does not exist. Try again.\n", username);
                remove("DATA.tmp");
                continue;
            }
            else
            {
                remove("DATA");
                rename("DATA.tmp", "DATA");
                printf("User '%s' deleted successfully.\n", username);
                break;
            }
        }
    }

    if (selection == 2) // List users
    {
        printf("\033[H\033[J-- LIST USERS --\n\n");

        FILE *fp = fopen("DATA", "r");
        if (!fp)
        {
            perror("fopen failed");
        }
        else
        {
            char buffer[1024];
            int count = 0;

            while (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                char lineCopy[1024];
                strcpy(lineCopy, buffer);
                char *username = strtok(lineCopy, ";");
                if (username)
                {
                    count++;
                    printf("%d. %s\n", count, username);
                }
            }

            if (count == 0)
            {
                printf("No users found.\n");
            }

            fclose(fp);
        }

        printf("\nPress Enter to exit..");
        getchar(); // wait for Enter
    }

    if (selection == 3) // Update user
    {
        printf("\033[H\033[J-- UPDATE USER --\n\n");

        char username[256];
        while (1)
        {
            printf("Enter Username to update: ");
            if (!fgets(username, sizeof(username), stdin))
            {
                printf("\nExiting update menu.\n");
                break;
            }

            trimNewline(username);
            trimSpaces(username);

            if (strlen(username) == 0)
            {
                printf("Username cannot be empty.\n");
                continue;
            }

            FILE *fp = fopen("DATA", "r");
            if (!fp)
            {
                perror("fopen failed");
                break;
            }

            FILE *temp = fopen("DATA.tmp", "w");
            if (!temp)
            {
                perror("fopen temp failed");
                fclose(fp);
                break;
            }

            char buffer[1024];
            int found = 0;

            while (fgets(buffer, sizeof(buffer), fp) != NULL)
            {
                char lineCopy[1024];
                strcpy(lineCopy, buffer);
                char *firstField = strtok(lineCopy, ";");

                if (firstField && strcmp(firstField, username) == 0)
                {
                    found = 1;

                    char newValues[4][256]; // Name, Surname, Age, Group
                    char *AddUser[] = {"Name", "Surname", "Age", "Group", NULL};

                    for (int i = 0; i < 4; i++)
                    {
                        while (1)
                        {
                            printf("%s: ", AddUser[i]);
                            if (!fgets(newValues[i], sizeof(newValues[i]), stdin))
                            {
                                printf("\nInput error. Try again.\n");
                                continue;
                            }
                            trimNewline(newValues[i]);
                            trimSpaces(newValues[i]);
                            if (strlen(newValues[i]) == 0)
                                printf("Input cannot be empty. Please enter %s.\n", AddUser[i]);
                            else
                                break;
                        }
                    }

                    fprintf(temp, "%s;%s;%s;%s;\n",
                            newValues[0], newValues[1], newValues[2], newValues[3]);
                }
                else
                {
                    fputs(buffer, temp);
                }
            }

            fclose(fp);
            fclose(temp);

            if (!found)
            {
                printf("Username '%s' does not exist. Try again.\n", username);
                remove("DATA.tmp");
                continue;
            }
            else
            {
                remove("DATA");
                rename("DATA.tmp", "DATA");
                printf("User '%s' updated successfully.\n", username);
                break;
            }
        }
    }

    fclose(fp);
    return 0;
}
