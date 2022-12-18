//Cabe�alho �nico do trabalho at� o momento
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TAM 100

struct Detalhes_Aviao {
  int id_aviao;
  int reserva_combustivel;
  int combustivel_inicial;
};

struct Avioes {
	Detalhes_Aviao dados;
	Avioes *prox,*ant;
};

struct Fila_de_espera {
	Avioes * primeiro_aviao;
	Avioes * ultimo_aviao;
	int Quantidade_aviao;
};

// Variaveis globais :
extern int i,contemergencial, cont_aviaocaido, cont_aviaoaterrissou, cont_aviaodecolou;
extern Fila_de_espera A1, A2, A3, A4, D1, D2, D3;
extern int Pista1, Pista2,Pista3;
extern float media_aterrissagem,media_decolagem;

//Fun��o que cria uma fila
void CriarFila (Fila_de_espera * F);
//Fun��o que insere um avi�o na fila
void Inserir_Fila (Fila_de_espera * F, Detalhes_Aviao e);
//Fun��o que imprime o conte�do da fila
void Imprimir (Fila_de_espera * F,FILE *arq);
//Fun��o que remove um avi�o da fila
void Retirar_Fila (Fila_de_espera * F);
//Fun��o que remove um avi�o em estado de emergencia
void Remove_Fila(Fila_de_espera * F,Avioes * pos);
//Fun��o que cria todas as filas de espera
void criar_filas_espera();
//Fun��o que insere o avi�o na fila de aterrisagem
void coloca_aviao_aterrissagem(int id_aviao,int unidade_tempo);
//Fun��o que insere o avi�o na fila de decolagem
void coloca_aviao_decolagem(int id_aviao,int unidade_tempo);
//Fun��o que aterrisa ou decola um avi�o
void aterrissar_decolar_aviao();
//Fun��o que verifica se um avi�o est� em estado de emerg�ncia
// e o coloca nas filas de emerg�ncia para serem aterrisados
void estado_emergencia(Fila_de_espera * F );
void atualizar_avioes(Fila_de_espera * F );
void atualizar_aterrissagem();
void atualizar_decolagem ();

void media_tempo_aterrissagem (Fila_de_espera *F,int tempo);
void media_tempo_decolagem (Fila_de_espera *F,int tempo);

void ImprimeHistoricoPousoDecolagem(FILE *ARQ);
void ImprimeSituacaoAeroporto(FILE *ARQ,int tempo);

#endif
