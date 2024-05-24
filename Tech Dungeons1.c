#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>
#include <time.h>

#define TECLA_CIMA 'w'
#define TECLA_ESQUERDA 'a'
#define TECLA_BAIXO 's'
#define TECLA_DIREITA 'd'
#define CHAVE_INTERATIVA 'i'

#define COR_JOGADOR 11    
#define COR_MONSTRO_NIVEL1 2   
#define COR_MONSTRO_NIVEL2 5   
#define COR_MONSTRO_NIVEL3 15   
#define COR_BOTAO 14      
#define COR_PORTA 10     
#define COR_CHAVE 13      
#define COR_ESPINHO 15 
#define COR_TELEPORTE 15   
#define COR_PADRAO_FASE1 4   
#define COR_PADRAO_FASE2 1     
#define COR_PADRAO_FASE3 6     

#define LARGURA_TELA_FASE1 15
#define ALTURA_TELA_FASE1 15

#define LARGURA_TELA_FASE2 30
#define ALTURA_TELA_FASE2 30

#define LARGURA_TELA_FASE3 60
#define ALTURA_TELA_FASE3 60

int espinhos_tocados = 0;
int jogador_x = LARGURA_TELA_FASE1 / 2;
int jogador_y = ALTURA_TELA_FASE1 / 2;
int jogador_vida = 3;
int contador_reiniciar_jogo = 0;
int fase_atual = 1;
int jogo_em_execucao = 1;

char mapa_fase1[ALTURA_TELA_FASE1][LARGURA_TELA_FASE1] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ','#',' ',' ','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ','#',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

