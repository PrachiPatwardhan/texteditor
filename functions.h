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
#include <fcntl.h>
#include <string.h>
#include <menu.h>
/*header file for the linked list structure used to read and store text*/
#define MAXCHAR 80

typedef struct node {
	char string[MAXCHAR];
	struct node *next, *prev; 
	int LineNumber;
}node;

typedef struct list{
	node *head, *tail;
	int LineCount;
}list;

/*Function prototype declarations*/

/*Initialising the list*/
void InitialiseBuffer(list *FileBuffer);

/*Checking if buffer is empty*/
int BufferEmpty(list *FileBuffer);

/*Checking if buffer is full*/
int BufferFull(list *FileBuffer);

/*Will store the read line in a new node and link to end of file buffer */
void AppendtoBuffer(list *FileBuffer, char *ReadLine);

/*Will print the entire file (in the buffer)*/
void PrintBuffer(list *FileBuffer, WINDOW *my_menu_win);

/*Will open a file in the buffer*/
void OpenFile(list *FileBuffer, char *Filename);

/*Will save the buffer as a file*/
void SaveFile(list *FileBuffer, char *Filename);

/*Will free the entire buffer*/
void FreeBuffer(list *FileBuffer);

/*Will edit a line in the file*/
void EditBuffer(list *FileBuffer, int LineNo, char *NewString);

/*Will insert a node in the buffer*/
void InsertBuffer(list *FileBuffer, int LineNo, char *InsertString);

/*Will delete a node from the buffer given line number*/
void DeleteBufferLineNo(list *FileBuffer, int LineNo);
