#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "functions.h"

int main(){
	
	setlocale(LC_ALL,"");
	
	char escolha;

	paciente pW; // Variável de escrita
	paciente pR; // Variável de leitura
	
	printf("===== BEM-VINDO AO SISTEMA STRUCTOR =====\n");
	
	do{
		printf("\nVocê deseja:\n[i]ncluir\n[l]istar\ne[x]cluir\n[s]air\n>> ");
		
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
			case 's': // sair
				break;
			default:
				printf("Escolha inválida! Por favor digite novamente.\n\n");
				break;
		}
	}while(escolha != 's');
			
	return 0;
}
