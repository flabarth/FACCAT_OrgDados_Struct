#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "functions.h"

int main(){
	
	srand(time(NULL));
	setlocale(LC_ALL,"");
	
	char escolha;
	char database[40];

	paciente pW; // Variável de escrita
	paciente pR; // Variável de leitura
	
	printf("===== BEM-VINDO AO SISTEMA STRUCTOR =====\n");
	
	printf("Digite o nome da base de dados desejada (sem espaços e extensão).\n>> ");
	scanf("%s", database);
	getchar();
	strcat(database, ".dat");
	
	do{
		
		printf("\nVocê deseja:\n[i]ncluir\n[l]istar\n[c]onsultar\ne[x]cluir\n[m]édia de idade\n[s]air\n>> ");
		
		escolha = getchar();
		getchar(); // Char sobrando
		switch(escolha){
			case 'i': // inserir
				insertNew(pW, database);
				break;
			case 'l': // listar
				showAll(pR, database);
				break;
			case 'c': // consulta por id
				getRegById(pR, database);
				break;
			case 'x': // excluir
				deleteReg(pW, database);
				break;
			case 'm': // média
				printf("\nA média de idade de todos os pacientes é: %.2f \n", mediaIdade(pR, database));
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
