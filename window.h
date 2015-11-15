/*Copyright 2015 Prachi Patwardhan

This program is a part of the project Charlie.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <curses.h>
#include <menu.h>
#include "functions.h"


/*Creates a new window*/
WINDOW *Create_NewWindow(int height, int width, int starty, int startx);

/*Deletes the window*/
void Destroy_Window(WINDOW *local_win);

//Toggles between the options on the menu bar
int ToggleMenu(WINDOW *my_menu_win, MENU *my_menu, int i);

//Opens a file
void MenuOpen(list *FileBuffer, WINDOW *my_menu_win);

//Opens a new window
void MenuNew(list *FileBuffer, WINDOW *my_menu_win, MENU *my_menu);

//Saves the current file
void MenuSave(list *FileBuffer, WINDOW *my_menu_win);

//Saves the current file under another name
void MenuSaveAs(list *FileBuffer, WINDOW *my_menu_win);

//Edit the current file
void MenuEdit(list *FileBuffer, WINDOW *my_menu_win);
	
//Exits from the program	
void MenuExit(list *FileBuffer, WINDOW *my_menu_win);
