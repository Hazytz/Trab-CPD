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

void incluirTabela(char *word, int iteration, int code, char *name);

void pesquisa(char *word, int iteration, FILE *dados, char *tabela);
