#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "locale.h"

typedef struct Player {
	int n;
	struct Player *left, *right;
}Player;

//===================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> ASSINATURAS <<<<<<<<<<<<<<<<<<<<<<<<<<<
//===================================================================

Player* insert(Player* helper, int n);
int status(Player* root);
int search(Player* helper, int n, int result);
int heightTree(Player* helper);
int searchFather(Player* father, Player* helper, int n, int result);
int checkBalance(Player* root);
int strictlyBinary(Player* root);
void showInOrder(Player* helper);
void showPreOrder(Player* helper);
void showDescendingOrder(Player* helper);


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

	setlocale(LC_ALL, "portuguese");

	do {
		printf("\n\n0 - SAIR");
		printf("\n1 - INSERIR UM N�: ");
		printf("\n2 - VERIFICAR O STATUS DA �RVORE");
		printf("\n3 - CONSULTAR A EXIST�NCIA DE UM N�");
		printf("\n4 - VERIFICAR O N�VEL DO N�");
		printf("\n5 - ALTURA DA �RVORE");
		printf("\n6 - ENCONTRAR O PAI DO N�");
		printf("\n7 - VEFICAR SE A �RVORE EST� BALANCEADA");
		printf("\n8 - VERIFICAR SE A �RVORE � ESTRITAMENTE BIN�RIA");
		printf("\n9 - IMPRIMIR EM ORDEM");
		printf("\n10 - IMPRIMIR EM PRE ORDEM");
		printf("\n11 - IMPRIMIR EM POS ORDEM");
		printf("\n12 - IMPRIMIR EM ORDEM DECRESCENTE");
		printf("\n==> ");
		scanf("%d", &option);

		switch (option) {
		case 1:
			printf("\nDigite um valor: ");
			scanf("%d", &n);
			root = insert(root, n);
			break;
		case 2:
			if (status(root))
				printf("\n�RVORE VAZIA!!");
			else
				printf("A �RVORE N�O ESTA VAZIA!!");
			break;
		case 3:
			printf("\Digite o valor do N�: ");
			scanf("%d", &n);
			if (search(root, n, result))
				printf("\nO N� ENCONTRADO!!");
			else
				printf("\nO N� NAO FOI ENCONTRADO!!");
			break;
		case 4:
			printf("\Digite o valor do N�: ");
			scanf("%d", &n);
			if (search(root, n, result))
				printf("O nivel do N� �: %d", nivel_no);
			else
				printf("\nO N� N�O FOI ENCONTRADO!!");
			nivel_no = 0;//curando a variavel pra futuras verifica��es
			break;
		case 5:
			if (status(root))
				printf("�RVORE VAZIA!!");
			else
				printf("A altura �: %d", heightTree(root));
			break;
		case 6:
			printf("\Informe o valor do N� filho: ");
			scanf("%d", &n);
			paiF6 = searchFather(root, root, n, result);
			if (paiF6 == 0)
				printf("\nO N� N�O FOI ENCONTRADO!!");
			break;
		case 7:
			if (checkBalance(root))
				printf("\n�RVORE BALANCEADA");
			else
				printf("\n�RVORE DESBALANCEADA");
			break;
		case 8:
			if (strictlyBinary(root))
				printf("A ARVORE � ESTRITAMENTE BIN�RIA");
			else
				printf("A ARVORE N�O � ESTRITAMENTE BIN�RIA");
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

Player* insert(Player* helper, int n) {

	//esse if � pra inserir de fato os dados
	if (helper == NULL) {
		helper = (Player*)malloc(sizeof(Player));
		helper->n = n;
		helper->left = NULL;
		helper->right = NULL;
	}
	else if (n < helper->n)
		helper->left = insert(helper->left, n);
	else
		helper->right = insert(helper->right, n);

	return helper;

	/*ENTENDIMENTO: a inser��o come�a sempre pela raiz*/
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>>>> BUSCAR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

int search(Player* helper, int n, int result) {
	if (helper != NULL && result == 0) {
		if (helper->n == n)
			result = 1;
		else if (n < helper->n) {
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
		return -1; // altura de �rvore vazia � -1
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
		if (helper->n == n) {
			result = 1;
			printf("\nO N� %d � o pai!", father->n);
		}
		else if (n < helper->n)
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
	int esq_a; // altura da subarvore esquerda
	int dir_a; // altura da subarvore direita

			   //se a arvore for vazia
	if (root == NULL)
		return 1;

	/* calcula a altura da subarvore esquerda e direita */
	esq_a = heightTree(root->left);
	dir_a = heightTree(root->right);

	if (abs(esq_a - dir_a) <= 1 && checkBalance(root->left) && checkBalance(root->right))
		return 1;

	//arvore n�o balanceada
	return 0;
}

int strictlyBinary(Player* root) {
	// se a arvore for vazia
	if (root == NULL)
		return 1;

	// If leaf node
	if (root->left == NULL && root->right == NULL)
		return 1;

	// se a direita e esqeurda n�o forem nulas e as subarvores da direita e esqeurdas estiverem cheias
	if ((root->left) && (root->right))
		return (strictlyBinary(root->left) && strictlyBinary(root->right));

	// n�o � estritamente binaria
	return 0;
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>> MOSTRAR EM ORDEM <<<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

void showInOrder(Player* helper) {
	if (helper != NULL) {
		showInOrder(helper->left);
		printf(" (%d)", helper->n);
		showInOrder(helper->right);
	}
}

//====================================================================
//>>>>>>>>>>>>>>>>>>>>>>>>> MOSTRAR PRE ORDEM <<<<<<<<<<<<<<<<<<<<<<<<
//====================================================================

void showPreOrder(Player* helper) {
	if (helper != NULL) {
		printf(" (%d)", helper->n);
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
		printf(" (%d)", helper->n);
		showDescendingOrder(helper->left);
	}
}

/*Calcular Altura
Calcular n�vel de determinado n�
Verificar se a arvore � estritamente bin�ria
Implementar um m�todo que imprima os elementos na ordem crescente e decrescente.
*/