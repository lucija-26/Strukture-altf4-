#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (256)
#define ERROR (-1)
#define EXIT_SUCCESS 0
struct _osoba;
typedef struct _osoba* Position;

typedef struct _osoba {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godina;

	Position next;
} Osoba;

Position unosOsobe(char*, char*, int);
Position pronadiPoPrezimenu(Position, char*);
Position nadjiPret(char*, Position);
int unosP(Position, Position);
int unosK(Position, Position);
int ispis(Position);
int izbrisi(char*, Position);
int unosIza(char*, Position, Position);
int unosIspred(char*, Position, Position);
int Sort(Position);
int unosDatoteka(char*, Position);
int ispisDatoteka(char*);

int main() {
	Osoba head = {
	.ime = {0},
	.prezime = {0},
	.godina = 0,
	.next = NULL
	};
	Position P = NULL;
	Position Q = NULL;
	Position tempp = NULL;
	char ime[MAX_LINE] = { 0 };
	char prezime[MAX_LINE] = { 0 };
	char temp[MAX_LINE] = { 0 };
	char filename[MAX_LINE] = { 0 };
	int god = 0, poz = 0, br = 0, izbor = 0, status = 0;

	printf("Koliko ljudi zelite unijeti? ");
	scanf("%d", &br);
	printf("\n");

	for (int i = 0; i < br; i++) 
	{
		printf("Zelite li unijeti osobu na:\n");
		printf("\t1 - pocetak\n\t2 - kraj\n");
		scanf("%d", &izbor);

		printf("\n");
		printf("Ime: ");
		scanf(" %s", ime);
		printf("Prezime: ");
		scanf(" %s", prezime);
		printf("Godina: ");
		scanf("%d", &god);
		printf("\n");


		P = unosOsobe(ime, prezime, god);

		switch (izbor) {
			case 1:
			{
				unosP(&head, P);
				break;
			}

			case 2:
			{
				unosK(&head, P);
				break;
			}
		}

	}
	ispis(&head);

	printf("\nUnesite prezime prije kojeg zelite upisati element: ");
	scanf(" %s", temp);

	printf("\n");
	printf("Ime: ");
	scanf(" %s", ime);
	printf("Prezime: ");
	scanf(" %s", prezime);
	printf("Godina: ");
	scanf("%d", &god);
	printf("\n");

	P = unosOsobe(ime, prezime, god);
	status = unosIspred(temp, &head, P);
	if (status != EXIT_SUCCESS)
		return;
	ispis(&head);


	printf("\nUnesite prezime iza kojeg zelite upisati element: ");
	scanf(" %s", temp);

	printf("\n");
	printf("Ime: ");
	scanf(" %s", ime);
	printf("Prezime: ");
	scanf(" %s", prezime);
	printf("Godina: ");
	scanf("%d", &god);
	printf("\n");

	P = unosOsobe(ime, prezime, god);
	unosIza(temp, &head, P);
	ispis(&head);

	printf("\nUnesite prezime osobe koju zelite naci: ");
	scanf(" %s", temp);

	Q = pronadiPoPrezimenu(&head, temp);
	printf("%s %s %d\n", Q->ime, Q->prezime, Q->godina);

	printf("\nUnesite prezime osobe koju zelite izbrisati: ");
	scanf(" %s", temp);
	izbrisi(temp, &head);
	ispis(&head);
	printf("\n");

	printf("Ime datoteke: ");
	scanf(" %s", filename);
	printf("\n");

	unosDatoteka(filename, &head);
	ispisDatoteka(filename);

	printf("\nSortirana lista:\n");
	Sort(&head);
	ispis(&head);

	while (head.next != NULL) {
		tempp = head.next;
		head.next = head.next->next;
		free(tempp);
	}

	return EXIT_SUCCESS;
}

Position unosOsobe(char* ime, char* prezime, int godina) {
	Position p = NULL;
	p = (Position)malloc(sizeof(Osoba));
	strcpy(p->ime, ime);
	strcpy(p->prezime, prezime);
	p->godina = godina;
	p->next = NULL;
	if (!p) {
		printf("Alokacija memorije je neuspjesna.\n");
		return NULL;
	}
	return p;
}

int unosP(Position head, Position p) {
	p->next = head->next;
	head->next = p;
	return EXIT_SUCCESS;
}

int ispis(Position head) {
	Position p = NULL;
	Position q = NULL;
	p = head->next;
	int i = 0;
	while (p != NULL) {
		q = p->next;
		printf("%d. %s %s %d\n", i + 1, p->ime, p->prezime, p->godina);
		p = q;
		i++;
	}
	return EXIT_SUCCESS;
}

int unosK(Position head, Position p) {
	while (head->next != NULL) {
		head = head->next;
	}
	p->next = head->next;
	head->next = p;
	return EXIT_SUCCESS;
}

Position pronadiPoPrezimenu(Position head, char* prez) {
	Position q = NULL;
	q = head->next;
	while (q != NULL) {
		if (strcmp(q->prezime, prez) == 0) {
			return q;
		}
		q = q->next;
	}
	printf("Neuspjesno pretrazivanje.\n");
	return ERROR;
}

Position nadjiPret(char* prezime, Position head) {
	Position p = NULL, q = NULL;
	p = head->next;
	while (p != NULL && strcmp(p->prezime, prezime) != 0) {
		q = p;
		p = p->next;
	}
	if (p == NULL)
		return NULL;
	return q;
}

int izbrisi(char* prez, Position head) {
	Position temp1 = head;
	while (temp1 != NULL) {
		if (strcmp(temp1->next->prezime, prez) == 0) {
			Position temp2 = temp1->next;
			temp1->next = temp2->next;
			free(temp2);
			return EXIT_SUCCESS;
		}
		temp1 = temp1->next;
	}
	printf("Neuspjesno pretrazivanje.\n");
	return ERROR;

	
}

int unosIza(char* prez, Position head, Position p) {
	Position q = NULL;
	q = head->next;
	while (q != NULL) {
		if (strcmp(q->prezime, prez) == 0) {
			p->next = q->next;
			q->next = p;
			return EXIT_SUCCESS;
		}
		q = q->next;
	}
	printf("Neuspjesno pretrazivanje.\n");
	return ERROR;
}

int unosIspred(char* prezime, Position head, Position p) {
	Position prev = NULL;
	prev = nadjiPret(prezime, head);
	p->next = prev->next;
	prev->next = p;
	return EXIT_SUCCESS;
}

int unosDatoteka(char* filename, Position head) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}
	head = head->next;
	while (head != NULL) {
		
		fprintf(fp, "\n%s %s %d", head->ime, head->prezime, head->godina);
		head = head->next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int ispisDatoteka(char* filename) {
	char ime[MAX_LINE] = { 0 };
	char prezime[MAX_LINE] = { 0 };
	int godina = 0;
	FILE* fp = NULL;
	int i = 1;
	fp = fopen(filename, "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}
	while (!feof(fp)) {
		fscanf(fp, "  %s %s %d", ime, prezime, &godina);
		printf("%d. %s %s %d\n", i, ime, prezime, godina);
		i++;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int Sort(Position head) {
	//bubble sort
	Position j, prev_j, temp, end;
	end = NULL;
	while (head->next != end) {
		prev_j = head;
		j = head->next;
		while (j->next != end) {
			if (strcmp(j->prezime, j->next->prezime) > 0) {
				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;
				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
	return EXIT_SUCCESS;
}