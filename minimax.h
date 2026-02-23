#ifndef MINIMAX_H
#define MINIMAX_H

#define N 8

typedef struct node {
        struct node * *fills;   //array de fills (pointers a node)
        int n_fills;
        int tauler[N][N];
        double valor;
} Node;

int calculaNumFills(Node *p);
double funcioHeuristica(Node *p);
Node* creaNode(Node *pare,int col,int nivel);
void creaNivell(Node *pare,int nivel);
void crearArbre(Node *arrel,int nivel);
void recorreArbreRec(Node *arrel,int nivel,int comptador);
void esborraNode(Node *p);
void esborra1Nivell(Node *p);
int deIndexaCol(Node *p,int i);
int recuperarCol(Node *p);
int ferMinimax(int tauler[N][N]);
void minimax(Node *p,int nivel);

#endif
