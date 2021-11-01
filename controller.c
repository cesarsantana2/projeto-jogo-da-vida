#include "view.c"
#include "model.c"

// Declarando a assinatura das funcoes
int verifica_se_a_posicao_estah_contida(int x, int y, int escolha);
int pega_quantidade_de_vizinhos_vivos();
int sobrevive_para_proxima_geracao(int posicao);
int nasce_para_proxima_geracao(int posicao);
void determinar_tamanho_da_matriz();
void fluxo_do_jogo(int opcao);
void adicionar_vida_em_uma_posicao();
void controla_jogo();
void controla_passagem_de_geracao();
void retorna_pecas_vivas();
void retorna_vizinhos_pecas_vivas();
void adicionar_vizinhos_canto_superior_esquerdo();
void adicionar_vizinhos_canto_superior_direito();
void adicionar_vizinhos_posicao_primeira_linha();
void mapear_vizinhos_de_uma_peca_viva();
void remover_vida_em_uma_posicao();
void remove_vida(int posicao);

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

        case 2: remover_vida_em_uma_posicao();
                mapear_vizinhos_de_uma_peca_viva();
                exibir_mundo(tamanho_da_matriz_quadrada);
                break;

        case 3: controla_passagem_de_geracao();
                mapear_vizinhos_de_uma_peca_viva();
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
   
    printf("\nPor favor selecione linha e coluna para adicionar vida ou 0 para sair | [Ex. de input: 4,5]:  ");
    scanf("%d,%d", &lin,&coln);

    pecas_vivas.pos[quantidade_pecas_vivas].linha = lin;
    pecas_vivas.pos[quantidade_pecas_vivas].coluna = coln;

    quantidade_pecas_vivas++;
}

void remover_vida_em_uma_posicao(){

    int i, lin, coln;

    printf("\n Por favor selecione linha e coluna para remover vida ou 0 para sair | [Ex. de input: 4,3]: ");
    scanf("%d,%d", &lin,&coln);

    for (i = 0; i < quantidade_pecas_vivas; i++){

        if(pecas_vivas.pos[i].linha == lin && pecas_vivas.pos[i].coluna == coln){
            remove_vida(i);
        }
    }
}

