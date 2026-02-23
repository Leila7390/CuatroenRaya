#include <stdio.h>
#include <stdlib.h>
#include "minimax.h"
#include <time.h>
#define RESET   "\x1b[0m"
#define GREEN   "\x1b[32m"
#define MAGENTA "\x1b[35m"   // morado

void refrescar() {
    printf("\033[2J\033[H");
}
void imprimirTablero(int t[N][N]) {
    printf("\n");
    printf("---------------------------------\n");
    for (int i= 0; i< N; i++) {
        printf("|");
        for (int j= 0; j < N; j++) {
            if (t[i][j] == 1) printf(" %sX%s |", GREEN, RESET);
            else if (t[i][j] == 2) printf(" %s●%s |", MAGENTA, RESET);
            else printf("   |");
        }
        printf("\n---------------------------------\n");
    }
    printf("\n");
}

void imprimirMatriu(int m[N][N]){
    for(int i=0;i<N; i++) {
            for(int j=0;j<N;j++){
                    printf("%i ", m[i][j]);
            } printf("\n");
    }
}
void matrizInicial(int  m[N][N]){
   for(int i=0;i<N; i++) {
            for(int j=0;j<N;j++){
                  m[i][j] = 0;
            }
    }
}
void copiaTauler(int taulernou[N][N], int tauler[N][N]){//ok
     for(int i=0;i<N; i++) {
            for(int j=0;j<N;j++){
                  taulernou[i][j] = tauler[i][j];
            }
    }
}

int evaluarTablero(int  m[N][N]){

    //en horizontal ok
    for(int i=0;i<N;i++){
            for(int j=0;j<N-3;j++){
                   if(m[i][j]!=0 && m[i][j]==m[i][j+1] && m[i][j+1]==m[i][j+2] && m[i][j+2]==m[i][j+3]){
                      return m[i][j];
                   }
            }
    }
    //en vertical ok
     for(int i=0;i<N;i++){
            for(int j=0;j<N-3;j++){
                   if(m[j][i]!=0 && m[j][i]==m[j+1][i] &&m[j+1][i]==m[j+2][i] && m[j+2][i]==m[j+3][i]){
                      return m[j][i];

                   }
            }
    }//en diagonal arriba izquierda abajo derecha ok
     for(int i=0;i<N-3;i++){
            for(int j=0;j<N-3;j++){
                    if(m[i][j]!=0 && m[i][j]==m[i+1][j+1] && m[i+1][j+1]==m[i+2][j+2] && m[i+2][j+2]==m[i+3][j+3]){
                       return m[i][j];

                    }
            }
    }
    //en diagonal arriba derecha abajo izquierda ok
     for(int i=0;i<N-3;i++){
            for(int j=3;j<N;j++){
                    if(m[i][j]!=0 && m[i][j]==m[i+1][j-1] && m[i+1][j-1]==m[i+2][j-2] && m[i+2][j-2]==m[i+3][j-3]){
                    return m[i][j];

                    }
            }
    }
     //el tablero no esta lleno
   for(int i=0;i<N; i++) {
            for(int j=0;j<N;j++){
                  if(m[i][j] == 0) return 0;//continuar jugando
            }
    }

    return 3;//el tablero esta lleno
}
int tirada(int  m[N][N],int col,int jugador) {//introduce la tirada en la matriz
          for(int i=N-1;i>=0;i--){//mirar la matriz
           if(m[i][col] == 0) {
                m[i][col]=jugador;
                break;
            }
            else if(i==0) return 1;
           }
           return 0;
}
int introducirJugada(int jugador,int  m[N][N]){
    int colH;//columna para humanos
    int entradaValida=0;
    while(entradaValida==0){
    if(jugador==1)printf("%sTurno del jugador CRUZ : %s\n",GREEN,RESET);
    else printf("%sTurno del jugador PUNTO : %s\n",MAGENTA,RESET);
    scanf("%i",&colH);
     if(colH<=N && colH>=1){//columna introducida correctamente
         if (tirada(m,colH-1,jugador)==0) entradaValida=1;
         else printf("La columna esta llena, elija otra columna\n ");
        }
     else printf("La columna no existe\n");
    }
    return colH-1;
}
void jugarHumanos(int m[N][N]){
    int aux;
    int jugador=1;
    imprimirTablero(m);
    while(1){//bucle infinito
         introducirJugada(jugador,m);
         refrescar();
         imprimirTablero(m);
         aux=evaluarTablero(m);
         if(aux==1){printf("%sEl juego se ha terminado. Ha ganado CRUZ%s\n",GREEN,RESET);return;}
         else if(aux==2){printf("%sEl juego se ha terminado. Ha ganado PUNTO%s\n",MAGENTA,RESET);return;}
         else if(aux==3){printf("Empate.El tablero esta lleno.\n");return;}
          jugador = (jugador == 1) ? 2 : 1;
    }

   }
void jugarOrdenador(int  m[N][N],int posicion){//el odenador siempre sera jugador dos aunque empieze primero
    int colmm;
    int aux;
    int jugador;
    if(posicion==1)jugador=1;
    else jugador=2;
    imprimirTablero(m);
    while(1){//bucle infinito
         if(jugador==1){
                introducirJugada(1,m);
              }
        else { printf("Turno del Ordenador\n");
             colmm=ferMinimax(m);//juega la maquina 3-posicion
             tirada(m,colmm,2);
             }
             refrescar();
            imprimirTablero(m);
             aux=evaluarTablero(m);
            if(aux==1){printf("%sEl juego se ha terminado. Ha ganado CRUZ%s\n",GREEN,RESET);return;}
            else if(aux==2){printf("%sEl juego se ha terminado. Ha ganado PUNTO%s\n",MAGENTA,RESET);return;}
            else if(aux==3){printf("Empate. El tablero esta lleno.\n");return;}

            jugador = (jugador == 1) ? 2 : 1;//cambia el jugador fancy
          }


     }

void iniciarJuego(int  m[N][N]){
    int modo;
    matrizInicial(m);
    printf("                  %s=== 4 EN RAYA ===%s\n",MAGENTA,RESET);
    printf("Instrucciones: Introduce el numero de columna (1-%d)\n", N);
    printf("Introduzca 1 para jugar entre humanos y 2 para jugar contra el ordenador \n");
    scanf("%i",&modo);
    if(modo==1) jugarHumanos(m);
    else if(modo==2){
           printf("Introduzca 1 para empezar primero o 2 para ser segundo\n");
           scanf("%i",&modo);
          if(modo==1) jugarOrdenador(m,1);
          else if(modo==2) jugarOrdenador(m,2);
    }
    else printf("La opción no es valida\n");
    

}
int main(void) {
     srand(time(NULL));
    int tauler[N][N];
    iniciarJuego(tauler);

	return 0;
}


