#include <stdio.h>
#include <stdlib.h>

struct no{
   int info;
   struct no* elo_anterior;
   struct no* elo_proximo;
};

typedef struct no No;

struct fila{
    No* inicio;
    No* fim;
};

typedef struct fila Fila;

Fila* cria(){
    //fila dinamica
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

No* insereFim(No* inicio, No* fim , int info){
    No* no = (No*) malloc(sizeof(No));
    no->info = info;
    no->elo_proximo = NULL;
    no->elo_anterior = fim;
    if (fim != NULL){
      fim->elo_proximo = no;
    }
    return no;
}


void insereComeco(Fila* fila , int info){
    No* noNovoParaInicio = (No*) malloc(sizeof(No));
    noNovoParaInicio->info = info;
    noNovoParaInicio ->elo_proximo = fila->inicio;
    noNovoParaInicio ->elo_anterior = NULL;

    No* noAuxiliar = fila->inicio;

    if(fila->inicio != NULL){
        fila->inicio->elo_anterior = noNovoParaInicio;
    }

    fila->inicio = noNovoParaInicio;
}

void enqueueInicio(Fila* fila , int info){
    insereComeco(fila, info);

    if(fila->fim == NULL){
      fila->fim = fila->inicio;
   }
}

void enqueueFim(Fila* fila , int info){
    fila->fim = insereFim(fila->inicio, fila->fim , info);

    if(fila->inicio == NULL){
        fila->inicio = fila->fim;
    }
}

No* retiraFim(No* fim){
   No* no = fim->elo_anterior;
   if (no != NULL){
      no->elo_proximo = NULL;
   }
   free(fim);
   return no;
}

int dequeueFim(Fila* fila){
   fila->fim = retiraFim(fila->fim);
   if (fila->fim == NULL){
      fila->inicio = NULL;
   }
}

No* retiraInicio(No* inicio){
   No* no = inicio->elo_proximo;
   if (no != NULL){
      no->elo_anterior = NULL;
   }
   free(inicio);
   return no;
}

int dequeueInicio(Fila* fila){
   int info;
   info = fila->inicio->info;
   fila->inicio = retiraInicio(fila->inicio);
   if (fila->inicio == NULL){
      fila->fim = NULL;
   }
   return info;
}

void imprime(Fila* fila){
   No* no;
   printf("\nFILA: %p\n\n NO_INICIO: %p\n NO_FIM: %p\n\n", fila, fila->inicio, fila->fim);
   for(no = fila->inicio; no != NULL; no = no->elo_proximo){
      //printf("%d\n",no->info);
      if(no->elo_anterior == NULL){
         printf("  NO:%p => | ELO_ANTERIOR:%p            | INFO: %d | ELO_PROXIMO:%p |\n",no, no->elo_anterior, no->info, no->elo_proximo);
      }else if(no->elo_proximo == NULL){
         printf("  NO:%p => | ELO_ANTERIOR:%p | INFO: %d | ELO_PROXIMO:%p            |\n",no, no->elo_anterior, no->info, no->elo_proximo);
      }else{
         printf("  NO:%p => | ELO_ANTERIOR:%p | INFO: %d | ELO_PROXIMO:%p |\n",no, no->elo_anterior, no->info, no->elo_proximo);
      }

   }
   printf("\n\n");
}


void libera(Fila* fila){
   No* no;
   No* no_anterior;
   for(no = fila->inicio; no != NULL; no = no_anterior){
      no_anterior = no->elo_proximo;
      free(no);
   }
   free(fila);
}

int mostraOpcao(){

    printf( "1 - Inserir elemento no inicio\n" );
	printf( "2 - Remover elemento no inicio\n" );
	printf( "3 - Mostrar elemento no inicio\n" );

	printf( "4 - Inserir o ultimo elemento\n" );
	printf( "5 - Remover elemento no fim\n" );
	printf( "6 - Mostrar elemento no fim\n" );

	printf( "7 - Mostrar lista\n" );
	printf( "0 - Sair\n" );
	printf( "Opcao? " );
    int valorEscolhido;
    scanf("%d", &valorEscolhido);

    return valorEscolhido;
}

void menu(Fila* fila){
        int opcao = mostraOpcao();
        int valor;

        do {

            switch(opcao){
                case 1: // inserir elemento no inicio
                    printf( "Valor a ser inserido? " );
                    scanf( "%d", &valor );
                    enqueueInicio(fila, valor);
                    menu(fila);
				break;

                case 2: // remover o primeiro
                    dequeueInicio(fila);

                    menu(fila);
				break;

                case 3: // mostra o primeiro
                    if (fila->inicio == NULL) {
                        printf("Fila vazia \n\n");
                    }else{
                        printf( "%O primeiro valor eh : %d \n", fila->inicio->info );
                    }

                    menu(fila);
				break;

				case 4: // inserir no ultimo
                    printf( "Valor a ser inserido? " );
                    scanf( "%d", &valor );
                    enqueueFim(fila, valor);
                    menu(fila);
				break;

                case 5: // remove no ultimo
                    dequeueFim(fila);

                    menu(fila);
                break;

                case 6: // mostra o ultimo
                    if (fila->fim == NULL) {
                        printf("Fila vazia \n\n");
                    }else{
                        printf( "O ultimo valor eh : %d \n", fila->fim->info );
                    }
                    menu(fila);
				break;

                case 7: //  mostrar lista
				if (fila->inicio == NULL && fila->fim == NULL) {
					printf("Fila vazia \n\n");
				}
				else {
					imprime(fila);
				}
				menu(fila);
				break;

                case 0:
                    libera(fila);
                    exit(1);
                break;

                default:
                    printf("Valor invalido escolhido, escolha outro");
                    opcao = mostraOpcao();

            }

        }while(opcao != 0);
}



int main(){

    Fila* fila;

   fila = cria();

   enqueueInicio(fila, 1);
   enqueueInicio(fila, 2);
   enqueueInicio(fila, 3);
   enqueueInicio(fila, 4);
   enqueueInicio(fila, 5);

   menu(fila);

  /*
   imprime(f1);

   enqueueFim(f1, 6);
   imprime(f1);

   dequeueInicio(f1);
   imprime(f1);

   dequeueFim(f1);
   imprime(f1);
   */

}
