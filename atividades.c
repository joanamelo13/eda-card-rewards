#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "atividades.h"

//atividades (heap simples)
heap* criar(int nmax){
    heap *h = (heap *) malloc(sizeof(heap));
    h->n = 0;
    h->nmax = nmax;
    h->v = (int *) malloc(h->nmax * sizeof(int));
    return h;
}

void heap_insere(heap *h, int valor){
	h->v[h->n++] = valor;
	sobe(h, h->n-1);
}

int heap_retira (heap *h){
	int topo = h->v[0];
	h->v[0] = h->v[--(h->n)];
	desce(h, 0);
	return topo;
}

void sobe(heap *h, int i){
	int pai;
	while(i>0){
		pai = pai(i);
		if((h->v[pai]) > (h->v[i]))
			break;
		troca(h, pai, i);
		i = pai;
	}
}

void troca(heap *h, int i, int j){
	int temp = h->v[i];
	h->v[i] = h->v[j];
	h->v[j] = temp;
}

void desce (heap *h, int i){
	int aux = esq(i);
	int filho_dir;
	while(aux < h->n){
		filho_dir = dir(i);
		if((filho_dir < h->n) && (h->v[filho_dir] >h->v[aux]))
			aux = filho_dir;
		if(h->v[aux] < h->v[i])
			break;
		troca(h, i, aux);
		i = aux;
		aux = esq(i);
	}
}


//categorias (union and find)
UniaoBusca* ub_cria (int n){

	int i;
	UniaoBusca* ub = ( UniaoBusca*) malloc(sizeof ( UniaoBusca));
	ub->n = n;
	ub->v = (int *) malloc(ub->n* sizeof (int ));	
	
	for (i=0; i<ub->n; ++i)
		ub->v[i] = -1; 

	return ub;
}

void ub_libera ( UniaoBusca* ub){
	free(ub->v);
	free(ub);
}

int ub_busca ( UniaoBusca* ub, int x){
	
	int r = x;
	
	while (ub->v[r] >= 0)
		r = ub->v[r];
	
	
	while (ub->v[x] >= 0) {
		int p = ub->v[x];
		ub->v[x] = r;
		x = p;
	}
	
	return r;
}

int ub_uniao ( UniaoBusca* ub, int x, int y){

	x = ub_busca(ub,x);
	y = ub_busca(ub,y);
	if (x == y) 
		return x;
	

	
	if (ub->v[x] <= ub->v[y]) {
		ub->v[x] += ub->v[y]; 
		ub->v[y] = x; 
		return x;
	}
	
	else {
		ub->v[y] += ub->v[x]; 
		ub->v[x] = y; 
		return y;
	}

}


//REGRA DE NEGÓCIO
void verCategoria(heap *hCliente, UniaoBusca* ubCat ){
	int i;
	int bronze = 0, prata = 0, ouro = 0, diamante = 0;

	for(i = 0; i < hCliente->n; i++){
		
		if( (hCliente->v[i] > 0) && (hCliente->v[i] <= 3) ){
			bronze += hCliente->v[i];
		}
		else if( (hCliente->v[i] >= 4) && (hCliente->v[i] <= 6) ){
			prata += hCliente->v[i];
		}
		else if( (hCliente->v[i] >= 7) && (hCliente->v[i] <= 9) ){
			ouro += hCliente->v[i];
		}
		else if( hCliente->v[i] >= 10 ){
			diamante += hCliente->v[i];
		}
		else{
			printf("Você não pertence a nenhuma categoria");
		}	
	}
	
	int categoriaAtual = 0, proximaCategoria = 0;
	
	//definindo a categoria atual
	if(categoriaAtual == 0){
		if(bronze == 6){
			categoriaAtual = 1;
		}
		else if(prata == 15){
			categoriaAtual = 2;
		}
		else if(ouro == 24){
			categoriaAtual = 3;
		}
		else if(diamante == 33){
			categoriaAtual = 4;
		}
		
		int i;
		for(i = 0; i < categoriaAtual; i++){
			ubCat->v[i+1] = i;
			ubCat->v[0]-=1;
		}
		
		//mostrando a categoria na tela
		if(ubCat->v[0] == -1)
			printf("\nVoce ainda nao tem categoria.");
		if(ubCat->v[0] == -2)
			printf("\nVoce esta na categoria bronze.");
		if(ubCat->v[0] == -3)
			printf("\nVoce esta na categoria prata.");	
		if(ubCat->v[0] == -4)
			printf("\nVoce esta na categoria ouro.");
		if(ubCat->v[0] == -5)
			printf("\nVoce esta na categoria diamante.");				
	}	

}



//MENU DE OPÇÕES DO USUÁRIO
void menu(){
	int op;
	
	heap *heapCliente = criar(12);
	UniaoBusca *uniaoBuscaCategoria = ub_cria(5);
	
	do{    
	    //--------------- Exibir menu ---------------------//
	        system("cls");
	        puts("\n\t\t\t\tBEM VINDO AO SEU CLUBE DE VANTAGENS\n");
	        puts("\t1  - VER MINHA CATEGORIA ATUAL\n \t2  - CADASTRAR ATIVIDADE REALIZADA\n \t3  - ZERAR ATIVIDADES REALIZADAS\n \t4  - EXIBIR CATEGORIAS EXISTENTES\n \t0  - SAIR");
	        printf("\nINFORME SUA OPCAO:\n");
	        scanf("%d", &op);
	        
	        switch(op){
	    		case 1:{
	    			verCategoria(heapCliente, uniaoBuscaCategoria);
	    			break; 						
				}
				case 2:{
					printf("\nLista de atividades: ");
					printf("\n1 - Nao fazer nada");
					printf("\n2 - Usar o cartão PremiCard na loja da Maria");
					printf("\n3 - Comprar 10 Real em Comidas Saudaveis");
					printf("\n4 - Comprar na loja Compre Aqui");
					printf("\n5 - Realizar 1500 Reais em compras virtuais");
					printf("\n6 - Realizar 500 Reais em compras virtuais");
					printf("\n7 - Acumular 1000 milhas de viagem");
					printf("\n8 - Realizar pagamentos no App EDA-Bank");
					printf("\n9 - Abastecer no posto Gasolina Barata");
					printf("\n10 - Comprar no restaurante Comida Boa");
					printf("\n11 - Usar o cartão PremiCard");
					printf("\n12 - Comprar na loja da Maria");
					
					int valor;
					printf("\n\nEscolha a Categoria que deseja inserir: ");
					scanf("%d", &valor);
					
					
					heap_insere(heapCliente, valor);
			
					break;  						
				}
				case 3:{
					//reseta heap
					while(heapCliente->n != 0){
						heap_retira(heapCliente);
					}
					
					//reseta categoria
					int i;
					for(i = 0; i < uniaoBuscaCategoria->n; i++){
						uniaoBuscaCategoria->v[i] = -1;
					}
					
					printf("As atividades foram apagadas, voce nao pertence mais a nenhuma categoria.");
					break;  						
				}
				case 4:{
					printf("\nCategorias existentes:\n");
	    			printf("\n1 - BRONZE\n");
	    			printf("2 - PRATA\n");
	    			printf("3 - OURO\n");
	    			printf("4 - DIAMANTE\n");
	    			
	    			break; 						
				}
				case 0:{
					printf("APLICACAO ENCERRADA");
					return; 						
				}
	    			
		    	default:
		    		puts("OPCAO INCORRETA,TENTE NOVAMENTE.");
					break;	      
		        }
			getch();
		}while(op!=0);
}











