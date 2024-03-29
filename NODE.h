#pragma once

#define CODE_SIZE 256

typedef struct node {
	unsigned char symb = '0';		//Храним символ
	unsigned char isSymb = '0';	//Храним признак символа
	unsigned int freq = 0;		//Частота встречаемости узла
	char code[CODE_SIZE];		//Битовый код символа
	int level;		//Уровень глубины дерева
	struct node* left = nullptr;
	struct node* right = nullptr;
	struct node* next = nullptr;
}NODE;

// Standart functions
NODE* CreateNode(unsigned char symb, unsigned char isSymb, unsigned int freq);
NODE* Add2List(NODE* head, NODE* newnode);
//void Add2List(NODE** pphead, NODE* newnode);
void PrintList(NODE* phead);
NODE* DeleteList(NODE* phead);
void PrintTree(const NODE* root);
NODE* CopyList(NODE* phead, NODE* savephead);

// Special functions
NODE* MakeNodeFromNode(NODE* left, NODE* right);
NODE* MakeTreeFromList(NODE* head);
NODE* MakeTree(NODE* phead);
void MakeCodes(NODE* head, char code[], int level);
