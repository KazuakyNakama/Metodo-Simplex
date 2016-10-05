#include <stdio.h>
#include <string.h>
#include <math.h>

/* Pesquisa Operacional - Trabalho 2
 * Luiz Fernando Kazuaky Nakama
 * Caio Cesar Lopes Teles de Menezes
 * Victor Almeida Chagas
 * 04/06/2016
 */

 float typedef tipo_dados;

 typedef struct{
    tipo_dados termo;
    char tipo[3];
    tipo_dados coeficiente[20];
 } restricao;

  typedef struct{
    int variaveis;
    int restricoes;
    int maxmin;
    tipo_dados objetivo[40];
    restricao r[40];
 } dados;
dados d;

void leitura_dados();
void passa_matriz(char);
void metodo_simplex(float [][*]);
void metodo_simplex_arquivo(float [][*]);
void instrucao();
void staff();

int main()
{
    char op;
    unsigned short int ibirapuera = 13;
    do{
        system("cls");
        printf("\n|===============================================|\n");
        printf("|  \t\t  METODO SIMPLEX\t\t|");
        printf("\n|===============================================|\n");
        printf("|\t<1> - Leitura de Dados\t\t\t|\n");
        printf("|\t<2> - Metodo Simplex\t\t\t|\n");
        printf("|\t<3> - Metodo Simplex com Arquivo\t|\n");
        printf("|\t<4> - Instrucoes\t\t\t|\n");
        printf("|\t<5> - Staff\t\t\t\t|\n");
        printf("|\t<0> - Sair do programa\t\t\t|");
        printf("\n|===============================================|\n");
        printf("|Selecione Opcao Desejada -> ");
        op = getch();
        if(ibirapuera == 13 && (op == '1' || op == '2' || op == '3')){
            op = '1';
            ibirapuera = 37;
        }
        switch(op){
        case '1': leitura_dados();
            break;
        case '2':
        case '3': passa_matriz(op);
            break;
        case '4': instrucao();
            break;
        case '5': staff();
        case '0':
            break;
        default:
            fprintf(stderr, "Opcao invalida...\n|Pressione qualquer tecla para continuar...\n");
            getch();
        }
    } while(op != '0');
    return 0;
}

