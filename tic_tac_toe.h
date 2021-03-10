/*************************************************************************
    > File Name: tic_tac_toe.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 18时53分28秒
 ************************************************************************/

#define UNKNOWN -1
#define OPIECE 1
#define XPIECE 2
#define CHANGEP(x) ((x)^0x3)

void print(unsigned pad);
//0 is empty, 1 is o, 2 is x.
int evaluate(unsigned pad);
//0 is draw, 1 is o win, 2 is x win, -1 is unknown.

