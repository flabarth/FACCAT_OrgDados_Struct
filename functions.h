#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "paciente.h"

// Escreve valor inteiro no arquivo de dados
void writei(int valor, FILE *f){
	fwrite(&valor, sizeof(valor), 1, f);
}

// Escreve string (array de char) no arquivo de dados
void writes(char *s, int sizeofstring, FILE *f){
	fwrite(s, sizeofstring, 1, f);
}

int readi(int campo, FILE *f){
	int resultado;
	fread(&resultado, sizeof(campo), 1, f);
	return resultado;
}

// Lê string (array de char) do arquivo de dados
char *reads(char *s, int sizeofstring, FILE *f){
	fread(s, sizeofstring, 1, f);
	return s;
}

// Insere novo registro (com interface)
void insertNew(paciente p){
	
	char escolha = 's';
	int id;
	char nome[45];
	int idade;
	char diagnostico[200];
	char tratamento[200];
	
	FILE *fout;
	fout = fopen("data.dat", "ab");
	fseek(fout, 0, SEEK_END);
	
	do{
		
		p.setAtivo(1);
		writei(p.ativo, fout);
		
		printf("ID > ");
		scanf("%d", &id);
		p.setId(id);
		writei(p.id, fout);
		
		getchar();
		
		printf("Nome > ");
		scanf("%s", nome);
		p.setNome(nome);
		writes(p.nome, 45, fout);
		
		printf("Idade > ");
		scanf("%d", &idade);
		p.setIdade(idade);
		writei(p.idade, fout);
		
		getchar();
		
		printf("Diagnóstico > ");
		scanf("%s", diagnostico);
		p.setDiagnostico(diagnostico);
		writes(p.diagnostico, 200, fout);
		
		printf("Tratamento > ");
		scanf("%s", tratamento);
		p.setTratamento(tratamento);
		writes(p.tratamento, 200, fout);
		
		getchar();
		
		printf("Deseja adicionar outro registro [s/n]?\n>> ");
		scanf("%c", &escolha);
		
		getchar();
		
	}while(escolha != 'n');
	
	fclose(fout);
	
}

void showAll(paciente p){
	
	int pacienteSize = p.pacienteSize;
	int fileSize;
	int numeroRegistros;
	int registrosLidosComSucesso = 0;
	
	FILE *fin;
	fin = fopen("data.dat", "rb"); // Abre arquivo de dados
	
	fseek(fin, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(fin); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // Número de registros (tamanho total / tamanho do registro)
	
	rewind(fin); // Volta ao início do arquivo
	
	if(numeroRegistros > 0){
		
		printf("----------------------------------------------------------------------\n");
		printf("|%-5s|%-13s|%-6s|%-20s|%-20s|\n", "ID", "Nome", "Idade", "Diagnóstico", "Tratamento");
		printf("----------------------------------------------------------------------\n");
		
		for(int x = 1; x <= numeroRegistros; x++){
			
			int ativo = readi(p.ativo, fin); // Captura estado do registro (ativo ou não)
			
			if(ativo == 1){ // Se for ativo, lê e mostra na tela
			
				printf("|%-5d|", readi(p.id, fin));
				printf("%-13s|", reads(p.nome, 45, fin));
				printf("%-6d|", readi(p.idade, fin));
				printf("%-20s|", reads(p.diagnostico, 200, fin));
				printf("%-20s|\n", reads(p.tratamento, 200, fin));
				
				registrosLidosComSucesso++;
				
			}else{ // Se não for ativo...
			
				// Valor que avançaremos o ponteiro. Tamanho do registo menos o tamanho de ativo (pois já foi lido)
				int valorParaAvancar = pacienteSize - sizeof(ativo);
				
				// Avança da posição atual + valor para avançar (avança um registro)
				fseek(fin, valorParaAvancar, SEEK_CUR); // Move ponteiro para depois do valor apagado
				
			}
			
		}
		
		printf("----------------------------------------------------------------------\n");
		
	}else{
		
		printf("\nNenhum registro!\n");
		
	}
	
	fclose(fin);
	
}
