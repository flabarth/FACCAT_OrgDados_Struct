#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct paciente{
	int ativo;		
	int id;
	char nome[45];
	int idade;
	char diagnostico[200];
	char tratamento[200];
		
	int pacienteSize =  + sizeof(ativo) + sizeof(id) + sizeof(nome) + sizeof(idade) + sizeof(diagnostico) + sizeof(tratamento);
	
	void setId(int idCliente){
		id = idCliente;
	}
	void setNome(char *stringNome){
		strncpy(nome, stringNome, 45);
	}
	void setIdade(int idadeCliente){
		idade = idadeCliente;
	}
	void setDiagnostico(char *stringDiag){
		strncpy(diagnostico, stringDiag, 200);
	}
	void setTratamento(char *stringTrat){
		strncpy(tratamento, stringTrat, 200);
	}
	void setAtivo(int ativoCliente){
		ativo = ativoCliente;
	}
};
