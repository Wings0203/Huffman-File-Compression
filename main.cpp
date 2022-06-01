#include "NODE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define BIT8 8
#pragma warning(disable : 4996)

typedef union bit2char {
	char symb;
	int value;
	struct bit {
		unsigned b1 : 1;
		unsigned b2 : 1;
		unsigned b3 : 1;
		unsigned b4 : 1;
		unsigned b5 : 1;
		unsigned b6 : 1;
		unsigned b7 : 1;
		unsigned b8 : 1;
	}mbit;
}BIT2CHAR;

int bit2value(BIT2CHAR test) {
	int temp = 0; // Число в 2 СС
	temp += test.mbit.b1 * pow(10, 7);
	temp += test.mbit.b2 * pow(10, 6);
	temp += test.mbit.b3 * pow(10, 5);
	temp += test.mbit.b4 * pow(10, 4);
	temp += test.mbit.b5 * pow(10, 3);
	temp += test.mbit.b6 * pow(10, 2);
	temp += test.mbit.b7 * pow(10, 1);
	temp += test.mbit.b8 * pow(10, 0);
	int res = 0; // Число в 10 СС
	int i = 0;
	while (temp) {
		res += (temp % 10) * 2 + pow(10, i);
		i++;
		temp /= 10;
	}
	return res;
}


int main() {
	unsigned int mas[256];
	for (int i = 0; i < 256; i++)
		mas[i] = 0;
	FILE* fr = fopen("from.txt", "rb");
	if (!fr)
		return 1;
	fseek(fr, 0L, SEEK_END);
	long length = ftell(fr);
	fseek(fr, 0, SEEK_SET);
	printf("%ld\n\n", length);
	for (int i = 0; i < length; ++i)
	{
		mas[(unsigned char)fgetc(fr)] ++;
	}
	NODE* phead = nullptr; // The beginning of the list. Then the root of the tree.
	NODE* pnew = nullptr;	// Element that we add to the list.
	for (int i = 0; i < 256; i++) {
		if (mas[i] != 0) {
			pnew = CreateNode((unsigned char)i, 1, mas[i]);
			phead = Add2List(phead, pnew);
		}
	}
	NODE* listphead = phead;
	PrintList(phead);
	//phead = MakeTreeFromList(phead); // Tree.
	phead = MakeTree(phead);
	printf("%d", phead->freq);
	printf("%d", phead->left->freq);
	//PrintTree(phead);

	//char code[CODE_SIZE] = { 0 };
	//MakeCodes(phead, code, 0);
	//fseek(fr, 0, SEEK_SET);
	//char* bitstring = (char*)malloc(1000 * length * sizeof(char));
	//char chh;
	//bool first = 1;
	//while ((chh = fgetc(fr)) != EOF)
	//{
	//	//printf("%c ", chh);
	//	listphead = savephead;
	//	while (listphead)
	//	{
	//		if (listphead->symb == chh)
	//		{
	//			if (first)
	//			{
	//				strcpy(bitstring, listphead->code);
	//				//printf("%c ", listphead->symb);
	//				first = 0;
	//				printf(listphead->code);
	//				printf("\n");
	//				break;
	//			}
	//			strcat(bitstring, listphead->code);
	//			//printf("%c ", listphead->symb);
	//			printf(listphead->code);
	//			printf("\n");
	//			break;
	//		}
	//		listphead = listphead->next;
	//	}
	//}
	////printf(bitstring);
	//fclose(fr);

	////string str;
	//int count = strlen(bitstring) / BIT8;
	//int tail = strlen(bitstring) % BIT8; //остаток из нулей
	//int len = count + 1;           //длина результирующей строки
	//BIT2CHAR symb;
	//char* bits = (char*)malloc(8 * sizeof(char));
	//char* res = (char*)malloc(len * sizeof(char));
	//for (int i = 0; i < count; ++i)
	//{
	//	symb.mbit.b1 = bitstring[i * BIT8 + 0];
	//	symb.mbit.b2 = bitstring[i * BIT8 + 1];
	//	symb.mbit.b3 = bitstring[i * BIT8 + 2];
	//	symb.mbit.b4 = bitstring[i * BIT8 + 3];
	//	symb.mbit.b5 = bitstring[i * BIT8 + 4];
	//	symb.mbit.b6 = bitstring[i * BIT8 + 5];
	//	symb.mbit.b7 = bitstring[i * BIT8 + 6];
	//	symb.mbit.b8 = bitstring[i * BIT8 + 7];
	//	res[i] = bit2value(symb);
	//}
	//if (tail != 0)
	//{
	//	for (int i = 0; i < tail; ++i)
	//	{
	//		symb.mbit.
	//	}
	//	for (int i = 0; i < tail; ++i)
	//}

	//BIT2CHAR test;
	//test.mbit.b1 = 0;
	//test.mbit.b2 = 0;
	//test.mbit.b3 = 0;
	//test.mbit.b4 = 1;
	//test.mbit.b5 = 0;
	//test.mbit.b6 = 0;
	//test.mbit.b7 = 0;
	//test.mbit.b8 = 0;
	//test.value = bit2value(test);
	//printf("yes %c == %c", test.symb, (char)test.value);
	return 0;
}