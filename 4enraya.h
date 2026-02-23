#ifndef ENRAYA_H
#define ENRAYA_H

#define N 8

void refrescar();//refresca la consola
void imprimirTablero(int t[N][N]);//imprime un tablero estetico
void imprimirMatriu(int  m[N][N]);
void matrizInicial(int  m[N][N]);//llena de ceros una matriz
int evaluarTablero(int  m[N][N]);//evalua el tablero, devuelve el jugador que gana(1 o 2)
int tirada(int  m[N][N],int col,int jugador);//hace la tirada en la matriz
int introducirJugada(int jugador,int  m[N][N]);
void jugarHumanos(int  m[N][N]);
void jugarOrdenador(int m[N][N],int posicion);
void iniciarJuego(int  m[N][N]);
void copiaTauler(int taulernou[N][N], int tauler[N][N]);

#endif
