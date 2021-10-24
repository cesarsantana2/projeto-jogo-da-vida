int verifica_se_a_posicao_estah_contida(int x, int y);

int menu_principal(){

    int opcao;

    printf("\n\nProjeto JOGO  DA  VIDA\n");
    printf("Grupo CCAJ\n");
    printf("=========================\n");
    printf("1 - Inicializar a Matriz\n");
    printf("2 - Salvar uma geracao\n");
    printf("3 - Recuperar uma geracao inicial cadastrada\n");
    printf("4 - INICIAR O PROCESSO\n");
    printf("5 - Exibir ultima geracao da ultima simluacao \n");
    printf("6 - Limpar o cadastro de 7 geracoes iniciais\n");
    printf("0 - Sair\n\n");

    scanf("%d", &opcao);

    return opcao;
}

int menu_fluxo_de_geracoes(){

    int opcao;

    printf("\n\nSelecione uma Opcao:\n\n");

    printf("1 - Adicionar vida em uma posicao\n");
    printf("2 - Remover vida de uma posicao\n");
    printf("3 - Iniciar Simulacao de Geracoes\n");
    printf("0 - Voltar para o menu principal\n\n");

    scanf("%d", &opcao);

    return opcao;
}

int menu_de_fim_de_jogo(){

    int opcao;

    printf("\n\nFIM DA SIMULACAO\n\n");
    
    printf("Selecione uma opcao para prosseguir:\n\n");

    printf("1 - Voltar para o inicio da simulacao\n");
    printf("2 - Comecar novo jogo\n");
    printf("3 - Carregar estrutura pre construida\n");
    printf("0 - Sair\n");

    scanf("%d", &opcao);

    return opcao;
}

void exibir_mundo(int tam){

    int i, j, z, w;
    int cont = tam;


    printf("\n\nMUNDO ATUAL\n\n");

    for(z = 0; z < cont; z++){
        if(z == 0){
            printf("   %d ", z);
       }else if(z == cont -1){
            printf("%d\n", z);     
       }else if(z >= 10){
            printf("%d ", z);
       }else{
            printf(" %d ", z);
       }
    }

    for (i = 0; i < cont; i++){
        printf("%d ", i);
        for (j = 0; j < cont; j++){

            if(verifica_se_a_posicao_estah_contida(i, j)){
               (i < 10 && j == 0) ? printf(" *  ") : printf("*  ");
            }else{
               (i < 10 && j ==0) ? printf(" -  ") : printf("-  ");
            }
        }
        printf("\n");
    }    
}
