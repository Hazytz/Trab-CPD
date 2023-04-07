#include "tabela.h"


void incluirTabela(char *word, int iteration, int code)
{
    FILE *tabela_1;
    int len = strlen(word), cod, s = 0;
    if(iteration < len)
    {
        for(auto i = 0; i < 26; i++)
        {
            if(word[iteration] == 65+i || word[iteration] == 97+i)
            {
                tabela_1 = fopen("search_file.bin", "rb");
                while(fread(&cod, sizeof(int), 1, tabela_1))
                {
                    if(cod == code)
                        s = 1;
                }
                fclose(tabela_1);
                if(s == 0)
                {
                    tabela_1 = fopen("search_file.bin", "ab");
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
                        incluirTabela(word, iteration+1, code);
                        chdir("..");
                        return;
                    }
                    chdir(dirnam);
                    incluirTabela(word, iteration+1, code);
                    chdir("..");
                }
                return;
            }
        }
    }

    tabela_1 = fopen("search_file.bin", "ab");

    fwrite(&code, sizeof(int), 1, tabela_1);
    fclose(tabela_1);

    return;


}

void pesquisa(char *word, int iteration, FILE *dados)
{
    int len = strlen(word);
    if(iteration < len)
    {
        for(auto i = 0; i < 26; i++)
        {
            if(word[iteration] == 65+i || word[iteration] == 97+i)
            {
                struct stat st = {0};
                char dirnam[3] = "./";
                char dirletter = 65+i;
                strncat(dirnam,  &dirletter, 1);
                if(!stat(dirnam, &st))
                {
                    chdir(dirnam);
                    pesquisa(word, iteration+1, dados);
                    chdir("..");
                    return;
                }
            }
        }
        if(word[iteration] != '\n')
        {
            printf("Nenhum resultado encontrado\n");
            return;
        }
    }

    FILE *tabela;
    int code;
    tabela = fopen("search_file.bin","rb");

    info tmp;

    while(fread(&code, sizeof(int), 1, tabela))
    {
        fseek(dados, code*sizeof(info), SEEK_SET);
        fread(&tmp, sizeof(info), 1, dados);
        printf("%s, %s, %s, %s, %f, %f\n", tmp.alimento, tmp.pais, tmp.tipoVenda, tmp.mercado, tmp.pos_pandemia, tmp.anual);
    }
    fclose(tabela);

}