void leitura_dados()
{
    int i, j, k, igual = 0;
    system("cls");
    //Caixa do menu
    for(i = 0; i < 75; i++){
        printf("%c", 219);
    }
    printf("%c%c%c%c",219,219,219,219);
    printf("\n%c%c%c%c",219,219,176,176);
    for(i = 0; i < 73; i++){
        printf("%c", 176);
    }
    printf("%c%c",219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\tLEITURA DE DADOS\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c\n",219,219,176,176,176,176,219,219);
    printf("%c%c",219,219);
    for(i = 0; i < 75; i++){
        printf("%c", 176);
    }
    printf("%c%c", 219,219);
    printf("\n");
    printf("%c%c", 219,219);
    for(i = 0; i < 77; i++){
        printf("%c", 219);
    }

    //Armazena os dados em uma estrutura dados
    printf("\n\n\nMinimizacao[0] - Maximizacao[1]: ");
    scanf("%d", &d.maxmin);
    while(d.maxmin < 0 || d.maxmin > 1){
        fprintf(stderr, "Valor invalido! Digite novamente: ");
        scanf("%d", &d.maxmin);
    }
    printf("\n\nQuantidade de variaveis (maximo 20): ");
    scanf("%d", &d.variaveis);
    while(d.variaveis > 20 || d.variaveis < 1){
        printf("Valor invalido! Digite novamente: ");
        scanf("%d", &d.variaveis);
    }

    printf("Quantidade de restricoes (maximo 20): ");
    scanf("%d", &d.restricoes);
    while(d.restricoes > 20 || d.restricoes < 1){
        printf("Valor invalido! Digite novamente: ");
        scanf("%d", &d.restricoes);
    }
    printf("\nFuncao Objetivo\n");
    for(i = 0; i < d.variaveis; i++){
        printf("Coeficiente da variavel x%d: ",i);
        scanf("%f", &d.objetivo[i]);
        if(d.maxmin == 1){
            d.objetivo[i] *= -1;
        }
    }

    for(i = 0; i < d.restricoes; i++){
        printf("\nRestricao %d:\n", i + 1);
        for(j = 0; j < d.variaveis; j++){
            printf("Coeficiente da variavel x%d: ", j);
            scanf("%f", &d.r[i + igual].coeficiente[j]);
        }
        printf("Tipo de Restricao: ");
        scanf("%2s", &d.r[i + igual].tipo);
        fflush(stdin);
        printf("Termo independente: ");
        scanf("%f", &d.r[i + igual].termo);
        //Caso o tipo de restrição seja >=, o termo e os coeficientes são multiplicados por -1
        if(d.r[i + igual].tipo[0] == '>'){
            for(k = 0; k < d.variaveis; k++){
                d.r[i + igual].coeficiente[k] *= -1;
            }
            d.r[i + igual].termo *= -1;
        }
        else{
            //Caso o tipo de restrição seja ==, será criada 2 restrições.
            //Uma normal e uma com o termo e os coeficientes multiplicados por -1
            if(d.r[i + igual].tipo[0] == '='){
                igual++;
                for(k = 0; k < d.variaveis; k++){
                    d.r[i + igual].coeficiente[k] = d.r[(i + igual) - 1].coeficiente[k] * -1;
                }
            d.r[i + igual].termo = d.r[(i + igual) - 1].termo * -1;
            }
        }
    }
    d.restricoes += igual;

    printf("\nPressione 0 para retornar ao menu...\n");
    while(getch() != '0');
}

void metodo_simplex(float matriz[][d.variaveis + d.restricoes + 1])
{
    float menor, div, teste, matriz2[d.restricoes + 1][d.variaveis + d.restricoes + 1];
    int i, j, coluna_menor, linha_menor, ok, cont = 0, bambam[d.restricoes];

    //Caixa do menu
    for(i = 0; i < 75; i++){
        printf("%c", 219);
    }
    printf("%c%c%c%c",219,219,219,219);
    printf("\n%c%c%c%c",219,219,176,176);
    for(i = 0; i < 73; i++){
        printf("%c", 176);
    }
    printf("%c%c",219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\tTABELA SIMPLEX\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c\n",219,219,176,176,176,176,219,219);
    printf("%c%c",219,219);
    for(i = 0; i < 75; i++){
        printf("%c", 176);
    }
    printf("%c%c", 219,219);
    printf("\n");
    printf("%c%c", 219,219);
    for(i = 0; i < 77; i++){
        printf("%c", 219);
    }

    for(i = 0; i < d.restricoes; i++){
        bambam[i] = i + d.variaveis;
    }

    //Printa o quadro inicial da tabela simplex
    printf("\n\n\nQuadro inicial\n");
    printf("Base     ");
    for(i = 0; i < d.variaveis + d.restricoes; i++){
        if(i == d.variaveis + d.restricoes - 1){
                printf("x%d    ", i);
        }
        else{
            if(i < 10){
                printf("x%d       ", i);
            }
            else{
                printf("x%d      ", i);
            }
        }
    }
    printf("Solucao\n");
    for(i = 0; i < d.restricoes + 1; i++){
        if(i == 0){
            if(d.maxmin == 1){
                printf("z     ");
            }
            else{
                printf("-z    ");
            }
        }
        else{
            printf("x%d    ", bambam[i - 1]);
        }
        for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
            printf("%7.2f  ", matriz[i][j]);
        }
        printf("\n");
    }

    while(cont >= 0){
        //Verifica se o problema é viável, procurando a linha mais negativa na coluna da solução
        menor = -0.001;
        div = 0;
        for(i = 1; i < d.restricoes + 1; i++){
            if(matriz[i][d.variaveis + d.restricoes] < menor){
                menor = matriz[i][d.variaveis + d.restricoes];
                linha_menor = i;
                div = 1;
            }
        }
        //Acha a razão da coluna da linha menor com a coluna da linha z mais próxima de 0, caso o problema não esteja viável
        if(div == 1){
            menor = 2147483647;
            for(i = 0; i < d.variaveis + d.restricoes; i++){
                if(matriz[linha_menor][i] < 0 && matriz[0][i] != 0){
                    teste = sqrt(powf(matriz[0][i] / matriz[linha_menor][i], 2));
                    if(matriz[0][i] / matriz[linha_menor][i] < menor){
                        menor = teste;
                        coluna_menor = i;
                        div = 1;
                    }
                }
            }
        }

            /*menor = -2147483647;
            for(i = 0; i < d.variaveis + d.restricoes; i++){
                if(matriz[linha_menor][i] < 0 && matriz[0][i] != 0){
                    if(matriz[0][i] / matriz[linha_menor][i] > menor){
                        menor = matriz[0][i] / matriz[linha_menor][i];
                        coluna_menor = i;
                        div = 1;
                    }
                }
            }*/

        //Verifica se o problema está otimizado identificando a coluna mais negativa
        if(div == 0){
            menor = 0;
            for(i = 0; i < d.variaveis + d.restricoes + d.maxmin; i++){
                if(matriz[0][i] < menor){
                    menor = matriz[0][i];
                    coluna_menor = i;
                }
            }
        }
        //Caso não haja números negativos nas colunas da linha da solução, o programa chegou na última interação e sai do laço
        if(menor == 0){
            break;
        }
        //Incrementa o contador, indicando o número da interação
        cont++;

        //Acha a linha do menor resultado da divisão dos termos independentes pelas linhas da coluna mais negativa
        if(div == 0){
            menor = 2147483647;
            for(i = 1; i < d.restricoes + 1; i++){
                div = matriz[i][d.variaveis + d.restricoes] / matriz[i][coluna_menor];
                if(div < menor && div > 0){
                    menor = div;
                    linha_menor = i;
                }
            }
        }

        //Coloca os elementos da linha menor divididos pelo pivô na matriz nova
        for(i = 0; i < d.variaveis + d.restricoes + 1; i++){
            matriz2[linha_menor][i] = matriz[linha_menor][i] / matriz[linha_menor][coluna_menor];
        }

        //Insere o elemento da matriz subtraído pelo elemento da coluna menor
        //multiplicado pela linha menor da matriz na nova matriz
        for(i = 0; i < d.restricoes + 1; i++){
            if(i != linha_menor){
                for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                    matriz2[i][j] = matriz[i][j] - (matriz[i][coluna_menor] * matriz2[linha_menor][j]);
                }
            }
        }

        //Matriz antiga recebe a matriz nova, para poder repetir o processo até chegar na solução
        for(i = 0; i < d.restricoes + 1; i++){
            for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                matriz[i][j] = matriz2[i][j];
            }
        }

        //Atualiza o vetor indicando quem entra e quem sai
        for(i = 0; i < d.restricoes; i++){
            if(i == linha_menor - 1){
                ok = bambam[i];
                bambam[i] = coluna_menor;
            }
        }

        printf("\nInteracao %d: entra x%d, sai x%d\n", cont, coluna_menor, ok);
        printf("Base     ");
        for(i = 0; i < d.variaveis + d.restricoes; i++){
            if(i == d.variaveis + d.restricoes - 1){
                printf("x%d    ", i);
            }
            else{
                if(i < 10){
                    printf("x%d       ", i);
                }
                else{
                    printf("x%d      ", i);
                }
            }
        }
        printf("Solucao\n");
        for(i = 0; i < d.restricoes + 1; i++){
            if(i == 0){
                if(d.maxmin == 1){
                    printf("z     ");
                }
                else{
                    printf("-z    ");
                }
            }
            else{
                if(bambam[i - 1] < 10){
                    printf("x%d    ", bambam[i - 1]);
                }
                else{
                    printf("x%d   ", bambam[i - 1]);
                }
            }
            for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                printf("%7.2f  ", matriz[i][j]);
            }
            printf("\n");
        }
    }

    printf("\nSolucao: %.2f\n", matriz[0][d.variaveis + d.restricoes]);
    //Printa o valor das variaveis para solução
    //linha_menor e coluna_menor foram reutilizados para economizar memória
    ok = -1;
    for(i = 0; i < d.variaveis; i++){
        coluna_menor = 2147483647;
        for(j = 0; j < d.restricoes; j++){
            if(bambam[j] < d.variaveis && bambam[j] < coluna_menor && bambam[j] > ok){
                coluna_menor = bambam[j];
                linha_menor = j;
            }
        }
        if(bambam[linha_menor] < d.variaveis && bambam[linha_menor] > ok){
            printf("x%d: %.2f\n", bambam[linha_menor], matriz[linha_menor + 1][d.variaveis + d.restricoes]);
        }
        ok = bambam[linha_menor];
    }

    printf("\nPressione 0 para retornar ao menu...\n");
    while(getch() != '0');
}