void remove_vida(int posicao){

    int i;

    for(i = posicao; i < quantidade_pecas_vivas; i++){

        if(i == quantidade_pecas_vivas - 1){
            quantidade_pecas_vivas = quantidade_pecas_vivas - 1;
        }else{
            
            pecas_vivas.pos[i].linha = pecas_vivas.pos[i+1].linha;
            pecas_vivas.pos[i].coluna = pecas_vivas.pos[i+1].coluna;
        }
    }
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
        if(coluna == tamanho_da_matriz_quadrada - 1){
            return 2;
        }
        if(coluna != 0 && coluna != tamanho_da_matriz_quadrada - 1){
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

    if(!((verifica_se_a_posicao_estah_contida(0, 1, 2)) || (verifica_se_a_posicao_estah_contida(0, 1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 0;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1;

        quantidade_vizinhos_mortos++;

    }

    if(!((verifica_se_a_posicao_estah_contida(1, 1, 2)) || (verifica_se_a_posicao_estah_contida(1, 1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1;

        quantidade_vizinhos_mortos++;

    }

    if(!((verifica_se_a_posicao_estah_contida(1, 0, 2)) || (verifica_se_a_posicao_estah_contida(1, 0, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 0;

        quantidade_vizinhos_mortos++;

    }
}

void adicionar_vizinhos_canto_superior_direito(){

    int i;

    if(!((verifica_se_a_posicao_estah_contida(0, tamanho_da_matriz_quadrada-2, 2)) || (verifica_se_a_posicao_estah_contida(0, tamanho_da_matriz_quadrada-2, 1)))){

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 0;

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-2;

       quantidade_vizinhos_mortos++;

    }

    if(!((verifica_se_a_posicao_estah_contida(1, tamanho_da_matriz_quadrada-2, 2)) || (verifica_se_a_posicao_estah_contida(1, tamanho_da_matriz_quadrada-2, 1)))){

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-2;

       quantidade_vizinhos_mortos++;

    }

    if(!((verifica_se_a_posicao_estah_contida(1, tamanho_da_matriz_quadrada-1, 2)) || (verifica_se_a_posicao_estah_contida(1, tamanho_da_matriz_quadrada-1, 1)))){

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = 1;

       vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-1;

       quantidade_vizinhos_mortos++;
    }
}

void adicionar_vizinhos_canto_inferior_esquerdo(){

    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, 0, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, 0, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-2;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 0; 

        quantidade_vizinhos_mortos++;
    }


    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, 1, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, 1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-2;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1; 

        quantidade_vizinhos_mortos++;

    }

    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-1, 1, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-1, 1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = 1; 

        quantidade_vizinhos_mortos++;
    }
}

void adicionar_vizinhos_canto_inferior_direito(){

    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-1, tamanho_da_matriz_quadrada-2, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-1, tamanho_da_matriz_quadrada-2, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-2;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, tamanho_da_matriz_quadrada-2, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, tamanho_da_matriz_quadrada-2, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-2;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-2;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, tamanho_da_matriz_quadrada-1, 2)) || (verifica_se_a_posicao_estah_contida(tamanho_da_matriz_quadrada-2, tamanho_da_matriz_quadrada-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = tamanho_da_matriz_quadrada-2;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = tamanho_da_matriz_quadrada-1;

        quantidade_vizinhos_mortos++;
    }
}


void adicionar_vizinhos_posicao_primeira_linha(int linha, int coluna){

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }
}


void adicionar_vizinhos_posicao_ultima_linha(int linha, int coluna){
    
    if(!((verifica_se_a_posicao_estah_contida(linha, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }
}

void adicionar_vizinhos_posicao_primeira_coluna(int linha, int coluna){
    
    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

}

void adicionar_vizinhos_posicao_ultima_coluna(int linha, int coluna){
    
    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }
}

void adicionar_vizinhos_posicao_do_meio(int linha, int coluna){

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)))){

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna-1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha-1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }

    if(!((verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 2)) || (verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)))){
        
        vizinhos_mortos.pos[quantidade_vizinhos_mortos].linha = linha+1;

        vizinhos_mortos.pos[quantidade_vizinhos_mortos].coluna = coluna+1;

        quantidade_vizinhos_mortos++;
    }
}

void mapear_vizinhos_de_uma_peca_viva(){

    int i, tipo;

    quantidade_vizinhos_mortos = 0;

    for(i = 0; i < quantidade_pecas_vivas; i++){


        tipo = identificar_tipo_de_posicao(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);

        switch(tipo){

            case 1: adicionar_vizinhos_canto_superior_esquerdo(); 
                    break;

            case 2: adicionar_vizinhos_canto_superior_direito();
                    break;

            case 3: adicionar_vizinhos_canto_inferior_esquerdo(); 
                    break;

            case 4: adicionar_vizinhos_canto_inferior_direito();
                    break;

            case 5: adicionar_vizinhos_posicao_primeira_linha(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);
                    break;

            case 6: adicionar_vizinhos_posicao_ultima_linha(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);
                    break;

            case 7: adicionar_vizinhos_posicao_primeira_coluna(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna); 
                    break;

            case 8: adicionar_vizinhos_posicao_ultima_coluna(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna); 
                    break;

            case 9: adicionar_vizinhos_posicao_do_meio(pecas_vivas.pos[i].linha, pecas_vivas.pos[i].coluna);
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

void controla_passagem_de_geracao(){

    int i;
  
    quantidade_pecas_vivas_proxima_geracao = 0;

    for(i = 0; i < quantidade_pecas_vivas; i++){

        if(sobrevive_para_proxima_geracao(i)){
            
            pecas_vivas_proxima_geracao.pos[quantidade_pecas_vivas_proxima_geracao].linha = pecas_vivas.pos[i].linha;
            pecas_vivas_proxima_geracao.pos[quantidade_pecas_vivas_proxima_geracao].coluna = pecas_vivas.pos[i].coluna;

            quantidade_pecas_vivas_proxima_geracao++;
        
        }
    }
   
    for(i = 0; i < quantidade_vizinhos_mortos; i++){
   
        if(nasce_para_proxima_geracao(i)){

            pecas_vivas_proxima_geracao.pos[quantidade_pecas_vivas_proxima_geracao].linha = vizinhos_mortos.pos[i].linha;
            pecas_vivas_proxima_geracao.pos[quantidade_pecas_vivas_proxima_geracao].coluna = vizinhos_mortos.pos[i].coluna;
            
            quantidade_pecas_vivas_proxima_geracao++;
        }

    }

    pecas_vivas = pecas_vivas_proxima_geracao;

    quantidade_pecas_vivas = quantidade_pecas_vivas_proxima_geracao;
}


int nasce_para_proxima_geracao(int posicao){

    int populacao, linha, coluna, tipo;

    linha = vizinhos_mortos.pos[posicao].linha;
    coluna = vizinhos_mortos.pos[posicao].coluna;

    tipo = identificar_tipo_de_posicao(linha, coluna);

    populacao = pega_quantidade_de_vizinhos_vivos(linha, coluna, tipo);

    if(populacao == 3){
        return 1;
    }
    return 0;
}

int sobrevive_para_proxima_geracao(int posicao){

   int populacao, linha, coluna, tipo;

   linha = pecas_vivas.pos[posicao].linha;
   coluna = pecas_vivas.pos[posicao].coluna;

   tipo = identificar_tipo_de_posicao(linha, coluna);

   populacao = pega_quantidade_de_vizinhos_vivos(linha, coluna, tipo);
   
   if(populacao >= 4 || populacao < 2){
       return 0;
    }
   return 1;
}

int pega_quantidade_de_vizinhos_vivos(int linha, int coluna, int tipo){

    int populacao = 0;


    switch(tipo){

        case 1: if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)){
                    populacao = populacao + 1;
                } 

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }
                    return populacao;

        case 2: if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }

                    return populacao;

        case 3: if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)){
                    populacao = populacao + 1;
                }
                
                if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                    return populacao;
        
        case 4: if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }
                
                if(verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)){
                    populacao = populacao + 1;
                }
                
                if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                    return populacao;

        case 5: if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }
                
                if(verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }


                if(verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }
                    
                    return populacao;

        case 6: if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)){
                    populacao = populacao + 1;
                }
                
                if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }
                    
                    return populacao;

        case 7: if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }
                    
                    return populacao;

        case 8: if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }

                    return populacao;


        case 9: if(verifica_se_a_posicao_estah_contida(linha-1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna+1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha+1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                if(verifica_se_a_posicao_estah_contida(linha-1, coluna-1, 1)){
                    populacao = populacao + 1;
                }

                    return populacao;
    }
}
