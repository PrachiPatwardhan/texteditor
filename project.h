/*header file for the linked list structure used to read and store text*/

typedef struct node {
	char string[MAXCHAR];
	node *next; 
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

/*Will store the read line in a new node and link to file buffer */
void ReadtoBuffer(list *FileBuffer, char *ReadLine);

/*Will print the entire file (in the buffer)*/
void PrintBuffer(list *FileBuffer, char *Filename);

/*Will save the buffer as a file*/
void SaveFile(list *FileBuffer, char *Filename);

/*Will free the entire buffer*/
void FreeBuffer(list *FileBuffer);