void metodo_simplex_arquivo(float matriz[][d.variaveis + d.restricoes + 1])
{
    float menor, div, teste, matriz2[d.restricoes + 1][d.variaveis + d.restricoes + 1];
    int i, j, coluna_menor, linha_menor, ok, cont = 0, bambam[d.restricoes];
    char nome[35];
    FILE *fp;

    printf("Nome do arquivo (MAX 30 CHARS): ");
    scanf("%30s", nome);
    strcat(nome, ".txt\0");

    fp = fopen (nome, "w");
    if(fp == NULL){
       fprintf (stderr, "Houve um erro ao abrir o arquivo.\n");
       return;
    }

    for(i = 0; i < d.restricoes; i++){
        bambam[i] = i + d.variaveis;
    }

    fprintf(fp, "TABELA SIMPLEX");

    //Printa o quadro inicial da tabela simplex
    fprintf(fp, "\n\nQuadro inicial\n");
    fprintf(fp, "Base     ");
    for(i = 0; i < d.variaveis + d.restricoes; i++){
        if(i == d.variaveis + d.restricoes - 1){
            fprintf(fp, "x%d    ", i);
        }
        else{
            if(i < 10){
                fprintf(fp, "x%d       ", i);
            }
            else{
                fprintf(fp, "x%d      ", i);
            }
        }
    }
    fprintf(fp, "Solucao\n");
    for(i = 0; i < d.restricoes + 1; i++){
        if(i == 0){
            if(d.maxmin == 1){
                fprintf(fp, "z     ");
            }
            else{
                fprintf(fp, "-z    ");
            }
        }
        else{
            if(bambam[i - 1] < 10){
                fprintf(fp, "x%d    ", bambam[i - 1]);
            }
            else{
                fprintf(fp, "x%d   ", bambam[i - 1]);
            }
        }
        for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
            fprintf(fp, "%7.2f  ", matriz[i][j]);
        }
        fprintf(fp, "\n");
    }

    while(cont >= 0){
        //Verifica se o problema é viável, procurando a linha mais negativa na coluna da solução
        menor = -0.001;
        div = 0;
        for(i = 1; i < d.restricoes + 1; i++){
            if(matriz[i][d.variaveis + d.restricoes] < menor){
                menor = matriz[i][d.variaveis + d.restricoes];
                linha_menor = i;
                div = 1;
            }
        }
        //Acha a razão da coluna da linha menor com a coluna da linha z mais próxima de 0, caso o problema não esteja viável
        if(div == 1){
            menor = 2147483647;
            for(i = 0; i < d.variaveis + d.restricoes; i++){
                if(matriz[linha_menor][i] < 0 && matriz[0][i] != 0){
                    teste = sqrt(powf(matriz[0][i] / matriz[linha_menor][i], 2));
                    if(matriz[0][i] / matriz[linha_menor][i] < menor){
                        menor = teste;
                        coluna_menor = i;
                        div = 1;
                    }
                }
            }
        }

        //Verifica se o problema está otimizado identificando a coluna mais negativa
        if(div == 0){
            menor = 0;
            for(i = 0; i < d.variaveis + d.restricoes + d.maxmin; i++){
                if(matriz[0][i] < menor){
                    menor = matriz[0][i];
                    coluna_menor = i;
                }
            }
        }
        //Caso não haja números negativos nas colunas da linha da solução, o programa chegou na última interação e sai do laço
        if(menor == 0){
            break;
        }
        //Incrementa o contador, indicando o número da interação
        cont++;

        //Acha a linha do menor resultado da divisão dos termos independentes pelas linhas da coluna mais negativa
        if(div == 0){
            menor = 2147483647;
            for(i = 1; i < d.restricoes + 1; i++){
                div = matriz[i][d.variaveis + d.restricoes] / matriz[i][coluna_menor];
                if(div < menor && div > 0){
                    menor = div;
                    linha_menor = i;
                }
            }
        }

        //Coloca os elementos da linha menor divididos pelo pivô na matriz nova
        for(i = 0; i < d.variaveis + d.restricoes + 1; i++){
            matriz2[linha_menor][i] = matriz[linha_menor][i] / matriz[linha_menor][coluna_menor];
        }

        //Insere o elemento da matriz subtraído pelo elemento da coluna menor
        //multiplicado pela linha menor da matriz na nova matriz
        for(i = 0; i < d.restricoes + 1; i++){
            if(i != linha_menor){
                for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                    matriz2[i][j] = matriz[i][j] - (matriz[i][coluna_menor] * matriz2[linha_menor][j]);
                }
            }
        }

        //Matriz antiga recebe a matriz nova, para poder repetir o processo até chegar na solução
        for(i = 0; i < d.restricoes + 1; i++){
            for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                matriz[i][j] = matriz2[i][j];
            }
        }

        //Atualiza o vetor indicando quem entra e quem sai
        for(i = 0; i < d.restricoes; i++){
            if(i == linha_menor - 1){
                ok = bambam[i];
                bambam[i] = coluna_menor;
            }
        }

        fprintf(fp, "\nInteracao %d: entra x%d, sai x%d\n", cont, coluna_menor, ok);
        fprintf(fp, "Base     ");
        for(i = 0; i < d.variaveis + d.restricoes; i++){
            if(i == d.variaveis + d.restricoes - 1){
                fprintf(fp, "x%d    ", i);
            }
            else{
                if(i < 10){
                    fprintf(fp, "x%d       ", i);
                }
                else{
                    fprintf(fp, "x%d      ", i);
                }
            }
        }
        fprintf(fp, "Solucao\n");
        for(i = 0; i < d.restricoes + 1; i++){
            if(i == 0){
                if(d.maxmin == 1){
                    fprintf(fp, "z     ");
                }
                else{
                    fprintf(fp, "-z    ");
                }
            }
            else{
                if(bambam[i - 1] < 10){
                    fprintf(fp, "x%d    ", bambam[i - 1]);
                }
                else{
                    fprintf(fp, "x%d   ", bambam[i - 1]);
                }
            }
            for(j = 0; j < d.variaveis + d.restricoes + 1; j++){
                fprintf(fp, "%7.2f  ", matriz[i][j]);
            }
            fprintf(fp, "\n");
        }
    }

    fprintf(fp, "\nSolucao: %.2f\n", matriz[0][d.variaveis + d.restricoes]);
    //Printa o valor das variaveis para solução
    //linha_menor e coluna_menor foram reutilizados para economizar memória
    ok = -1;
    for(i = 0; i < d.variaveis; i++){
        coluna_menor = 2147483647;
        for(j = 0; j < d.restricoes; j++){
            if(bambam[j] < d.variaveis && bambam[j] < coluna_menor && bambam[j] > ok){
                coluna_menor = bambam[j];
                linha_menor = j;
            }
        }
        if(bambam[linha_menor] < d.variaveis && bambam[linha_menor] > ok){
            fprintf(fp, "x%d: %.2f\n", bambam[linha_menor], matriz[linha_menor + 1][d.variaveis + d.restricoes]);
        }
        ok = bambam[linha_menor];
    }

    fclose(fp);
    printf("Arquivo gerado com sucesso!\n\n");
    printf("Pressione 0 para retornar ao menu...\n");
    while(getch() != '0'){
    }
}

