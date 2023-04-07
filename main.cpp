#include<iostream>
#include<tuple>
#include<string>
#include<vector>
#include<unordered_map>
#include<bits/stdc++.h>
#include<map>
#include<chrono>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#include "tabela.h"


int main()
{
    info tmp;

    FILE *entrada, *data, *data2;

    setlocale(LC_ALL,"");

    char linha[500], *palavra, *ptr;

    // Abrir os arquivos
    entrada = fopen("dom_change_percent.csv", "r");
    data = fopen("data_file.bin", "wb");
    if (entrada == NULL) //se n�o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo dom_change_percent.csv");
        return -1;
    }
    if (data == NULL) //se n�o conseguiu abrir o arquivo
    {
        printf ("Erro ao abrir o arquivo search_file.bin");
        return -1;
    }

    struct stat st = {0};

    if(stat("search_files", &st) == -1)
        mkdir("search_files");
    chdir("search_files");

    printf("Carregando...");
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
        fwrite(&tmp, sizeof(info), 1, data);
        incluirTabela(tmp.alimento, 0, tmp.n);
    }
    fclose(entrada);
    fclose(data);

    char word[50];
    printf("\rDigite o nome do alimento: ");
    fgets(word, sizeof(word), stdin);
    printf("\r");
    chdir("..");
    data2 = fopen("data_file.bin", "rb");
    chdir("search_files");
    pesquisa(word, 0, data2);
    return 0;
}
