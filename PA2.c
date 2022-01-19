#include "PA2.h"

void initialize(List* plist)
{
	plist->head = NULL;
}

Node* makeNode(Record * data)
{
	Node* pMem = (Node*)malloc(sizeof(Node));

	if (pMem != NULL)
	{
		pMem->next = NULL;
		pMem->prev = NULL;

		pMem->data = (Record*)malloc(sizeof(Record));

		if (pMem->data != NULL)
		{

			pMem->data->artist = (char*)malloc(sizeof(char) * strlen(data->artist) + 1);
			strcpy(pMem->data->artist, data->artist);

			pMem->data->album_title = (char*)malloc(sizeof(char) * strlen(data->album_title) + 1);
			strcpy(pMem->data->album_title, data->album_title);

			pMem->data->song_title = (char*)malloc(sizeof(char) * strlen(data->song_title) + 1);
			strcpy(pMem->data->song_title, data->song_title);

			pMem->data->genre = (char*)malloc(sizeof(char) * strlen(data->genre) + 1);
			strcpy(pMem->data->genre, data->genre);

			pMem->data->songLength = data->songLength;
			pMem->data->Number_times_played = data->Number_times_played;
			pMem->data->Rating = data->Rating;

		}
	}
	return pMem;
}


int insertFront(Node ** plist, Record* data)
{
	Node* pMem = makeNode(data);

	int success = 0;

	if (pMem != NULL)
	{
		if (pMem->data != NULL)
		{
			success = 1;

			if ((*plist)->data == NULL)
			{
				*plist = pMem;
			}
			else
			{
				pMem->next = *plist;
				(*plist)->prev = pMem;
				(*plist) = pMem;
			}

		}
	}

	return success;
}

int insert_at_front(List* plist, Record* data)
{
	Node* newnode = makeNode(data);
	int success = 0;

	if (newnode != NULL)
	{
		if (newnode->data != NULL)
		{
			success = 1;
			if (plist->head == NULL)
			{
				plist->head = newnode;
			}
			else
			{
				newnode->next = plist->head;
				plist->head->prev = newnode;
				plist->head = newnode;
			}
		}

	}
	return success;
}

void printList(Node* pdata)
{
	if (pdata == NULL)
		return;
	else
		printf("%s %s %s %s %d:%d %d %d", pdata->data->artist, pdata->data->album_title, pdata->data->song_title,
			pdata->data->genre, pdata->data->songLength.minutes, pdata->data->songLength.Seconds, pdata->data->Number_times_played, pdata->data->Rating);
	printList(pdata->next);
}

void load(Node* pMem, FILE* infile)
{

	Record record1 = { " ", " ", " ", " ",{ -1, -1 }, -1, -1 };

	char line[256] = " ";
	char delim[2] = ",";
	char lim[2] = ":";
	char dlim = '\"';
	char hold[25] = " ";
	char hold2[25] = " ";

	//char * duration;

	if (infile != NULL)
	{
		while (fgets(line, 256, infile) != NULL)
		{
			//"Swift, Taylor", 1989, Shake it Off, Pop, 3:35, 12, 3

		/*	strcpy(data->artist, strtok(line, delim));
			strcpy(data->album_title, strtok(NULL, delim));
			strcpy(data->song_title, strtok(NULL, delim));
			strcpy(data->genre, strtok(NULL, delim));

			data->songLength.minutes = atoi(strtok(NULL, lim));
			data->songLength.Seconds = atoi(strtok(NULL, lim));

			data->Number_times_played = atoi(strtok(NULL, delim));
			data->Rating = atoi(strtok(NULL, delim));

			insertFront(plist->head, data);*/

			//old = strtok(line, dlim);

			strcpy(hold, strtok(line, ","));

			if (hold[0] == '\"')
			{

				strncpy(hold2, hold + 1, strlen(hold));
				hold2[strlen(hold2) - 1] = '\0';
				
				record1.artist = hold2;
				//stycpy(record1.artist, hold2);
				//Taylor Swift
			}
			else
			{
				record1.artist = hold;
			}

				//record1.artist = strtok(line, delim);

				record1.album_title = strtok(NULL, delim);
				//printf("%s\n", record1.album_title);

				record1.song_title = strtok(NULL, delim);
				//printf("%s\n", record1.song_title);

				record1.genre = strtok(NULL, delim);
				//printf("%s\n", record1.genre);

				record1.songLength.minutes = atoi(strtok(NULL, lim));
				//printf("%d:", record1.songLength.minutes);


				record1.songLength.Seconds = atoi(strtok(NULL, delim));
				//printf("%d\n", record1.songLength.Seconds);

				//duration = strtok(NULL, delim);


				record1.Number_times_played = atoi(strtok(NULL, delim));
				//printf("%d\n", record1.Number_times_played);
				record1.Rating = atoi(strtok(NULL, delim));
				//printf("%d\n", record1.Rating);

				/*record1.songLength.minutes = atoi(strtok(duration, lim));
				printf("%d\n", record1.songLength.minutes);
				record1.songLength.Seconds = atoi(strtok(NULL, lim));
				printf("%d\n", record1.songLength.Seconds);*/

				insert_at_front(pMem, &record1);
				//insertFront(&pMem, &record1);

			
		}
			
			}
		
	//return pMem;
}
		


