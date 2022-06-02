#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#include "microdistrict.h"
int check(char* s)
{
	for (int k = 0; k < strlen(s); k++) 
		if ((isspace(s[k]) == 0) && (isalpha(s[k]) == 0))
		{
			printf("\nYour input is incorrect!\n");
			return -1;
		}
	return 0;
}
//работает
int fill_in_base()
{	
	int n;
	FILE* f;
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "wb+")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	printf("Enter the number of citizens - ");
	if ((scanf("%d", &n) != 1) || (n <= 0))
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	for (int i = 0; i < n; i++)
	{
		rewind(stdin);
		printf("\nEnter a full name as in the example: Ivanov_Ivan_Ivanovich - ");
		gets(micro.full_name);
		if (check(micro.full_name) == -1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			return -1;
		}
		printf("\nEnter a street name as in the example: Rublevskoe Highway - ");
		gets(micro.street_name);
		if (check(micro.street_name) == -1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			return -1;
		}
		printf("Enter a house number - ");
		if (scanf("%d", &micro.house_number) != 1 || micro.house_number <= 0)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		printf("Enter a flat number - ");
		if (scanf("%d", &micro.flat_number) != 1 || micro.flat_number <= 0)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		printf("Enter the year of birth - ");
		if (scanf("%d", &micro.year) != 1 || micro.year <= 1900 || micro.year > 2020)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		fwrite(&micro, sizeof(microdistrict), 1, f); 
	}
	fclose(f);
}
//работает
int show_base() 
{
	int i = 1;
	FILE* f;
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "rb")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}

	printf("Your database:\n");
	printf("________________________________________________________________________________________\n");
	printf("|   |                      |               |		  |             |              |\n");
	printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
	printf("|___|______________________|_______________|______________|_____________|______________|\n");

	while (!feof(f))
	{
		fread(&micro, sizeof(microdistrict), 1, f);
		if (!feof(f))
		{
			printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
			i++;
		}
	}

	printf("|___|______________________|_______________|______________|_____________|______________|\n");
	printf("\n");
	fclose(f);
}
//работает
int add_to_base()
{
	FILE* f;
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "ab")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	rewind(stdin);
	printf("Adding a new person to the database");
	printf("\nEnter a full name as in the example: Ivanov_Ivan_Ivanovich - ");
	gets(micro.full_name);
	if (check(micro.full_name) == -1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		return -1;
	}
	printf("\nEnter a street name as in the example: Rublevskoe Highway - ");
	gets(micro.street_name);
	if (check(micro.street_name) == -1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		return -1;
	}
	printf("Enter a house number - ");
	if (scanf("%d", &micro.house_number) != 1 || micro.house_number <= 0)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	printf("Enter a flat number - ");
	if (scanf("%d", &micro.flat_number) != 1 || micro.flat_number <= 0)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	printf("Enter the year of birth - ");
	if (scanf("%d", &micro.year) != 1 || micro.year <= 1900 || micro.year > 2020)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	fwrite(&micro, sizeof(microdistrict), 1, f);
	fclose(f);
}
//работает
int delete_person()
{
	FILE* f;
	int i = 0, size = 0;
	rewind(stdin);
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "r+b")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	printf("Specify the number of a person you want to delete - ");
	if (scanf("%d", &i) != 1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f) / sizeof(microdistrict); 
	while (i > size || i <= 0) 
	{
		printf("There is no person with such number in the database. Enter the name again - ");
		if (scanf("%d", &i) != 1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
	}
	for (int k = i - 1; k < size - 1; k++) 
	{
		fseek(f, (k + 1) * sizeof(microdistrict), SEEK_SET);
		fread(&micro, sizeof(microdistrict), 1, f); 
		fseek(f, k * sizeof(microdistrict), SEEK_SET); 
		fwrite(&micro, sizeof(microdistrict), 1, f); 
	}
	chsize(_fileno(f), (size - 1) * sizeof(microdistrict));
	fclose(f);


}
//работает
int search_in_database()
{
	int a, flag = 0, house = 0, flat = 0, year = 0, i = 0;
	char s[20];
	FILE* f;
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "rb")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	printf("Search mode\n");
	printf("1 - Search by the name\n");
	printf("2 - Search by the street name\n");
	printf("3 - Search by the house number\n");
	printf("4 - Search by the flat number\n");
	printf("5 - Search by the birth year\n");
	if (scanf("%d", &a) != 1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	rewind(stdin);
	switch(a)
	{
		case 1:
		{
			i = 1;
			flag = 0;
			printf("Enter a full name - ");
			gets(s);
			printf("________________________________________________________________________________________\n");
			printf("|   |                      |               |		  |             |              |\n");
			printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
			printf("|___|______________________|_______________|______________|_____________|______________|\n");
			while (!feof(f))
			{
				fread(&micro, sizeof(microdistrict), 1, f);
				if (!feof(f) && !strcmp(micro.full_name, s))
				{
					printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
					i++;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("|------------------------There is no such person in the database-----------------------|\n");
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				break;
			}
			else
			{
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				printf("\n");
			}
			break;
		}
		case 2:
		{
			i = 1;
			flag = 0;
			printf("Enter the streen name - ");
			gets(s);
			printf("________________________________________________________________________________________\n");
			printf("|   |                      |               |		  |             |              |\n");
			printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
			printf("|___|______________________|_______________|______________|_____________|______________|\n");
			while (!feof(f))
			{
				fread(&micro, sizeof(microdistrict), 1, f);
				if (!feof(f) && !strcmp(micro.street_name, s))
				{
					printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
					i++;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("|------------------------There is no such street in the database-----------------------|\n");
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				break;
			}
			else
			{
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				printf("\n");
			}
			break;
		}
		case 3:
		{
			i = 1;
			flag = 0;
			printf("Enter the house number - ");
			if (scanf("%d", &house) != 1)
			{
				printf("\nYour input is incorrect!\n");
				break;
			}
			printf("________________________________________________________________________________________\n");
			printf("|   |                      |               |		  |             |              |\n");
			printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
			printf("|___|______________________|_______________|______________|_____________|______________|\n");
			while (!feof(f))
			{
				fread(&micro, sizeof(microdistrict), 1, f);
				if (!feof(f) && (micro.house_number == house))
				{
					printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
					i++;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("|------------------------There is no such house number in the database-----------------|\n");
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				break;
			}
			else
			{
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				printf("\n");
			}
			break;
		}
		case 4:
		{
			i = 1;
			flag = 0;
			printf("Enter the flat number - ");
			if (scanf("%d", &flat) != 1)
			{
				printf("\nYour input is incorrect!\n");
				break;
			}
			printf("________________________________________________________________________________________\n");
			printf("|   |                      |               |		  |             |              |\n");
			printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
			printf("|___|______________________|_______________|______________|_____________|______________|\n");
			while (!feof(f))
			{
				fread(&micro, sizeof(microdistrict), 1, f);
				if (!feof(f) && (micro.flat_number == flat))
				{
					printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
					i++;
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("|------------------------There is no such flat number in the database------------------|\n");
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				break;
			}
			else
			{
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				printf("\n");
			}
			break;
		}
		case 5:
		{
			i = 1;
			flag = 0;
			printf("Enter the birth year - ");
			if (scanf("%d", &year) != 1)
			{
				printf("\nYour input is incorrect!\n");
				break;
			}
			printf("________________________________________________________________________________________\n");
			printf("|   |                      |               |		  |             |              |\n");
			printf("| N |         FIO          |  Street_name  | House_number | Flat_number |  Birth_year  |\n");
			printf("|___|______________________|_______________|______________|_____________|______________|\n");
			while (!feof(f))
			{
				fread(&micro, sizeof(microdistrict), 1, f);
				if (!feof(f) && (micro.year == year))
				{
					printf("|%-3d|%-22s|%-15s|%-14d|%-13d|%-14d|\n", i, micro.full_name, micro.street_name, micro.house_number, micro.flat_number, micro.year);
					flag = 1;
				}
			}
			if (flag == 0)
			{
				printf("|------------------------There is no such birth year in the database-------------------|\n");
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				break;
			}
			else
			{
				printf("|___|______________________|_______________|______________|_____________|______________|\n");
				printf("\n");
			}
			break;
		}
	}
}
//работает
int edit_certain_record()
{
	FILE* f;
	int i = 0, size = 0, flag = 0, b = 0;
	rewind(stdin);
	microdistrict micro;
	if ((f = fopen("microdistrict.bin", "r+b")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	printf("Specify the number of a person you want to edit - ");
	if (scanf("%d", &i) != 1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	fseek(f, 0, SEEK_END);
	size = ftell(f) / sizeof(microdistrict);
	while (i > size || i <= 0)
	{
		printf("There is no person with such number in the database. Enter the name again - ");
		if (scanf("%d", &i) != 1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
	}
	printf("Editing mode\n");
	printf("1 - Edit the name\n");
	printf("2 - Edit the street name\n");
	printf("3 - Edit the house number\n");
	printf("4 - Edit the flat number\n");
	printf("5 - Edit the birth year\n");
	if (scanf("%d", &b) != 1)
	{
		printf("\nYour input is incorrect!\n");
		fclose(f);
		rewind(stdin);
		return -1;
	}
	fseek(f, (i - 1) * sizeof(microdistrict), SEEK_SET); 
	fread(&micro, 1, sizeof(microdistrict), f); 
	rewind(stdin);
	switch (b)
	{
	case 1:
	{
		printf("\nEnter new name as in the example: Ivanov_Ivan_Ivanovich - ");
		gets(micro.full_name);
		if (check(micro.full_name) == -1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			return -1;
		}
		break;
	}
	case 2:
	{
		printf("\nEnter new street name as in the example: Rublevskoe Highway - ");
		gets(micro.street_name);
		if (check(micro.street_name) == -1)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			return -1;
		}
		break;
	}
	case 3:
	{
		printf("Enter new house number - ");
		if (scanf("%d", &micro.house_number) != 1 || micro.house_number <= 0)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		break;
	}
	case 4:
	{
		printf("Enter new flat number - ");
		if (scanf("%d", &micro.flat_number) != 1 || micro.flat_number <= 0)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		break;
	}
	case 5:
	{
		printf("Enter the year of birth - ");
		if (scanf("%d", &micro.year) != 1 || micro.year <= 1900 || micro.year > 2020)
		{
			printf("\nYour input is incorrect!\n");
			fclose(f);
			rewind(stdin);
			return -1;
		}
		break;
	}
	default:
	{
		printf("There is no such field you want to edit ");
		break;
	}
	}
	fseek(f, (i - 1) * sizeof(microdistrict), SEEK_SET);
	fwrite(&micro, sizeof(microdistrict), 1, f);
	fclose(f);
}
void exchange(microdistrict micro[], int* i)
{
	microdistrict buff;
	buff = micro[*i];
	micro[*i] = micro[*i + 1];
	micro[*i + 1] = buff;
}
//работает
int sort_database()
{
	FILE* f;
	int flag = 0, flag1 = 0, a = 0, k = 0, b = 0, number = 0;
	rewind(stdin);
	if ((f = fopen("microdistrict.bin", "r+b")) == NULL)
	{
		printf("Cannot open the file\n");
		return -1;
	}
	fseek(f, 0, SEEK_END);
	number = ftell(f) / sizeof(microdistrict); 
	fseek(f, 0, SEEK_SET);
	microdistrict* micro = (microdistrict*)malloc(number * sizeof(microdistrict)); 
	microdistrict tmp;
	for (int i = 0; i < number; i++)
		fread(&micro[i], sizeof(microdistrict), 1, f);

	printf("Sort mode\n");
	printf("Sort by:\n1 - increase\n2 - decrease\n");
	flag = scanf("%d", &a);
	if (flag == NULL)
	{
		printf("Error");
		exit(1);
	}
	while (k < 1)
	{
		if ((a == 1) || (a == 2))
		{
			k++;
		}
		else
		{
			printf("Your input is incorect, please, input again");
			flag1 = scanf("%d", &a);
			if (flag1 == NULL)
			{
				printf("Error");
				exit(1);
			}
		}
	}
	switch (a)
	{
	case 1:
	{
		k = 0, flag = 0, flag1 = 0;
		printf("Sorting mode\n");
		printf("1 - Sort by the name\n");
		printf("2 - Sort by the street name\n");
		printf("3 - Sort by the house number\n");
		printf("4 - Sort by the flat number\n");
		printf("5 - Sort by the birth year\n");
		flag = scanf("%d", &b);
		if (flag == NULL)
		{
			printf("Error");
			exit(1);
		}
		while (k < 1)
		{
			if ((a == 1) || (a == 2) || (a == 3) || (a == 4) || (a == 5))
			{
				k++;
			}
			else
			{
				printf("Your input is incorect, please, input again");
				flag1 = scanf("%d", &a);
				if (flag1 == NULL)
				{
					printf("Error");
					exit(1);
				}
			}
		}
		switch (b)
		{
		case 1:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (strcmp(micro[m].full_name, micro[m + 1].full_name) > 0)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 2:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (strcmp(micro[m].street_name, micro[m + 1].street_name) > 0)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 3:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].house_number > micro[m + 1].house_number)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 4:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].flat_number > micro[m + 1].flat_number)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 5:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].year > micro[m + 1].year)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		}
		break;
	}
	case 2:
	{
		k = 0, flag = 0, flag1 = 0;
		printf("Sorting mode\n");
		printf("1 - Sort by the name\n");
		printf("2 - Sort by the street name\n");
		printf("3 - Sort by the house number\n");
		printf("4 - Sort by the flat number\n");
		printf("5 - Sort by the birth year\n");
		flag = scanf("%d", &b);
		if (flag == NULL)
		{
			printf("Error");
			exit(1);
		}
		while (k < 1)
		{
			if ((a == 1) || (a == 2) || (a == 3) || (a == 4) || (a == 5))
			{
				k++;
			}
			else
			{
				printf("Your input is incorect, please, input again");
				flag1 = scanf("%d", &a);
				if (flag1 == NULL)
				{
					printf("Error");
					exit(1);
				}
			}
		}
		switch (b)
		{
		case 1:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (strcmp(micro[m].full_name, micro[m + 1].full_name) < 0)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 2:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (strcmp(micro[m].street_name, micro[m + 1].street_name) < 0)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 3:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].house_number < micro[m + 1].house_number)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 4:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].flat_number < micro[m + 1].flat_number)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		case 5:
		{
			for (int l = 0; l < number; l++)
			{
				for (int m = 0; m < (number) - l - 1; m++)
				{
					if (micro[m].year < micro[m + 1].year)
					{
						exchange(micro, &m);
					}
				}
			}
			printf("Sorted!\n");
			break;
		}
		}
		break;
	}
	}
	fseek(f, 0, SEEK_SET);
	for (int i = 0; i < number; i++) 
		fwrite(&micro[i], sizeof(microdistrict), 1, f);
	free(micro);
	fclose(f);
}
void menu()
{
	printf("1 - Fill in the database\n");
	printf("2 - Show the database\n");
	printf("3 - Adding a record to the database\n");
	printf("4 - Deleting a specified record from the database\n");
	printf("5 - Search for a record by a specified field\n");
	printf("6 - Editing a given record in the database\n");
	printf("7 - Sorting in the database by a specified field\n");
	printf("0 - Exit\n");
}
int main()
{
	int a, count = 0, check = 0;
	microdistrict micro[100];
	int* number = &count;
	menu();
	while (1)
	{
		printf("Choose the action:\n");
		check = scanf("%d", &a);
		if (check != 1)
		{
			printf("Error\n");
			exit(1);
		}
		switch (a)
		{
		case 1:
		{
			fill_in_base();
			menu();
			break;
		}
		case 2:
		{
			show_base();
			menu();
			break;
		}
		case 3:
		{
			add_to_base();
			menu();
			break;
		}
		case 4:
		{
			delete_person();
			menu();
			break;
		}
		case 5:
		{
			search_in_database();
			menu();
			break;
		}
		case 6:
		{
			edit_certain_record();
			menu();
			break;
		}
		case 7:
		{
			sort_database();
			menu();
			break;
		}
		case 0:
		{
			return(0);
		}
		}
	}
	system("pause");
	return 0;
}
