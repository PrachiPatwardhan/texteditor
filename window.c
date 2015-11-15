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

/*Creates a new window*/
WINDOW *Create_NewWindow(int height, int width, int starty, int startx){
	WINDOW *local_win;
	
	local_win = newwin(height, width, starty, startx);
	
	assume_default_colors(COLOR_WHITE, COLOR_BLACK);
	
	
	return local_win;
}

/*Deletes the window*/
void Destroy_Window(WINDOW *local_win){	
	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	
	wrefresh(local_win);
	delwin(local_win);
}

//Toggles between the options on the menu bar
int ToggleMenu(WINDOW *my_menu_win, MENU *my_menu, int i){

	int c, choice;
	choice = 0;
	
	while((c = wgetch(my_menu_win)) != KEY_F(6)){
		switch(c){	
	    	case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				if (i < 5)
					i = i + 1;
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				if (i > 0)
					i = i - 1;
				break;
			case KEY_LEFT:
				menu_driver(my_menu, REQ_LEFT_ITEM);
				if (i > 0)
					i = i - 1;
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_RIGHT_ITEM);
				if (i < 5)
					i = i + 1;
				break;
			case KEY_NPAGE:
				if (i < 5)
					i = i + 1;
				menu_driver(my_menu, REQ_SCR_DPAGE);
				break;
			case KEY_PPAGE:
				if (i > 0)
					i = i - 1;
				menu_driver(my_menu, REQ_SCR_UPAGE);
				break;
			case KEY_ENTER: case KEY_BREAK: case 10: case 13:
				choice = 1;
				break;
		}
		
			
        wrefresh(my_menu_win);
       
        if (choice)
        	break;
	}	
	return i;
}

//Opens a file
void MenuOpen(list *FileBuffer, WINDOW *my_menu_win){
	char str[MAXCHAR];
	int i = 0, c;
	
	mvwprintw(my_menu_win, LINES - 3, 0 , "Enter the name of the file: ");
	int y = LINES - 2, x = 0;
	while((c = wgetch(my_menu_win)) != 10){
		switch(c){
			case KEY_BACKSPACE: case 8:
				if (x > 0){
					x--;
					wmove(my_menu_win, y, x);
					i--;
				}
				mvwprintw(my_menu_win, y, x, " ");	
				str[i] = ' ';
				
				break;
			default:
				str[i] = c;
				i++;
				mvwprintw(my_menu_win, y, x, "%c", c);
				x++;
				break;
		}
	}
	
	str[i] = '\0';
	
	
	OpenFile(FileBuffer, str);
	
	MenuEdit(FileBuffer, my_menu_win);
}


//Opens a new window
void MenuNew(list *FileBuffer, WINDOW *my_menu_win, MENU *my_menu){
	int j;
	MenuExit(FileBuffer, my_menu_win);
	 
	clrtoeol();
	refresh();	
	main();
	exit(1);
}

//Saves the current file
void MenuSave(list *FileBuffer, WINDOW *my_menu_win){
	char str[MAXCHAR];
	int i = 0, c;
	
	//Taking the name of the file from the user
	mvwprintw(my_menu_win, LINES - 3, 0 , "Enter the name of the file: ");
	int y = LINES - 2, x = 0;
	while((c = wgetch(my_menu_win)) != 10){
		switch(c){
			case KEY_BACKSPACE: case 8:
				if (x > 0){
					x--;
					wmove(my_menu_win, y, x);
					i--;
				}
				mvwprintw(my_menu_win, y, x, " ");	
				str[i] = ' ';
				
				break;
			default:
				str[i] = c;
				i++;
				mvwprintw(my_menu_win, y, x, "%c", c);
				x++;
				break;
		}
	}
	
	str[i] = '\0';
	
	SaveFile(FileBuffer, str);
	
	
}

