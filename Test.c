#include "Test.h"

void testInsert(void)
{
	List a;
	initialize(&a);

	int result = 0;
	
	result = insert(&a);


	if (result)
		printf("Successfully inserted the record in your file\n\n");
	else
		printf("Failure to insert the record in your file\n\n");
}

void testdelete(void)
{
	List a;
	initialize(&a);

	Record  data = { "", "", "Own it", "",{ -1, -1 }, -1, -1 };
	
	int success = 0;

	success = insert_at_front(&a,&data);

	success = deleteRecord(&a);

	if (success == 1)
		printf("Successfully delete the song title in your Music record \n");
	else
		printf("Failure to delete the song title in your Music record \n");
}

void testshuffle(void)
{
	List a;
	initialize(&a);
	
	int success = 0;

	FILE* infile = NULL;

	infile = fopen("musicPlayList.csv", "r");

	if (infile == NULL)
	{
		printf("FILE DOES NOT EXIST. \n");
	}

	load(&a.head, infile);

	success = shuffle(&a);

	if (success == 1)
		printf("Succssfully shuffle your Music record in your player \n");
	else
		printf("Failure to shuffle your Music record in your player \n");


	fclose(infile);
}

	


