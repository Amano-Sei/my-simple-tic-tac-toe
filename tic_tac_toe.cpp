/*************************************************************************
    > File Name: tic_tac_toe.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 19时09分26秒
 ************************************************************************/

#include <cstdio>
#include <cstring>

void print(unsigned pad){
    puts("=====");
    for(int i = 0; i < 3; i++){
        putchar(' ');
        for(int j = 0; j < 3; j++, pad >>= 2)
            switch(pad&0x3){
                case 1:
                    putchar('o');
                    break;
                case 2:
                    putchar('x');
                    break;
                default:
                    putchar('+');
                    break;
            }
        putchar('\n');
    }
    puts("=====");
}

int evaluate(unsigned pad){
    int tmp = pad&0x3f;
    if(tmp == 0x15)
        return 1;
    else if(tmp == 0x2a)
        return 2;
    tmp = (pad>>6)&0x3f;
    if(tmp == 0x15)
        return 1;
    else if(tmp == 0x2a)
        return 2;
    tmp = (pad>>12)&0x3f;
    if(tmp == 0x15)
        return 1;
    else if(tmp == 0x2a)
        return 2;

    tmp = pad&0x30c3;
    if(tmp == 0x1041)
        return 1;
    else if(tmp == 0x2082)
        return 2;
    tmp = (pad>>2)&0x30c3;
    if(tmp == 0x1041)
        return 1;
    else if(tmp == 0x2082)
        return 2;
    tmp = (pad>>4)&0x30c3;
    if(tmp == 0x1041)
        return 1;
    else if(tmp == 0x2082)
        return 2;

    tmp = pad&0x30303;
    if(tmp == 0x10101)
        return 1;
    else if(tmp == 0x20202)
        return 2;
    tmp = pad&0x3330;
    if(tmp == 0x1110)
        return 1;
    else if(tmp == 0x2220)
        return 2;

    for(int i = 0; i < 9; i++, pad>>=2)
        if((pad&0x3) == 0)
            return -1;
    return 0;
}