void store(Node* pMem, FILE* outfile)
{
	Node* temp = pMem;
	while (temp != NULL)
	{
		fprintf(outfile, "%s, %s, %s, %s, %d:%d, %d, %d\n", temp->data->artist, temp->data->album_title, temp->data->song_title,
			temp->data->genre, temp->data->songLength.minutes, temp->data->songLength.Seconds, temp->data->Number_times_played, temp->data->Rating);

		//update the pointer
		
		temp = temp->next;
	}

}

void display(Node* pMem)
{
	int input = 0;
	char artist[20];

	printf("Choose from option below: \n");
	printf("1. Print all records: \n");
	printf("2. print all records that match an artist: \n");
	scanf("%d", &input);

	if (input == 1)
	{
		if (pMem != NULL)
		{

			printf("MusicPlayList: %s, %s, %s, %s, %d:%d, %d, %d\n", pMem->data->artist, pMem->data->album_title, 
				pMem->data->song_title, pMem->data->genre, pMem->data->songLength.minutes, pMem->data->songLength.Seconds,
				pMem->data->Number_times_played, pMem->data->Rating);
			printList(pMem->next);
		}
	}
	else if (input == 2)
	{
		Node* temp = pMem;

		printf("Enter an artist name: ");
		//scanf("%s", &artist);
		fgets(artist, 20, stdin);
		fgets(artist, 20, stdin);
		artist[strlen(artist) - 1] = '\0';

		while (temp != NULL)
		{
			if (strcmp(artist, temp->data->artist) == 0)
			{
				printf("Songs by %s: \n%s\n", artist, temp->data->song_title);
			}
			temp = temp->next;
		}

	}
	else
	{
		printf("---------------Invalid------------------\n");
	}

}

void play(Node* pMem)
{
	int input = 0;
	char song[20];
	int option = 0;

	printf("Choose from option below: \n");
	printf("1. For playing all songs: \n");
	printf("2. For searching for specific song title: \n");

	scanf("%d", &option);

	if (option == 1)
	{
		if (pMem != NULL)
		{
			if (pMem->data != NULL)
			{
				printf("MusicPlayList: %s, %s, %s, %s, %d:%d, %d, %d\n", pMem->data->artist, pMem->data->album_title,
					pMem->data->song_title, pMem->data->genre, pMem->data->songLength.minutes, pMem->data->songLength.Seconds,
					pMem->data->Number_times_played, pMem->data->Rating);
				printList(pMem->next);
			}
		}

	}
	else if (option == 2)
	{
		Node* temp = pMem;
		printf("Enter the song title: \n");
		fgets(song, 20, stdin);
		fgets(song, 20, stdin);
		song[strlen(song) - 1] = '\0';

		while (temp != NULL)
		{
			if (strcmp(song, temp->data->song_title) == 0)
			{
				printf("Here is your request Song by %s: \n%s\n", song, temp->data->song_title);
			}
			else
			{
				printf("Next record song in the list: %s \n", temp->data->song_title);
			}

			temp = temp->next;
		}
	}
}

