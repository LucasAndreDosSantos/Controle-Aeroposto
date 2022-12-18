#include "header.hpp"


int i,contemergencial, cont_aviaocaido, cont_aviaoaterrissou, cont_aviaodecolou;	
Fila_de_espera A1, A2, A3, A4, D1, D2, D3; 	
int Pista1, Pista2,Pista3;
float media_aterrissagem,media_decolagem;
	
int main() {
	srand(time(NULL));
	criar_filas_espera();
	FILE *arq;
	arq = fopen("aeroporto.txt","w");
	
	int avioes_decolagem,avioes_aterrissando, unidade_tempo, id_aterrissa = 0,id_decola = -1, tempo;
	float media;

	for (tempo = 0; tempo < TAM; tempo++) {
		avioes_aterrissando = rand()%4;
		
		for(i=0; i < avioes_aterrissando; i++) {
	    	unidade_tempo = (rand()%20)+1;
	    	id_aterrissa += 2 ; 
	    	coloca_aviao_aterrissagem(id_aterrissa, unidade_tempo);
    	}
		
		avioes_decolagem = rand()%4;
    	
		for (i = 0; i < avioes_decolagem; i++) {
    		id_decola += 2 ; 
			unidade_tempo = 20;
			coloca_aviao_decolagem(id_decola,unidade_tempo);
    	}
     //verifica se alguma fila de aterrissagem tem um avião 
    // em estado emergencial
	aterrissar_decolar_aviao();	
  atualizar_aterrissagem();

	media_tempo_aterrissagem (&A1,tempo);


	media_tempo_aterrissagem (&A2,tempo);
	

	media_tempo_aterrissagem (&A3,tempo);

	media_tempo_aterrissagem (&A4,tempo);

	atualizar_decolagem();
	
	media_tempo_decolagem (&D1,tempo);

	media_tempo_decolagem (&D2,tempo);
	
	media_tempo_decolagem (&D3,tempo);

	ImprimeSituacaoAeroporto(arq,tempo);
  }
	ImprimeHistoricoPousoDecolagem(arq);
  return 0;
}
