#include "tabela.h"


void incluirTabela(char *word, int iteration, int code, char *name)
{
    FILE *tabela_1;
    int len = strlen(word), cod, s = 0;
    if(iteration < len)
    {
        for(auto i = 0; i < 26; i++)
        {
            if(word[iteration] == 65+i || word[iteration] == 97+i)
            {
                tabela_1 = fopen(name, "rb");
                while(fread(&cod, sizeof(int), 1, tabela_1))
                {
                    if(cod == code)
                        s = 1;
                }
                fclose(tabela_1);
                if(s == 0)
                {
                    tabela_1 = fopen(name, "ab");
                    fwrite(&code, sizeof(int), 1, tabela_1);
                    fclose(tabela_1);
                    struct stat st = {0};
                    char dirnam[3] = "./";
                    char dirletter = 65+i;
                    strncat(dirnam,  &dirletter, 1);
                    if(stat(dirnam, &st) == -1)
                    {
                        mkdir(dirnam);
                        chdir(dirnam);
                        incluirTabela(word, iteration+1, code, name);
                        chdir("..");
                        return;
                    }
                    chdir(dirnam);
                    incluirTabela(word, iteration+1, code, name);
                    chdir("..");
                }
                return;
            }
        }
        if(word[iteration] == 32)
        {
            tabela_1 = fopen(name, "rb");
            while(fread(&cod, sizeof(int), 1, tabela_1))
            {
                if(cod == code)
                    s = 1;
            }
            fclose(tabela_1);
            if(s == 0)
            {
                tabela_1 = fopen(name, "ab");
                fwrite(&code, sizeof(int), 1, tabela_1);
                fclose(tabela_1);
                struct stat st = {0};
                char dirnam[] = "./SPACE";
                if(stat(dirnam, &st) == -1)
                {
                    mkdir(dirnam);
                    chdir(dirnam);
                    incluirTabela(word, iteration+1, code, name);
                    chdir("..");
                    return;
                }
                chdir(dirnam);
                incluirTabela(word, iteration+1, code, name);
                chdir("..");
            }
            return;
        }
        else if(word[iteration] == 39)
        {
            tabela_1 = fopen(name, "rb");
            while(fread(&cod, sizeof(int), 1, tabela_1))
            {
                if(cod == code)
                    s = 1;
            }
            fclose(tabela_1);
            if(s == 0)
            {
                tabela_1 = fopen(name, "ab");
                fwrite(&code, sizeof(int), 1, tabela_1);
                fclose(tabela_1);
                struct stat st = {0};
                char dirnam[] = "./'";
                if(stat(dirnam, &st) == -1)
                {
                    mkdir(dirnam);
                    chdir(dirnam);
                    incluirTabela(word, iteration+1, code, name);
                    chdir("..");
                    return;
                }
                chdir(dirnam);
                incluirTabela(word, iteration+1, code, name);
                chdir("..");
            }
            return;
        }
    }

    tabela_1 = fopen(name, "ab");

    fwrite(&code, sizeof(int), 1, tabela_1);
    fclose(tabela_1);

    return;


}

void pesquisa(char *word, int iteration, FILE *dados, char *tabela_n)
{
    int len = strlen(word);
    if(iteration < len)
    {
        for(auto i = 0; i < 26; i++)
        {
            if(word[iteration] == 65+i || word[iteration] == 97+i)
            {
                struct stat st = {0};
                char dirnam[] = "./";
                char dirletter = 65+i;
                strncat(dirnam,  &dirletter, 1);
                if(!stat(dirnam, &st))
                {
                    chdir(dirnam);
                    pesquisa(word, iteration+1, dados, tabela_n);
                    chdir("..");
                    return;
                }
            }
        }
        if(word[iteration] == 32)
        {
            struct stat st = {0};
            char dirnam[] = "./SPACE";
            if(!stat(dirnam, &st))
            {
                chdir(dirnam);
                pesquisa(word, iteration+1, dados, tabela_n);
                chdir("..");
                return;
            }
        }
        else if(word[iteration] == 39)
        {
            struct stat st = {0};
            char dirnam[] = "./'";
            if(!stat(dirnam, &st))
            {
                chdir(dirnam);
                pesquisa(word, iteration+1, dados, tabela_n);
                chdir("..");
                return;
            }
        }
        else if(word[iteration] != '\n')
        {
            printf("Nenhum resultado encontrado\n");
            return;
        }
    }

    FILE *tabela;
    int code;
    tabela = fopen(tabela_n,"rb");

    info tmp;

    char file1[] = "search_file.bin", file2[] = "search_file_pais.bin";

    while(fread(&code, sizeof(int), 1, tabela))
    {
        fseek(dados, code*sizeof(info), SEEK_SET);
        fread(&tmp, sizeof(info), 1, dados);
        if(!strcmp(tabela_n, file1))
            printf("%s, %s, %s, %s, %f, %f\n", tmp.alimento, tmp.pais, tmp.tipoVenda, tmp.mercado, tmp.pos_pandemia, tmp.anual);
        else if(!strcmp(tabela_n, file2))
            printf("%s, %s, %s, %s, %f, %f\n", tmp.pais, tmp.alimento, tmp.tipoVenda, tmp.mercado, tmp.pos_pandemia, tmp.anual);
    }
    fclose(tabela);

}


