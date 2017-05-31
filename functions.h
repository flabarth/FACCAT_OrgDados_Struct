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
	
	FILE *fin;
	fin = fopen("data.dat", "rb");
	
	fseek(fin, 0L, SEEK_END);
	fileSize = ftell(fin);
	numeroRegistros = fileSize / pacienteSize;
	
	rewind(fin);

	printf("-------------------------------------------------------------------------\n");
	printf("|%-2s|%-5s|%-13s|%-6s|%-20s|%-20s|\n", "E", "ID", "Nome", "Idade", "Diagnóstico", "Tratamento");
	printf("-------------------------------------------------------------------------\n");
	for(int x = 0; x < numeroRegistros; x++){
		int ativo = readi(p.ativo, fin);
		if(ativo == 1){	
			printf("|%-2d|", ativo);
			printf("%-5d|", readi(p.id, fin));
			printf("%-13s|", reads(p.nome, 45, fin));
			printf("%-6d|", readi(p.idade, fin));
			printf("%-20s|", reads(p.diagnostico, 200, fin));
			printf("%-20s|\n", reads(p.tratamento, 200, fin));
		}
	}
	printf("-------------------------------------------------------------------------\n");
	
	fclose(fin);
	
}
