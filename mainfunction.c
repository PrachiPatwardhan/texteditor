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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "window.h"
#include <menu.h>
#define MENU_OPTIONS 6

char *menu_options[]={
						"Open",
						"New",
						"Save",
						"Save As",
						"Edit",
						"Exit",
					};
						
int nchoices = sizeof(menu_options) / sizeof(char *);

int main(){

	WINDOW *my_win, *menu_win, *my_menu_win;
	ITEM **my_items;
	MENU *my_menu;
	list *FileBuffer;
	
	int height, width, startx, starty, exit = 0;
	int highlight = 1;
	int ch, c, choice = 0, i, j;
	char str[81];
	
	FileBuffer = (list *)malloc(sizeof(list));
	
	
	if (FileBuffer == NULL)
		return;
	
	InitialiseBuffer(FileBuffer);
	
	initscr();
	clear();
	noecho();
	cbreak();
	
	start_color();
	
	
	/*Checking whether the terminal supports colors*/
	if (has_colors() == FALSE){
		endwin();
		printf("Your terminal does not support colors\n");
	}
		
	
	keypad(stdscr, TRUE);
	
	height = 3;
	width = 10;
	starty = (LINES - height)/2;
	startx = (COLS - width) / 2;	

	refresh();
	
	my_win = Create_NewWindow(height, width, starty, startx);

	mvwhline(my_win, 5, 1,	ACS_HLINE, width - 1);
	
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_CYAN, COLOR_BLACK);
	
	/* Create items */
    my_items = (ITEM **)calloc(nchoices, sizeof(ITEM *));
    for(i = 0; i < nchoices; ++i)
    	my_items[i] = new_item(menu_options[i], menu_options[i]);

	/* Create menu */	
	my_menu = new_menu((ITEM **)my_items);

	/* Set menu option not to show the description */
	menu_opts_off(my_menu, O_SHOWDESC);

	/* Create the window to be associated with the menu */
    my_menu_win = newwin(0, 0, 0, 0);
    keypad(my_menu_win, TRUE);
     
	/* Set main window and sub window */
    set_menu_win(my_menu, my_menu_win);
	set_menu_sub(my_menu, derwin(my_menu_win, 0, 0, 0, 0));
 	set_menu_format(my_menu, 1, 6);
	set_menu_mark(my_menu, " * ");


	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_menu_win);
	
	i = 0;
		
	mvwhline(my_menu_win, 1, 0, ACS_HLINE, COLS);
	mvwprintw(my_menu_win, LINES - 1, 0, "Press F3 to go to the menu, F6 to exit", c);
	
	
	while(1){
		choice = ToggleMenu(my_menu_win, my_menu, i);
		i = choice;
		switch(choice){
			case 0:
				MenuOpen(FileBuffer, my_menu_win);
				break;
			case 1:
				MenuNew(FileBuffer, my_menu_win, my_menu);
				break;
			case 2:
				MenuSave(FileBuffer, my_menu_win);
				break;
			case 3:
				MenuSaveAs(FileBuffer, my_menu_win);
				break;
			case 4:
				MenuEdit(FileBuffer, my_menu_win);
				break;
			case 5:
				MenuExit(FileBuffer, my_menu_win);
				exit = 1;
				break;
			default:
				break;
		}
		if (exit)
			break;
	}
	/*Assertion: the user wants to exit the program*/
    
		
	/* Unpost and free all the memory taken up */
       unpost_menu(my_menu);
       free_menu(my_menu);
       for(j = 0; j < nchoices; ++j)
               free_item(my_items[j]);
                
	clrtoeol();
	refresh();	
	
	/*Ending curses mode*/
	
	endwin();		
	return 0;
}