void passa_matriz(char op)
{
    float matriz[d.restricoes + 1][d.variaveis + d.restricoes + 1];
    int i, j, k, z = 1;
    system("cls");

    //Passa os dados para a matriz
    for(i = 0; i < d.restricoes + 1; i++){
        if(i == 0){
            for(j = 0; j < d.variaveis; j++){
                matriz[i][j] = d.objetivo[j];
            }
            for(k = 0; k < d.restricoes + 1; k++){
                matriz[i][j++] = 0;
            }
        }
        else{
            for(j = 0; j < d.variaveis; j++){
                matriz[i][j] = d.r[i - 1].coeficiente[j];
            }
            for(k = 0; k < d.restricoes; k++){
                if(i == z && k + 1 == z){
                    matriz[i][j++] = 1;
                    z++;
                }
                else{
                    matriz[i][j++] = 0;
                }
            }
            matriz[i][j] = d.r[i - 1].termo;
        }
    }

    switch(op){
    case '2': metodo_simplex(matriz);
        break;
    case '3': metodo_simplex_arquivo(matriz);
    }
}

void instrucao()
{
    int i;
    system("cls");
    //Caixa do menu
    for(i = 0; i < 75; i++){
        printf("%c", 219);
    }
    printf("%c%c%c%c",219,219,219,219);
    printf("\n%c%c%c%c",219,219,176,176);
    for(i = 0; i < 73; i++){
        printf("%c", 176);
    }
    printf("%c%c",219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t   INSTRUCOES\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c\n",219,219,176,176,176,176,219,219);
    printf("%c%c",219,219);
    for(i = 0; i < 75; i++){
        printf("%c", 176);
    }
    printf("%c%c", 219,219);
    printf("\n");
    printf("%c%c", 219,219);
    for(i = 0; i < 77; i++){
        printf("%c", 219);
    }
    printf("\n\n\nAntes de selecionar qualquer opcao, o usuario devera entrar com os dados\n");
    printf("do problema. Portanto, mesmo que o usuario entre primeiramente com alguma\n");
    printf("operacao, FORCAREMOS A LEITURA DE DADOS.\n");
    printf("\n\nMetodo simplex:\n");
    printf("Na opcao metodo simplex voce entrara com os dados do problema e o programa\n");
    printf("te dara todas as interacoes do metodo simplex e no final dara a solucao e\n");
    printf("o valor das variaveis.\n");
    printf("Recomendamos essa opcao para quantidades de variaveis e restricoes menores,\n");
    printf("que provavelmente caibam na tela.\n");
    printf("\n\nMetodo simplex com arquivo:\n");
    printf("A opcao metodo simplex com arquivo e basicamente a mesma coisa da opcao\n");
    printf("anterior. A diferenca e que ao inves de mostrar as interacoes, solucao e\n");
    printf("valor das variaveis na tela, o programa criara um arquivo com tudo isso,\n");
    printf("na pasta onde o codigo fonte estiver salvo.\n");
    printf("Recomendamos essa opcao para quantidades de variaveis e restricoes muito\n");
    printf("grandes que provavelmente nao caberiam na tela.\n");
    printf("\n\nPressione 0 para retornar ao menu...\n");
    while(getch() != '0');
}

void staff()
{
    int i;
    system("cls");
    //Caixa do menu
    for(i = 0; i < 75; i++){
        printf("%c", 219);
    }
    printf("%c%c%c%c",219,219,219,219);
    printf("\n%c%c%c%c",219,219,176,176);
    for(i = 0; i < 73; i++){
        printf("%c", 176);
    }
    printf("%c%c",219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t    STAFF\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c",219,219,176,176,176,176,219,219);
    printf("\n%c%c%c%c\t\t\t\t\t\t\t\t\t   %c%c%c%c\n",219,219,176,176,176,176,219,219);
    printf("%c%c",219,219);
    for(i = 0; i < 75; i++){
        printf("%c", 176);
    }
    printf("%c%c", 219,219);
    printf("\n");
    printf("%c%c", 219,219);
    for(i = 0; i < 77; i++){
        printf("%c", 219);
    }
    printf("\n\n\n\t%c Luiz Fernando Kazuaky Nakama (Ciencias da Computacao)\n\n", 16);
    printf("\n\n\t%c Caio Cesar Lopes Teles de Menezes (Ciencias da Computacao)\n\n", 16);
    printf("\n\n\t%c Victor Almeida Chagas (Ciencias da Computacao)\n\n", 16);
    printf("\nPressione 0 para retornar ao menu...\n");
    while(getch() != '0');
}
