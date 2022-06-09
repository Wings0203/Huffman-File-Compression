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
    NODE* savephead = nullptr;
    phead = MakeTree(phead); // Tree

    MakeCodes(phead);

    fseek(fr, 0, SEEK_SET);
    string bitstring = string();
    char chh;
    NODE* listphead;
    while ((chh = fgetc(fr)) != EOF)
    {
            bitstring += *Symb_code(phead, chh);
    }
    fclose(fr);


    int count = bitstring.length() / BIT8;
    cout << bitstring.length()<< "\n";
    int tail = bitstring.length() % BIT8;
    int len = count + 1;
    BIT2CHAR symb;
    FILE* fw = fopen("from_h.txt", "wb");
    for (int i = 0; i < count; ++i)
    {
        symb.mbit.b1 = (unsigned int)bitstring[i * BIT8 + 0];
        symb.mbit.b2 = (unsigned int)bitstring[i * BIT8 + 1];
        symb.mbit.b3 = (unsigned int)bitstring[i * BIT8 + 2];
        symb.mbit.b4 = (unsigned int)bitstring[i * BIT8 + 3];
        symb.mbit.b5 = (unsigned int)bitstring[i * BIT8 + 4];
        symb.mbit.b6 = (unsigned int)bitstring[i * BIT8 + 5];
        symb.mbit.b7 = (unsigned int)bitstring[i * BIT8 + 6];
        symb.mbit.b8 = (unsigned int)bitstring[i * BIT8 + 7];
        fputc(symb.symb, fw);
    }

    char arr[8];
    if (tail != 0)
    {
        for (int i = 0; i < (8 - tail); i++)
        {
            arr[i] = '0';
        }
        for (int i = (8 - tail); i < 8; i++)
        {
            arr[i] = bitstring[count * BIT8 + i - 8 + tail];
        }

    }
    symb.mbit.b1 = arr[0];
    symb.mbit.b2 = arr[1];
    symb.mbit.b3 = arr[2];
    symb.mbit.b4 = arr[3];
    symb.mbit.b5 = arr[4];
    symb.mbit.b6 = arr[5];
    symb.mbit.b7 = arr[6];
    symb.mbit.b8 = arr[7];
    fputc(symb.symb, fw);
    fclose(fw);


    //unpacking
    FILE* fr1 = fopen("from_h.txt", "rb");
    FILE* fw1 = fopen("to.txt", "wb");
    fseek(fr1, 0L, SEEK_END);
    long length3 = ftell(fr);
    fseek(fr1, 0, SEEK_SET);
    int index2 = 0;
    if (!fr1)
    {
        exit(15);
    }
    string code_new;
    BIT2CHAR symb1;
    int l = 1;
    while (l <= length3)
    {
        symb1.symb = fgetc(fr1);
        index2++;
        l++;
        code_new.push_back((char)(((int)'0')+symb1.mbit.b1));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b2));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b3));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b4));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b5));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b6));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b7));
        code_new.push_back((char)(((int)'0')+symb1.mbit.b8));
    }

    int i = 0;
    int length1 = code_new.length();
    string cd;
    char symbol;
    int counti = 0;
    while (i < length1)
    {
        if ((tail != 0) && (i >= (length1 - 8)) && (i < (length1 - tail)))
        {
            i++;
            continue;
        }
        cd.push_back(code_new[i]);
        if (symbol = Code_symb(phead, cd))
        {
           counti++;
           fputc(symbol, fw1);
           cd = string();
        }
        i++;
    }
    fclose(fr1);
    fclose(fw1);
    return 0;
}
