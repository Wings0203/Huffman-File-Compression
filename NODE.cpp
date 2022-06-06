#include "NODE.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#define _CRT_SECURE_NO_WARNINGS
using namespace std;

// Standart functions
NODE* CreateNode(unsigned char symb, unsigned char isSymb, unsigned int freq) {
    NODE* res = new NODE;
    if (res) {
        res->symb = symb;
        res->isSymb = 1;
        res->freq = freq;
    }
    return res;
}

NODE* Add2List(NODE* head, NODE* newnode) {
    NODE* tmp = newnode;
    if (!newnode) {
        cout << "Error";
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
    //PrintTree(phead->left);
    //printf("%d\n", phead->freq);
    //PrintTree(phead->right);
    if (phead->isSymb) {
        cout << phead->symb << " " ;
        //printf("%c %d\n", phead->symb, phead->freq);
    }
    else {
        PrintTree(phead->left);
        PrintTree(phead->right);
    }
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

NODE* MakeTree(NODE* phead) {
    while (phead->next) {
        NODE* res = new NODE;
        NODE* left = phead;
        NODE* right = phead->next;
        if (res) {
            res->freq = left->freq + right->freq;
            res->isSymb = 0;
            res->symb = 0;
            res->left = left;
            res->right = right;
            res->next = nullptr;
        }
        phead = phead->next->next;
        left->next = nullptr;
        right->next = nullptr;
        phead = Add2List(phead, res);
        //res = nullptr;
    }
    return phead;
}


void MakeCodes(node* phead)
{
//    if (phead->left) {
//        cout << "0 " << phead->left->code << " 1\n";
//    }
//    if (phead->right) {
//        cout << "2 " << phead->right->code << " 3\n";
//    }
    if (phead->left)
    {
       // phead->left->code + "0";
        *phead->left->code = *phead->code + "0";
        MakeCodes(phead->left);
    }
    if (phead->right)
    {
        *phead->right->code = *phead->code + '1';
        MakeCodes(phead->right);
    }
}
/*
void MakeCodes(node* head, string code, int level)
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
			head->code = code; //strcpy(head->code, code);
	}
}*/
