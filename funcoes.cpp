#include "header.hpp"

//FUNÇÕES BÁSICAS DE FILAS

//Função que cria uma fila
void CriarFila (Fila_de_espera * F) {
	F->primeiro_aviao = NULL; 
	F->ultimo_aviao = NULL; 
	F->Quantidade_aviao = 0; 
}

//Função que insere um avião na fila
void Inserir_Fila (Fila_de_espera * F, Detalhes_Aviao e) {
	Avioes * novo; 
	novo = (Avioes*) malloc (sizeof(Avioes));
	
	if (novo != NULL) { 
		novo->dados = e;
		novo->prox = NULL;
		novo->ant = F->ultimo_aviao;
		
		if (F->primeiro_aviao == NULL)
			F->primeiro_aviao = novo;
		else
			F->ultimo_aviao->prox = novo;

		F->ultimo_aviao = novo;
		F->Quantidade_aviao++; 
	}	 
}

//Função que imprime o conteúdo da fila
void Imprimir (Fila_de_espera * F,FILE *arq) {
	Avioes * pos;
	pos = F->primeiro_aviao;
	
	while (pos != NULL) {
		fprintf(arq,"%d ", pos->dados.id_aviao);
		fprintf (arq,"%d\n\n", pos->dados.reserva_combustivel);
		pos = pos->prox;
	}
}


//Função que remove um avião da fila
void Remove_Fila(Fila_de_espera * F, Avioes * pos) {
	Avioes * ant;
	ant= F->primeiro_aviao;
	
	if (F->primeiro_aviao == NULL) 
		return;
	
	if (F->primeiro_aviao == F->ultimo_aviao) {	
		F->primeiro_aviao = NULL; 
		F->Quantidade_aviao--; 
		return;
	}
	
	if (pos == F->primeiro_aviao) {
		ant = F->primeiro_aviao;
		F->primeiro_aviao = F -> primeiro_aviao->prox;
		F->primeiro_aviao->ant = NULL; 
		free(ant); 
	} else if(pos == F->ultimo_aviao) {
		ant = F->ultimo_aviao;
		F->ultimo_aviao = F -> ultimo_aviao->ant;
		F->ultimo_aviao->prox = NULL; 
		free(ant); 		
	} else {
		while(ant!=NULL && ant != pos)
			ant = ant->prox;
		
		if ( ant->prox != NULL ) { 
			ant->ant->prox = pos->prox;
			ant->prox->ant = pos->ant;	
			free (ant);	
		} else return;
	}

	F->Quantidade_aviao--; 
}

//--------------------------------------------------------
//ENTRADAS

//Função que cria todas as filas de espera
void criar_filas_espera() {
	CriarFila(&A1); // Inicializa a Fila 1 de aterrissagem vazia da pista 1
	CriarFila(&A2); // Inicializa a Fila 2 de aterrissagem vazia da pista 1
	CriarFila(&A3); // Inicializa a Fila 1 de aterrissagem vazia da pista 2
	CriarFila(&A4); // Inicializa a Fila 2 de aterrissagem vazia da pista 2
	CriarFila(&D1); // Inicializa a Fila 1 de decolagem vazia da pista 1
	CriarFila(&D2); // Inicializa a Fila 1 de decolagem vazia da pista 2
	CriarFila(&D3); // Inicializa a Fila 1 de decolagem vazia da pista 3
}

//Função que insere o avião na fila
void coloca_aviao_aterrissagem(int id_aviao, int unidade_tempo) {
	Detalhes_Aviao aux; 
	//Variável auxiliar recebendo os valores de unidade de tempo e id
	aux.reserva_combustivel = unidade_tempo;
	aux.combustivel_inicial = unidade_tempo;
	aux.id_aviao = id_aviao;

	if ((A1.Quantidade_aviao + A2.Quantidade_aviao) <= (A3.Quantidade_aviao + A4.Quantidade_aviao)) { //Testando qual pista tem mais elementos (pista 1 ou pista 2)
		if (A1.Quantidade_aviao <= A2.Quantidade_aviao) {
			if (A1.Quantidade_aviao <= A3.Quantidade_aviao) {
				if (A1.Quantidade_aviao <= A4.Quantidade_aviao)//Descobrindo a menor fila de aterrissagem
					Inserir_Fila (&A1, aux); //Inserindo na menor fila
        		else 
					Inserir_Fila (&A4, aux);//Inserindo na menor fila
     		} else {//Descobrindo a menor fila
				if (A3.Quantidade_aviao <= A4.Quantidade_aviao)
					Inserir_Fila (&A3, aux);//Inserindo na menor fila
				else
					Inserir_Fila (&A4, aux);	//Inserindo na menor fila
    		}
    	} else {//Descobrindo a menor fila
			if (A2.Quantidade_aviao <= A4.Quantidade_aviao)
				Inserir_Fila (&A2, aux);//Inserindo na menor fila
			else 
				Inserir_Fila(&A4, aux);		//Inserindo na menor fila
    	}
  	} else {//Descobrindo a menor fila
		if (A4.Quantidade_aviao <= A3.Quantidade_aviao) {
			if (A4.Quantidade_aviao <= A2.Quantidade_aviao) {
				if (A4.Quantidade_aviao <= A1.Quantidade_aviao)
					Inserir_Fila(&A4, aux);//Inserindo na menor fila
				else 
					Inserir_Fila(&A1, aux);//Inserindo na menor fila
      		} else {//Descobrindo a menor fila
				if (A2.Quantidade_aviao <= A1.Quantidade_aviao)
					Inserir_Fila(&A2, aux);//Inserindo na menor fila
				else 
					Inserir_Fila(&A1, aux);//Inserindo na menor fila
    		}
  		} else {//Descobrindo a menor fila 
			if (A3.Quantidade_aviao <= A1.Quantidade_aviao)
				Inserir_Fila(&A3, aux);//Inserindo na menor fila
			else 
				Inserir_Fila(&A1, aux);//Inserindo na menor fila
    	}
  	}		
}

