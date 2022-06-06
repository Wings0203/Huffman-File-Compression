#include "NODE.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS
#define BIT8 8

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
    int temp = 0; // ����� � 2 ��
    temp += test.mbit.b1 * pow(10, 7);
    temp += test.mbit.b2 * pow(10, 6);
    temp += test.mbit.b3 * pow(10, 5);
    temp += test.mbit.b4 * pow(10, 4);
    temp += test.mbit.b5 * pow(10, 3);
    temp += test.mbit.b6 * pow(10, 2);
    temp += test.mbit.b7 * pow(10, 1);
    temp += test.mbit.b8 * pow(10, 0);
    int res = 0; // ����� � 10 ��
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
        exit(1);
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
    //cout << 1;

    printf("\n\n");

    NODE* savephead = nullptr;
    savephead = CopyList(phead, savephead);
    //PrintList(savephead);
    phead = MakeTree(phead); // Tree.
    //printf("%d    ", phead->right->freq);
    //char code[CODE_SIZE] = { 0 };
    //string code;
    PrintTree(phead);
    MakeCodes(phead);

    cout << "ok";
    fseek(fr, 0, SEEK_SET);
    //char* bitstring = (char*)malloc(1000 * length * sizeof(char));
    string bitstring = string();
    char chh;
    NODE* listphead;
    while ((chh = fgetc(fr)) != EOF)
    {
        //printf("%c ", chh);
        listphead = savephead;
        while (listphead)
        {
            if (listphead->symb == chh)
            {
                //strcat(bitstring, listphead->code);
                cout << *listphead->code << "\n";
                bitstring += *listphead->code;
                //cout << bitstring << '\n';
                //printf("%c ", listphead->symb);
                //printf(listphead->code);
                //printf("\n");
                break;
            }
            //printf(bitstring);

            listphead = listphead->next;
        }
    }
    cout << "\n" << bitstring ;
    fclose(fr);
    //string str;
    int count = bitstring.length() / BIT8;
    printf("%d", bitstring.length());
    int tail = bitstring.length() % BIT8;
    //printf("%d", tail);
    int len = count + 1;
    BIT2CHAR symb;
    /*char* bits = (char*)malloc(8 * sizeof(char));
    char* res = (char*)malloc(len * sizeof(char));*/
    FILE* fw = fopen("from_h.txt", "wb");
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


    //unpacking
    FILE* fr1 = fopen("from_h.txt", "rb");
    FILE* fw1 = fopen("to.txt", "wb");
    if (!fr1)
    {
        exit(15);
    }
    string code_new;
    char chh1;
    BIT2CHAR symb1;
    while ((chh1 = fgetc(fr1)) != EOF)
    {
        symb1.symb = chh1;
        code_new.push_back((char)symb1.mbit.b1);
        code_new.push_back((char)symb1.mbit.b2);
        code_new.push_back((char)symb1.mbit.b3);
        code_new.push_back((char)symb1.mbit.b4);
        code_new.push_back((char)symb1.mbit.b5);
        code_new.push_back((char)symb1.mbit.b6);
        code_new.push_back((char)symb1.mbit.b7);
        code_new.push_back((char)symb1.mbit.b8);
    }
    int i = 0;
    int length1 = code_new.length();
    string cd;
    while (i < length1)
    {
        if ((tail != 0) && (i >= (length1 - 8)) && (i < (length1 - tail)))
        {
            cd = string();
            i++;
            continue;
        }
        cd.push_back(code_new[i]);
        listphead = savephead;
        while (listphead)
        {
            if (*listphead->code == cd)
            {
                fputc(listphead->symb, fw1);
                cd = string();
                break;
            }
            listphead = listphead->next;
        }
        i++;
    }
    fclose(fr1);
    fclose(fw1);
    return 0;
}
