#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct no{
	char time[20];
	int pontos;
	int vitorias;
	int derrotas;
	int saldo_gols;
	struct no *prox;
};
typedef struct no no;

no *cria();
void carrega(no *lista);
void insere_ordenado(no *novo,no *lista);
int compara(no *novo, no *auxiliar);
void salva(no *lista);
void printa();

int main(){
	no *lista;
	lista=cria();
	carrega(lista);
	salva(lista);
	
	return 0;
	
	}
no *cria(){
	no *head=malloc(sizeof(no));
	if(head==NULL){
		printf("Erro de alocacao");
		exit(1);
		}
	
	head->prox=NULL;
	return head;
	
	}
	
	void carrega(no *lista){
		FILE *arq;
		arq=fopen("tabela.txt","r");
		
		if(arq==NULL){
			printf("erro ao abrir o arquivo\n");
			return;
			}

		char linha[100];
		char *token;
		
		while(fgets(linha,sizeof(linha),arq) !=NULL){
			
			no *novo=malloc(sizeof(no));
			novo->prox=NULL;
			linha[strcspn(linha,"\n")] = '\0';
		
			token=strtok(linha,"|");
			strcpy(novo->time,linha);
			
			token=strtok(NULL,"|");
			novo->pontos=atoi(token);
			
			token=strtok(NULL,"|");
			novo->vitorias=atoi(token);
			
			token=strtok(NULL,"|");
			novo->derrotas=atoi(token);
			
			token=strtok(NULL,"|");
			novo->saldo_gols=atoi(token);
				
			insere_ordenado(novo, lista);
			}
		fclose(arq);
		salva(lista);
} 

void insere_ordenado(no *novo, no *lista){
	no *atual;
	atual=lista;
	
	if(lista->prox==NULL){
		lista->prox=novo;
		novo->prox=NULL;
		return;
		}
	while(atual->prox !=NULL && compara(novo,atual->prox)==0){
		atual=atual->prox;
		}
	novo->prox=atual->prox;
	atual->prox=novo;
	
	}
	
int compara(no *novo, no *auxiliar){
	if(novo->pontos>auxiliar->pontos){
		return 1;
	}
	if(novo->pontos<auxiliar->pontos){
		return 0;}
		
		
	if(novo->vitorias>auxiliar->vitorias){
		return 1;
		}
	if(novo->vitorias<auxiliar->vitorias){
		return 0;
		}
		
	if(novo->derrotas<auxiliar->derrotas){
		return 1;
		}
	if(novo->derrotas>auxiliar->derrotas){
		return 0;
		}
		
	if(novo->saldo_gols>auxiliar->saldo_gols){
		return 1;
		}
	return 0;
}

void salva(no *lista){
	FILE *arq;
	arq=fopen("resultado.txt","w");
	
	if(arq==NULL){
		printf("Nao foi possivel criar o arquivo");
	}
	
	no *aux;
	aux=lista->prox;
	
	
	while(aux!=NULL){
		fprintf(arq,"---------------------------------------------------\n");
		fprintf(arq,"%s|p: %d|v: %d|d: %d|saldo: %d\n",aux->time,aux->pontos,aux->vitorias,aux->derrotas,aux->saldo_gols);
		fprintf(arq,"---------------------------------------------------\n");
		aux=aux->prox;
		}
		fclose(arq);
		printa();
	
	}
	
	void printa(){
		FILE *arq;
		arq=fopen("resultado.txt","r");
		if(arq==NULL){
			printf("Nao foi possivel ler");
			return;
			}
		char linha[200];
		while(fgets(linha,sizeof(linha),arq)!=NULL){
			printf("%s",linha);
			}	
		
		}