void edit(Node** pMem)
{
	Node* temp = *pMem;
	char artist[20];
	int rating = 0;
	int option = 0;
	
	printf("Enter the Artist: \n");
	//scanf("%s", artist);


	fgets(artist, 20, stdin);
	fgets(artist, 20, stdin);


	artist[strlen(artist) - 1] = '\0';

	while (temp != NULL)
	{
		if (strcmp(artist, temp->data->artist) == 0)
		{
		
			printf("%s \n", temp->data->song_title);

		}
		temp = temp->next;

	}

	temp = *pMem;

	printf("Enter the song title: \n");
	
	fgets(artist, 20, stdin);
	//fgets(artist, 20, stdin);


	artist[strlen(artist) - 1] = '\0';
	

	while (temp != NULL)
	{
		if (strcmp(artist, temp->data->song_title) == 0)
		{

			printf("Enter 1 for Artist: \n");
			printf("Enter 2 for Album Title: \n");
			printf("Enter 3 for Song Title: \n");
			printf("Enter 4 for Times played: \n");
			printf("Enter 5 for Rating: \n");


			scanf("%d", &option);

			switch (option)
			{
			case 1:
				printf("Enter the Artist name you want to edit in your record: ");
				fgets(artist, 20, stdin);
				fgets(artist, 20, stdin);
				artist[strlen(artist) - 1] = '\0';
				strcpy(temp->data->artist, artist);
				break;

			case 2:
				printf("Enter the Album Title name you want to edit in your record: ");
				fgets(artist, 20, stdin);
				fgets(artist, 20, stdin);
				artist[strlen(artist) - 1] = '\0';
				strcpy(temp->data->album_title, artist);
				break;

			case 3:
				printf("Enter the Song Title name you want to edit in your record: ");
				fgets(artist, 20, stdin);
				fgets(artist, 20, stdin);
				artist[strlen(artist) - 1] = '\0';
				strcpy(temp->data->song_title, artist);
				break;

			case 4:
				printf("Enter the song times played you want to edit in your record: ");
				scanf("%d", &rating);
				temp->data->Number_times_played = rating;
				break;

			case 5:
				printf("Enter the song rate you want to edit in your record: ");
				scanf("%d", &rating);
				temp->data->Rating = rating;
				break;
			}
		}
		temp = temp->next;
	}

}


//Node * rate(Node * pMem)
//{
//	Node* plist = pMem;
//	int newRating;
//	char song[20];
//
//	printf("Enter a song you would like to change rating for: \n");
//	//scanf("%[^\n]s", song);
//	fgets(song, 20, stdin);
//	fgets(song, 20, stdin);
//
//	song[strlen(song) - 1] = '\0';
//
//	printf("Enter the rate of this song: \n");
//	scanf("%d", &newRating);
//
//	while (plist != NULL)
//	{
//		if (strcmp(song, plist->data->song_title) == 0)
//		{
//			plist->data->Rating = newRating;
//		}
//		plist = plist->next;
//	}
//
//	return pMem;
//
//}

void rate(Node** pMem)
{
	Node* temp = *pMem;
	int rating = 0;
	char str[20];

	printf("Enter the song title: ");
	
	fgets(str, 20, stdin);
	fgets(str, 20, stdin);

	str[strlen(str) - 1] = '\0';

	printf("Enter the song rate: ");
	scanf("%d", &rating);

	while (temp != NULL)
	{
		if (strcmp(str, temp->data->song_title) == 0)
		{
			
			/*printf("Enter the song rate: ");
			scanf("%d", &rating);*/
			temp->data->Rating = rating;
		}
		temp = temp->next;
	}

}

int insert(List* plist)
{
	Record data = { "", "", "", "",{ -1, -1 }, -1, -1 };
	int success = 0;
	Node* temp = plist->head;
	Node* newnode = makeNode(&data);
	char newRecord[20];
	int newData = 0;

	if (newnode != NULL)
	{
		if (newnode->data != NULL)
		{
			success = 1;
			//prmopt the new Record

			printf("-------------Enter the details of a new record from the user-----------------\n\n");
			printf("Enter the new Artist: ");
			fgets(newRecord, 20, stdin);
			fgets(newRecord, 20, stdin);
			newRecord[strlen(newRecord) - 1] = '\0';
			strcpy(newnode->data->artist, newRecord);


			printf("Enter the new album Title: ");
			fgets(newRecord, 20, stdin);
			newRecord[strlen(newRecord) - 1] = '\0';
			strcpy(newnode->data->album_title, newRecord);

			printf("Enter the new song title: ");
			fgets(newRecord, 20, stdin);
			newRecord[strlen(newRecord) - 1] = '\0';
			strcpy(newnode->data->song_title, newRecord);

			printf("Enter the new genre: ");
			fgets(newRecord, 20, stdin);
			newRecord[strlen(newRecord) - 1] = '\0';
			strcpy(newnode->data->genre, newRecord);

			printf("Enter the new song length minutes: ");
			scanf("%d", &newData);
			newnode->data->songLength.minutes = newData;

			printf("Enter the new song length Seconds: ");
			scanf("%d", &newData);
			newnode->data->songLength.Seconds = newData;

			printf("Enter the new number play: ");
			scanf("%d", &newData);
			newnode->data->Number_times_played = newData;

			printf("Enter the new rate: ");
			scanf("%d", &newData);
			newnode->data->Rating = newData;

			if (plist->head == NULL)
			{
				success = 1;
				plist->head = newnode;
			}
			else
			{
				success = 1;
				newnode->next = plist->head;
				plist->head = newnode;
			}

		}
	}
	return success;
}

