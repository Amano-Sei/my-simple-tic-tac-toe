/*************************************************************************
    > File Name: pvp.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 19时37分57秒
 ************************************************************************/

#include <cstdio>
#include "tic_tac_toe.h"

int main(){
    int cp = 1;
    int cx, cy;
    int cv;
    unsigned pad = 0;
    print(pad);
    while((cv = evaluate(pad)) == -1){
        do
            scanf("%d%d", &cx, &cy);
        while(cx <= 0 || cx > 3 || cy <= 0 || cy > 3 || ((pad>>(((cx-1)*3+cy-1)*2))&0x3));
        pad |= cp<<(((cx-1)*3+cy-1)*2);
        print(pad);
        cp ^= 3;
    }
    switch(cv){
        case 1:
            puts("o win.");
            break;
        case 2:
            puts("x win.");
            break;
        default:
            puts("draw");
            break;
    }
    return 0;
}

