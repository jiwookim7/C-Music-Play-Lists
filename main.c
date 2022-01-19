/***************************************************************************************
Programmer's name: Jiwoo Kim
Class: CptS 122 Summer 2021
Programming Assignment: Programming Assignment 3: Digital Music Manager & Doubly Linked Lists – Part II
Date: 06/27/21
****************************************************************************************/

#include "PA2.h"
#include "Test.h"

int main(void)
{
	List pList;

	initialize(&pList);

	FILE* infile = NULL;
	FILE* outfile = NULL;
	
	infile = fopen("musicPlayList.csv", "r");
	outfile = fopen("Result.csv", "w");

	if (infile == NULL)
	{
		printf("FILE DOES NOT EXIST");
	}

	if (outfile == NULL)
	{
		printf("FILE DOES NOT EXIST");
	}

	//pList.head = load(&pList.head, infile);

	int option = 0;
	int success = 0;
	//Record* d1 = { "Own it" };
	
	while (option != 11)
	{
		option = determineOption();

		switch (option)
		{
		case 1:
			load(&pList.head, infile);
			break;
		case 2: 
			store(pList.head, outfile);
			break;
		case 3:
			display(pList.head);
			break;
		case 4:
			success = insert(&pList);
			break;
		case 5:
			success = deleteRecord(&pList);
			//d1 = deleteRecord(&pList);
			break;
		case 6:
			edit(&pList.head);
			break;
		case 7:
			sort(&pList);
			break;
		case 8:
			//pList.head = rate(pList.head);
			rate(&pList.head);
			break;
		case 9:
			play(pList.head);
			break;
		case 10:
			success = shuffle(&pList);
			break;
		case 11:
			printf("Music play list is terminated...\n\n");
			break;
		}
	}

	//printList(pList.head);

	//testInsert();
	//testdelete();

	fclose(infile);

	//testshuffle();

	//fclose(infile);
	fclose(outfile);
	
	return 0;

}