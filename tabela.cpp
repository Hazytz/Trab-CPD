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

void pesquisa(char *word, int iteration, FILE *dados, char *tabela_n, int code_switch, int order)
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
                    pesquisa(word, iteration+1, dados, tabela_n, code_switch, order);
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
                pesquisa(word, iteration+1, dados, tabela_n, code_switch, order);
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
                pesquisa(word, iteration+1, dados, tabela_n, code_switch, order);
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
    orderedPrint(dados, tabela_n, code_switch, order);
}

void alterarDado(int code, char *name)
{
    FILE *dados;
    info tmp;
    dados = fopen(name,"rb+");
    fseek(dados, code*sizeof(info), SEEK_SET);
    if(fread(&tmp, sizeof(info), 1, dados))
    {
        fseek(dados, code*sizeof(info), SEEK_SET);
        printf("%s, %s, %s, %s, ", tmp.alimento, tmp.pais, tmp.tipoVenda, tmp.mercado);
        scanf("%f, %f", &tmp.pos_pandemia, &tmp.anual);
        fwrite(&tmp, sizeof(info), 1, dados);
    }
    else
    {
        printf("Nenhum resultado encontrado");
        getch();
    }
    fclose(dados);
}

void orderedPrint(FILE *dados, char *tabela_n, int code_switch, int order)
{
    char file1[] = "search_file.bin", file2[] = "search_file_pais.bin";
    FILE *tabela;
    tabela = fopen(tabela_n,"rb");
    int code, i = 0;
    while(fread(&code, sizeof(int), 1, tabela))
    {
        i++;
    }
    info entries[i], aux;
    fseek(tabela, 0, SEEK_SET);
    for(auto j = 0; j < i; j++)
    {
        fread(&code, sizeof(int), 1, tabela);
        fseek(dados, code*sizeof(info), SEEK_SET);
        fread(&entries[j], sizeof(info), 1, dados);
    }
    int ordered = 0;

    while(ordered == 0)
    {
        ordered = 1;
        for(auto k = 0; k < i-1; k++)
        {
            if(!strcmp(tabela_n, file1) && (strcmpi(entries[k].alimento,entries[k+1].alimento) > 0))
            {
                aux = entries[k];
                entries[k] = entries[k+1];
                entries[k+1] = aux;
                ordered = 0;
            }
            else if(!strcmp(tabela_n, file2) && (strcmpi(entries[k].pais,entries[k+1].pais) > 0))
            {
                aux = entries[k];
                entries[k] = entries[k+1];
                entries[k+1] = aux;
                ordered = 0;
            }
        }
    }

    if(order == 0)
    {
        for(auto k = 0; k < i; k++)
        {
            if(!strcmp(tabela_n, file1))
                printf("%s, %s, %s, %s, %f, %f", entries[k].alimento, entries[k].pais, entries[k].tipoVenda, entries[k].mercado, entries[k].pos_pandemia, entries[k].anual);
            else if(!strcmp(tabela_n, file2))
                printf("%s, %s, %s, %s, %f, %f", entries[k].pais, entries[k].alimento, entries[k].tipoVenda, entries[k].mercado, entries[k].pos_pandemia, entries[k].anual);
            if(code_switch == 1)
                printf(", %d\n", entries[k].n);
            else
                printf("\n");
        }
    }
    else
    {
        for(auto k = i-1; k >= 0; k--)
        {
            if(!strcmp(tabela_n, file1))
                printf("%s, %s, %s, %s, %f, %f", entries[k].alimento, entries[k].pais, entries[k].tipoVenda, entries[k].mercado, entries[k].pos_pandemia, entries[k].anual);
            else if(!strcmp(tabela_n, file2))
                printf("%s, %s, %s, %s, %f, %f", entries[k].pais, entries[k].alimento, entries[k].tipoVenda, entries[k].mercado, entries[k].pos_pandemia, entries[k].anual);
            if(code_switch == 1)
                printf(", %d\n", entries[k].n);
            else
                printf("\n");
        }
    }

}