char mapa_fase2[ALTURA_TELA_FASE2][LARGURA_TELA_FASE2] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','*'},
   {'*',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

char mapa_fase3[ALTURA_TELA_FASE3][LARGURA_TELA_FASE3] = {
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*',' ','#',' ','*',' ',' ',' ',' ',' ','#','*','*','*','*','*','*','*','*',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','*',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*','*','*','*',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','#','#',' ',' ','*','*','*','*','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','#','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*','*','*','*','*','*','*',' ','*','*','*','*','*','#','*','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*','*','*','*','*','#',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','#',' ','*','*','*',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','#',' ','#','*','*',' ','*','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ','#',' ',' ',' ',' ','#',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ','#','*','*','*','*','*','*','*','*','*','*','*','*',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','#',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ',' ','#','*',' ',' ',' ',' ',' ',' ','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','*',' ',' ',' ',' ',' ','#','*'},
   {'*',' ',' ',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ','*',' ',' ',' ',' ',' ',' ','*'},
   {'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'},
};

typedef struct {
    int x1, y1;
    int portaIDfase1;
    int estaTrancadafase1;
} PortaFase1;

PortaFase1 portasfase1[] = {
    {0, 13, 1, 1},  
};

int numPortasfase1 = sizeof(portasfase1) / sizeof(portasfase1[0]);

typedef struct {
    int x2, y2;
    int chaveIDfase1;
} PosicaoChaveFase1;

PosicaoChaveFase1 posicoes_chaves_fase1[] = {
    {1, 9, 1},  
};

int numChavesfase1 = sizeof(posicoes_chaves_fase1) / sizeof(posicoes_chaves_fase1[0]);

typedef struct {
    int x3, y3;
} Monstro_nivel1;

Monstro_nivel1 monstro;

typedef struct {
    int x4, y4;
} Monstro_nivel2;

Monstro_nivel2 monstro2;

typedef struct {
    int x5, y5; 
    int x6, y6;
} Teleportefase2;

Teleportefase2 teletransportesfase2[] = {
    {28, 11, 1, 13},  
};

int numTeleportesfase2 = sizeof(teletransportesfase2) / sizeof(teletransportesfase2[0]);

typedef struct {
    int x7, y7;
    int portaIDfase2;
    int estaTrancada;
} PortaFase2;

PortaFase2 portasfase2[] = {
    {29, 27, 1, 1},  
};

int numPortasfase2 = sizeof(portasfase2) / sizeof(portasfase2[0]);

typedef struct {
    int x8, y8;
    int chaveIDfase2;
} PosicaoChaveFase2;

PosicaoChaveFase2 posicoes_chaves_fase2[] = {
    {1, 1, 1},  
};

int numChavesfase2 = sizeof(posicoes_chaves_fase2) / sizeof(posicoes_chaves_fase2[0]);

typedef struct {
    int x9, y9;
    int botaoIDfase2;
} BotaoFase2;

BotaoFase2 botaofase2[] = {
    {5, 5, 1},  
};

int numBotaofase2 = sizeof(botaofase2) / sizeof(botaofase2[0]);

typedef struct {
    int x10, y10;
} Monstro_nivel3;

Monstro_nivel3 monstro3;

typedef struct {
    int x11, y11; 
    int x12, y12;
} Teleportefase3;

Teleportefase3 teletransportesfase3[] = {
    {1, 37, 1, 1},  
};

int numTeleportesfase3 = sizeof(teletransportesfase3) / sizeof(teletransportesfase3[0]);

typedef struct {
    int x13, y13;
    int portaIDfase3;
    int estaTrancada;
} PortaFase3;

PortaFase3 portasfase3[] = {
    {59, 58, 1, 1},  
};

int numPortasfase3 = sizeof(portasfase3) / sizeof(portasfase3[0]);

typedef struct {
    int x14, y14;
    int chaveIDfase3;
} PosicaoChaveFase3;

PosicaoChaveFase3 posicoes_chaves_fase3[] = {
    {1, 58, 1},  
};

int numChavesfase3 = sizeof(posicoes_chaves_fase3) / sizeof(posicoes_chaves_fase3[0]);

typedef struct {
    int x15, y15;
    int botaoIDfase3;
} BotaoFase3;

BotaoFase3 botaofase3[] = {
    {5, 5, 1},  
};

int numBotaofase3 = sizeof(botaofase3) / sizeof(botaofase3[0]);

void movimento_cima_fase1() {
    int i;
    if (jogador_y > 0 && mapa_fase1[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortasfase1; i++) {
            if (next_x == portasfase1[i].x1 && next_y == portasfase1[i].y1 && portasfase1[i].estaTrancadafase1) {
                return; 
            }
        }
        jogador_y--;
    }
}

void movimento_esquerda_fase1() {
    int i;
    if (jogador_x > 0 && mapa_fase1[jogador_y][jogador_x - 1] != '*') {
        int next_x = jogador_x - 1;
        int next_y = jogador_y;

        for (i = 0; i < numPortasfase1; i++) {
            if (next_x == portasfase1[i].x1 && next_y == portasfase1[i].y1 && portasfase1[i].estaTrancadafase1) {
                return; 
            }
        }
        jogador_x--;
    }
}

void movimento_baixo_fase1() {
    if (jogador_y < LARGURA_TELA_FASE1 - 1 && mapa_fase1[jogador_y + 1][jogador_x] != '*') {
        jogador_y++;
    }
}

void movimento_direita_fase1() {
    if (jogador_x < LARGURA_TELA_FASE1 - 1 && mapa_fase1[jogador_y][jogador_x + 1] != '*') {
        jogador_x++;
    }
}

void movimento_cima_fase2() {
    int i;
    if (jogador_y > 0 && mapa_fase2[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortasfase2; i++) {
            if (next_x == portasfase2[i].x7 && next_y == portasfase2[i].y7 && portasfase2[i].estaTrancada) {
                return; 
            }
        }

        jogador_y--;
    }
}

void movimento_esquerda_fase2() {
    int i;
    if (jogador_x > 0 && mapa_fase2[jogador_y][jogador_x - 1] != '*') {
        int next_x = jogador_x - 1;
        int next_y = jogador_y;
        jogador_x--;
    }
}

void movimento_baixo_fase2() {
    if (jogador_y < LARGURA_TELA_FASE2 - 1 && mapa_fase2[jogador_y + 1][jogador_x] != '*') {
        jogador_y++;
    }
}

void movimento_direita_fase2() {
    if (jogador_x < LARGURA_TELA_FASE2 - 1 && mapa_fase2[jogador_y][jogador_x + 1] != '*') {
        jogador_x++;
    }
}

void movimento_cima_fase3() {
    int i;
    if (jogador_y > 0 && mapa_fase3[jogador_y - 1][jogador_x] != '*') {
        int next_x = jogador_x;
        int next_y = jogador_y - 1;

        for (i = 0; i < numPortasfase3; i++) {
            if (next_x == portasfase3[i].x13 && next_y == portasfase3[i].y13 && portasfase3[i].estaTrancada) {
                return; 
            }
        }

        jogador_y--;
    }
}

void movimento_esquerda_fase3() {
    int i;
    if (jogador_x > 0 && mapa_fase3[jogador_y][jogador_x - 1] != '*') {
        int next_x = jogador_x - 1;
        int next_y = jogador_y;
        jogador_x--;
    }
}

void movimento_baixo_fase3() {
    if (jogador_y < LARGURA_TELA_FASE3 - 1 && mapa_fase3[jogador_y + 1][jogador_x] != '*') {
        jogador_y++;
    }
}

void movimento_direita_fase3() {
    if (jogador_x < LARGURA_TELA_FASE3 - 1 && mapa_fase3[jogador_y][jogador_x + 1] != '*') {
        jogador_x++;
    }
}

void definir_posicao_inicial_monstro() {
    do {
        monstro.x3 = rand() % LARGURA_TELA_FASE1;
        monstro.y3 = rand() % ALTURA_TELA_FASE1;
    } while (mapa_fase1[monstro.y3][monstro.x3] == '*');
}

void movimento_monstro_nivel1() {
    int direcao = rand() % 4;

    switch (direcao) {
        case 0:
            if (mapa_fase1[monstro.y3 - 1][monstro.x3] != '*' && monstro.y3 > 0 && mapa_fase1[monstro.y3 - 1][monstro.x3] != '#' && monstro.y3 > 0) {
                monstro.y3--;
            }
            break;
        case 1:
            if (mapa_fase1[monstro.y3 + 1][monstro.x3] != '*' && monstro.y3 < ALTURA_TELA_FASE1 - 1 && mapa_fase1[monstro.y3 + 1][monstro.x3] != '#' && monstro.y3 < ALTURA_TELA_FASE1 - 1) {
                monstro.y3++;
            }
            break;
        case 2:
            if (mapa_fase1[monstro.y3][monstro.x3 - 1] != '*' && monstro.x3 > 0 && mapa_fase1[monstro.y3][monstro.x3 - 1] != '#' && monstro.x3 > 0 ) {
                monstro.x3--;
            }
            break;
        case 3:
            if (mapa_fase1[monstro.y3][monstro.x3 + 1] != '*' && monstro.x3 < LARGURA_TELA_FASE1 - 1 && mapa_fase1[monstro.y3][monstro.x3 + 1] != '#' && monstro.x3 < LARGURA_TELA_FASE1 - 1) {
                monstro.x3++;
            }
            break;
        default:
            break;
    }
}

void definir_posicao_inicial_monstro2() {
    do {
        monstro2.x4 = rand() % LARGURA_TELA_FASE2;
        monstro2.y4 = rand() % ALTURA_TELA_FASE2;
    } while (mapa_fase2[monstro2.y4][monstro2.x4] == '*' || 
             (monstro2.x4 == jogador_x && monstro2.y4 == jogador_y) ||
             (monstro2.x4 == monstro.x3 && monstro2.y4 == monstro.y3) ||
             (monstro2.x4 == jogador_x && monstro2.y4 == jogador_y) ||
             (monstro2.x4 == monstro.x3 && monstro2.y4 == monstro.y3) ||
             (monstro2.x4 < 0 || monstro2.x4 >= LARGURA_TELA_FASE2 || monstro2.y4 < 0 || monstro2.y4 >= ALTURA_TELA_FASE2));
}

void movimento_monstro_nivel2() {
    int dx = jogador_x - monstro2.x4;
    int dy = jogador_y - monstro2.y4;

    if (abs(dx) <= 1 && abs(dy) <= 1) {
        if (dx > 0 && mapa_fase2[monstro2.y4][monstro2.x4 + 1] != '*' && dx > 0 && mapa_fase2[monstro2.y4][monstro2.x4 + 1] != '#') {
            monstro2.x4++;
        } else if (dx < 0 && mapa_fase2[monstro2.y4][monstro2.x4 - 1] != '*' && dx < 0 && mapa_fase2[monstro2.y4][monstro2.x4 - 1] != '#') {
            monstro2.x4--;
        } else if (dy > 0 && mapa_fase2[monstro2.y4 + 1][monstro2.x4] != '*' && dy > 0 && mapa_fase2[monstro2.y4 + 1][monstro2.x4] != '#') {
            monstro2.y4++;
        } else if (dy < 0 && mapa_fase2[monstro2.y4 - 1][monstro2.x4] != '*' && dy < 0 && mapa_fase2[monstro2.y4 - 1][monstro2.x4] != '#') {
            monstro2.y4--;
        }
    } else {
        int random_move = rand() % 4;
            switch (random_move) {
            case 0:
                if (mapa_fase2[monstro2.y4 - 1][monstro2.x4] != '*' && mapa_fase2[monstro2.y4 - 1][monstro2.x4] != '#') {
                    monstro2.y4--;
                }
                break;
            case 1:
                if (mapa_fase2[monstro2.y4 + 1][monstro2.x4] != '*' && mapa_fase2[monstro2.y4 + 1][monstro2.x4] != '#') {
                    monstro2.y4++;
                }
                break;
            case 2:
                if (mapa_fase2[monstro2.y4][monstro2.x4 - 1] != '*' && mapa_fase2[monstro2.y4][monstro2.x4 - 1] != '#') {
                    monstro2.x4--;
                }
            break;
            case 3:
                if (mapa_fase2[monstro2.y4][monstro2.x4 + 1] != '*' && mapa_fase2[monstro2.y4][monstro2.x4 + 1] != '#') {
                    monstro2.x4++;
                }
            break;
        }
    }
}

void removePorta(int portaID) {
    int i, j;
    for (i = 0; i < numPortasfase1; i++) {
        if (portasfase1[i].portaIDfase1 == portaID) {
            for (j = i; j < numPortasfase1 - 1; j++) {
                portasfase1[j] = portasfase1[j + 1];
            }
            numPortasfase1--;
            break;
        }
    }
}

void removePortafase2(int portaIDfase2) {
    int i, j;
    for (i = 0; i < numPortasfase2; i++) {
        if (portasfase2[i].portaIDfase2 == portaIDfase2) {
            for (j = i; j < numPortasfase2 - 1; j++) {
                portasfase2[j] = portasfase2[j + 1];
            }
            numPortasfase2--;
            break;
        }
    }
}

void removePortafase3(int portaIDfase3) {
    int i, j;
    for (i = 0; i < numPortasfase3; i++) {
        if (portasfase3[i].portaIDfase3 == portaIDfase3) {
            for (j = i; j < numPortasfase3 - 1; j++) {
                portasfase3[j] = portasfase3[j + 1];
            }
            numPortasfase3--;
            break;
        }
    }
}

void interacao_fase1() {
    int i;

    for (i = 0; i < numChavesfase1; i++) {
        if (jogador_x == posicoes_chaves_fase1[i].x2 && jogador_y == posicoes_chaves_fase1[i].y2) {
            printf("Você pegou a chave %d!\n", posicoes_chaves_fase1[i].chaveIDfase1);
            Sleep(1000);

            int j;
            for (j = i; j < numChavesfase1 - 1; j++) {
                posicoes_chaves_fase1[j] = posicoes_chaves_fase1[j + 1];
            }
            numChavesfase1--;

            int k;
            for (k = 0; k < numPortasfase1; k++) {
                if (posicoes_chaves_fase1[i].chaveIDfase1 == portasfase1[k].portaIDfase1) {
                    portasfase1[k].estaTrancadafase1 = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase1[i].chaveIDfase1);
                    Sleep(1000);

                    mapa_fase1[portasfase1[k].y1][portasfase1[k].x1] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void interacao_fase2() {
    int i;

    for (i = 0; i < numChavesfase2; i++) {
        if (jogador_x == posicoes_chaves_fase2[i].x8 && jogador_y == posicoes_chaves_fase2[i].y8) {
            printf("Você pegou a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
            Sleep(1000);

            int j;
            for (j = i; j < numChavesfase2 - 1; j++) {
                posicoes_chaves_fase2[j] = posicoes_chaves_fase2[j + 1];
            }
            numChavesfase2--;

            int k;
            for (k = 0; k < numPortasfase2; k++) {
                if (posicoes_chaves_fase2[i].chaveIDfase2 == portasfase2[k].portaIDfase2) {
                    portasfase2[k].estaTrancada = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase2[i].chaveIDfase2);
                    Sleep(1000);

                    mapa_fase2[portasfase2[k].y7][portasfase2[k].x7] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void interacao_fase3() {
    int i;

    for (i = 0; i < numChavesfase3; i++) {
        if (jogador_x == posicoes_chaves_fase3[i].x14 && jogador_y == posicoes_chaves_fase3[i].y14) {
            printf("Você pegou a chave %d!\n", posicoes_chaves_fase3[i].chaveIDfase3);
            Sleep(1000);

            int j;
            for (j = i; j < numChavesfase3 - 1; j++) {
                posicoes_chaves_fase3[j] = posicoes_chaves_fase3[j + 1];
            }
            numChavesfase3--;

            int k;
            for (k = 0; k < numPortasfase3; k++) {
                if (posicoes_chaves_fase3[i].chaveIDfase3 == portasfase3[k].portaIDfase3) {
                    portasfase3[k].estaTrancada = 0; 
                    printf("Você destrancou a porta com a chave %d!\n", posicoes_chaves_fase3[i].chaveIDfase3);
                    Sleep(1000);

                    mapa_fase3[portasfase3[k].y13][portasfase3[k].x13] = '=';
                    return;
                }
            }
            return;
        }
    }
}

void resetar_mapa_fase1(char mapa_fase1[ALTURA_TELA_FASE1][LARGURA_TELA_FASE1]) {
    jogador_x = LARGURA_TELA_FASE1 / 2;
    jogador_y = ALTURA_TELA_FASE1 / 2;
    jogador_vida = 3;
}

void resetar_mapa_fase2(char mapa_fase1[ALTURA_TELA_FASE2][LARGURA_TELA_FASE2]) {
    jogador_x = LARGURA_TELA_FASE2 / 2;
    jogador_y = ALTURA_TELA_FASE2 / 2;
    jogador_vida = 3;
}

void resetar_mapa_fase3(char mapa_fase1[ALTURA_TELA_FASE3][LARGURA_TELA_FASE3]) {
    jogador_x = LARGURA_TELA_FASE3 / 2;
    jogador_y = ALTURA_TELA_FASE3 / 2;
    jogador_vida = 3;
}

void checa_dano_espinho() {
    if (mapa_fase1[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Você foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase1(mapa_fase1);
            }
        }
    }
}

void checa_dano_espinho_fase2() {
    if (mapa_fase2[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Você foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa 1|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase2(mapa_fase2);
            }
        }
    }
}

void checa_dano_espinho_fase3() {
    if (mapa_fase3[jogador_y][jogador_x] == '#') {
        jogador_vida--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase3(mapa_fase3);
            }
        }
    }
}

void resetar_jogo() {
    if (contador_reiniciar_jogo >= 3) {
        contador_reiniciar_jogo = 0;
        jogo_em_execucao = 0; 
    }
}


void checa_dano_monstro() {
    if (jogador_x == monstro.x3 && jogador_y == monstro.y3) {
        jogador_vida--;
        printf("Você foi atingido pelo monstro! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou o mapa!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase1(mapa_fase1);
            }
        }
    }
}

void checa_dano_monstro2() {
    if (jogador_x == monstro2.x4 && jogador_y == monstro2.y4) {
        jogador_vida--;
        printf("Voce foi atingido pelo monstro nível 2! Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou a fase!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase2(mapa_fase2);
            }
        }
    }
}

void checa_dano_monstro3() {
    if (jogador_x == monstro3.x10 && jogador_y == monstro3.y10) {
        jogador_vida--;
        printf("Voce foi atingido pelo monstro nível 3 Vidas restantes: %d\n", jogador_vida);
        Sleep(1000);

        if (jogador_vida <= 0) {
            printf("|          GAME OVER!        |\n");
            printf("|Você reiniciou a fase!|\n");
            Sleep(1000);
            contador_reiniciar_jogo++;
            if (contador_reiniciar_jogo >= 3) {
                jogo_em_execucao = 0;
            } else {
                resetar_mapa_fase3(mapa_fase3);
            }
        }
    }
}

void desenhar_vida() {
    printf("Vida: ");
    int i;
    for (i = 0; i < jogador_vida; i++) {
        printf("&");
    }
    printf("\n");
}

int verificar_teleportefase2() {
    int i;
    for (i = 0; i < numTeleportesfase2; i++) {
        if (jogador_x == teletransportesfase2[i].x5 && jogador_y == teletransportesfase2[i].y5) {
            jogador_x = teletransportesfase2[i].x6;
            jogador_y = teletransportesfase2[i].y6;
            return 1;
        } else if (jogador_x == teletransportesfase2[i].x6 && jogador_y == teletransportesfase2[i].y6) {
            jogador_x = teletransportesfase2[i].x5;
            jogador_y = teletransportesfase2[i].y5;
            return 1; 
        }
    }
    return 0; 
}

int verificar_teleportefase3() {
    int i;
    for (i = 0; i < numTeleportesfase3; i++) {
        if (jogador_x == teletransportesfase3[i].x11 && jogador_y == teletransportesfase3[i].y11) {
            jogador_x = teletransportesfase3[i].x12;
            jogador_y = teletransportesfase3[i].y12;
            return 1;
        } else if (jogador_x == teletransportesfase3[i].x12 && jogador_y == teletransportesfase3[i].y12) {
            jogador_x = teletransportesfase3[i].x11;
            jogador_y = teletransportesfase3[i].y11;
            return 1; 
        }
    }
    return 0; 
}

void interagir_com_botaofase2() {
    int acao = rand() % 2;  

    if (jogador_x == botaofase2[0].x9 && jogador_y == botaofase2[0].y9) {
        switch (acao) {
            case 0:
                printf("O botâo causou dano ao jogador!\n");
                jogador_vida--;
                    if (jogador_vida <= 0) {
                        printf("|          GAME OVER!        |\n");
                        printf("|VocÊ reiniciou a fase!|\n");
                        Sleep(1000);
                        contador_reiniciar_jogo++;
                            if (contador_reiniciar_jogo >= 3) {
                                jogo_em_execucao = 0;
                            } else {
                                resetar_mapa_fase2(mapa_fase2);
                            }
                        } 
            break;
            case 1:
                printf("O botão concedeu uma vida extra ao jogador!\n");
                jogador_vida++;  
            break;
        default:
            break;
        }
    } 
}

void interagir_com_botaofase3() {
    int acao = rand() % 2;  

    if (jogador_x == botaofase3[0].x15 && jogador_y == botaofase3[0].y15) {
        switch (acao) {
            case 0:
                printf("O botão causou dano ao jogador!\n");
                jogador_vida--;
                    if (jogador_vida <= 0) {
                        printf("|          GAME OVER!        |\n");
                        printf("|Você reiniciou a fase!|\n");
                        Sleep(1000);
                        contador_reiniciar_jogo++;
                            if (contador_reiniciar_jogo >= 3) {
                                jogo_em_execucao = 0;
                            } else {
                                resetar_mapa_fase3(mapa_fase3);
                            }
                        } 
            break;
            case 1:
                printf("O botão concedeu uma vida extra ao jogador!\n");
                jogador_vida++;  
            break;
        default:
            break;
        }
    } 
}

void definir_posicao_inicial_monstro3() {
    do {
        monstro3.x10 = rand() % LARGURA_TELA_FASE2;
        monstro3.y10 = rand() % ALTURA_TELA_FASE2;
    } while (mapa_fase2[monstro3.y10][monstro3.x10] == '*' || 
             (monstro3.x10 == jogador_x && monstro3.y10 == jogador_y) ||
             (monstro3.x10 == monstro2.x4 && monstro3.y10 == monstro2.y4) ||
             (monstro3.x10 == jogador_x && monstro3.y10 == jogador_y) ||
             (monstro3.x10 == monstro2.x4 && monstro3.y10 == monstro2.y4) ||
             (monstro3.x10 < 0 || monstro3.x10 >= LARGURA_TELA_FASE2 || monstro3.y10 < 0 || monstro3.y10 >= ALTURA_TELA_FASE2));
}

void movimento_monstro_nivel3() {
    int dx = jogador_x - monstro3.x10;
    int dy = jogador_y - monstro3.y10;
    int i;
    if (abs(dx) <= 1 && abs(dy) <= 1) {
        if (dx > 0 && mapa_fase3[monstro3.y10][monstro3.x10 + 1] != '*' && dx > 0 && mapa_fase3[monstro3.y10][monstro3.x10 + 1] != '#') {
            monstro3.x10++;
        } else if (dx < 0 && mapa_fase3[monstro3.y10][monstro3.x10 - 1] != '*' && dx < 0 && mapa_fase3[monstro3.y10][monstro3.x10 - 1] != '#') {
            monstro3.x10--;
        } else if (dy > 0 && mapa_fase3[monstro3.y10 + 1][monstro3.x10] != '*' && dy > 0 && mapa_fase3[monstro3.y10 + 1][monstro3.x10] != '#') {
            monstro3.y10++;
        } else if (dy < 0 && mapa_fase3[monstro3.y10 - 1][monstro3.x10] != '*' && dy < 0 && mapa_fase3[monstro3.y10 - 1][monstro3.x10] != '#') {
            monstro3.y10--;
        }
    } else {
        int random_move = rand() % 4;
            switch (random_move) {
            case 0:
                if (mapa_fase3[monstro3.y10 - 1][monstro3.x10] != '*' && mapa_fase3[monstro3.y10 - 1][monstro3.x10] != '#') {
                    monstro3.y10--;
                }
                break;
            case 1:
                if (mapa_fase3[monstro3.y10 + 1][monstro3.x10] != '*' && mapa_fase3[monstro3.y10 + 1][monstro3.x10] != '#') {
                    monstro3.y10++;
                }
                break;
            case 2:
                if (mapa_fase3[monstro3.y10][monstro3.x10 - 1] != '*' && mapa_fase3[monstro3.y10][monstro3.x10 - 1] != '#') {
                    monstro3.x10--;
                }
            break;
            case 3:
                if (mapa_fase3[monstro3.y10][monstro3.x10 + 1] != '*' && mapa_fase3[monstro3.y10][monstro3.x10 + 1] != '#') {
                    monstro3.x10++;
                }
            break;
        }
    }

    for (i = 0; i < numTeleportesfase3; i++) {
        if (monstro3.x10 == teletransportesfase3[i].x11 && monstro3.y10 == teletransportesfase3[i].y11) {
            monstro3.x10 = teletransportesfase3[i].x12;
            monstro3.y10 = teletransportesfase3[i].y12;
            break;
        } else if (monstro3.x10 == teletransportesfase3[i].x12 && monstro3.y10 == teletransportesfase3[i].y12) {
            monstro3.x10 = teletransportesfase3[i].x11;
            monstro3.y10 = teletransportesfase3[i].y11;
        }
    }
}

void mostrar_tela_vitoria() {
    system("cls");
    printf("Parabéns! Você chegou ao final da fase3!\n");
    printf("Pressione qualquer tecla para continuar...\n");
    getch();
}

int verificar_chegada_porta_transicao() {
    if (fase_atual == 1 && jogador_x == 0 && jogador_y == 13) {
        fase_atual = 2;
        jogador_x = LARGURA_TELA_FASE2 / 2;
        jogador_y = ALTURA_TELA_FASE2 / 2;
        definir_posicao_inicial_monstro();
        definir_posicao_inicial_monstro2();
        definir_posicao_inicial_monstro3();
        verificar_teleportefase2();
        interacao_fase2();
        return 1;
    } else if (fase_atual == 2 && jogador_x == 29 && jogador_y == 27) {  
        fase_atual = 3;
        jogador_x = LARGURA_TELA_FASE3 / 2;
        jogador_y = ALTURA_TELA_FASE3 / 2;
        return 1;
    } else if (fase_atual == 3 && jogador_x == 59 && jogador_y == 58) {  
        fase_atual = 3;
        jogo_em_execucao = 0;
        mostrar_tela_vitoria();
        return 1;
    }
    return 0;
}

void setar_cor_texto(int cor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, cor);
}


void mostrar_menu() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 12);
#define INICIAR '1'
#define TUTORIAL '2'
#define SAIR '3'

    system("cls");
    printf(" \n");
    printf(" |TTTTT|  |EEEEE|  |CCCCC|  |H| |H|  |DDDD|   |U| |U|  |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|      /11111|\n");
    printf("   \\T/    |E|      |C|      |H|_|H|  |D|  D|  |U| |U|  |NN||N|  |G|      |E|     |O| |O| |NN||N| |S|         /11||11|\n");
    printf("   |T|    |EEEE|   |C|      |HHHHH|  |D|  D|  |U| |U|  |N|N|N|  |G| GG|  |EEEE|  |O| |O| |N|N|N| |SSSSS|         |11|\n");
    printf("   |T|    |E|      |C|      |H| |H|  |D|  D|  |U| |U|  |N||NN|  |G|  G|  |E|     |O| |O| |N||NN|     |S|  	 |11|\n");
    printf("   |T|    |EEEEE|  |CCCCC|  |H| |H|  |DDDD|    |UUU|   |N| |N|  |GGGGG|  |EEEEE| |OOOOO| |N| |N| |SSSSS|  	 |11|\n");
    printf("           |1| Iniciar jogo\n");
    printf("           |2| Tutorial\n");
    printf("           |3|  Sair\n");
}


void show_tutorial() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 5);
    system("cls");
    printf("           === TUTORIAL ===\n");
    printf("- Objetivo: Passar por três níveis, coletando uma chave em cada para abrir uma porta.\n");
    printf("- Comandos: W (cima), A (esquerda), S (baixo), D (direita), I (interagir).\n");
    printf(" - Símbolos:\n");
    printf(" & = Jogador.\n");
    printf(" * = Parede (não atravessável).\n");
    printf(" @ = Chave.\n");
    printf(" D = Porta fechada.\n");
    printf(" = = Porta aberta (após pegar a chave).\n");
    printf(" O = Botão (interagir ao ficar em cima).\n");
    printf(" # = Espinho (reinicia fase ao tocar).\n");
    printf(" > = Teletransporte (em pares).\n");
    printf(" X = Monstro nível 1 (movimento aleatório).\n");
    printf(" V = Monstro nível 2 (segue jogador).\n");
    printf(" Z = Monstro nível 3 (segue jogador e atravessa portais. \n");
    printf(" Pressione qualquer tecla para continuar.\n");
    getch();
}

