# Student Manager

A simple C program to manage a list of students stored in a plain text file (`DATA`).  
It allows you to **add**, **delete**, **update**, and **list** students.

---

## How It Works

- All student data is stored in a file called `DATA` in the format:

NAME:SURNAME:AGE


- Each operation works by reading the `DATA` file, modifying it in memory or a temporary file, and then rewriting the updated data back to `DATA`.

- Functions:

  - `writeNew(const char *toWrite)`: Adds a new student at the end of the file.  
  - `findUser(char *name)`: Returns the line number of a student by name, or `-1` if not found.  
  - `deleteUser(int lineToDelete)`: Deletes a student by line number.  
  - `updateUser(int lineToUpdate, char* newLine)`: Updates a student’s details on a specific line.  
  - `listUser()`: Prints all student names with numbering.

- The program uses ANSI escape codes (`cls`) to clear the screen before showing menus.

---

## Usage

1. Compile the program:

```bash
gcc student_manager.c -o student_manager
./student_manager
```
## Available commands
1. Add User
2. Delete User
3. Update User
4. List all
5. Quit
