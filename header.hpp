//Cabeçalho único do trabalho até o momento
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

//Função que cria uma fila
void CriarFila (Fila_de_espera * F);
//Função que insere um avião na fila
void Inserir_Fila (Fila_de_espera * F, Detalhes_Aviao e);
//Função que imprime o conteúdo da fila
void Imprimir (Fila_de_espera * F,FILE *arq);
//Função que remove um avião da fila
void Retirar_Fila (Fila_de_espera * F);
//Função que remove um avião em estado de emergencia
void Remove_Fila(Fila_de_espera * F,Avioes * pos);
//Função que cria todas as filas de espera
void criar_filas_espera();
//Função que insere o avião na fila de aterrisagem
void coloca_aviao_aterrissagem(int id_aviao,int unidade_tempo);
//Função que insere o avião na fila de decolagem
void coloca_aviao_decolagem(int id_aviao,int unidade_tempo);
//Função que aterrisa ou decola um avião
void aterrissar_decolar_aviao();
//Função que verifica se um avião está em estado de emergência
// e o coloca nas filas de emergência para serem aterrisados
void estado_emergencia(Fila_de_espera * F );
void atualizar_avioes(Fila_de_espera * F );
void atualizar_aterrissagem();
void atualizar_decolagem ();

void media_tempo_aterrissagem (Fila_de_espera *F,int tempo);
void media_tempo_decolagem (Fila_de_espera *F,int tempo);

void ImprimeHistoricoPousoDecolagem(FILE *ARQ);
void ImprimeSituacaoAeroporto(FILE *ARQ,int tempo);

#endif