//Saves the current file under another name
void MenuSaveAs(list *FileBuffer, WINDOW *my_menu_win){
	char str[MAXCHAR];
	int i = 0, c;
	
	mvwprintw(my_menu_win, LINES - 3, 0 , "Enter the  new name of the file: ");
	int y = LINES - 2, x = 0;
	
	while((c = wgetch(my_menu_win)) != 10){
		switch(c){
			case KEY_BACKSPACE: case 8:
				if (x > 0){
					x--;
					wmove(my_menu_win, y, x);
					i--;
				}
				mvwprintw(my_menu_win, y, x, " ");	
				str[i] = ' ';
				
				break;
			default:
				str[i] = c;
				i++;
				mvwprintw(my_menu_win, y, x, "%c", c);
				x++;
				break;
		}
	}
	
	str[i] = '\0';
	
	SaveFile(FileBuffer, str);
}

//Edits the current file
void MenuEdit(list *FileBuffer, WINDOW *my_menu_win){
	
	//Printing the existing file in the buffer to the window
	PrintBuffer(FileBuffer, my_menu_win);
	
	int x = 0, y = 2, c, choice = 0;
	int ymax = 2;
	
	//Creating temporary buffers
	char str[100][MAXCHAR], string[MAXCHAR];
	int i = 0, j = 0;
	char ch;
	int ln = 2;
	node *p;
	
	//Copying the contents of the buffer into the 2D temporary buffer
	p = FileBuffer->head;
	while(p){
		strcpy(&str[ln][0], p->string);
		p = p->next;
		ln++;
	}	
	
		
	//If the buffer was non-empty, the contents of the temp buffer will be rewritten
	FreeBuffer(FileBuffer);
	InitialiseBuffer(FileBuffer);
	
	ymax = ln;
	y = ymax;
	x = 0;
	
	//Taking input from the user
	while((c = wgetch(my_menu_win)) != KEY_F(6) ||(c = wgetch(my_menu_win)) != KEY_F(3) ){
		switch(c){
			case KEY_UP:				
				if (y > 2){
					y--;
					wmove(my_menu_win, y, x);
					ln--;
				}
				break;
			case KEY_DOWN:
				y++;
				if (y > ymax)
					ymax = y;
				wmove(my_menu_win, y, x);
				ln++;
				break;
			case KEY_LEFT:
				if (x > 0){
					x--;
					wmove(my_menu_win, y, x);
					i--;
				}
				break;
			case KEY_RIGHT:
				if (x < MAXCHAR){
					x++;
					wmove(my_menu_win, y, x);
					i++;
				}
				break;
			case KEY_BACKSPACE: case 8:
				if (x > 0){
					x--;
					wmove(my_menu_win, y, x);
					i--;
				}
				mvwprintw(my_menu_win, y, x, " ");	
				str[y][x] = ' ';
				
				break;
			case 10: case 13:
				
				str[y][x] = '\n';
				
				y++;
				ln++;
				if (y > ymax)
					ymax = y;
				x = 0;
				wmove(my_menu_win, y, x);
				break;
			//Escape
			case 27:
				choice = 1;
				break;
			default:
				str[y][x] = c;
				//Printing the character read to the screen				
				mvwprintw(my_menu_win, y, x, "%c", c);
				x++;
				
				wmove(my_menu_win, y, x);

				break;
		}
		//If the user has pressed escape
		if (choice)
			break;
	}
	
	//Copying from temp buffer to permanent buffer
	
	for (i = 2; i < ymax ; i++){	
		//for each character that was read
		for (j = 0; str[i][j] != '\n'; j++){
			
			string[j] = str[i][j];
		}
		string[j] = '\0';
		//Reinserting the strings from the temp buffer to the file buffer
		AppendtoBuffer(FileBuffer, string);
	}
	
	

}

	
//Exits from the program	
void MenuExit(list *FileBuffer, WINDOW *my_menu_win){
	FreeBuffer(FileBuffer);

	Destroy_Window(my_menu_win);
	endwin();	
}
