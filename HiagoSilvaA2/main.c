#include <stdio.h>
#include <stdlib.h>

struct no{
    int info;
    struct no* elo;
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

    if(fim == NULL){
        no->elo = no;
    }else{
        fim->elo = no;
        no->elo = inicio;
    }
    return no;
}

void insereComeco(Fila* fila , int info){
    No* noNovoParaInicio = (No*) malloc(sizeof(No));
    noNovoParaInicio->info = info;

    No* noAuxiliar = fila->inicio;

    if(fila->inicio != NULL){
        No* noSuporte = fila->inicio;
        noNovoParaInicio->elo = noSuporte;

        while(noSuporte != noAuxiliar->elo){
            noAuxiliar = noAuxiliar->elo;
        }

        fila->inicio = noNovoParaInicio;
        noAuxiliar ->elo = noNovoParaInicio;
    }else{
        noNovoParaInicio->elo = noNovoParaInicio;
    }
    fila->inicio = noNovoParaInicio;
    fila->fim = noAuxiliar;
}

void enqueue(Fila* fila , int info, int insereNoFim){
    if(insereNoFim > 0){
        fila->fim = insereFim(fila->inicio, fila->fim , info);

        if(fila->inicio == NULL){
            fila->inicio = fila->fim;
        }
    }else{
        insereComeco(fila, info);
    }
}

int removerFim(Fila* fila){
    if(fila->fim == NULL){
     return -1;
    }
    else if(fila->inicio == fila->inicio->elo){
        fila = NULL;
        return -1;
    } else{
        No* noRemovido;
        No* primeiroNo;
        No* noNovoUltimo;

        primeiroNo = fila->inicio;
        noRemovido = primeiroNo->elo;
        while(primeiroNo != noRemovido->elo){
            noNovoUltimo = noRemovido;
            noRemovido = noRemovido->elo;
        }

        noNovoUltimo->elo = primeiroNo;
        fila->fim = noNovoUltimo;
        free(noRemovido);
        return 1;
    }
}

int removeInicio(Fila* fila){
    if(fila->inicio == NULL){
     return -1;
    }
    else if(fila->inicio == fila->inicio->elo){
        fila = NULL;
        return -1;
    } else{
        No* noRemovido;
        No* novoPrimeiro;
        No* noAuxiliar;

        noRemovido = fila->inicio;
        novoPrimeiro = noRemovido->elo;
        noAuxiliar = fila->inicio->elo;

        while(noRemovido != noAuxiliar->elo){
            noAuxiliar = noAuxiliar->elo;
        }

        fila->fim = novoPrimeiro;
        noAuxiliar->elo = novoPrimeiro;
        fila->fim = noAuxiliar;

        free(noRemovido);
    }
}


void imprime(Fila* fila){
    No* no;
    printf("\n");
    printf("\nFILA: %p\n\n NO_INICIO: %p\n NO_FIM: %p\n\n", fila, fila->inicio, fila->fim);
    no = fila->inicio;
    do{
        //printf("info: %d \n"no->info);
        printf("  NO:%p => | INFO: %d | ELO:%p |\n",no, no->info, no->elo);
        no = no->elo;
    }while(no != fila->inicio);
    printf("\n");
}


void libera(Fila* fila){
    No* no;
    No* no_anterior;
    for(no = fila->inicio; no != NULL; no = no_anterior){
        no_anterior = no->elo;
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
                    enqueue(fila, valor, 0);
                    menu(fila);
				break;

                case 2: // remover o primeiro
                    if(removeInicio(fila) < 0 ){
                       printf("Fila vazia \n\n");
                    }
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
                    enqueue(fila, valor, 1);
                    menu(fila);
				break;

                case 5: // remove no ultimo
                    if(removerFim(fila) < 0 ){
                       printf("Fila vazia \n\n");
                    }
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

    //enqueue(fila, 1, 1);
    //enqueue(fila, 2, 1);
    //enqueue(fila, 3, 1);
    //enqueue(fila, 4, 1);

    menu(fila);


    //imprime(fila);

    //libera(f1);

}