int deleteRecord(List* plist)
{
	Node* pCur = plist->head;
	Node* pPrev = NULL;
	Node* temp;
	char songtitle[20];
	int success = 0;

	printf("Enter the song title you want to delete: ");
	fgets(songtitle, 20, stdin);
	fgets(songtitle, 20, stdin);

	songtitle[strlen(songtitle) - 1] = '\0';


	while (pCur != NULL) //loop till not NULL
	{
		if (strcmp(pCur->data->song_title, songtitle) == 0) //if the song title match
		{
			success = 1;
			if (plist->head->next == NULL && plist->head->prev == NULL ) //if list is an empty
			{
				success = 1;
				temp = plist->head;
				plist->head = NULL;
				pCur = NULL;
				free(temp);
				break;

			}
			else if (pPrev == NULL) //if the delete one is first node
			{
				success = 1;
				temp = pCur;
				plist->head = pCur->next;
				plist->head->prev = NULL;
				free(temp);
				break;

			}
			else if (pCur->next == NULL) //checking the last
			{
				success = 1;
				temp = pCur;
				pPrev->next = NULL; //pPrev next should be pCur but set to NULL because pPrev is going to be the last node
				free(temp);
				break;

			}
			else
			{

				//checking the middle
				temp = pCur;
				pPrev->next = pCur->next;
				pCur->next->prev = pPrev;
				success = 1;

				/*pCur->prev->next = pCur->next;
				pCur->next->prev = pCur->prev;*/
				
				free(temp);
				break;
			}
		}


		pPrev = pCur;
		pCur = pCur->next;
	}
	return success;
}

//Record* deleteRecord(List* plist)
//{
//	Node* pCur = plist->head;
//	Node* pPrev = NULL;
//	Node* temp;
//	char songtitle[20];
//	int success = 0;
//
//	Record* d1 = { NULL };
//
//	d1 = pCur->data->song_title;
//
//	printf("Enter the song title you want to delete: ");
//	fgets(songtitle, 20, stdin);
//	fgets(songtitle, 20, stdin);
//
//	songtitle[strlen(songtitle) - 1] = '\0';
//
//
//	while (pCur != NULL) //loop till not NULL
//	{
//		if (strcmp(pCur->data->song_title, songtitle) == 0) //if the song title match
//		{
//			success = 1;
//			if (pPrev == NULL) //if the delete one is first node
//			{
//				success = 1;
//				temp = pCur;
//				plist->head = pCur->next;
//				plist->head->prev = NULL;
//				free(temp);
//				break;
//
//			}
//			else if (pCur->next == NULL) //checking the last
//			{
//				success = 1;
//				temp = pCur;
//				pPrev->next = NULL; //pPrev next should be pCur but NULL because pPrev is going to be the last node
//				free(temp);
//				break;
//
//			}
//			else
//			{
//				success = 1;
//				//checking the middle
//				temp = pCur;
//				pPrev->next = pCur->next;
//				pCur->next->prev = pPrev;
//
//				/*pCur->prev->next = pCur->next;
//				pCur->next->prev = pCur->prev;*/
//
//				free(temp);
//				break;
//			}
//		}
//
//
//		pPrev = pCur;
//		pCur = pCur->next;
//	}
//	return d1;
//}
//
//void swap(Node* a, Node* b)
//{
//	char temp = a->data;
//	a->data = b->data;
//	b->data = temp;
//}


