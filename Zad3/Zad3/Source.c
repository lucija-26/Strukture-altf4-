#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (256)
#define ERROR (-1)
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
void unosP(Position, Position);
void unosK(Position, Position);
void ispis(Position);
void izbrisi(int n, Position);
void unosIza(int n, Position, Position);
int unosIspred(char*, Position, Position);
void unosDatoteka(char*, Position);
void ispisDatoteka(char*);

int main() {
	Osoba head;
	Position P = NULL;
	Position Q = NULL;
	char ime[MAX_LINE] = { 0 };
	char prezime[MAX_LINE] = { 0 };
	char temp[MAX_LINE] = { 0 };
	char filename[MAX_LINE] = { 0 };
	int god = 0, poz, br, izbor, status;
	head.next = NULL;
	printf("Koliko ljudi zelite unijeti? ");
	scanf("%d", &br);
	for (int i = 0; i < br; i++) {
		printf("Zelite li unijeti osobu na:\n");
		printf("\t1 - pocetak\n\t2 - kraj\n");
		scanf("%d", &izbor);
		printf("Ime: ");
		scanf(" %s", ime);
		printf("Prezime: ");
		scanf(" %s", prezime);
		printf("Godina: ");
		scanf("%d", &god);
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
	printf("Ime: ");
	scanf(" %s", ime);
	printf("Prezime: ");
	scanf(" %s", prezime);
	printf("Godina: ");
	scanf("%d", &god);
	P = unosOsobe(ime, prezime, god);
	status = unosIspred(temp, &head, P);
	if (status != EXIT_SUCCESS)
		return;
	ispis(&head);

	printf("\nUnesite broj iza kojeg zelite upisati element: ");
	scanf("%d", &poz);
	printf("Ime: ");
	scanf(" %s", ime);
	printf("Prezime: ");
	scanf(" %s", prezime);
	printf("Godina: ");
	scanf("%d", &god);
	P = unosOsobe(ime, prezime, god);
	unosIza(poz, &head, P);
	ispis(&head);

	printf("\nUnesite prezime: ");
	scanf(" %s", temp);
	Q = pronadiPoPrezimenu(&head, temp);

	printf("%s %s %d\n", Q->ime, Q->prezime, Q->godina);
	printf("\nUnesite broj koji zelite izbrisati: ");
	scanf("%d", &poz);
	izbrisi(poz, &head);
	ispis(&head);

	printf("Ime datoteke: ");
	scanf(" %s", filename);
	unosDatoteka(filename, &head);
	ispisDatoteka(filename);
	return 0;
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

void unosP(Position head, Position p) {
	p->next = head->next;
	head->next = p;
}

void ispis(Position head) {
	Position p = NULL;
	Position q = NULL;
	p = head->next;
	int i = 0;
	while (p != NULL) {
		q = p->next;
		printf("\n%d. %s %s %d\n", i + 1, p->ime, p->prezime, p->godina);
		p = q;
		i++;
	}
}

void unosK(Position head, Position p) {
	while (head->next != NULL) {
		head = head->next;
	}
	p->next = head->next;
	head->next = p;
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

void izbrisi(int n, Position head) {
	Position temp1 = head;
	int i;
	for (i = 0; i < n - 1; i++) {
		temp1 = temp1->next;
	}
	Position temp2 = temp1->next;
	temp1->next = temp2->next;
	free(temp2);
}

void unosIza(int n, Position head, Position p) {
	Position temp1 = head;
	int i;
	for (i = 0; i < n; i++) {
		temp1 = temp1->next;
	}
	p->next = temp1->next;
	temp1->next = p;
}

int unosIspred(char* prezime, Position head, Position p) {
  Position prev = NULL;
	prev = nadjiPret(prezime, head);
	p->next = prev->next;
  prev->next = p;
	return EXIT_SUCCESS;
}

void unosDatoteka(char* filename, Position head) {
	FILE* fp = NULL;
	fp = fopen(filename, "w");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return ERROR;
	}
	head = head->next;
	while (head != NULL) {

		fprintf(fp, "%s %s %d\n", head->ime, head->prezime, head->godina);
		head = head->next;
	}
	fclose(fp);
}

void ispisDatoteka(char* filename) {
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
}
