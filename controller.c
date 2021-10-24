#include "view.c"
#include "model.c"

// Declarando a assinatura das funcoes
void determinar_tamanho_da_matriz();
void fluxo_do_jogo(int opcao);
void adicionar_vida_em_uma_posicao();
int verifica_se_a_posicao_estah_contida(int x, int y);
void controla_jogo();
void retorna_pecas_vivas();
void retorna_vizinhos_pecas_vivas();


//CONTADORES GLOBAIS
int tamanho_da_matriz_quadrada;
int quantidade_pecas_vivas = 0;
int quantidade_vizinhos_mortos = 0;
int quantidade_pecas_vivas_proxima_geracao = 0;
int quantidade_vizinhos_mortos_proxima_geracao = 0;


void entrypoint(){

    int opcao_menu_principal = -1;

    while(opcao_menu_principal != 0){

        opcao_menu_principal = menu_principal();
        fluxo_do_jogo(opcao_menu_principal);
    }
}

void fluxo_do_jogo(int opcao){

    switch(opcao){
        
        case 1: controla_jogo();
                break;

        default:
            break;
    }
}   

void fluxo_de_geracoes(int opcao){

    switch(opcao){
  

        case 1: adicionar_vida_em_uma_posicao();
                exibir_mundo(tamanho_da_matriz_quadrada);
                break;

        default: break;
    }
}

void controla_jogo(){

    int opcao_menu_de_geracoes = -1;

    determinar_tamanho_da_matriz();

    while(opcao_menu_de_geracoes != 0){

        opcao_menu_de_geracoes =  menu_fluxo_de_geracoes();
        fluxo_de_geracoes(opcao_menu_de_geracoes);
    }
}



void controla_geracoes(){}

int verifica_se_a_posicao_estah_contida(int x, int y){

    int i;

    for (i = 0; i < quantidade_pecas_vivas; i++){

        if(pecas_vivas.pos[i].linha == x && pecas_vivas.pos[i].coluna == y){
            return 1;
        }
    }

    return 0;
}


void determinar_tamanho_da_matriz(){

    printf("\nPor favor, informe o tamanho da matriz quadrada: ");
    scanf("%d", &tamanho_da_matriz_quadrada);

}

void adicionar_vida_em_uma_posicao(){

    int lin, coln;
    int opcao = -1;
   
    printf("\nPor favor selecione linha e coluna para adicionar vida ou 0 para sair | [Ex.de input: 4,5]:  ");
     


    scanf("%d,%d", &lin,&coln);

    pecas_vivas.pos[quantidade_pecas_vivas].linha = lin;
    pecas_vivas.pos[quantidade_pecas_vivas].coluna = coln;

    quantidade_pecas_vivas++;
}

void retorna_pecas_vivas(){

    int i;

    for(i = 0; i < quantidade_pecas_vivas; i++){

            printf("[%d]|[%d]", pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);
    }
}










void identificar_vizinhos_de_uma_peca_viva(){

    


}


void retorna_vizinhos_pecas_vivas(){



}