void loop_da_fase3() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 6);
    int y, x, k;

    while (jogo_em_execucao) {
        if (fase_atual == 3) {
            for (y = 0; y < ALTURA_TELA_FASE3; y++) {
                for (x = 0; x < LARGURA_TELA_FASE3; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        setar_cor_texto(COR_JOGADOR);
                        printf("&");
                    } else if (x == monstro.x3 && y == monstro.y3) {
                        setar_cor_texto(COR_MONSTRO_NIVEL1);
                        printf("X");
                    } else if (x == monstro2.x4 && y == monstro2.y4) {
                        setar_cor_texto(COR_MONSTRO_NIVEL2);
                        printf("V");
                    } else if (x == teletransportesfase3[0].x11 && y == teletransportesfase3[0].y11) {
                        setar_cor_texto(COR_TELEPORTE);
                        printf(">");
                    } else if (x == teletransportesfase3[0].x12 && y == teletransportesfase3[0].y12) {
                        setar_cor_texto(COR_TELEPORTE);
                        printf(">");
                    } else if (x == botaofase3[0].x15 && y == botaofase3[0].y15) {
                        setar_cor_texto(COR_BOTAO);
                        printf("O");
                    } else if (x == monstro3.x10 && y == monstro3.y10) {
                        setar_cor_texto(COR_TELEPORTE);
                        printf("Z");
                    } else {
                        int containsKeyfase3 = 0;
                        for (k = 0; k < numChavesfase3; k++) {
                            if (x == posicoes_chaves_fase3[k].x14 && y == posicoes_chaves_fase3[k].y14) {
                                containsKeyfase3 = 1;
                                break;
                            } 
                        }
                        if (containsKeyfase3) {
                            setar_cor_texto(COR_CHAVE);
                            printf("@");
                        } else {
                        	setar_cor_texto(COR_PADRAO_FASE3);
                            printf("%c", mapa_fase3[y][x]);
                        }
                    }
                }
                printf("\n");
            }
        }
        movimento_monstro_nivel1();
        movimento_monstro_nivel2();
        movimento_monstro_nivel3();
        checa_dano_monstro();
        checa_dano_monstro2();
        checa_dano_monstro3();
        desenhar_vida();
        verificar_teleportefase3();
        interacao_fase3();
        interagir_com_botaofase3();
        checa_dano_espinho_fase3();
        char input = getch();
        switch (input) {
            case TECLA_CIMA:
                movimento_cima_fase3();
                break;
            case TECLA_ESQUERDA:
                movimento_esquerda_fase3();
                break;
            case TECLA_BAIXO:
                movimento_baixo_fase3();
                break;
            case TECLA_DIREITA:
                movimento_direita_fase3();
                break;
            default:
                break;
        }  
        system("cls");
        if (verificar_chegada_porta_transicao()) {
            fase_atual = 3;
            jogo_em_execucao = 0;
            mostrar_tela_vitoria();
            break;
        }
    }
    if (jogo_em_execucao = 0) {
        mostrar_menu();
    }
}

