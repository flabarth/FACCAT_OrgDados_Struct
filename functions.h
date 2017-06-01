#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "paciente.h"

// Escreve valor inteiro no arquivo de dados
void writei(int valor, FILE *f){
	fwrite(&valor, sizeof(valor), 1, f);
}

// Escreve string (array de char) no arquivo de dados
void writes(char *s, int sizeofstring, FILE *f){
	fwrite(s, sizeofstring, 1, f);
}

// L� int do arquivo de dados
int readi(int campo, FILE *f){
	int resultado;
	fread(&resultado, sizeof(campo), 1, f);
	return resultado;
}

// L� string (array de char) do arquivo de dados
char *reads(char *s, int sizeofstring, FILE *f){
	fread(s, sizeofstring, 1, f);
	return s;
}

// Retorna um ID randomizado que ainda n�o existe na base
int randomID(){
	int pacienteSize = sizeof(struct paciente);
	int fileSize;
	int numeroRegistros;
	bool existe = false;
	bool encontrou;
	int r;
	paciente p;
	
	FILE *fin;
	fin = fopen("data.dat", "rb"); // Abre arquivo de dados
	
	fseek(fin, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(fin); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // N�mero de registros (tamanho total / tamanho do registro)
	
	rewind(fin); // Volta ao in�cio do arquivo
	
	if(numeroRegistros > 0){
	
		do{
			
			encontrou = false;
			r = rand() % (999 + 1 - 0) + 0;
		
			for(int x = 1; x <= numeroRegistros; x++){
			
				int ativo = readi(p.ativo, fin); // Captura APENAS estado do registro (ativo ou n�o)
		
				if(ativo == 1){ // Se for ativo...
		
					int idCons = readi(p.id, fin); // Captura ID do registro percorrid
					if(idCons == r){
						encontrou = true;
					}
					
					int valorParaAvancar = pacienteSize - (sizeof(ativo) + sizeof(idCons));
					fseek(fin, valorParaAvancar, SEEK_CUR); // Avanca para pr�ximo registro
					
				}else{ // Se n�o for ativo...
			
					fseek(fin, -sizeof(ativo), SEEK_CUR); // Volta para inicio do registro
					fseek(fin, pacienteSize, SEEK_CUR); // Avan�a um registro
					
				}
				
			}
			
			if(encontrou == true){
				existe == true;
			}else{
				existe == false;
			}
			
		}while(existe == true);
		
	}else{
		
		return rand() % (999 + 1 - 0) + 0;
		
	}
	
	fclose(fin);
	
	return r;
}

// M�dia de idade dos pacientes ativos
float mediaIdade(paciente p){
	int pacienteSize = sizeof(struct paciente);
	int fileSize;
	int numeroRegistros;
	int total = 0;
	int registrosAtivos = 0;
	FILE *fin;
	fin = fopen("data.dat", "rb"); // Abre arquivo de dados
	
	fseek(fin, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(fin); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // N�mero de registros (tamanho total / tamanho do registro)
	
	rewind(fin); // Volta ao in�cio do arquivo
	
	for(int x = 1; x <= numeroRegistros; x++){
		int ativo = readi(p.ativo, fin); // Captura APENAS estado do registro (ativo ou n�o)
		fseek(fin, -sizeof(ativo), SEEK_CUR); // Volta para inicio do registro
			
		if(ativo == 1){ // Se for ativo...
			fread(&p, sizeof(struct paciente), 1, fin); // L� registro inteiro
			
			total = total + p.idade;
			
			registrosAtivos++;
							
		}else{ // Se n�o for ativo...
				
			fseek(fin, pacienteSize, SEEK_CUR); // Avan�a um registro
				
		}
	}
	
	return (float)total / (float)registrosAtivos;
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
		
		p.setAtivo(1); // Define que � ativo (n�o exclu�do)
		
		p.setId(randomID()); // Define ID aleat�rio (sem repetir)
		
		printf("Nome > ");
		scanf("%44[^\n]", nome);
		p.setNome(nome);
		
		getchar();
		
		printf("Idade > ");
		scanf("%d", &idade);
		p.setIdade(idade);
		
		getchar();
		
		printf("Diagn�stico > ");
		scanf("%199[^\n]", diagnostico);
		p.setDiagnostico(diagnostico);
		
		getchar();
		
		printf("Tratamento > ");
		scanf("%199[^\n]", tratamento);
		p.setTratamento(tratamento);

		fwrite(&p, sizeof(struct paciente), 1, fout); // Escreve toda a estrutura no arquivo
		
		getchar();
		
		printf("Deseja adicionar outro registro [s/n]?\n>> ");
		scanf("%c", &escolha);
		
		getchar();
		
	}while(escolha != 'n');
	
	fclose(fout);
	
}

// Lista registros existentes
void showAll(paciente p){
	
	int pacienteSize = sizeof(struct paciente);
	int fileSize;
	int numeroRegistros;
	int registrosLidosComSucesso = 0;
	
	FILE *fin;
	fin = fopen("data.dat", "rb"); // Abre arquivo de dados
	
	fseek(fin, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(fin); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // N�mero de registros (tamanho total / tamanho do registro)
	
	rewind(fin); // Volta ao in�cio do arquivo
	
	if(numeroRegistros > 0){
		
		printf("----------------------------------------------------------------------------\n");
		printf("|%-5s|%-15s|%-6s|%-22s|%-22s|\n", "ID", "Nome", "Idade", "Diagn�stico", "Tratamento");
		printf("----------------------------------------------------------------------------\n");
		
		for(int x = 1; x <= numeroRegistros; x++){
			
			// Aqui controlamos quais registros podem ser lidos ou n�o.
			// Primeiro lemos apenas o estado (ativo ou n�o). Desta forma
			// carregamos apenas o campo "ativo" na mem�ria. Se for ativo,
			// lemos o registro inteiro, se n�o, apenas avan�amos.
			// Desta forma o registro n�o � carregado inteiramente na 
			// mem�ria, n�o havendo desperdicio.
			
			int ativo = readi(p.ativo, fin); // Captura APENAS estado do registro (ativo ou n�o)
			fseek(fin, -sizeof(ativo), SEEK_CUR); // Volta para inicio do registro
			
			if(ativo == 1){ // Se for ativo, l� e mostra na tela

				fread(&p, sizeof(struct paciente), 1, fin); // L� registro inteiro
				
				printf("|%-5d|", p.id);
				printf("%-15s|", p.nome);
				printf("%-6d|", p.idade);
				printf("%-22s|", p.diagnostico);
				printf("%-22s|\n", p.tratamento);
				
				registrosLidosComSucesso++;
				
			}else{ // Se n�o for ativo...
				
				fseek(fin, pacienteSize, SEEK_CUR); // Avan�a um registro
				
			}
			
		}
		
		printf("----------------------------------------------------------------------------\n");
		
	}else{
		
		printf("\nNenhum registro!\n");
		
	}
	
	fclose(fin);
	
}

// Deleta um registro baseado no ID
void deleteReg(paciente p){
	
	FILE *f;
	f = fopen("data.dat", "r+b"); // Abre arquivo de dados
	int pacienteSize = sizeof(struct paciente);
	int fileSize;
	int numeroRegistros;
	int idEx;
	
	fseek(f, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(f); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // N�mero de registros (tamanho total / tamanho do registro)
	
	rewind(f); // Volta ao in�cio do arquivo
	
	printf("Digite o ID do paciente que deseja excluir > ");
	scanf("%d", &idEx);
	getchar();
	
	for(int x = 1; x <= numeroRegistros; x++){ // Percorre todos os registros at� encontrar o desejado
		
		// Aqui lemos o campo ativo, e s� lemos o campo id tamb�m se o registro for ativo.
		// No fim, n�o lemos o registro inteiro, apenas ativo e id (se for ativo).
		
		int ativo = readi(p.ativo, f); // Captura APENAS estado do registro (ativo ou n�o)
		
		if(ativo == 1){ // Se for ativo...
		
			int idCons = readi(p.id, f); // Captura ID do registro percorrido
			
			if(idCons == idEx){ // Testa se � igual ao ID desejado
				// Se for...
				fseek(f, -(sizeof(idCons) + sizeof(ativo)), SEEK_CUR); // Volta dois campos (ID e ativo), pois teremos que alterar ativo, que fica antes de ID
				writei(0, f); // J� na posi��o do campo ativo, alteramos ele para 0
				break; // Sai do loop, pois encontramos o que quer�amos
			}
			
			int valorParaAvancar = pacienteSize - (sizeof(ativo) + sizeof(idCons));
			fseek(f, valorParaAvancar, SEEK_CUR); // Avanca para pr�ximo registro
			
		}else{ // Se n�o for ativo...
			
			fseek(f, -sizeof(ativo), SEEK_CUR); // Volta para inicio do registro
			fseek(f, pacienteSize, SEEK_CUR); // Avan�a um registro
			
		}
		
	}
	
	fclose(f); // Fecha arquivo
	
}

void getRegById(paciente p){
	
	FILE *f;
	f = fopen("data.dat", "r+b"); // Abre arquivo de dados
	int pacienteSize = sizeof(struct paciente);
	int fileSize;
	int numeroRegistros;
	int idEx;
	
	fseek(f, 0L, SEEK_END); // Vai para fim do arquivo para medir tamanho
	fileSize = ftell(f); // Tamanho total do arquivo
	numeroRegistros = fileSize / pacienteSize; // N�mero de registros (tamanho total / tamanho do registro)
	
	rewind(f); // Volta ao in�cio do arquivo
	
	printf("Digite o ID do paciente que deseja consultar > ");
	scanf("%d", &idEx);
	getchar();
	
	for(int x = 1; x <= numeroRegistros; x++){ // Percorre todos os registros at� encontrar o desejado
		
		// Aqui lemos o campo ativo, e s� lemos o campo id tamb�m se o registro for ativo.
		// No fim, n�o lemos o registro inteiro, apenas ativo e id (se for ativo).
		
		int ativo = readi(p.ativo, f); // Captura APENAS estado do registro (ativo ou n�o)
		
		if(ativo == 1){ // Se for ativo...
		
			int idCons = readi(p.id, f); // Captura ID do registro percorrido
			
			if(idCons == idEx){ // Testa se � igual ao ID desejado
				// Se for...
				
				fseek(f, -(sizeof(ativo) + sizeof(idCons)), SEEK_CUR); // Volta para in�cio do registro encontrado
				fread(&p, sizeof(struct paciente), 1, f); // L� registro inteiro
				printf("----------------------------------------------------------------------------\n");
				printf("|%-5s|%-15s|%-6s|%-22s|%-22s|\n", "ID", "Nome", "Idade", "Diagn�stico", "Tratamento");
				printf("----------------------------------------------------------------------------\n");
				printf("|%-5d|", p.id);
				printf("%-15s|", p.nome);
				printf("%-6d|", p.idade);
				printf("%-22s|", p.diagnostico);
				printf("%-22s|\n", p.tratamento);
				printf("----------------------------------------------------------------------------\n");
				
			}else{
				// Se n�o for...
				
				int valorParaAvancar = pacienteSize - (sizeof(ativo) + sizeof(idCons));
				fseek(f, valorParaAvancar, SEEK_CUR); // Avanca para pr�ximo registro	
				
			}
			
		}else{ // Se n�o for ativo...
			
			fseek(f, -sizeof(ativo), SEEK_CUR); // Volta para inicio do registro
			fseek(f, pacienteSize, SEEK_CUR); // Avan�a um registro
			
		}
		
	}
	
	fclose(f); // Fecha arquivo
	
}
