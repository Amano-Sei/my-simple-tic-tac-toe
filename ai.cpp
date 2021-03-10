/*************************************************************************
    > File Name: ai.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 21时53分57秒
 ************************************************************************/

#include "tic_tac_toe.h"
#include "pn_search.h"
#include <cstdio>

int main(){
    int cx, cy;
    unsigned pad = 0;
    printf("o/x?");
    char cp = getchar();
    int pc = (cp=='x');
    int tv;
    print(pad);
    for(int i = 0; i < 9; i++){
        if((i&1) == pc){
            do{
                scanf("%d%d", &cx, &cy);
                cx--;
                cy--;
            }while((cx < 0 || cx >= 3 || cy < 0 || cy >= 3 || (pad&(0x3<<(2*(cx*3+cy))))) && puts("error input") >= 0);
            pad |= ((pc+1)<<(2*(cx*3+cy)));
        }else
            pad = solve(pad);
        print(pad);
        if((tv = evaluate(pad)) >= 0){
            switch(tv){
                case 0:
                    puts("draw");
                    break;
                default:
                    if(tv == pc+1)
                        puts("You win.");
                    else
                        puts("You lose.");
            }
            break;
        }
    }
    return 0;
}

