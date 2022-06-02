#include "NODE.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define BIT8 8
#pragma warning(disable : 4996)

typedef union bit2char {
	unsigned char symb;
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
	//NODE* listphead = phead;
	PrintList(phead);
	printf("\n\n");

	NODE* savephead = nullptr;
	savephead = CopyList(phead, savephead);
	//PrintList(savephead);
	
	phead = MakeTreeFromList(phead); // Tree.
	char code[CODE_SIZE] = {0};
	MakeCodes(phead, code, 0);
	fseek(fr, 0, SEEK_SET);
	char* bitstring = (char*)malloc(1000*length*sizeof(char));
	char chh;
	bool first = 1;
	NODE* listphead;
	while ((chh = fgetc(fr)) != EOF)
	{
		//printf("%c ", chh);
		listphead = savephead;
		while (listphead)
		{
			if (listphead->symb == chh)
			{
				if (first)
				{
					strcpy(bitstring, listphead->code);
					first = 0;
					//printf(listphead->code);
					//printf("\n");
					break;
				}
				strcat(bitstring, listphead->code);
				//printf("%c ", listphead->symb);
				//printf(listphead->code);
				//printf("\n");
				break;
			}
			printf(bitstring);
			printf("\n");
			listphead = listphead->next;
		}
	}
	//printf(bitstring);
	fclose(fr);
	//string str;
	int count = strlen(bitstring) / BIT8;
	printf("%d", strlen(bitstring));
	int tail = strlen(bitstring) % BIT8; 
	//printf("%d", tail);//остаток из нулей
	int len = count + 1;           //длина результирующей строки
	BIT2CHAR symb;
	char* bits = (char*)malloc(8 * sizeof(char));
	char* res = (char*)malloc(len * sizeof(char));
	FILE* fw = fopen("from_h", "wb");
	for (int i = 0; i < count; ++i)
	{
		symb.mbit.b1 = (unsigned int)bitstring[i * BIT8 + 0];
		printf("%d", symb.mbit.b1);
		symb.mbit.b2 = (unsigned int)bitstring[i * BIT8 + 1];
		symb.mbit.b3 = (unsigned int)bitstring[i * BIT8 + 2];
		symb.mbit.b4 = (unsigned int)bitstring[i * BIT8 + 3];
		symb.mbit.b5 = (unsigned int)bitstring[i * BIT8 + 4];
		symb.mbit.b6 = (unsigned int)bitstring[i * BIT8 + 5];
		symb.mbit.b7 = (unsigned int)bitstring[i * BIT8 + 6];
		symb.mbit.b8 = (unsigned int)bitstring[i * BIT8 + 7];
		printf("%c", symb.symb);
		fputc(symb.symb, fw);
	}
	//printf(res);
	printf("\n");
	// запись хвоста с 0
	char arr[8];
	if (tail != 0)
	{
		for (int i = 0; i < (8 - tail); i++)
		{
			arr[i] = '0';
			//printf("%c", arr[i]);
		}
		for (int i = (8 - tail); i < 8; i++)
		{
			arr[i] = bitstring[count * BIT8 + i - 8 + tail];
			//printf("%c", arr[i]);
		}
		
	}
	//printf("\n");
	symb.mbit.b1 = arr[0];
	symb.mbit.b2 = arr[1];
	symb.mbit.b3 = arr[2];
	symb.mbit.b4 = arr[3];
	symb.mbit.b5 = arr[4];
	symb.mbit.b6 = arr[5];
	symb.mbit.b7 = arr[6];
	symb.mbit.b8 = arr[7];
	fputc(symb.symb, fw);
	//fclose(fr);
	fclose(fw);
	return 0;
}
