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

/*Implementation of a text editor using a linked list data structure*/

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "functions.h"
#include <menu.h>
 
/*Initialising the list*/
void InitialiseBuffer(list *FileBuffer){
	FileBuffer->head = NULL;
	FileBuffer->tail = NULL;
	FileBuffer->LineCount = 0;
}

/*Checking if buffer is empty*/
int BufferEmpty(list *FileBuffer){
	if (FileBuffer->head == NULL)
		return 0;
	return 1;	
}

/*Checking if buffer is full*/
int BufferFull(list *FileBuffer){
	//buffer isnt full unless malloc fails
	return 0; 	
}
 
/*Will store the read character in the node (or in a new node and link to end of file buffer) */
void AppendtoBuffer(list *FileBuffer, char *ReadLine){
	node *newnode;
	int i;
	
	newnode = (node *)malloc(sizeof(node));
	
	//Checking if malloc has failed
	if (newnode == NULL)
		return;
	
	FileBuffer->LineCount++;
	//Assertion: Malloc has not failed
	//strcpy(newnode->string, ReadLine);
	for(i = 0; i < strlen(ReadLine); i++)
		newnode->string[i] = ReadLine[i];
	newnode->prev = FileBuffer->tail;
	if (FileBuffer->tail)
		FileBuffer->tail->next = newnode;
	newnode->next = NULL;
	newnode->LineNumber = FileBuffer->LineCount;
	
	//Linking the new node
	FileBuffer->tail = newnode;
	if (FileBuffer->head == NULL)
		FileBuffer->head = newnode;
}

/*Will print the entire file (in the buffer)*/
void PrintBuffer(list *FileBuffer, WINDOW *my_menu_win){
	node *p;
	p = FileBuffer->head;
	int y = 2;
	int x = 0;
	while (p){
		mvwprintw(my_menu_win, y, x, "%s\n", p->string);
		//printf("%s\n", p->string);
		p = p->next;
		y++;
	}
}

/*Will open the file into the buffer*/
void OpenFile(list *FileBuffer, char *Filename){
	
	FILE *fp;
	fp = fopen(Filename, "r");
	if (fp == NULL)
		return;
	
	char str[MAXCHAR], ch;
	int i = 0, c;
	int y = 5, x = 0;
	
	//Get the input from the file and store in a string
	c = fgetc(fp);
	while(c != EOF){
	
		str[i] = c;
		i++;
		x++;
		if (c == 10 || c == 13){
			str[i] = '\0';
			//Insert string into the buffer
			AppendtoBuffer(FileBuffer, str);
			i = 0;
			y++;
		}
		c = fgetc(fp);
	}
	
	
	fclose(fp);
}

/*Will save the buffer as a file*/
void SaveFile(list *FileBuffer, char *Filename){
	
	FILE *fp;
	fp = fopen(Filename, "w");
	node *p;
	p = FileBuffer->head;
	if (p == NULL)
		return;
	
	while(p){
		fprintf(fp, "%s\n", p->string);
		p = p->next;
	}
	
	fclose(fp);
}

/*Will free the entire buffer*/
void FreeBuffer(list *FileBuffer){
	node *p;
	p = FileBuffer->head;
	if (p == NULL)
		return;
	
	while (p){
		p = p->next;
		free(FileBuffer->head);
		FileBuffer->head = p;		
	}
	
	InitialiseBuffer(FileBuffer);
}

/*Will edit a line in the file*/
void EditBuffer(list *FileBuffer, int LineNo, char *NewString){
	node *p;
	p = FileBuffer->head;
	while (p->LineNumber < LineNo)
		p = p->next;
		
	strcpy(p->string, NewString);
}

/*Will insert a node in the buffer*/
void InsertBuffer(list *FileBuffer, int LineNo, char *InsertString){
	node *p, *tmp;
	p = FileBuffer->head;
	
	/*Traversing uptil node to be inserted*/
	while (p->LineNumber < LineNo - 1)
		p = p->next;
	
	/*Creating the new node*/
	tmp = (node *)malloc(sizeof(node));
	tmp->LineNumber = LineNo;
	strcpy(tmp->string, InsertString);
	
	/*Inserting the new node*/
	if (LineNo == 1){
		tmp->prev = NULL;
		tmp->next = p;
		FileBuffer->head = tmp;
	}
	else if (LineNo == FileBuffer->LineCount + 1){
		tmp->prev = FileBuffer->tail;
		tmp->next = NULL;
		FileBuffer->tail = tmp;
	}
	
	else{
		tmp->prev = p;
		tmp->next = p->next;
		p->next = tmp;
	}
	
	/*Changing line numbers of the rest of the nodes*/
	p = tmp->next;
	while(p){
		(p->LineNumber)++;
		p = p->next;
	}	
	
	(FileBuffer->LineCount)++;
}

/*Will delete a node from the buffer given line number*/
void DeleteBufferLineNo(list *FileBuffer, int LineNo){
	node *p, *q, *r;
	p = FileBuffer->head;
	
	/*Traversing the list*/
	while (p->LineNumber < LineNo - 1)
		p = p->next;
	
	/*Deleting the node*/
	if (LineNo != 1)
		q = p->next;
	else if (LineNo == 1)
		q = p;
	r = q->next;
	
	if (q == FileBuffer->head)
		FileBuffer->head = r;
		
	if (q == FileBuffer->tail)
		FileBuffer->tail = p;
	
	p->next = r;
	r->prev = p;
	free(q);
	
	/*Changing the subsequent line numbers*/		
	while(r){
		(r->LineNumber)--;
		r = r->next;
	}
	
	(FileBuffer->LineCount)--;	
}
