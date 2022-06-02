#include "NODE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

// Standart functions
NODE* CreateNode(unsigned char symb, unsigned char isSymb, unsigned int freq) {
	NODE* res = (NODE*)malloc(sizeof(NODE));
	if (res) {
		res->symb = symb;
		res->isSymb = 1;
		res->freq = freq;
	}
	return res;
}
NODE* Add2List(NODE* head, NODE* newnode) {
	NODE* tmp = nullptr;
	tmp = (NODE*)malloc(sizeof(NODE));
	if (tmp) {
		tmp->symb = newnode->symb;
		tmp->isSymb = newnode->isSymb;
		tmp->freq = newnode->freq;
	}
	if ((head == nullptr) || (newnode->freq < head->freq)) {
		tmp->next = head;
		return tmp;
	}
	else {
		NODE* savehead = head;
		while (head->next && head->next->freq <= newnode->freq) {
			head = head->next;
		}
		tmp->next = head->next;
		head->next = tmp;
		return savehead;
	}
}
void PrintNODE(NODE* head) {
	printf("%c - %u\n", head->symb, head->freq);
}
void PrintList(NODE* phead)
{
	printf("\n\n");
	while (phead)
	{
		PrintNODE(phead);
		phead = phead->next;
	}
}
NODE* DeleteList(NODE* phead)
{
	if (phead)
	{
		DeleteList(phead->next);
		free(phead);
	}
	return NULL;
}
void PrintTree(const node* phead) {
	if (!phead)
		return;
	PrintTree(phead->left);
	printf("%d\n", phead->freq);
	PrintTree(phead->right);
	/*if (phead->isSymb) {
		printf("%c %d\n", phead->symb, phead->freq);
	}
	else {
		PrintTree(phead->left);
		PrintTree(phead->right);
	}*/
}
NODE* CopyList(NODE* phead, NODE* savephead) {
	NODE* pnew = nullptr;
	while (phead) {
		pnew = CreateNode(phead->symb, phead->isSymb, phead->freq);
		savephead = Add2List(savephead, pnew);
		phead = phead->next;
	}
	return savephead;
}

// Special functions
NODE* MakeNodeFromNode(NODE* left, NODE* right) {
	NODE* res = (NODE*)malloc(sizeof(NODE));
	if (res) {
		res->freq = left->freq + right->freq;
		res->isSymb = 0;
		res->symb = 0;
		res->left = left;
		res->right = right;
		res->next = 0;
	}
	return res;
}
NODE* MakeTreeFromList(NODE* head) {
	while (head && head->next)
	{
		NODE* left = head;
		NODE* right = head->next;
		head = Add2List(head->next->next, MakeNodeFromNode(left, right));
		head = head->next->next;
	}
	return head;
}
NODE* MakeTree(NODE* phead) {
	while (phead->next) {
		NODE* res = (NODE*)malloc(sizeof(NODE));
		NODE* left = phead;
		NODE* right = phead->next;
		if (res) {
			res->freq = left->freq + right->freq;
			res->isSymb = '0';
			res->symb = '0';
			res->left = left;
			res->right = right;
			res->next = nullptr;
		}
		phead = phead->next->next;
		left->next = nullptr;
		right->next = nullptr;
		phead = Add2List(phead, res);
		free(res);
		res = nullptr;
	}
	return phead;
}
void MakeCodes(node* head, char* code, int level)
{
	if (head)
	{
		if (!head->isSymb)
		{
			if (head->left)
			{
				code[level] = '0';
				MakeCodes(head->left, code, level + 1);
			}
			if (head->right)
			{
				code[level] = '1';
				MakeCodes(head->right, code, level + 1);
			}
			code[level] = 0;
		}
		else
			strcpy(head->code, code);
	}
}
