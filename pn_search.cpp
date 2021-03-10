/*************************************************************************
    > File Name: pn_search.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com
    > Created Time: 2021年03月10日 星期三 20时00分41秒
 ************************************************************************/

#include "pn_search.h"
#include "tic_tac_toe.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <algorithm>
using namespace std;

static Node *pool;
static int ctot, ctop;

static void init_pool(int ep){
    int nc = 1, cfac = 1;
    for(int i = ep; i >= 1; i--)
        nc += (cfac*=i);
    ctot = 0;
    ctop = nc;
    pool = (Node *)malloc(nc*sizeof(Node));
    if(pool == NULL){
        fprintf(stderr, "pool_init error: %s\n", strerror(errno));
        exit(-1);
    }
}
static void deinit_pool(){
    free(pool);
}

Node *new_node(unsigned pad, Node *prt, bool nodetype, bool book){
    int np, ep;
    get_npep(pad, np, ep);
    if(prt == NULL)
        init_pool(ep);

    if(ctot >= ctop){
        fprintf(stderr, "node pool is full, while ctot = %d, ctop = %d\n", ctot, ctop);
        exit(-1);
    }
    Node *ret = &pool[ctot++];

    ret->pad = pad;
    ret->nodetype = nodetype;
    ret->prt = prt;
    ret->chd = NULL;

    ret->np = np;
    ret->clen = ep;
    if(nodetype == ANDNODE)
        np = CHANGEP(np);
    int cv = evaluate(pad);
    if(cv != UNKNOWN){
        if(book)
            cv = (cv!=CHANGEP(np));
        else
            cv = (cv==np);
    }
    ret->val = cv;
    setpn(ret);
    return ret;
}

void setpn(Node *node){
    if(node->chd != NULL){
        int pn, dpn;
        if(node->nodetype == ANDNODE){
            pn = 0;
            dpn = INFINITY;
            for(int i = 0; i < node->clen; i++){
                if(pn < INFINITY)
                    pn += (node->chd[i]).pn;
                dpn = min(dpn, (node->chd[i]).dpn);
            }
        }else{
            pn = INFINITY;
            dpn = 0;
            for(int i = 0; i < node->clen; i++){
                pn = min(pn, (node->chd[i]).pn);
                if(dpn < INFINITY)
                    dpn += (node->chd[i]).dpn;
            }
        }
        node->pn = min(pn, INFINITY);
        node->dpn = min(dpn, INFINITY);
    }else{
        switch(node->val){
            case UNKNOWN:
                node->pn = node->dpn = 1;
                break;
            case FALSE:
                node->pn = INFINITY;
                node->dpn = 0;
                break;
            case TRUE:
                node->pn = 0;
                node->dpn = INFINITY;
                break;
        }
    }
}

unsigned solve(unsigned pad){
    Node *root = new_node(pad, NULL, ORNODE, false);
    Node *cur = root;
    while(root->pn != 0 && root->dpn != 0){
        cur = get_provingnode(cur);
        expand(cur, false);
        cur = update_ancestor(cur);
    }
    if(root->pn != 0){
        re_evaluate(root);
        cur = root;
        while(root->pn != 0 && root->dpn != 0){
            cur = get_provingnode(cur);
            expand(cur, true);
            cur = update_ancestor(cur);
        }
        if(root->pn != 0){
            fprintf(stderr, "unbelievable...\n");
            exit(-1);
        }
        //puts("can't always win...");
    }
    //else
    //    puts("i can win...");
    for(int i = 0; i < root->clen; i++)
        if((root->chd[i]).pn == 0){
            pad = (root->chd[i]).pad;
            break;
        }
    deinit_pool();
    return pad;
}
void get_npep(unsigned pad, int &np, int &ep){
    int tnp = OPIECE;
    int tep = 0;
    for(int i = 0; i < 9; i++, pad>>=2)
        switch(pad&0x3){
            case OPIECE:
                tnp++;
                break;
            case XPIECE:
                tnp--;
                break;
            default:
                tep++;
        }
    np = tnp;
    ep = tep;
}

Node *get_provingnode(Node *node){
    while(node->chd){
        if(node->nodetype == ANDNODE){
            for(int i = 0; i < node->clen; i++)
                if(node->dpn == (node->chd[i]).dpn){
                    node = &(node->chd[i]);
                    break;
                }
        }else{
            for(int i = 0; i < node->clen; i++)
                if(node->pn == (node->chd[i]).pn){
                    node = &(node->chd[i]);
                    break;
                }
        }
    }
    return node;
}

void expand(Node *node, bool book){
    int np = node->np;
    int tot = 0;
    unsigned cpad = node->pad;
    bool ntype = (node->nodetype)^1;

    for(int i = 0; i < 9; i++)
        if((cpad&(0x3<<(2*i)))==0){
            Node *tmp = new_node((cpad|(np<<(2*i))), node, ntype, book);
            if(node->chd == NULL)
                node->chd = tmp;
        }
}

Node *update_ancestor(Node *node){
    bool book = true;
    Node *ret = NULL;
    while(book && node != NULL){
        int opn = node->pn, odpn = node->dpn;
        setpn(node);
        book = ((opn != node->pn) || (odpn != node->dpn));
        ret = node;
        node = node->prt;
    }
    return ret;
}


void re_evaluate(Node *node){
    if(node->chd){
        for(int i = 0; i < node->clen; i++)
            re_evaluate(&(node->chd[i]));
    }else{
        int cv = evaluate(node->pad);
        int np = node->np;
        if(node->nodetype == ANDNODE)
            np = CHANGEP(np);
        if(cv != UNKNOWN)
            cv = (cv != CHANGEP(np));
        node->val = cv;
    }
    setpn(node);
}

