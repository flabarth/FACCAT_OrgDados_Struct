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

	paciente pW; // Vari�vel de escrita
	paciente pR; // Vari�vel de leitura
	
	printf("===== BEM-VINDO AO SISTEMA STRUCTOR =====\n");
	
	printf("Digite o nome da base de dados desejada (sem espa�os e extens�o).\n>> ");
	scanf("%s", database);
	getchar();
	strcat(database, ".dat");
	
	do{
		
		printf("\nVoc� deseja:\n[i]ncluir\n[l]istar\n[c]onsultar\ne[x]cluir\n[m]�dia de idade\n[s]air\n>> ");
		
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
			case 'm': // m�dia
				printf("\nA m�dia de idade de todos os pacientes �: %.2f \n", mediaIdade(pR, database));
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