void sort(List* plist)
{

	Node* pCur;
	Node* pPrev = NULL;
	Record * d = { NULL };
	int option = 0;
	int swapped = 0;

	printf("Enter the sort method below: \n");
	printf("1. For sorting based on artist (A-Z)\n");
	printf("2. For sorting based on album title (A-Z)\n");
	printf("3. For sorting based on rating (1-5)\n");
	printf("4. For sorting based on times played (largest-smallest)\n");

	scanf("%d", &option);

	if (option == 1)
	{
		do
		{
			pCur = plist->head;
			swapped = 0;


			while (pCur->next != NULL)
			{
				if (strcmp(pCur->data->artist, pCur->next->data->artist) > 0)
				{

					d = pCur->data;
					pCur->data = pCur->next->data;
					pCur->next->data = d;
					swapped = 1;

				}

				pCur = pCur->next;
			}

		} while (swapped == 1);


	}

	else if (option == 2)
	{
		do
		{
			pCur = plist->head;
			swapped = 0;

			while (pCur->next != NULL)
			{
				if (strcmp(pCur->data->album_title, pCur->next->data->album_title) > 0)
				{
					d = pCur->data;
					pCur->data = pCur->next->data;
					pCur->next->data = d;
					swapped = 1;
				}
				pCur = pCur->next;
			}

		} while (swapped == 1);
	}

	else if (option == 3)
	{
		do
		{
			pCur = plist->head;
			swapped = 0;

			while (pCur->next != NULL)
			{
				if (pCur->data->Rating > pCur->next->data->Rating)
				{
					d = pCur->data;
					pCur->data = pCur->next->data;
					pCur->next->data = d;
					swapped = 1;
				}
				pCur = pCur->next;
			}
		} while (swapped == 1);
	}

	else if (option == 4)
	{
		do
		{
			pCur = plist->head; //first node
			swapped = 0;

			while (pCur->next != NULL)
			{
				if (pCur->data->Number_times_played < pCur->next->data->Number_times_played) //largest to smallest
				{
					d = pCur->data;
					pCur->data = pCur->next->data;
					pCur->next->data = d;
					swapped = 1;
				}
				pCur = pCur->next;
			}
		} while (swapped == 1);
	}
	else
	{
		printf("Invalid");
	}
}

//15 pts – Correct “shuffle” command implementation
//
//1.    (5 pts) For generating the random order based on the number of songs in the list
//
//2.    (10 pts) For moving through the list(forwards and backwards) and playing the songs in the order generated
int shuffle(List* plist)
{
	int success = 0;
	Node* pHead = plist->head;
	int temp = 0;
	int size = 0;
	int random_num = 0;
	srand((unsigned int) time(NULL));

	while (pHead != NULL)
	{
		pHead = pHead->next;
		size++;
	}
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };


	for (int i = 0; i < size; i++)
	{
		success = 1;
		random_num = rand() % size;
		temp = arr[i];
		arr[i] = arr[random_num];
		arr[random_num] = temp;
	}

	pHead = plist->head; //set to zero line

	for (int i = 0; i < size; i++)
	{//number of songs 
		for (int j = 0; j < arr[i]; j++)
		{ //find the song the specific one in the list
			pHead = pHead->next;
		}
		success = 1;
		
		printf("MusicPlayList: %s, %s, %s, %s, %d:%d, %d, %d\n", pHead->data->artist, pHead->data->album_title,
			pHead->data->song_title, pHead->data->genre, pHead->data->songLength.minutes, pHead->data->songLength.Seconds,
			pHead->data->Number_times_played, pHead->data->Rating);
		//printf("\n");
		//printf("\n");
		pHead = plist->head; //traverse line
	}
	return success;
}

void display_menu()
{
	printf("Please choose from the option below: \n");
	printf("1. load \n");
	printf("2. store \n");
	printf("3. display \n");
	printf("4. insert \n");
	printf("5. delete \n");
	printf("6. edit \n");
	printf("7. sort \n");
	printf("8. rate \n");
	printf("9. play \n");
	printf("10. shuffle \n");
	printf("11. Exit. \n");

}

int getoption()
{
	int option = 0, status = 0;
	
	status = scanf("%d", &option);

	if (status < 1 || status > 11)
	{
		printf("Invalid type of input ");
	}

	return option;
}

int determineOption()
{
	int option = 0;

	do
	{
		display_menu();
		option = getoption();
		system("cls");

		if ((option < 1) || (option > 11))
		{
			printf("Invalid option\n\n");
		}
	} while ((option < 1) || (option > 11));

	return option;
}