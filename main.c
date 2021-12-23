#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

//Struct de login
typedef struct{
    char login[30];
    char senha[30];
} Usuario;
Usuario usuario[1];

//Struct de Paciente
typedef struct{
    char nome[30];
    long cpf[11];
    long telefone[11];
    char rua[100];
    int numero[6];
    char bairro[50];
    char cidade[30];
    char estado[30];
    long cep;
    char email[20];
    char data[10];
    char dataNascimento[10];
    char comorbidade[50];
    int op;
} Paciente;
Paciente paciente;

int dataConsulta[3];

void entrar();
void cabecalho();
void cadastrar();
void calculaData(char entrada[], int qualData);
void risco(long cep, int idade);

int main()
{
    setlocale(LC_ALL,"");
    //cabecalho();
    //entrar();
    cadastrar();
    return 0;
}

void cabecalho(){
    printf("\n**********************************************************************\n");
    printf("\n----------------------- MONITORAMENTO COVID-19 -----------------------\n");
    printf("\n**********************************************************************\n");
}

void entrar(){
    char login[30];
    char senha[30];

    strcpy(usuario[0].login, "admin"); // Definindo o login "admin" na struct
    strcpy(usuario[0].senha, "admin"); // Definindo a senha "admin"  na struct

    printf("\nLogin: ");
    scanf("%s", login); // armazenando os dados inseridos pelo usuário para o vetor login que está dentro da função main

    printf("\nSenha: ");
    scanf("%s", senha); // armazenando os dados inseridos pelo usuário para o vetor senha que está dentro da função main

    if ((strcmp(login,usuario[0].login)==0) && (strcmp(senha,usuario[0].senha)==0)){ // A função strcmp é responsável por comparar string com string
        printf("Usuário logado!");// se os vetores de dentro da struct tiver os mesmos dados do vetor interno da função main, usuário será logado.
        system("cls");
    }else{
        printf("\nLogin e/ou senha INCORRETOS! Por favor tente novamente.\n");
        entrar();
    }
}

void cadastrar(){

    cabecalho();
    FILE* cadastro;

    cadastro = fopen ("monitoracovid.txt", "a");
    if (!cadastro){
        printf("Problemas na abertura do arquivo\n");
    } else{
        do{
            fflush(stdin);
            printf("\nData da consulta: ");
            gets(paciente.data);

            calculaData(paciente.data, 0);

            fflush(stdin);
            printf("\nNome: ");
            gets(paciente.nome);

            printf("\nCPF: ");
            scanf("%ld", &paciente.cpf);

            printf("\nTelefone: ");
            scanf("%ld", &paciente.telefone);

            fflush(stdin);
            printf("\nRua: ");
            gets(paciente.rua);

            printf("\nNúmero: ");
            scanf("%ld", &paciente.numero);

            fflush(stdin);
            printf("\nBairro: ");
            gets(paciente.bairro);

            fflush(stdin);
            printf("\nCidade: ");
            gets(paciente.cidade);

            fflush(stdin);
            printf("\nEstado: ");
            gets(paciente.estado);

            printf("\nCEP: ");
            scanf("%ld", &paciente.cep);

            fflush(stdin);
            printf("\nE-mail: ");
            gets(paciente.email);

            fflush(stdin);
            printf("\nComorbidade: ");
            gets(paciente.comorbidade);

            fflush(stdin);
            printf("\nData de Nascimento: ");
            gets(paciente.dataNascimento);

            calculaData(paciente.dataNascimento, 1);

            fwrite(&paciente, sizeof(Paciente), 1, cadastro);

            printf("\nCadastro realizado com sucesso!");
            printf("\nDeseja continuar?(s/n)");

        }while(getche() == 's');
        fclose(cadastro);
    }
}

void calculaData(char entrada[], int qualData){
  int i = 0;
  int dataNasc[3];
  int idade, difMes, difDia;
  const char delimitador[2] = "/";
  char *token = strtok(entrada, delimitador);

  // Alimenta o vetor de inteiros
  if (qualData == 0){
    while (token != NULL)
    {
    dataConsulta[i++] = atoi(token);
    token = strtok(NULL, delimitador);
    }

  } else {
        while (token != NULL){
            dataNasc[i++] = atoi(token);
            token = strtok(NULL, delimitador);
        }

        idade = dataConsulta[2] - dataNasc[2];
        difMes = dataConsulta[1] - dataNasc[1];
        difDia = dataConsulta[0] - dataNasc[0];

        if (difMes < 0){
            idade--;
        } else if (difMes == 0 && difDia <= 0 ){
            idade--;
        }
        if (idade >= 65){
            risco(paciente.cep, idade);
            printf("\nGRUPO DE RISCO %d", idade);
        }
    }
}

void risco(long cep, int idade){
    FILE* grupoRisco;
    int result;

    grupoRisco = fopen("grupoderisco.txt", "a");
    if (!grupoRisco){
        printf("Erro na abertura do arquivo");
    } else {
        result = fprintf(grupoRisco, "\nIdade: %d CEP: %d", idade, cep);
        if (result == EOF){
            printf("\nErro na gravação do arquivo 'grupo de risco'\n");
        }

        fclose(grupoRisco);
    }
}
