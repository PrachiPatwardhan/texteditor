/*Implementation of a text editor using a linked list data structure*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "project.h" 

int main(){
	return 0;
}
 
/*Initialising the list*/
void InitialiseBuffer(list *FileBuffer){
	FileBuffer->head = NULL;
	FileBuffer->tail = NULL;
	FileBuffer->LineCount = 0;
}

/*Checking if buffer is empty*/
int BufferEmpty(list *FileBuffer){
	if (FileBuffer->head == NULL)
		return 1;
	return 0;	
}

/*Checking if buffer is full*/
int BufferFull(list *FileBuffer){
	//buffer isnt full unless malloc fails
	return 0; 	
}
 
/*Will store the read line in a new node and link to file buffer */
void ReadtoBuffer(list *FileBuffer, char *ReadLine){
	node *newnode;
	
	newnode = (node *)malloc(sizeof(node));
	
	//Checking if the malloc has worked
	if (newnode == NULL)
		return;
	
	//Assertion: malloc has not failed
	strcpy(newnode->string, ReadLine);
	newnode->LineNuber = (++FileBuffer->LineCount);
	newnode->next = NULL;
	
	//Linking the new node
	if (FileBuffer->tail)
		FileBuffer->tail->next = newnode;
	FileBuffer->tail = newnode;
	if (FileBuffer->head == NULL)
		FileBuffer->head = newnode;
}

/*Will print the entire file (in the buffer)*/
void PrintBuffer(list *FileBuffer, char *Filename){
	printf("%s:\n", Filename);
	node *p;
	p = FileBuffer->head;
	while (p){
		if (p->LineNumber < 10)
			printf("0%d. %s\n",p->LineNumber, p->string);
		else
			printf("%d. %s\n",p->LineNumber, p->string);			
		p = p->next;
	}
}

/*Will save the buffer as a file*/
void SaveFile(list *FileBuffer, char *Filename){
	int fd;
	fd = open(Filename, O_WRONLY, S_IWUSR);
	
	node *p;
	p = FileBuffer->head;
	if (p == NULL)	
		return;
		
	while (p){
		write(fd, p->string, sizeof(p->string));
		p = p->next;
	}	
	close(fd);
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
