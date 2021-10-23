#include "view.c"
#include "model.c"

// Declarando a assinatura das funcoes
void determinar_tamanho_da_matriz();
void fluxo_do_jogo(int opcao);

//CONTADORES GLOBAIS

int tamanho_da_matriz_quadrada = 0;
int quantidade_pecas_vivas = 0;
int quantidade_vizinhos_mortos = 0;


void entrypoint(){

    int opcao, tamanho_da_matriz;

    opcao = menu_principal();
    fluxo_do_jogo(opcao);

    //TO-DO 
    //exibir_mundo();


}

void inicia_posicoes_das_listas_do_jogo(){

    int i;

    for (i = 0, i < 500; i++){
        
        pecas_vivas[i] = 0;
        vizinhos_mortos = 0;
        pecas_vivas_proxima_geracao[i] = 0;
        vizinhos_mortos_proxima_geracao[i] = 0;
    }
}

void fluxo_do_jogo(int opcao){

    switch(opcao){
        
        case 1: determinar_tamanho_da_matriz();
                break;

        default:
            break;
    }

}     

int verifica_se_a_posicao_estah_contida(int x, int y){

    int i = 0;

}

void determinar_tamanho_da_matriz(){

    printf("Por favor, informe o tamanho da matriz quadrada: ");
    scanf("%d", &tamanho_da_matriz_quadrada);

}

void selecionar_posicoes_para_atribuir_vida(){

}