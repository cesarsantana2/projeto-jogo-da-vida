#include "view.c"
#include "model.c"

//VARIAVEIS GLOBAIS
int geracao;
int i, j;

//PROTOTIPO DAS FUNCOES DO JOGO

//Funcoes de controle de fluxo
void iniciaMundo(int posicoes[10][10]);
void proximaGeracao(Mundo *mundo);
void definirPrimeiroSeresVivos(int posicoes[10][10]);
int verifica_tipo_de_posicao(int i, int j);
int vivo_ou_morto(int tipo_de_posicao, int i, int j, int posicoes[10][10]);

//Funcoes que analisam os cantos superiores
int analisar_se_deve_nascer_canto_superior_esquerdo(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_canto_superior_esquerdo(int posicoes[10][10], int i, int j);
int analisar_se_deve_nascer_canto_superior_direito(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_canto_superior_direito(int posicoes[10][10], int i, int j);

//Funcoes que analisam os cantos inferiores
int analisar_se_deve_nascer_canto_inferior_esquerdo(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_canto_inferior_esquerdo(int posicoes[10][10], int i, int j);
int analisar_se_deve_nascer_canto_inferior_direito(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_canto_inferior_direito(int posicoes[10][10], int i, int j);

//Funcoes que analisam as linhas incial e final
int analisar_se_deve_nascer_primeira_linha(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_primeira_linha(int posicoes[10][10], int i, int j);
int analisar_se_deve_nascer_ultima_linha(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_ultima_linha(int posicoes[10][10], int i, int j);

//Funcoes que analisam as colunas inicial e final
int analisar_se_deve_nascer_primeira_coluna(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_primeira_coluna(int posicoes[10][10], int i, int j);
int analisar_se_deve_nascer_ultima_coluna(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_ultima_coluna(int posicoes[10][10], int i, int j);

//Funcoes que analisam as pecas centrais
int analisar_se_deve_nascer_peca_do_meio(int posicoes[10][10], int i, int j);
int analisar_se_deve_morrer_peca_do_meio(int posicoes[10][10], int i, int j);


//COMECO DA LOGICA
Mundo mundo;



//TESTANDO O JOGO
void test(){
iniciaMundo(mundo.posicoes);
mostraMundo(mundo.posicoes);
definirPrimeiroSeresVivos(mundo.posicoes);

printf("\n\nPROXIMA GERACAO\n\n");

proximaGeracao(&mundo);
mostraMundo(mundo.posicoes);

}

void iniciaMundo(int posicoes[10][10]){

    int i, j;

    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++){
            posicoes[i][j] = 0;
        }
    }
}


//funcao que captura as primeiras 10 posicoes dos seres vivos
void definirPrimeiroSeresVivos(int posicoes[10][10]){
    
    int i, linha, coluna;

    printf("\n\nVoce deve selecionar a posicao dos 10 primeiros seres vivos seguindo as instrucoes a baixo: \n\n");

    for (i = 0; i < 10; i++){
        printf("Linha do ser vivo de numero %d: ", i);
        scanf("%d", &linha);
        printf("Coluna do ser vivo de numero %d: ", i);
        scanf("%d", &coluna);

        posicoes[linha][coluna] = 1;

        mostraMundo(posicoes);
    }
}


void proximaGeracao(Mundo *mundo){
    
    int i, j, tipo_de_posicao, valor_que_a_posicao_tera;
    int z = 0;
    int w = 0;
 
    //Identificando vivos e mortos da proxima geracao
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            tipo_de_posicao = verifica_tipo_de_posicao(i, j);
            valor_que_a_posicao_tera = vivo_ou_morto(tipo_de_posicao, i, j, mundo->posicoes);

            //ficar atento de falar dessa sacada aqui
            (*mundo).valores_das_posicoes_da_nova_geracao[z] = valor_que_a_posicao_tera;
            z = z + 1;
        }
    }

    //Repovoando o mundo com a nova geracao
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            (*mundo).posicoes[i][j] = (*mundo).valores_das_posicoes_da_nova_geracao[w];
            w = w + 1; 
        }
    }
}


int vivo_ou_morto(int tipo_de_posicao, int i, int j, int posicoes[10][10]){

    int viveu_ou_morreu;

    switch (tipo_de_posicao){
        case 1:
            if (posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_canto_superior_esquerdo(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_canto_superior_esquerdo(posicoes, i, j);
                return viveu_ou_morreu;
                }
        case 2:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_canto_superior_direito(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_canto_superior_direito(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 3:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_canto_inferior_esquerdo(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_canto_inferior_esquerdo(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 4:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_canto_inferior_direito(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_canto_inferior_direito(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 5:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_primeira_linha(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_primeira_linha(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 6:
            if(posicoes[i][j == 0]){
                viveu_ou_morreu = analisar_se_deve_nascer_ultima_linha(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_ultima_linha(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 7:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_primeira_coluna(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_primeira_coluna(posicoes, i, j);
                return viveu_ou_morreu;
                }
            break;

        case 8:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_ultima_coluna(posicoes, i, j);
                return viveu_ou_morreu;
            }else{
                viveu_ou_morreu = analisar_se_deve_morrer_ultima_coluna(posicoes, i, j);
                return viveu_ou_morreu;
            }
            break;

        case 9:
            if(posicoes[i][j] == 0){
                viveu_ou_morreu = analisar_se_deve_nascer_peca_do_meio(posicoes, i, j);
                return viveu_ou_morreu;
            }else {
                return viveu_ou_morreu = analisar_se_deve_morrer_peca_do_meio(posicoes, i, j);
                return viveu_ou_morreu;
            }

        default:
            printf("ALGO DE ERRADO ACONTECEU");
            break;
        }
}


int verifica_tipo_de_posicao(int i, int j){

    if(i != 0 == j != 0){

        if(i == 0 && j == 9){
            return 2;
        }

        if(i == 9 && j == 0){
            return 3;
        }

        if(i == 9 && j == 9){
            return 4;
        }

        if(i == 0 && (j != 0 && j != 9)){
            return 5;
        }

        if(i == 9 && (j != 0 && j != 9)){
            return 6;
        }
        
        if(j == 0 && (i != 0 && i != 9)){
            return 7;
        }

        if(j == 9 && (i != 0 && i != 9)){
            return 8;
        }

        if(i != 9 && j!= 9){
            return 9;
        }
    }
    return 1;
}


int analisar_se_deve_nascer_canto_superior_esquerdo(int posicoes[10][10], int i, int j){

    if(posicoes[i][j+1] == 1 && posicoes[i+1][j+1] == 1 && posicoes[i+1][j] == 1){
        return 1;
    }
    return 0;
}
    

int analisar_se_deve_morrer_canto_superior_esquerdo(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao < 2 ){
        return 0;
    }
    return 1;
}


int analisar_se_deve_nascer_canto_superior_direito(int posicoes[10][10], int i, int j){

    if(posicoes[i][j-1] == 1 && posicoes[i+1][j-1] == 1 && posicoes[i+1][j] == 1){
        return 1;
    }
    return 0;
}


int analisar_se_deve_morrer_canto_superior_direito(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao < 2){
        return 0;
    }
    return 1;
}


int analisar_se_deve_nascer_canto_inferior_esquerdo(int posicoes[10][10], int i, int j){

    if(posicoes[i-1][j] == 1 && posicoes[i-1][j+1] == 1 && posicoes[i][j+1] == 1){
        return 1;
    }
    return 0;
}


int analisar_se_deve_morrer_canto_inferior_esquerdo(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao < 2){
        return 0;
    }
    return 1;
}


int analisar_se_deve_nascer_canto_inferior_direito(int posicoes[10][10], int i, int j){

    if(posicoes[i][j-1] == 1 && posicoes[i-1][j-1] == 1 && posicoes[i-1][j] == 1){
        return 1;
    }
    return 0;

}


int analisar_se_deve_morrer_canto_inferior_direito(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao < 2){
        return 0;
    }
    return 1;
}


//Funcoes que analisam as linhas incial e final
int analisar_se_deve_nascer_primeira_linha(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 3){
        return 1;
    }
    return 0;
}


int analisar_se_deve_morrer_primeira_linha(int posicoes[10][10], int i, int j){
    
    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 2 || populacao == 3){
        return 1;
    }
    return 0;
}


int analisar_se_deve_nascer_ultima_linha(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 3){
        return 1;
    }
    return 0;

}
int analisar_se_deve_morrer_ultima_linha(int posicoes[10][10], int i, int j){
        
    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 2 || populacao == 3){
        return 1;
    }
    return 0;
}

//Funcoes que analisam as colunas inicial e final
int analisar_se_deve_nascer_primeira_coluna(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;

    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 3){
        return 1;
    }
    return 0;
}

int analisar_se_deve_morrer_primeira_coluna(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;

    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 2 || populacao == 3){
        return 1;
    }
    return 0;
}



int analisar_se_deve_nascer_ultima_coluna(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 3){
        return 1;
    }
    return 0;
}


int analisar_se_deve_morrer_ultima_coluna(int posicoes[10][10], int i, int j){

    int populacao = 0;

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 2 || populacao == 3){
        return 1;
    }
    return 0;
}



//Funcoes que analisam as pecas centrais
int analisar_se_deve_nascer_peca_do_meio(int posicoes[10][10], int i, int j){
    
    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;

    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 3){
        return 1;
    }
    return 0;
}


int analisar_se_deve_morrer_peca_do_meio(int posicoes[10][10], int i, int j){
        
    int populacao = 0;

    if(posicoes[i][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i-1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i][j+1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j-1] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j] == 1){
        populacao = populacao + 1;
    }

    if(posicoes[i+1][j+1] == 1){
        populacao = populacao + 1;
    }

    if(populacao == 2 || populacao == 3){
        return 1;
    }
    return 0;
}
