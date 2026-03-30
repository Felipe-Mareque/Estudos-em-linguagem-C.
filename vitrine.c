#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct no {
    char nome[30];
    float preco;
    int avaliacao;
    int estoque;
    struct no *prox;
};
typedef struct no no;
no *head();
void carrega_e_filtra_produtos(no *lista);
void insere(no *novo, no *lista);
int compara(no *aux, no *novo);
void salva_vitrine(no *lista);
void libera_lista(no *lista);

int main() {
    no *vitrine = head();
    
    carrega_e_filtra_produtos(vitrine); // Só insere se estoque > 0
    
    printf("Gerando vitrine premium...\n");
    salva_vitrine(vitrine);
    
    // Desafio extra: Função para liberar todos os nós antes de fechar
    libera_lista(vitrine); 
    system("start vitrine.txt");
    return 0;
}
no *head(){
	no *head=malloc(sizeof(no));
	head->prox=NULL;
	
	return head;
	
	}
	
	void carrega_e_filtra_produtos(no *lista){
		FILE *arq;
		arq=fopen("produtos.txt","r");
		if(arq==NULL){
			printf("nao foi possivel ler o arquivo");
			return;
			}
			
		char linha[100];
		char *token; 
		
	while(fgets(linha,sizeof(linha),arq)!=NULL){
		linha[strcspn(linha,"\n")]='\0';
		
		no *novo=malloc(sizeof(no));
		novo->prox=NULL;
		
		token=strtok(linha,"#");
		token[strcspn(token,"\n")]='\0';
		strcpy(novo->nome,token);
		
		token=strtok(NULL,"#");
		novo->preco=atof(token);
		
		token=strtok(NULL,"#");
		novo->avaliacao=atoi(token);
		
		token=strtok(NULL,"#");
		novo->estoque=atoi(token);
		
		if(novo->estoque>0){
			insere(novo,lista);
			}
		else{
			free(novo);
			}
		}
		
	fclose(arq);	
	}
	
	void insere(no *novo, no *lista){
		no *aux;
		aux=lista;
		
		while(aux->prox!=NULL && compara(aux->prox,novo)==0){
			aux=aux->prox;
			}
		novo->prox=aux->prox;
		aux->prox=novo;
		
		return;
		}
		
	int compara(no *aux, no *novo){
		if(aux->avaliacao>novo->avaliacao){
			return 0;
			}
		if (aux->avaliacao<novo->avaliacao){
			return 1;
			}
		//---------------------------
		if(aux->preco<novo->preco){
			return 0;
			}
		if(aux->preco>novo->preco){
			return 1;
			}
		//---------------------------
		if(aux->estoque>novo->estoque){
			return 0;
			}
		if(aux->estoque<novo->estoque){
			return 1;
			}
		//---------------------------
		if(strcmp(aux->nome,novo->nome)<0){
			return 1;
			}
		return 0;
		}
		
	void salva_vitrine(no *lista){
		FILE *arq;
		arq=fopen("vitrine.txt","w");
		if(arq==NULL){
			printf("nao foi possivel criar outro arquivo texto");
			return;
			}
		
		no *aux;
		aux=lista->prox;
		
		fprintf(arq,"================== VITRINE PREMIUM ==================\n");
		
		while(aux!=NULL){
			fprintf(arq,"PRODUTO: %s\n",aux->nome);
			fprintf(arq,"PRECO: %f | AVALIACAO: %d | ESTOQUE: %d\n",aux->preco,aux->avaliacao,aux->estoque);
			fprintf(arq,"-----------------------------------------------------\n");
			aux=aux->prox;
			}
		fclose(arq);
		}
	void libera_lista(no *lista){
		while(lista!=NULL){
			no *aux;
			aux=lista;
			lista=lista->prox;
			free(aux);
			
			}
		
		
		}
