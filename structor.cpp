#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "functions.h"

int main(){
	
	srand(time(NULL));
	setlocale(LC_ALL,"");
	
	char escolha;

	paciente pW; // Vari�vel de escrita
	paciente pR; // Vari�vel de leitura
	
	printf("===== BEM-VINDO AO SISTEMA STRUCTOR =====\n");
	
	do{
		
		printf("\nVoc� deseja:\n[i]ncluir\n[l]istar\ne[x]cluir\n[m]�dia de idade\n[s]air\n>> ");
		
		escolha = getchar();
		getchar(); // Char sobrando
		switch(escolha){
			case 'i': // inserir
				insertNew(pW);
				break;
			case 'l': // listar
				showAll(pR);
				break;
			case 'x': // excluir
				deleteReg(pW);
				break;
			case 'm':
				printf("\nA m�dia de idade de todos os pacientes �: %.2f \n", mediaIdade(pR));
				break;
			case 's': // sair
				break;
			default:
				printf("Escolha inv�lida! Por favor digite novamente.\n\n");
				break;
		}
	}while(escolha != 's');
			
	return 0;
}