void loop_da_fase2() {
    int y, x, k;

    while (jogo_em_execucao) {
        if (fase_atual == 2) {
            for (y = 0; y < ALTURA_TELA_FASE2; y++) {
                for (x = 0; x < LARGURA_TELA_FASE2; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        setar_cor_texto(COR_JOGADOR);
                        printf("&");
                    } else if (x == monstro.x3 && y == monstro.y3) {
                        setar_cor_texto(COR_MONSTRO_NIVEL1);
                        printf("X");
                    } else if (x == monstro2.x4 && y == monstro2.y4) {
                        setar_cor_texto(COR_MONSTRO_NIVEL2);
                        printf("V");
                    } else if (x == teletransportesfase2[0].x5 && y == teletransportesfase2[0].y5) {
                        setar_cor_texto(COR_TELEPORTE);
                        printf(">");
                    } else if (x == teletransportesfase2[0].x6 && y == teletransportesfase2[0].y6) {
                        setar_cor_texto(COR_TELEPORTE);
                        printf(">");
                    } else if (x == botaofase2[0].x9 && y == botaofase2[0].y9) {
                        setar_cor_texto(COR_BOTAO);
                        printf("O");
                    } else {
                        int containsKeyfase2 = 0;
                        for (k = 0; k < numChavesfase2; k++) {
                            if (x == posicoes_chaves_fase2[k].x8 && y == posicoes_chaves_fase2[k].y8) {
                                containsKeyfase2 = 1;
                                break;
                            } 
                        }
                        if (containsKeyfase2) {
                            setar_cor_texto(COR_CHAVE);
                            printf("@");
                        } else if (mapa_fase2[y][x] == '#') {
                            setar_cor_texto(COR_ESPINHO);
                            printf("%c", mapa_fase2[y][x]);
                        } else if (mapa_fase1[y][x] == '=') {
                            setar_cor_texto(COR_PORTA);
                            printf("%c", mapa_fase2[y][x]);
                        } else {
                            setar_cor_texto(COR_PADRAO_FASE2);
                            printf("%c", mapa_fase2[y][x]);
                        }
                    }
                }
                printf("\n");
            }
        }
        movimento_monstro_nivel1();
        movimento_monstro_nivel2();
        checa_dano_monstro();
        checa_dano_monstro2();
        desenhar_vida();
        verificar_teleportefase2();
        interacao_fase2();
        interagir_com_botaofase2();
        checa_dano_espinho_fase2();
        char input = getch();
        switch (input) {
            case TECLA_CIMA:
                movimento_cima_fase2();
                break;
            case TECLA_ESQUERDA:
                movimento_esquerda_fase2();
                break;
            case TECLA_BAIXO:
                movimento_baixo_fase2();
                break;
            case TECLA_DIREITA:
                movimento_direita_fase2();
                break;
            default:
                break;
        }
        if (verificar_chegada_porta_transicao()) {
            fase_atual = 3;
            resetar_mapa_fase2(mapa_fase2);
            definir_posicao_inicial_monstro();
            break;
        }
        system("cls");
    }
    if (fase_atual == 3) {
        loop_da_fase3(); 
    }
}