void coloca_aviao_decolagem(int id_aviao,int unidade_tempo){
	Detalhes_Aviao aux;
	aux.id_aviao = id_aviao;
	aux.reserva_combustivel = unidade_tempo;
	aux.combustivel_inicial = unidade_tempo;
	//Variável auxiliar recebendo os valor do id
	
	if (D3.Quantidade_aviao <= D2.Quantidade_aviao)//Descobrindo a menor fila de decolagem
		if (D3.Quantidade_aviao <= D1.Quantidade_aviao)
			Inserir_Fila (&D3, aux);//Inserindo na menor fila
		else
			Inserir_Fila (&D1, aux);//Inserindo na menor fila
	else //Descobrindo a menor fila de decolagem
		if(D2.Quantidade_aviao <= D1.Quantidade_aviao)
			Inserir_Fila (&D2, aux);//Inserindo na menor fila
		else
			Inserir_Fila (&D1, aux);//Inserindo na menor fila
}


//--------------------------------------------------------
//DESENVOLVIMENTO

void aterrissar_decolar_aviao () {
  estado_emergencia(&A1);
  estado_emergencia(&A2);
  estado_emergencia(&A3);
  estado_emergencia(&A4);

  if (Pista1 == 0) {
		if (A1.primeiro_aviao == NULL && A2.primeiro_aviao == NULL && (D1.primeiro_aviao == NULL || (D1.Quantidade_aviao < A1.Quantidade_aviao || 		D1.Quantidade_aviao < A2.Quantidade_aviao))) {
			return;
		}
    
	//testes com filas de mesmo tamanho
    if (A1.Quantidade_aviao == A2.Quantidade_aviao) {
		if (A1.Quantidade_aviao < D1.Quantidade_aviao) {
			cont_aviaodecolou++;
    		Remove_Fila(&D1, D1.primeiro_aviao);
			Pista1 = 1;
      	} else {
        	if (A1.primeiro_aviao->dados.reserva_combustivel <=  A2.primeiro_aviao->dados.reserva_combustivel){
        		cont_aviaoaterrissou++;
        		Remove_Fila(&A1, A1.primeiro_aviao);
    			Pista1 = 1;
        	} else {
        		cont_aviaoaterrissou++;
        		Remove_Fila(&A2, A2.primeiro_aviao);
        		Pista1 = 1;
    		}
    	}
    } else if (A1.Quantidade_aviao == D1.Quantidade_aviao) {
		if(A1.Quantidade_aviao < A2.Quantidade_aviao) {
			cont_aviaoaterrissou++;
        	Remove_Fila(&A2, A2.primeiro_aviao);
				Pista1 = 1;
    	} else {
    		cont_aviaoaterrissou++;
        	Remove_Fila(&A1, A1.primeiro_aviao);
        	Pista1 = 1;
    	}
    } else if(D1.Quantidade_aviao == A2.Quantidade_aviao) {
    	if(D1.Quantidade_aviao < A1.Quantidade_aviao) {
    		cont_aviaoaterrissou++;
        	Remove_Fila(&A1, A1.primeiro_aviao);
    		Pista1 = 1;
    	} else {
    		cont_aviaoaterrissou++;
    		Remove_Fila(&A2, A2.primeiro_aviao);
    		Pista1 = 1;
    	}	
    } else //testes com filas de tamanhos diferentes
    if (A1.Quantidade_aviao < A2.Quantidade_aviao) {
    	if (A2.Quantidade_aviao < D1.Quantidade_aviao) {
    		cont_aviaodecolou++;
    		Remove_Fila(&D1, D1.primeiro_aviao);
        	Pista1 = 1;
		} else {
			cont_aviaoaterrissou++;
    		Remove_Fila(&A2, A2.primeiro_aviao);
       		Pista1 = 1;
    	}
    } else if (A1.Quantidade_aviao < D1.Quantidade_aviao) {
    	cont_aviaodecolou++;
      Remove_Fila(&D1, D1.primeiro_aviao);
      Pista1 = 1;
    	} else {
    		cont_aviaoaterrissou++;
    		Remove_Fila(&A1, A1.primeiro_aviao);
        	Pista1 = 1;
    }
    //contemergencial++;
	}
  if(Pista2 == 0){
    if(A3.primeiro_aviao == NULL && A4.primeiro_aviao == NULL && (D2.primeiro_aviao == NULL || (D2.Quantidade_aviao < A3.Quantidade_aviao || D2.Quantidade_aviao < A4.Quantidade_aviao))){
				return;
		}
    //testes com filas de mesmo tamanho
    if(A3.Quantidade_aviao == A4.Quantidade_aviao){
      if(A3.Quantidade_aviao < D2.Quantidade_aviao){
      	cont_aviaodecolou++;
        Remove_Fila(&D2, D2.primeiro_aviao);
        Pista2 = 1;
      }else{
        if(A3.primeiro_aviao->dados.reserva_combustivel <=  A4.primeiro_aviao->dados.reserva_combustivel){
        	cont_aviaoaterrissou++;
          Remove_Fila(&A3, A3.primeiro_aviao);
          Pista2 = 1;
        }else{
        	cont_aviaoaterrissou++;
          Remove_Fila(&A4, A4.primeiro_aviao);
          Pista2 = 1;
        }
      }
    }else if(A3.Quantidade_aviao == D2.Quantidade_aviao){
      if(A3.Quantidade_aviao < A4.Quantidade_aviao){
      	cont_aviaoaterrissou++;
        Remove_Fila(&A4, A4.primeiro_aviao);
        Pista2 = 1;
      }else{
      	cont_aviaoaterrissou++;
        Remove_Fila(&A3, A3.primeiro_aviao);
        Pista2 = 1;
      }
    }else if(D2.Quantidade_aviao == A4.Quantidade_aviao){
      if(D2.Quantidade_aviao < A3.Quantidade_aviao){
      	cont_aviaoaterrissou++;
        Remove_Fila(&A3, A3.primeiro_aviao);
        Pista2 = 1;
      }else{
      	cont_aviaoaterrissou++;
        Remove_Fila(&A4, A4.primeiro_aviao);
        Pista2 = 1;
      }
    }else //testes com filas de tamanhos diferentes
    if(A3.Quantidade_aviao < A4.Quantidade_aviao){
      if(A4.Quantidade_aviao < D2.Quantidade_aviao){
      	cont_aviaodecolou++;
        Remove_Fila(&D2, D2.primeiro_aviao);
        Pista2 = 1;
      }else{
      	cont_aviaoaterrissou++;
        Remove_Fila(&A4, A4.primeiro_aviao);
        Pista2 = 1;
      }
    }else if(A3.Quantidade_aviao < D2.Quantidade_aviao){
    	cont_aviaodecolou++;
      Remove_Fila(&D2, D2.primeiro_aviao);
      Pista2 = 1;
      }else{
      	cont_aviaoaterrissou++;
        Remove_Fila(&A3, A3.primeiro_aviao);
        Pista2 = 1;
    }
    //contemergencial++;
	}
  if(Pista3 == 0){
		if(D3.primeiro_aviao == NULL){
  		return;
	  }
  	cont_aviaodecolou++;
    Remove_Fila(&D3, D3.primeiro_aviao);
    Pista3 = 1;
    //contemergencial++;
	}

  return;
}

