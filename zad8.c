#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
typedef struct tree* Position;

typedef struct tree{
  int el;
  Position left;
  Position right;
}Tree;

Position insert(Position, Position);
int levelOrder(Position p);
int inOrder(Position p);
int postOrder(Position p);
int preOrder(Position p);
int height(Position p);
int currentLevel(Position p, int level);
Position delete(Position p, int br);
Position findEl(Position p, int br);
Position findMax(Position p);
Position findMin(Position p);
Position newNode(int el);

int main() {
  Position root = NULL;
  Position q = NULL;
  Position p = NULL;
  int el, c;
  do
	{
		printf("Odaberite:\n");
		printf("1 - unos novog elementa u stablo\n");
		printf("2 - inorder ispis\n");
		printf("3 - postorder ispis\n");
		printf("4 - preorder ispis\n");
		printf("5 - trazenje elementa\n");
		printf("6 - brisanje elementa\n");
		printf("7 - kraj\n\n");
    printf("Odabir: ");
		scanf("%d", &c);

    system("clear");
    
		switch (c)
		{
		case 1:
			printf("Unesite element:\n");
			scanf("%d", &el);
      q = newNode(el);
			root = insert(root, q);
			break;
		case 2:
      printf("Inorder ispis: \n");
			inOrder(root);
      printf("\n");
			break;
		case 3:
      printf("Postorder ispis: \n");
			postOrder(root);
      printf("\n");
			break;
		case 4:
      printf("Preorder ispis: \n");
			preOrder(root);
      printf("\n");
			break;
		case 5:
			printf("Unesite element koji trazite u stablu:\n");
			scanf("%d", &el);
			p = findEl(root, el);
			printf("Element: %d\n", p->el);
			break;
		case 6:
			printf("Unesite element koji zelite izbrisati:\n");
			scanf("%d", &el);
			root = delete(root, el);
		case 7:
			break;
		default:
			printf("Krivi unos!\n");
		}
	} while (c != '7');
  return 0;
}

Position insert(Position p, Position q) {
  if(p == NULL) {
    return q;
  }
  if(p->el < q->el) {
    p->right = insert(p->right, q);
  }
  else if(p->el > q->el) {
    p->left=insert(p->left, q);
  }
  else {
    free(q);
  }
  return p;
}


int inOrder(Position p){
  if (p == NULL){
    return 0;
  }
  inOrder(p->left);
  printf("%d ", p->el);
  inOrder(p->right);
}

int preOrder(Position p){
  if (p == NULL){
    return 0;
  }
  printf("%d ", p->el);
  preOrder(p->left);
  preOrder(p->right);
}

int postOrder(Position p){
  if (p == NULL){
    return 0;
  }
  postOrder(p->left);
  postOrder(p->right);
  printf("%d ", p->el);
}

Position delete(Position p, int br){
  if (p == NULL)
    return NULL;
  
  if (p->el < br)
    p->right = delete(p->right, br);
  else if (p->el > br)
    p->left = delete(p->left, br);
  else{
    if (p->left){
      Position temp = findMax(p->left);
      p->el = temp->el;
      p->left = delete(p->left, temp->el);
    }
    else if (p->right){
      Position temp = findMin(p->right);
      p->el = temp->el;
      p->right = delete(p->right, temp->el);
    }
    else{
      free(p);
      return NULL;
    }
  }
  return p;
}

Position findEl(Position p, int br){
  if (p == NULL){
    printf("Element nije pronadjen!\n");
    return NULL;
  }
  
  if (p->el < br)
    p->right = findEl(p->right, br);
  else if (p->el > br)
    p->left = findEl(p->left, br);
  else{
    return p;
    }
}


Position newNode(int el) {
  Position new = NULL;
  new = (Position)malloc(sizeof(Tree));
  if (!new) {
      printf("Memory allocation unsuccessful.\n");
      return NULL;
    }
  new->el = el;
  new->left = NULL;
  new->right = NULL;
  return new;
}

Position findMax(Position p) {
  while(p->right!=NULL)
    p = p->right;
  return p;
}

Position findMin(Position p) {
  while(p->left!=NULL)
    p = p->left;
  return p;
}

int height(Position p) {
  if (p == NULL)
      return 0;
  else {
    int lheight = height(p->left);
    int rheight = height(p->right);
    if (lheight > rheight)
      return (lheight + 1);
    else
      return (rheight + 1);
    }
}

int currentLevel(Position p, int level) {
  if (p == NULL)
    return -1;
  if (level == 1)
    printf("%d ", p->el);
  else if (level > 1) {
    currentLevel(p->left, level - 1);
    currentLevel(p->right, level - 1);
  }
  return 0;
}

int levelOrder(Position p) {
  int h = height(p);
  int i;
  for (i = 1; i <= h; i++)
      currentLevel(p, i);
  return 0;
}
