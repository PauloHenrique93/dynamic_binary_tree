#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"
#include "string.h"

typedef struct Player {
	int id;
	char name[100];
	char classPlayer[100];
	float points;
	struct Player *left, *right;
}Player;

//===================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> ASSINATURAS <<<<<<<<<<<<<<<<<<<<<<<<<<<
//===================================================================

Player* insert(Player* helper, Player player);
int status(Player* root);
int search(Player* helper, int n, int result);
int heightTree(Player* helper);
int searchFather(Player* father, Player* helper, int n, int result);
int checkBalance(Player* root);
int strictlyBinary(Player* root);
void showInOrder(Player* helper);
void showPreOrder(Player* helper);
void showDescendingOrder(Player* helper);
Player* readFile(Player* root, FILE *fp);


//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> VAR. GLOBAIS <<<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int nivel_no = 0;

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> FUNC. PRINCIPAL <<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int main()
{
	Player* root = NULL;
	int option = 0;
	int n = 0;
	int result = 0;
	int paiF6 = 0;

	FILE *fp;
	fp = fopen("AlunosIFE.txt", "rt");

	setlocale(LC_ALL, "portuguese");

	do {
		printf("\n\n0 - SAIR");
		printf("\n1 - CARREGAR A ÁRVORE: ");
		printf("\n2 - VERIFICAR O STATUS DA ÁRVORE");
		printf("\n3 - CONSULTAR A EXISTÊNCIA DE UM NÓ");
		printf("\n4 - VERIFICAR O NÍVEL DO NÓ");
		printf("\n5 - ALTURA DA ÁRVORE");
		printf("\n6 - ENCONTRAR O PAI DO NÓ");
		printf("\n7 - VEFICAR SE A ÁRVORE ESTÁ BALANCEADA");
		printf("\n8 - VERIFICAR SE A ÁRVORE É ESTRITAMENTE BINÁRIA");
		printf("\n9 - IMPRIMIR EM ORDEM");
		printf("\n10 - IMPRIMIR EM PRE ORDEM");
		printf("\n11 - IMPRIMIR EM POS ORDEM");
		printf("\n12 - IMPRIMIR EM ORDEM DECRESCENTE");
		printf("\n==> ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			root = readFile(root, fp);
			break;
		case 2:
			if (status(root))
				printf("\nÁRVORE VAZIA!!");
			else
				printf("A ÁRVORE NÃO ESTA VAZIA!!");
			break;
		case 3:
			printf("\Digite o valor do NÓ: ");
			scanf("%d", &n);
			if (search(root, n, result))
				printf("\nO NÓ ENCONTRADO!!");
			else
				printf("\nO NÓ NAO FOI ENCONTRADO!!");
			break;
		case 4:
			printf("\Digite o valor do NÓ: ");
			scanf("%d", &n);
			if (search(root, n, result))
				printf("O nivel do NÓ é: %d", nivel_no);
			else
				printf("\nO NÓ NÃO FOI ENCONTRADO!!");
			nivel_no = 0;//curando a variavel pra futuras verificações
			break;
		case 5:
			if (status(root))
				printf("ÁRVORE VAZIA!!");
			else
				printf("A altura é: %d", heightTree(root));
			break;
		case 6:
			printf("\Informe o valor do NÓ filho: ");
			scanf("%d", &n);
			paiF6 = searchFather(root, root, n, result);
			if (paiF6 == 0)
				printf("\nO NÓ NÃO FOI ENCONTRADO!!");
			break;
		case 7:
			if (checkBalance(root))
				printf("\nÁRVORE BALANCEADA");
			else
				printf("\nÁRVORE DESBALANCEADA");
			break;
		case 8:
			if (strictlyBinary(root))
				printf("A ARVORE É ESTRITAMENTE BINÁRIA");
			else
				printf("A ARVORE NÃO É ESTRITAMENTE BINÁRIA");
			break;
		case 9:
			showInOrder(root);
			break;
		case 10:
			showPreOrder(root);
			break;
		case 11:
			printf("Funcionalidade Deletada!!");//mostrarPosOrdem(root);
			break;
		case 12:
			showDescendingOrder(root);
			break;
		}
	} while (option != 0);
	system("PAUSE");

	return 0;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> STATUS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int status(Player* root) {
	if (root == NULL)
		return 1;
	else return 0;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> INSERIR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

Player* insert(Player* helper, Player player) {

	//esse if é pra inserir de fato os dados
	if (helper == NULL) {
		helper = (Player*)malloc(sizeof(Player));
		helper->id = player.id;
		strcpy(helper->name, player.name);
		strcpy(helper->classPlayer, player.classPlayer);
		helper->points = player.points;
		helper->left = NULL;
		helper->right = NULL;
	}
	else if (player.id < helper->id)
		helper->left = insert(helper->left, player);
	else
		helper->right = insert(helper->right, player);

	return helper;

	/*ENTENDIMENTO: o processo de inserção começa sempre pela raiz*/
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> BUSCAR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int search(Player* helper, int n, int result) {
	if (helper != NULL && result == 0) {
		if (helper->id == n)
			result = 1;
		else if (n < helper->id) {
			nivel_no++;
			result = search(helper->left, n, result);
		}
		else {
			nivel_no++;
			result = search(helper->right, n, result);
		}
	}

	return result;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> CALCULAR ALTURA <<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int heightTree(Player* helper) {
	if (helper == NULL)
		return -1; // altura de árvore vazia é -1
	else {
		int he = heightTree(helper->left);
		int hd = heightTree(helper->right);

		if (he < hd)
			return hd + 1;
		else
			return he + 1;
	}
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> BUSCAR NO PAI <<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int searchFather(Player* father, Player* helper, int n, int result) {
	if (helper != NULL && result == 0) {
		if (helper->id == n) {
			result = 1;
			printf("\nO NÓ %d é o pai!", father->id);
		}
		else if (n < helper->id)
			result = searchFather(helper, helper->left, n, result);
		else
			result = searchFather(helper, helper->right, n, result);
	}

	return result;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>> VERIFICA O BALANCEAMENTO <<<<<<<<<<<<<<<<<
//====================================================================

int checkBalance(Player* root) {
	int leftHeight; // altura da subarvore esquerda
	int rightHeight; // altura da subarvore direita

			   //se a arvore for vazia
	if (root == NULL)
		return 1;

	/* calcula a altura da subarvore esquerda e direita */
	leftHeight = heightTree(root->left);
	rightHeight = heightTree(root->right);

	if (abs(leftHeight - rightHeight) <= 1 && checkBalance(root->left) && checkBalance(root->right))
		return 1;

	//arvore não balanceada
	return 0;
}

int strictlyBinary(Player* root) {
	// se a arvore for vazia
	if (root == NULL)
		return 1;

	// If leaf node
	if (root->left == NULL && root->right == NULL)
		return 1;

	// se a direita e esqeurda não forem nulas e as subarvores da direita e esqeurdas estiverem cheias
	if ((root->left) && (root->right))
		return (strictlyBinary(root->left) && strictlyBinary(root->right));

	// não é estritamente binaria
	return 0;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>> MOSTRAR EM ORDEM <<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

void showInOrder(Player* helper) {
	if (helper != NULL) {
		showInOrder(helper->left);
		printf(" (%d)", helper->id);
		showInOrder(helper->right);
	}
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>> MOSTRAR PRE ORDEM <<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

void showPreOrder(Player* helper) {
	if (helper != NULL) {
		printf(" (%d)", helper->id);
		showPreOrder(helper->left);
		showPreOrder(helper->right);
	}
}


//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>> MOSTRAR EM ORDEM DECRESCENTE <<<<<<<<<<<<<<<
//====================================================================

void showDescendingOrder(Player* helper) {
	if (helper != NULL) {
		showDescendingOrder(helper->right);
		printf(" (%d)", helper->id);
		showDescendingOrder(helper->left);
	}
}




Player* readFile(Player* root, FILE *fp) {
	char nameAndClass[200];

	int h, y, quant;//index for name and classes

	char character;
	int i = 0;
	int id = 0, position = 0;
	float points = 0;
	char classPlayer[100];
	char name[100];

	//SCROLL TO THE END OF FILE
	while (!feof(fp)) {

		//GETTING ID         
		fscanf(fp, "%d", &id);

		//JUMPING THE CHARACTER ; 
		fgetc(fp);

		//GETTING NAME AND CLASS

		y = 0;
		quant = 0;
		while (quant < 2) {
			fscanf(fp, "%c", &character);
			if (character == ';')
				quant++;
			if (quant < 2) {
				nameAndClass[y] = character;
				y++;
			}
		}

		nameAndClass[y] = '\0';

		///separating the name and class putting in their respective vectors
		int z = 0;
		int x = 0;
		while (1) {
			name[z] = nameAndClass[z];

			if (nameAndClass[z] == ';') {
				name[z] = '\0';
				while (nameAndClass[z] != '\0') {
					classPlayer[x] = nameAndClass[z + 1];
					x++; z++;
				}
				classPlayer[y] = '\0';
				break;
			}

			z++;
		}

		//GETTING THE POINTS
		fscanf(fp, "%f", &points);

		//ADDING IN THE TREE STRUCTURE
		Player player;

		player.id = id;
		strcpy(player.name, name);
		strcpy(player.classPlayer, classPlayer);
		player.points = points;

		root = insert(root, player);
		i++;
	}
	fclose(fp);

	return root;
}