void estado_emergencia(Fila_de_espera * F){
  //Verifica se a lista está vazia
	if(F->primeiro_aviao == NULL)
		  return;
  Avioes * pos;
  
  for(pos = F->primeiro_aviao;pos != NULL;pos = pos->prox){
    //verifica se o avião está em estado de emergência
    if(pos->dados.reserva_combustivel == 0){
    	if(Pista1 == 0){//verifica se a pista 1 pode ser utilizada para a emergência
    		Remove_Fila(F, pos);
    		Pista1 = 1;
    		cont_aviaoaterrissou++;
    		contemergencial++;
			}
      else if(Pista2 == 0){//verifica se a pista 2 pode ser utilizada para a emergência
        Remove_Fila(F, pos);
        Pista2 = 1;
        cont_aviaoaterrissou++;
        contemergencial++;
      }
      else if(Pista3 == 0){//verifica se a pista 3 pode ser utilizada para a emergência
        Remove_Fila(F, pos);
        Pista3 = 1;
        cont_aviaoaterrissou++;
        contemergencial++;
      }	
		}else if(pos->dados.reserva_combustivel < 0){//verifica se algum avião caiu
		  Remove_Fila(F, pos);
		  cont_aviaocaido++;//contador de aviões que cairam 
		}
	}
}
//Função que decrementa o combustível dos aviões 
void atualizar_avioes(Fila_de_espera * F) {
  	Avioes * pos;
  	pos = F->primeiro_aviao;
    while(pos != NULL) {
    	pos->dados.reserva_combustivel -= 1;
    	pos = pos->prox;
	}
}
void atualizar_aterrissagem() {
		atualizar_avioes(&A1);
		atualizar_avioes(&A2);
		atualizar_avioes(&A3);
		atualizar_avioes(&A4);
		Pista1 = 0;
		Pista2 = 0;
		Pista3 = 0;
		contemergencial = 0;
}		

