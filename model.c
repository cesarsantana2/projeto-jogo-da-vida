typedef struct{

    int linha, coluna, valor;
    
} Celula;

typedef struct{

    int cont;
    Celula pos[500];

} Tlista;              

Tlista pecas_vivas;
Tlista vizinhos_mortos;
Tlista pecas_vivas_proxima_geracao;
Tlista vizinhos_mortos_proxima_geracao;