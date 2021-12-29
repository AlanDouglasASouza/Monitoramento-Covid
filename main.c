#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

//Struct de login
typedef struct{
    char login[30];
    char senha[30];
} Usuario;
Usuario usuario[1];

//Struct de Paciente
typedef struct{
    char nome[30];
    char cpf[11];
    char telefone[11];
    char rua[100];
    char numero[6];
    char bairro[50];
    char cidade[30];
    char estado[30];
    char cep[];
    char email[20];
    char data[10];
    char dataNascimento[10];
    char comorbidade[50];
    int op;
} Paciente;
Paciente paciente;

int dataConsulta[3];
int dataNasc[3];
int idade = 0;

void entrar();
void cabecalho();
void cadastrar();
int calculaData(char entrada[], int qualData);
void risco(char cep[], int idade);
int validaChar(char entrada[]);
int validaNumero(char diaV[]);
int validaEmail(char email[]);
int validarCPF(char *cpf);
void imprimir();

int main()
{
    setlocale(LC_ALL,"");
    cabecalho();
    entrar();
    cadastrar();
    //imprimir();
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
    char copyDta[10];
    char copyNasc[10];
    cabecalho();
    FILE* cadastro;

    cadastro = fopen ("monitoracovid.txt", "a");
    if (!cadastro){
        printf("Problemas na abertura do arquivo\n");
    } else{
        do{

            do{
                fflush(stdin);
                printf("\nData da consulta: ");
                gets(paciente.data);
                strcpy(copyDta, paciente.data);
            }while(calculaData(copyDta, 0) == 0);

            do{
                fflush(stdin);
                printf("\nNome: ");
                gets(paciente.nome);
            }while(validaChar(paciente.nome) == 0);

            do{
                fflush(stdin);
                printf("\nCPF: ");
                gets(paciente.cpf);
            }while(validarCPF(paciente.cpf) == 0);

            do{
                fflush(stdin);
                printf("\nTelefone: ");
                gets(paciente.telefone);
            }while(validaNumero(paciente.telefone) == 0);

            do{
                fflush(stdin);
                printf("\nRua: ");
                gets(paciente.rua);
            }while(validaChar(paciente.rua) == 0);

            do{
                fflush(stdin);
                printf("\nNúmero: ");
                gets(paciente.numero);
            }while(validaNumero(paciente.numero) == 0);

            do{
                fflush(stdin);
                printf("\nBairro: ");
                gets(paciente.bairro);
            }while(validaChar(paciente.rua) == 0);

            do{
                fflush(stdin);
                printf("\nCidade: ");
                gets(paciente.cidade);
            }while(validaChar(paciente.cidade) == 0);

            do{
                fflush(stdin);
                printf("\nEstado: ");
                gets(paciente.estado);
            }while(validaChar(paciente.estado) == 0);

            do{
                fflush(stdin);
                printf("\nCEP: ");
                gets(paciente.cep);
            }while(validaNumero(paciente.cep) == 0);

            do{
                fflush(stdin);
                printf("\nE-mail: ");
                gets(paciente.email);
            }while(validaEmail(paciente.email) == 0);

            do{
                fflush(stdin);
                printf("\nComorbidade: ");
                gets(paciente.comorbidade);
            }while(validaChar(paciente.comorbidade) == 0);

            do{
                fflush(stdin);
                printf("\nData de Nascimento: ");
                gets(paciente.dataNascimento);
                strcpy(copyNasc, paciente.dataNascimento);
            }while(calculaData(copyNasc, 1) == 0);

            fwrite(&paciente, sizeof(Paciente), 1, cadastro);

            printf("\nCadastro realizado com sucesso!");
            printf("\nDeseja continuar?(s/n)");

        }while(getche() == 's');
        fclose(cadastro);
    }
}