void atualizar_decolagem () {
		atualizar_avioes(&D1);
		atualizar_avioes(&D2);
		atualizar_avioes(&D3);
		Pista1 = 0;
		Pista2 = 0;
		Pista3 = 0;
		contemergencial = 0;
}



//----------------------------------------------------------
//SAIDA



void media_tempo_aterrissagem (Fila_de_espera *F,int tempo) {
	Avioes *pos;
	int soma = 0, tempo_espera;
	
	pos = F->primeiro_aviao;
	if (pos != NULL) {
		//printf ("\n\ncombustivel inicial %d", pos->dados.combustivel_inicial);
		//printf("\nreserva: %d\n", pos->dados.reserva_combustivel);
		tempo_espera = tempo_espera + pos->dados.combustivel_inicial - pos->dados.reserva_combustivel;
		//printf ("tempo espera %d\n", tempo_espera); 
		media_aterrissagem = (float)tempo_espera/tempo;
	
	}
}
void media_tempo_decolagem (Fila_de_espera *F,int tempo) {
	Avioes *pos;
	int soma = 0, tempo_espera;
	
	pos = F->primeiro_aviao;
	if (pos != NULL) {
		//printf ("\n\ncombustivel inicial %d", pos->dados.combustivel_inicial);
		//printf("\nreserva: %d\n", pos->dados.reserva_combustivel);
		tempo_espera = tempo_espera + pos->dados.combustivel_inicial - pos->dados.reserva_combustivel;
		//printf ("tempo espera %d\n", tempo_espera); 
		media_decolagem = (float)tempo_espera/tempo;
	
	}
}

void ImprimeHistoricoPousoDecolagem(FILE *ARQ)
{


   fprintf(ARQ,"\n");
   fprintf(ARQ,"\n***********************************************************");
   fprintf(ARQ,"\n***   HISTORICO DE AVIOES QUE DECOLARAM E ATERRISARAM   ***");
   fprintf(ARQ,"\n***********************************************************");
   fprintf(ARQ,"\n");
   fprintf(ARQ,"\n-------------Numero de aviões que Aterrissaram--------------\n\n%d",cont_aviaoaterrissou);
   fprintf(ARQ,"\n");
   fprintf(ARQ,"\n-------------Numero de avioes que decolaram----------------\n\n%d",cont_aviaodecolou);
   fprintf(ARQ,"\n");
   fprintf(ARQ,"\n-------------Numero de avioes que cairam----------------\n\n%d",cont_aviaocaido);	 	
   fprintf(ARQ,"\n");
}

void ImprimeSituacaoAeroporto(FILE *ARQ,int tempo)
{	
	fprintf(ARQ,"\n");
    fprintf(ARQ,"\n******* Situacao nas filas na Unidade de Tempo: %d*****",tempo);
    fprintf(ARQ,"\n");
	fprintf(ARQ,"\n------- Conteúdo das filas de aterrisagem------ :");
	fprintf(ARQ,"\n--------     	Fila de Aterrisagem 1      --------\n\n");
	Imprimir(&A1,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Aterrisagem 2      --------\n\n");
	Imprimir(&A2,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Aterrisagem 3      --------\n\n");
	Imprimir(&A3,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Aterrisagem 4      --------\n\n");
	Imprimir(&A4,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Decolagem 1        --------\n\n");
	Imprimir(&D1,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Decolagem 2        --------\n\n");
	Imprimir(&D2,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");
	fprintf(ARQ,"\n--------     	Fila de Decolagem 3        --------\n\n");
	Imprimir(&D3,ARQ);
	fprintf(ARQ,"\n ------------------------------------------------");

	fprintf(ARQ,"\n Tempo médio de espera para decolagem: %f", media_decolagem);
	fprintf(ARQ,"\n Tempo médio de espera para aterrisagem: %f",media_aterrissagem);
	fprintf(ARQ,"\n Número de avióes que aterrisaram sem reserva de combustível: %d",contemergencial);
}
