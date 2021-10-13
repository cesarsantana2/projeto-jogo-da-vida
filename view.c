void mostraMundo(int posicoes[10][10]){
 int i, j;
 
    for(i = 0; i < 11; i++){
        if (i == 0){
            printf("  ");
            for (j = 0; j < 10; j++){
                if(j != 9){
                    printf("%d ", j);
                } else{
                    printf("%d\n", j);
                }
            }
        }else{
            printf("%d ", (i-1));
            for (j = 0; j < 10; j++){
                if(j != 9){
                    (posicoes[i-1][j] == 0 ? printf("  ") : printf("* ")); 
                } else{
                    (posicoes[i-1][j] == 0 ? printf(" ") : printf("*")); 
                    printf("\n");
                }
            }
        }
    }
}
