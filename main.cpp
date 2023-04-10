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
#include<conio.h>
#include<filesystem>

#include "tabela.h"

int main()
{
    info tmp;

    FILE *entrada, *data, *data2, *n;

    n = fopen("entries_n.bin", "rb");

    int entries_n;


    if(!fread(&entries_n, sizeof(int), 1, n))
        entries_n = 0;

    fclose(n);

    std::string inputPath = "./search_files";
    const std::filesystem::path path = inputPath;

    setlocale(LC_ALL,"");

    char linha[500], *palavra, *ptr;

    int menu, code_switch = 0, code, order = 0;

    char word[50], filename1[] = "search_file.bin", filename2[] = "search_file_pais.bin", filename3[] = "data_file.bin", filename4[20];

    while(1)
    {
        system ("cls");
        printf("Pressione uma das seguintes teclas:\n1 - Inicializar/Reset\n2 - Pesquisa por nome de alimento\n3 - Pesquisa por pais\n4 - Adicionar dado\n5 - Alterar Dado");
        if(code_switch == 0)
            printf("\n6 - Exibir codigo dos dados");
        else
            printf("\n6 - Parar de exibir codigo dos dados");
        if(order == 0)
            printf("\n7 - Mudar para ordem alfabetica inversa");
        else
            printf("\n7 - Mudar para ordem alfabetica");
        printf("\n8 - Carregar um arquivo");
        menu = getch() - '0';
        system ("cls");
        switch (menu)
        {
        //Reset
        case 1:
            printf("Carregando...");
            unlink("data_file.bin");
            remove_all(path);
            // Abrir os arquivos
            entrada = fopen("dom_change_percent.csv", "r");
            data = fopen("data_file.bin", "wb");
            // Leitura dos dados
            entries_n = 0;
            mkdir("search_files");
            chdir("search_files");
            while (fgets(linha,100,entrada))
            {
                palavra = strtok(linha, ",");
                tmp.n = entries_n;
                for(auto i = 0; i < 5; i++)
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
                incluirTabela(tmp.alimento, 0, tmp.n, filename1);
                incluirTabela(tmp.pais, 0, tmp.n, filename2);
                entries_n++;
            }
            fclose(entrada);
            fclose(data);
            chdir("..");
            n = fopen("entries_n.bin", "wb");
            fwrite(&entries_n, sizeof(int), 1, n);
            fclose(n);
            break;
        //Pesquisar por alimento
        case 2:
            fflush(stdin);
            printf("Digite o nome do alimento: ");
            fgets(word, sizeof(word), stdin);
            system ("cls");
            data2 = fopen("data_file.bin", "rb");
            chdir("search_files");
            pesquisa(word, 0, data2,filename1, code_switch, order);
            fclose(data2);
            getch();
            chdir("..");
            break;
        //Pesquisar por pais
        case 3:
            fflush(stdin);
            printf("Digite o nome do pais: ");
            fgets(word, sizeof(word), stdin);
            system ("cls");
            data2 = fopen("data_file.bin", "rb");
            chdir("search_files");
            pesquisa(word, 0, data2,filename2, code_switch, order);
            fclose(data2);
            getch();
            chdir("..");
            break;
        //Incluir dados novos
        case 4:
            fflush(stdin);
            tmp.n = entries_n;
            printf("Digite o pais: ");
            fgets(tmp.pais, 20*sizeof(char), stdin);
            tmp.pais[strcspn(tmp.pais, "\n")] = 0;
            fflush(stdin);
            printf("Digite o tipo de venda: ");
            fgets(tmp.tipoVenda, 20*sizeof(char), stdin);
            tmp.tipoVenda[strcspn(tmp.tipoVenda, "\n")] = 0;
            fflush(stdin);
            printf("Digite o mercado ou se eh media nacional: ");
            fgets(tmp.mercado, 20*sizeof(char), stdin);
            tmp.mercado[strcspn(tmp.mercado, "\n")] = 0;
            fflush(stdin);
            printf("Digite o nome do alimento: ");
            fgets(tmp.alimento, 20*sizeof(char), stdin);
            tmp.alimento[strcspn(tmp.alimento, "\n")] = 0;
            fflush(stdin);
            printf("Digite a mudanca de preco apos a pandemia: ");
            scanf("%f", &tmp.pos_pandemia);
            fflush(stdin);
            printf("Digite a media das mudancas de preco anuais anteriores: ");
            scanf("%f", &tmp.anual);
            data = fopen("data_file.bin", "ab");
            fwrite(&tmp, sizeof(info), 1, data);
            fclose(data);
            chdir("search_files");
            incluirTabela(tmp.alimento, 0, tmp.n, filename1);
            incluirTabela(tmp.pais, 0, tmp.n, filename2);
            chdir("..");
            entries_n++;
            n = fopen("entries_n.bin", "wb");
            fwrite(&entries_n, sizeof(int), 1, n);
            fclose(n);
            system ("cls");
            break;
        //Alterar dados
        case 5:
            printf("Digite o codigo do dado a ser alterado: ");
            scanf("%d", &code);
            alterarDado(code, filename3);
            break;
        //Mostrar codigo identificador da entrada
        case 6:
            if(code_switch == 0)
                code_switch = 1;
            else
                code_switch = 0;
            break;
        //Mudar ordem
        case 7:
            if(order == 0)
                order = 1;
            else
                order = 0;
            break;
        //Carregar arquivo
        case 8:
            //Input do usuario
            printf("Digite o nome do arquivo(inclua o tipo ex.: .csv, .txt): ");
            fgets(filename4, 20*sizeof(char), stdin);
            filename4[strcspn(filename4, "\n")] = 0;
            system ("cls");

            printf("Carregando...");
            // Abrir os arquivos
            entrada = fopen(filename4, "r");
            data = fopen("data_file.bin", "ab");
            chdir("search_files");
            // Leitura dos dados
            while (fgets(linha,100,entrada))
            {
                palavra = strtok(linha, ",");
                tmp.n = entries_n;
                for(auto i = 0; i < 5; i++)
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
                incluirTabela(tmp.alimento, 0, tmp.n, filename1);
                incluirTabela(tmp.pais, 0, tmp.n, filename2);
                entries_n++;
            }
            fclose(entrada);
            fclose(data);
            chdir("..");
            n = fopen("entries_n.bin", "wb");
            fwrite(&entries_n, sizeof(int), 1, n);
            fclose(n);
            break;
        }
    }
}
