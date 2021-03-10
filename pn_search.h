/*************************************************************************
    > File Name: pn_search.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 19时50分52秒
 ************************************************************************/

#define UNKNOWN -1
#define INFINITY 0x3f3f3f3f
#define TRUE 1
#define FALSE 0
#define ANDNODE 0
#define ORNODE 1

struct Node{
    unsigned pad;
    int val;

    int pn, dpn;

    int np;

    bool nodetype;

    Node *prt;

    Node *chd;
    int clen;
};

Node *new_node(unsigned pad, Node *prt, bool nodetype, bool book);
//book -- whether to allow draw
unsigned solve(unsigned pad);
void setpn(Node *node);
void get_npep(unsigned pad, int &np, int &ep);
//np -- next_piece
//ep -- number of empty pieces.
Node *get_provingnode(Node *node);
void expand(Node *node, bool book);
Node *update_ancestor(Node *node);
//void delete_node(Node *node);
void re_evaluate(Node *node);

