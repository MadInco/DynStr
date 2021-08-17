#define _CRT_SECURE_NO_WARNINGS

#include "DynStr.h"
#include <stdio.h>
#include <string>
#include <list>

using namespace std;

char c;
//Эта функция была нужна для проверки операции сравнения строк из двух символов в реализации класса String и нового класса DynStr
//Чтобы убедиться, что операторы сравнения для нового класса работают корректно
void TestCompare() {
    char *s1, *s2;
    string str1, str2;
    string alp[28] = {""," ", "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z" };
    //                0   1    2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27
    s1 = new char[2+1];
    s2 = new char[2+1];
    unsigned int i, j, k, l, err, errL, errG, countall;
    unsigned int size = 28;
    bool boolerrL, boolerrG, boolImage;
    unsigned int ind;

    ind = 0;
    err = errL = errG = 0;
    countall = size * size * size * size;//все случаи
    countall = (countall / 2) + (countall % 2);//из-за симметричности можно расмотреть лишь половину случаев
    printf("\n--------------------------------------------------------------");
    printf("\nDo you need to draw error cases in this Test?(y/n)");
    c = '\0';
    scanf("%2c", &c);
    if (c == 'y') {
        boolImage = true;
    }
    else {
        boolImage = false;
    }
    printf("\n--------------------------------------------------------------");
    printf("\nTest begins");
    printf("\n--------------------------------------------------------------");
    for (ind = 0; ind < countall; ind ++) {
        i = ind / (size * size * size);
        j = (ind % (size * size * size)) / (size * size);
        k = (ind % (size * size)) / size;
        l = ind % size;
        str1.clear();
        str2.clear();
        str1.append(alp[i]);//i
        str1.append(alp[j]);//j
        str2.append(alp[k]);//k
        str2.append(alp[l]);//l
        sprintf(s1, str1.c_str());
        sprintf(s2, str2.c_str());
        DynStr dstr1(s1);
        DynStr dstr2(s2);
        boolerrL = ((str1 < str2) != (dstr1 < dstr2));
        boolerrG = ((str1 > str2) != (dstr1 > dstr2));
        if (boolerrL || boolerrG) {
            err++;
            if (boolerrL)
                errL++;
            if (boolerrG)
                errG++;
            if (boolImage) {
                printf("\n-----------Print-error-case-index-%d--from-%d-----------------", ind,countall);
                printf("\nSymbols s1 = '%s'|    s2 = '%s' | (i,j,k,l)=(%d,%d,%d,%d)", s1, s2, i, j, k, l);
                printf("\n   alp[%d] = '%s'|alp[%d] = '%s'|alp[%d] = '%s'|alp[%d] = '%s'", i, alp[i].c_str(), j, alp[j].c_str(), k, alp[k].c_str(), l, alp[l].c_str());
                printf("\nString-cmp '%2s' < '%2s' = '%d' | '%2s' > '%2s' = '%d'", s1, s2, str1 < str2, s1, s2, str1 > str2);
                printf("\nMyCompare  '%2s' < '%2s' = '%d' | '%2s' > '%2s' = '%d'", s1, s2, dstr1 < dstr2, s1, s2, dstr1 > dstr2);
            }
        }
    }
    printf("\n--------------------------------------------------------------");
    printf("\nLast %d-th sym s1 = '%2s', s2 = '%2s' | (l,i,j,k)=(%d,%d,%d,%d)", ind - 1, s1, s2, l, i, j, k);
    printf("\nError cases: %6d . All count = %6d . Percent is %.2f", err, countall, 100 * (1.0 * err / (countall)));
    printf("\nError cases: %6d / %6d (less'<'/great'>')", errL, errG);
    delete[] s1;
    delete[] s2;
}

int main(int argc, char* argv[])
{
    list<DynStr> L;
    bool cmd = false;
    c = '\0';
    try {
        if (argc > 1) {
            printf("Would you like to read args from cmd?(y/n)");
            scanf("%2c",&c);
            if (c == 'y') {
                cmd = true;
                printf("\nReading from cmd...");
                for (int i = 1; i < argc; i++) {
                    printf("\nSymbols in 'argc[%d]' are: '%s'", i, argv[i]);
                    L.push_back(move(argv[i]));
                }
                L.sort(greater<DynStr>());
                //L.reverse();
                printf("\n...Reverse-Sorted List...");
                int sizeL = (int)L.size();
                for (int i = 1; i <= sizeL;i++) {
                   printf("\n||| %s",L.front().GetStr());
                   L.pop_front();
                }
                printf("\n...Drawing is End...");
            }
        }
        if(!cmd){
            printf("Activate Test compare String/DynStr?(y/n)");
            c = '\0';
            scanf("%2c", &c);
            if (c == 'y') {
                TestCompare();       
            }
            else {
                char* sym;
                DynStr ds[4];
                printf("\nLets draw default DynStr's");
                ds[0] = "Lets ";
                sym = new char[strlen("draw ") + 1];
                strcpy(sym,"draw ");
                ds[1] = sym;
                ds[2] = ds[0] + ds[1];
                ds[3] = ds[2]+" HAHAHA ds[2] will be moved ";
                for (int i = 0; i < 4; i++) {
                    printf("\n ds[%d]|||%10s|||",i, ds[i].GetStr());
                }
                ds[3] = move(ds[2]);
                printf("\nAfter ds[2] moving in ds[3]");
                for (int i = 0; i < 4; i++) {
                    printf("\n ds[%d]|||%10s|||", i, ds[i].GetStr());
                }
                delete[] sym;
            }
        }
    }
    catch (...) {
        printf("EXCEPTION!!!\n");
    }
    return 0;
}