int calculaData(char entrada[], int qualData){
  int i = 0;
  int difMes, difDia;
  const char delimitador[2] = "/";
  const char substring[3] = "//";

  if (strstr(entrada, substring) != NULL)
  {
    printf("\nA formatação da data é inválida! Por favor insira novamente.\n");
    return 0;
  }

  if (!validaNumero(entrada))
  {

    return 0;
  }

  char *token = strtok(entrada, delimitador);

  // Alimenta o vetor de inteiros
  if (qualData == 0){
    while (token != NULL)
    {
    dataConsulta[i++] = atoi(token);
    token = strtok(NULL, delimitador);
    }
    if ((dataConsulta[0] >= 1 && dataConsulta[0] <= 31) && (dataConsulta[1] == 1 || dataConsulta[1] == 3 || dataConsulta[1] == 5 || dataConsulta[1] == 7 || dataConsulta[1] == 8 || dataConsulta[1] == 10 || dataConsulta[1] == 12)){
        return 1;
        } else if ((dataConsulta[0] >= 1 && dataConsulta[0] <= 30) && (dataConsulta[1] == 4 || dataConsulta[1] == 6 || dataConsulta[1] == 9 || dataConsulta[1] == 11)){
                return 1;
        } else if ((dataConsulta[0] >= 1 && dataConsulta[0] <= 28) && (dataConsulta[1] == 2)){
                return 1;
        } else if (dataConsulta[0] == 29 && dataConsulta[1] == 2 && (dataConsulta[2] % 400 == 0 || (dataConsulta[2] % 4 == 0 && dataConsulta[2] % 100 != 0))){
                return 1;
        } else {
                printf("\nA formatação da data é inválida! Por favor insira novamente.\n");
                return 0;
        }

  } else {
        while (token != NULL){
            dataNasc[i++] = atoi(token);
            token = strtok(NULL, delimitador);
        }
        if ((dataNasc[0] >= 1 && dataNasc[0] <= 31) && (dataNasc[1] == 1 || dataNasc[1] == 3 || dataNasc[1] == 5 || dataNasc[1] == 7 || dataNasc[1] == 8 || dataNasc[1] == 10 || dataNasc[1] == 12)){
        return 1;
        } else if ((dataNasc[0] >= 1 && dataNasc[0] <= 30) && (dataNasc[1] == 4 || dataNasc[1] == 6 || dataNasc[1] == 9 || dataNasc[1] == 11)){
                return 1;
        } else if ((dataNasc[0] >= 1 && dataNasc[0] <= 28) && (dataNasc[1] == 2)){
                return 1;
        } else if (dataNasc[0] == 29 && dataNasc[1] == 2 && (dataNasc[2] % 400 == 0 || (dataNasc[2] % 4 == 0 && dataNasc[2] % 100 != 0))){
                return 1;
        } else {
                printf("\nA formatação da data é inválida! Por favor insira novamente.\n");
                return 0;
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
        return 1;
    }
}

void risco(char cep, int idade){
    FILE* grupoRisco;
    int result;

    grupoRisco = fopen("grupoderisco.txt", "a");
    if (!grupoRisco){
        printf("Erro na abertura do arquivo");
    } else {
        result = fprintf(grupoRisco, "\nIdade: %s CEP: %s", idade, cep);
        if (result == EOF){
            printf("\nErro na gravação do arquivo 'grupo de risco'\n");
        }

        fclose(grupoRisco);
    }
}

int validaChar (char entrada[]){
    int i;

    for(i=0; entrada[i] != '\0'; i++){
        if (isalpha(entrada[i]) == 0 && isspace(entrada[i]) == 0){
            break;
        }
    }
    if (entrada[i] != '\0'){
    printf("\nCaracteres inválidos! Por favor insira somente letras nesse campo.\n");
    return 0;
    } else {
        return 1;
    }
}

int validaNumero (char diaV[]){
    int i;
    int dataTam = strlen(diaV);

    for(i=0; i < dataTam; i++){
        if (isalpha(diaV[i]) > 0) {
            printf("\nOs caracteres dígitados não correspondem a números! Por favor insira novamente.\n");
            return 0;
            break;
        }
    }
    return 1;
}

int validaEmail(char email[]){
    int i;
    char com[5] = ".com";
    char arroba[2] = "@";

    printf("\nEsta assim: %s", email);

    for(i=0; email[i] != '\0'; i++){
        if (isspace(email[i]) != 0){
        printf("\nE-mail inválido! Por favor insira novamente.");
            return 0;
        }
    }

    if (strstr(email, arroba) == NULL || strstr(email, com) == NULL){
        printf("\nE-mail inválido! Por favor insira novamente.");
        return 0;
    }
    return 1;
}

int validarCPF(char *cpf)
{
    int i, j, digito1 = 0, digito2 = 0;
    if(strlen(cpf) != 11){
        printf("\nCPF inválido! Por favor insira novamente.\n");
        return 0;}
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0)){
        printf("\nCPF inválido! Por favor insira novamente.\n");
        return 0;} ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1){
            printf("\nCPF inválido! Por favor insira novamente.\n");
            return 0;} ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2){
            digito2 = 0;}
        else{
            digito2 = 11 - digito2;}
        if((cpf[10]-48) != digito2){
            printf("\nCPF inválido! Por favor insira novamente.\n");
            return 0;} ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}
/*
void imprimir(){
    printf("\nData da consulta: %s", paciente.data);
    printf("\nNome: %s", paciente.nome);
    printf("\nCPF: %s", paciente.cpf);
    printf("\nTelefone: %s", paciente.telefone);
    printf("\nRua: %s", paciente.rua);
    printf("\nNúmero: %s", paciente.numero);
    printf("\nBairro: %s", paciente.bairro);
    printf("\nCidade: %s", paciente.cidade);
}*/