void loop_da_fase1() {
    int y, x, k;

    while (jogo_em_execucao) {
        if (fase_atual == 1) {
            for (y = 0; y < ALTURA_TELA_FASE1; y++) {
                for (x = 0; x < LARGURA_TELA_FASE1; x++) {
                    if (x == jogador_x && y == jogador_y) {
                        setar_cor_texto(COR_JOGADOR);
                        printf("&");
                    } else if (x == monstro.x3 && y == monstro.y3) {
                        setar_cor_texto(COR_MONSTRO_NIVEL1);
                        printf("X");
                    } else {
                        int containsKey = 0;
                        for (k = 0; k < numChavesfase1; k++) {
                            if (x == posicoes_chaves_fase1[k].x2 && y == posicoes_chaves_fase1[k].y2) {
                                containsKey = 1;
                                break;
                            }
                        }
                        if (containsKey) {
                            setar_cor_texto(COR_CHAVE);
                            printf("@");
                        } else if (mapa_fase1[y][x] == '*') {
                            setar_cor_texto(COR_PADRAO_FASE1);
                            printf("%c", mapa_fase1[y][x]);
                        } else if (mapa_fase1[y][x] == '#') {
                            setar_cor_texto(COR_ESPINHO);
                            printf("%c", mapa_fase1[y][x]);
                        } else if (mapa_fase1[y][x] == '=') {
                            setar_cor_texto(COR_PORTA);
                            printf("%c", mapa_fase1[y][x]);
                        } else {
                            setar_cor_texto(COR_PADRAO_FASE1);
                            printf("%c", mapa_fase1[y][x]);
                        }
                    }
                }
                printf("\n");
            }
        }
        desenhar_vida();
        char input = getch();
        switch (input) {
            case TECLA_CIMA:
                movimento_cima_fase1();
                break;
            case TECLA_ESQUERDA:
                movimento_esquerda_fase1();
                break;
            case TECLA_BAIXO:
                movimento_baixo_fase1();
                break;
            case TECLA_DIREITA:
                movimento_direita_fase1();
                break;
            case CHAVE_INTERATIVA:
                interacao_fase1();
                break;
            default:
                break;
        }
        movimento_monstro_nivel1();
        checa_dano_monstro();
        checa_dano_espinho();
        system("cls");

        if (verificar_chegada_porta_transicao()) {
            fase_atual = 2;
            resetar_mapa_fase1(mapa_fase1);
            definir_posicao_inicial_monstro();
            break;
        }
    }
    if (fase_atual == 2) {
        loop_da_fase2();
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    SetConsoleTextAttribute(console, 5);
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = 0;
    SetConsoleCursorInfo(console, &cursor_info);
    system("mode con: cols=80 lines=24");
    system("cls");

    while (1) {
        mostrar_menu();
        char escolha = getch();

        switch (escolha) {
            case INICIAR:
                fase_atual = 1;
                definir_posicao_inicial_monstro();
                loop_da_fase1();
                definir_posicao_inicial_monstro2();
                break;
            case TUTORIAL:
                show_tutorial();
                break;
            case SAIR:
                return 0; 
                break;
            default:
                printf("Escolha invalida. Por favor, tente novamente.\n");
                Sleep(500);
                break;
        }
    }
    return 0;
}
