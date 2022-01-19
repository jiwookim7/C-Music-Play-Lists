#ifndef PA2_H
#define PA2_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>

typedef struct duration
{
	int minutes;
	int Seconds;
}Duration;

typedef struct record
{
	char* artist;
	char* album_title;
	char* song_title;
	char* genre;
	Duration songLength;
	int Number_times_played;
	int Rating;

}Record;

typedef struct node
{
	Record * data;
	struct node* prev;
	struct node* next;
}Node;

typedef struct list
{
	Node* head;
}List;

void initialize(List* plist);

Node* makeNode(Record* data); //doubly linked list

int insertFront(Node** plist, Record* data); //first way to insert at front

void printList(Node* pdata); //recursive

/*Correct “play” command implementation

1.For playing all songs in order until the end of the list

2.For searching for specific song based on song titleand playing all songs until the end of the list has been reached*/

void play(Node* pMem);

/*For correctly opening musicPlayList.csv for mode “read”

2. For correctly extracting each attribute from each record in the file

3. For correctly using insertFront()

4. For correctly closing musicPlayList.csv */

void load (Node * pMem, FILE* infile);

//The “store” command writes the current records, in the dynamic doubly linked list, to the musicPlayList.csv file.
//The store will completely overwrite the previous contents in the file.

void store(Node* pMem, FILE* outfile);

//The “display” command prints records to the screen. This command must support two methods, one of which is selected by the user:

/*1.Print all records.
2.Print all records that match an artist.*/

void display(Node* pMem);

//The “edit” command must allow the user to find a record in the list by artist.If there are multiple records with the same artist, 
//then your program must prompt the user which one to edit.The user may modify all of the attributes in the record.

void edit(Node ** pMem);

//Node* rate(Node* pMem); first way

//The “rate” command must allow the user to assign a value of 1 – 5 to a song; 
//1 is the lowest rating and 5 is the highest rating. The rating will replace the previous rating.

void rate(Node** pMem); //second way

int insert_at_front(List* plist, Record* data); //second way to insert at front

//The “insert” command must prompt the user for the details of a new record. 
//The prompt must request the artist name, album title, song title, genre, song length, number of times played, and rating. 
//The new record must be inserted at the front of the list.
int insert(List* plist);

//The “delete” command must prompt the user for a song title, and remove the matching record from the list. 
//If the song title does not exist, then the list remains unchanged.
int deleteRecord(List* plist);

//Record * deleteRecord(List* plist);

//The “sort” command must prompt the user for 4 different methods to sort the records in the list.These include :
//
//1.    Sort based on artist(A - Z)
//
//2.    Sort based on album title(A - Z)
//
//3.    Sort based on rating(1 - 5)
//
//4.    Sort based on times played(largest - smallest)
//
//Once a sort method is selected by the user, the sort must be performed on the records in the list.Consider using bubble sort, insertion sort, or selection sort.
void sort(List* plist);

//The “shuffle” command must provide a random order in which the songs are played.This command must not modify the links in the list.
//It must just specify the order in which songs are played, based on the position of the song in the list.
//For example, let’s say we have a list with 5 songs at positions 1 – 5 in the list, shuffle must generate an order 1 – 5 in which the songs are played.
//An order 2, 5, 3, 1, 4 would require that the second song in the list is played first, 
//the fifth song in the list is played second, the third song in the list is played third, 
//the first song in the list is played fourth, and the fourth song in the list is played fifth.
//The songs are accessed by traversing the list both forwardsand backwards to satisfy the order.
//Hence, the need for a doubly linked list!
int shuffle(List* plist);

int determineOption();

#endif
