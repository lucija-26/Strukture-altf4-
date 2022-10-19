#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_BROJ_BODOVA (50)


typedef struct { 
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int bodovi;
} Student;

int countStudentsFromFile(char* filename);
int readStudentsFromFile(char* filename, Student* studenti);
int ispis(Student* studenti, int brojStudenata);

int main(void)
{
	char filename[MAX_FILE_NAME] = { 0 };
	Student *studenti;

	printf("Insert filename > ");
	scanf(" %s", filename);

	int brojStudenata = countStudentsFromFile(filename);

	if (brojStudenata != FILE_DIDNT_OPEN_ERROR)
		printf("Broj studenata u datoteci %s je %d.\n\n", filename, brojStudenata);

	studenti = (Student*)malloc(brojStudenata * sizeof(Student));

	readStudentsFromFile(filename, studenti);

	ispis(studenti, brojStudenata);

	return 0;
}

int countStudentsFromFile(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = {0};

	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		printf("The file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (strcmp("\n", buffer) != 0)
			count++;
	}

	fclose(fp);
	return count;
}

int readStudentsFromFile(char* filename, Student *studenti)
{
	FILE* fp = NULL;
	int i = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (NULL == fp)
	{
		printf("The file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s", studenti[i].ime);
		fscanf(fp, "%s", studenti[i].prezime);
		fscanf(fp, "%d", &studenti[i].bodovi);
		i++; 
	}

	fclose(fp);
	return 0;
}

int ispis(Student* studenti, int brojStudenata)
{
	int i = 0;
	float relativanBrojBodova = 0;

	for (i = 0; i < brojStudenata; i++)
	{
		printf("%d. student:\n", i+1);
		relativanBrojBodova = ((float)studenti[i].bodovi / (float)MAX_BROJ_BODOVA) * 100.0;
		printf(" Ime: %s\n Prezime: %s\n Apsolutni broj bodova: %d\n Relativni broj bodova: %.2f\n\n", 
			studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativanBrojBodova);
	}

	return 0;
}