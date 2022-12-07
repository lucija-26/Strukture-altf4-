#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define ERROR (-1)
#define SUCCESS (0)

typedef struct _stog Stog;
typedef struct _stog* Position;

struct _stog{  
  int element;
  Position next;
};

int izracunajPostfix(char *);
int push(int, Position);
int pop(Position);
int printStog(Position);
int citajIzDatoteke(char* , char* );

int main() {
  char str[MAX_LINE] = {0};
  char filename[MAX_LINE] = {0};
  
  printf("Unesite ime datoteke: ");
  scanf(" %s", filename);
  
  citajIzDatoteke(filename, str);
  printf("\nUcitani postfix: %s\n", str);
  printf("\n\n%d\n", izracunajPostfix(str));
  
  
  return SUCCESS;
}

int izracunajPostfix(char* str){
  char t[] = "";
  int n = 0, b = 0;
  int rezultat = 0;
  int temp1 = 0, temp2 = 0;
  Stog head = {.element = 0, .next = NULL};
  Position p = &head;
  

  while (strlen(str) != 0){
    b = sscanf(str, "%s %n", t, &n);
    if(b != 1){
        printf("Neispravan postfix!\n");
        return ERROR;
    }
    str = str + n;
    
    if (strcmp(t, "+") == 0){
      if (head.next == NULL || head.next->next == NULL){
        printf("Neispravan postfix!\n");
        break;
      }
      temp1 = pop(&head);
      temp2 = pop(&head);
      push(temp1 + temp2, &head);
    }
    else if (strcmp(t, "-") == 0){
      if (head.next == NULL || head.next->next == NULL){
        printf("Neispravan postfix!\n");
        break;
      }
      temp1 = pop(&head);
      temp2 = pop(&head);
      push(temp1 - temp2, &head);
    }
    else if (strcmp(t, "*") == 0){
      if (head.next == NULL || head.next->next == NULL){
        printf("Neispravan postfix!\n");
        break;
      }
      temp1 = pop(&head);
      temp2 = pop(&head);
      push(temp1 * temp2, &head);
    }
    else{
      push(atoi(t), &head);
    }
    printf("\n\nUcitani element: %s\n", t);
    printStog(&head);
  }
  
  if (head.next == NULL || head.next->next != NULL){
        printf("Neispravan postfix!\n");
        return ERROR;
      }
  
  rezultat = pop(&head);
  return rezultat;
}

int push(int x, Position head){
  Position p = head;
  
  while (p->next != NULL){
    p = p->next;
  }
  p->next = (Position)malloc(sizeof(Stog));
  p->next->next = NULL;
  p->next->element = x;
  
  return SUCCESS;
}

int pop(Position head){
  
  Position p = head;
  Position temp = NULL;
  int x = 0;
  
  while (p->next->next != NULL){
    p = p->next;
  }

  temp = p->next;
  x = temp->element;
  p->next = NULL;
  free(temp);

  return x;
}

int printStog(Position head){
  Position p = head->next;

  printf("\n\tSTOG\n");
  while (p != NULL){
    printf("\t%d\n", p->element);
    p = p->next;
  }
  return SUCCESS;
}

int citajIzDatoteke(char* filename, char* string){
  FILE *fp = fopen(filename, "r");
  char buffer[MAX_LINE];
  
  if(!fp) {
    printf("Greska pri otvaranju datoteke!\n");
    return ERROR;
  }
  while(!feof(fp)) {
    fgets(buffer, MAX_LINE, fp);
    if (strcmp("\n", buffer) != 0)
      break;
  }
  strcpy(string, buffer);
  return SUCCESS;
}
