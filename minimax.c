#include <stdio.h>
#include <stdlib.h>

#include "minimax.h"
#define maxProfundidad 6//llega hasta profundidad 7 con una demora de 2-3 sg,8 peta
#include "4enraya.h"

int calculaNumFills(Node *p){//calcula el numero de columnas vacias para despues calcular el numero de hijos ok
    int columnasContador=0;
    for (int col=0;col<N;col++) {
        // Si la columna no está llena
        if (p->tauler[0][col]==0) {
            columnasContador++;
        }
    }
    return columnasContador;}
double funcioHeuristica(Node *p){
          int aux=evaluarTablero(p->tauler);
          if(aux==1) return -1e6;
          else if(aux==2) return 1e6;
          return (rand() % 201) - 100;

}

Node* creaNode(Node *pare,int col,int nivel) {
    Node *p = malloc(sizeof(Node));
    copiaTauler(p->tauler,pare->tauler);
	int jugador;
    if (nivel%2==1) jugador=2;  //si el nivell del pare es parell juega el ordenador
    else jugador=1;
    tirada(p->tauler,col,jugador);
    int aux=evaluarTablero(p->tauler);
    if(aux!=0 || nivel>=maxProfundidad){
        p->n_fills=0;
        p->fills=NULL;
        p->valor=funcioHeuristica(p);
    }
    else{
        p->n_fills=calculaNumFills(p);
		p->fills=malloc( p->n_fills * sizeof(Node*));
	}
	return p;
}
void creaNivell(Node *pare,int nivel) {
	int k=0;
    for (int col=0;col<N;col++) {
          //si la columna no está llena
           if (pare->tauler[0][col]==0) {
             pare->fills[k] = creaNode(pare,col,nivel);
             k++;
              }
            if(k>=pare->n_fills) break;
           }
}
void crearArbre(Node *arrel,int nivel) {
    if(nivel>=maxProfundidad) return;
    creaNivell(arrel,nivel+1);
	for(int i=0 ; i<arrel->n_fills ; i++) {
       if (arrel->fills[i]->n_fills>0){
            crearArbre(arrel->fills[i],nivel+1);//nivel de fills
       }
	}
}
void recorreArbreRec(Node *arrel,int nivel,int comptador) {
    for(int i=0;i<nivel;i++) {
        printf("  ");
    }
    printf("%i-%f\n",comptador++,arrel->valor);
    for(int i=0 ; i<arrel->n_fills ; i++) {
        recorreArbreRec(arrel->fills[i],nivel+1,comptador);
    }
}
void esborraNode(Node *p){
   if(p==NULL) return;
   if(p->fills!=NULL){
     for(int i=0;i<p->n_fills; i++){
         if(p->fills[i]!=NULL){
        esborraNode(p->fills[i]);
        p->fills[i]=NULL;
          }
      }
       free(p->fills);
       p->fills=NULL;
  }
    free(p);
} //esborra 1 node de l’arbre i todo lo demas
void esborra1Nivell(Node *p){
    if(p==NULL)return;
    if(p->fills!=NULL){
        for(int i=0; i<p->n_fills; i++) {
            if(p->fills[i]!=NULL){
                esborraNode(p->fills[i]);
                p->fills[i]=NULL;
            }
        }
        free(p->fills);
        p->fills=NULL;
    }
    p->n_fills=0;
} //esborra tots els fills d’1 node, però no aquest

int deIndexaCol(Node *p,int i){//identifica el indice de un hijo con una columna
    int k=0;
     for (int col=0;col<N;col++) {
          //si la columna no está llena
           if (p->tauler[0][col]==0) {

             if(k==i) return col;
              k++;//se creo un hijo
           }
             if(k>=p->n_fills) break;
      }
  return -1;
}
int recuperarCol(Node *p){//recupera la columna si le pasas la arrel
  int indexFill=-1;
   for(int i=0;i<p->n_fills;i++){//busco cual es el hijo que tiebne el valor maximo,cogera el primero si los hijos tienen el mismo valor
    if((p->fills[i]->valor)==(p->valor)){
        indexFill=i;
        break;
    }
   }

   return deIndexaCol(p,indexFill) ;

}

void minimax(Node *p,int nivel){//hacer algoritmo de minimax con los valores del nodo fulla
    if(p==NULL || p->n_fills==0|| nivel==maxProfundidad)return;
     //recursion para llegar hasta el final
   for(int j=0;j<p->n_fills;j++) {
        minimax(p->fills[j],nivel+1);
        }
     //p es pare de un node fulla
       if(nivel%2==0){//el pare esta en un nivell parell  ok
        //Assigna el valor màxim dels fills quan el pare està en un nivell parell.
        double max=p->fills[0]->valor;
           for(int i=1;i<p->n_fills;i++){
              if((p->fills[i]->valor)>max){
                 max=p->fills[i]->valor;
                }
         }
         p->valor=max;
      }
    //Assigna el valor mínim dels fills quan el pare està en un nivell senar.
    else{ double min=p->fills[0]->valor;//ok
          for(int i=1;i<p->n_fills;i++) {
              if((p->fills[i]->valor)<min){
                 min=p->fills[i]->valor;
                }
         }
        p->valor=min;
     }

}

int ferMinimax(int tauler[N][N]){//retorna la columna escollida per a la millor jugada
    Node *p = malloc(sizeof(Node));
    copiaTauler(p->tauler,tauler);
    p->n_fills=calculaNumFills(p);
    p->fills=malloc(p->n_fills * sizeof(Node*));
    crearArbre(p,0);
    minimax(p,0);
    int aux = recuperarCol(p);
    esborraNode(p);
    return aux;
}


