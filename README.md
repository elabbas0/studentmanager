## Student Manager

### How does it work?
- All user data is stored in a file named `DATA` (no extension).  
Each line in the file represents a single user.  
Each line has fields separated by semicolons (`;`) in this order:  

- When the program starts, it presents a terminal menu to **Add, Delete, List, or Update users**.  
Inputs are validated: empty or whitespace-only inputs are rejected.  

---

### Usage

#### 1. Add User
- Select `Add user` from the menu.  
You will be prompted to enter:
- Name  
- Surname  
- Age  
- Group  
All fields must be filled.  
The new user is appended to the `DATA` file.  

#### 2. Delete User
- Select `Delete user`.  
- Enter the **username** (first field, `Name`) you want to delete.  
- If the username does not exist, the program will ask again.  
- Press **Ctrl+D** (EOF) to exit the delete menu without deleting.  

#### 3. List Users
- Select `List user`.  
- All usernames stored in the file are printed with a numbered list.  
- Press **Enter** to return to the main menu.  

#### 4. Update User
- Select `Update user`.  
- Enter the **username** to update.  
- You will be prompted for new values for:
- Name  
- Surname  
- Age  
- Group  
- Empty inputs are not allowed.  
- Press **Ctrl+D** to exit the update menu.  
- The existing line in `DATA` is replaced with the new values.  

#### 5. Quit
- Select `Quit` to exit the program.  

---

### Notes / Tips
- The program uses **terminal input** and ANSI escape codes (`\033[H\033[J`) to clear the screen.  
- Usernames are considered **case-sensitive** when deleting or updating.  
- Each user is stored on a separate line, so you can manually inspect the `DATA` file if needed.  
- Input validation ensures no empty fields are written to the file.  
