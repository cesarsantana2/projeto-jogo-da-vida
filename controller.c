#include "view.c"
#include "model.c"

// Declarando a assinatura das funcoes
int verifica_se_a_posicao_estah_contida(int x, int y, int escolha);
void determinar_tamanho_da_matriz();
void fluxo_do_jogo(int opcao);
void adicionar_vida_em_uma_posicao();
void controla_jogo();
void retorna_pecas_vivas();
void retorna_vizinhos_pecas_vivas();
void adicionar_vizinhos_canto_superior_esquerdo();
void mapear_vizinhos_de_uma_peca_viva();

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
                mapear_vizinhos_de_uma_peca_viva();
                exibir_mundo(tamanho_da_matriz_quadrada);
                break;

        default: break;

        mapear_vizinhos_de_uma_peca_viva();

        
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

int verifica_se_a_posicao_estah_contida(int x, int y, int escolha){

    int i;

    switch(escolha){
    
        case 1: for (i = 0; i < quantidade_pecas_vivas; i++){
                    if(pecas_vivas.pos[i].linha == x && pecas_vivas.pos[i].coluna == y){
                        return 1;
                    }
                }
                     return 0;

        case 2: for (i = 0; i < quantidade_vizinhos_mortos; i++){
                    if(vizinhos_mortos.pos[i].linha == x && vizinhos_mortos.pos[i].coluna == y){
                        return 1;
                    }

                } 
                    return 0;
    }
}


void determinar_tamanho_da_matriz(){

    printf("\nPor favor, informe o tamanho da matriz quadrada: ");
    scanf("%d", &tamanho_da_matriz_quadrada);

}

void adicionar_vida_em_uma_posicao(){

    int lin, coln;
   
    printf("\nPor favor selecione linha e coluna para adicionar vida ou 0 para sair | [Ex.de input: 4,5]:  ");
    scanf("%d,%d", &lin,&coln);

    pecas_vivas.pos[quantidade_pecas_vivas].linha = lin;
    pecas_vivas.pos[quantidade_pecas_vivas].coluna = coln;

    quantidade_pecas_vivas++;
}

void retorna_pecas_vivas(){

    int i;

    for(i = 0; i < quantidade_pecas_vivas; i++){

            printf("[%d|%d]", pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);
    }
}

int identificar_tipo_de_posicao(int linha, int coluna){
    
    if(linha == 0){
        if(coluna == 0){
            return 1;
        }
        if(coluna == 9){
            return 2;
        }
        if(coluna != 0 && coluna != 9){
            return 5;
        }
    }

    if(linha == (tamanho_da_matriz_quadrada - 1)){
        if(coluna == 0){
            return 3;
        }
        if(coluna == (tamanho_da_matriz_quadrada - 1)){
            return 4;
        }
        if(coluna != 0 && coluna != (tamanho_da_matriz_quadrada - 1)){
            return 6;
        }
    }

    if(coluna == 0){
        if(linha != 0 && linha != (tamanho_da_matriz_quadrada - 1)){
            return 7;
        }
    }
    
    if(coluna == (tamanho_da_matriz_quadrada - 1)){
        if(linha != 0 && linha != (tamanho_da_matriz_quadrada - 1)){
            return 8;
        }
    }

    return 9;
}

void adicionar_vizinhos_canto_superior_esquerdo(){

    int i;

    printf("CHEGUEI AQUI");

    if(!(verifica_se_a_posicao_estah_contida(0, 1, 2))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 0;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1;

        quantidade_vizinhos_mortos++;

    }

    if(!(verifica_se_a_posicao_estah_contida(1, 1, 2))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1;

        quantidade_vizinhos_mortos++;

    }

    if(!(verifica_se_a_posicao_estah_contida(1, 0, 2))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 0;

        quantidade_vizinhos_mortos++;

    }

}

void mapear_vizinhos_de_uma_peca_viva(){

    int i, tipo;

    for(i = 0; i < quantidade_pecas_vivas; i++){


        tipo = identificar_tipo_de_posicao(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);

        switch(tipo){

            case 1: adicionar_vizinhos_canto_superior_esquerdo(); 
                    break;

            case 2: //to-do - fazer funcao para pegar vizinhos do canto superior direito
                    break;

            case 3: //to-do - fazer funcao para pegar vizinhos canto inferior esquerdo;
                    break;

            case 4: //to-do - fazer funcao para pegar vizinhos canto inferior direito
                    break;

            case 5: //to-do - fazer funcao para pegar vizinhos de posicao da primeira linha
                    break;

            case 6: //to-do - fazer funcao para pegar vizinhos de posicao da ultima linha
                    break;

            case 7: //to-do - fazer funcao para pegar vizinhos de posicao da primeira coluna
                    break;

            case 8: //to-do - fazer funcao para pegar vizinhos de posicao da ultima coluna
                    break;

            case 9: //to-do - fazer funcao para pegar vizinhos de peca central
                    break;
        }
    }
}

void retorna_vizinhos_pecas_vivas(){

    int i;

    for(i = 0; i < quantidade_vizinhos_mortos; i++){
        printf("[%d|%d]", vizinhos_mortos.pos[i].linha, vizinhos_mortos.pos[i].coluna);
    }
        
}

