#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<unordered_map>
#include<bits/stdc++.h>
#include<map>
#include<chrono>

// Struct para cada informação para pesquisa
struct info_t
{
    int n;
    char alimento[50];
    char tipoVenda[20];
    char pais[20];
    char mercado[20];
    float anual;
    float pos_pandemia;
};
typedef struct info_t info;

int main()
{
    info tmp;

    FILE *entrada, *saida;

    setlocale(LC_ALL,"");

    char linha[500], *palavra, *ptr;

    // Abrir os arquivos
    entrada = fopen("dom_change_percent.csv", "r");
    saida = fopen("search_file.bin", "wb");
    if (entrada == NULL) //se n�o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo dom_change_percent.csv");
        return -1;
    }
    if (saida == NULL) //se n�o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo search_file.bin");
        return -1;
    }

    // Leitura dos dados
    while (fgets(linha,100,entrada))
    {
        palavra = strtok(linha, ",");
        tmp.n = strtol(palavra, &ptr, 10);
        for(auto i = 0; i < 5;i++)
        {
            switch (i)
            {
                case 0:
                    palavra = strtok(NULL, ",");
                    strcpy(tmp.pais,palavra);
                    break;
                case 1:
                    palavra = strtok(NULL, ",");
                    strcpy(tmp.tipoVenda,palavra);
                    break;
                case 2:
                    palavra = strtok(NULL, ",");
                    strcpy(tmp.mercado,palavra);
                    break;
                case 3:
                    palavra = strtok(NULL, ",");
                    strcpy(tmp.alimento,palavra);
                    break;
                case 4:
                    palavra = strtok(NULL, ",");
                    tmp.pos_pandemia = strtof(palavra, &ptr);
            }
        }
        palavra = strtok(NULL, ",");
        tmp.anual = strtof(palavra, &ptr);
        fwrite(&tmp, sizeof(info), 1, saida);
    }
    fclose(entrada);
    fclose(saida);


    // Teste para ver se os dados foram salvos no arquivo binario
    saida = fopen("search_file.bin", "rb");

    while(fread(&tmp, sizeof(info), 1, saida))
    {
        printf("%d, %s, %s, %s, %s, %f, %f\n", tmp.n, tmp.pais, tmp.tipoVenda, tmp.mercado, tmp.alimento, tmp.pos_pandemia, tmp.anual);
    }


    return 0;
}
