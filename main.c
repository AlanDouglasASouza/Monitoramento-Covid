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
    long cep[8];
    char email[20];
    char data[10];
    char dataNascimento[10];
    char comorbidade[50];
    int op;
} Paciente;
Paciente paciente;

void entrar();
void cabecalho();
void cadastrar();
void consulData(char entrada[]);

int main()
{
    setlocale(LC_ALL,"");
    cabecalho();
    entrar();
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
    scanf("%s", login); // armazenando os dados inseridos pelo usu�rio para o vetor login que est� dentro da fun��o main

    printf("\nSenha: ");
    scanf("%s", senha); // armazenando os dados inseridos pelo usu�rio para o vetor senha que est� dentro da fun��o main

    if ((strcmp(login,usuario[0].login)==0) && (strcmp(senha,usuario[0].senha)==0)){ // A fun��o strcmp � respons�vel por comparar string com string
        printf("Usu�rio logado!");// se os vetores de dentro da struct tiver os mesmos dados do vetor interno da fun��o main, usu�rio ser� logado.
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

            printf("\nN�mero: ");
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

           /* printf("\n--------Data de Nascimento--------");
            printf("\nDia: ");
            scanf("%d", &nasc.dia);

            printf("\nM�s: ");
            scanf("%d", &nasc.mes);

            printf("\nAno: ");
            scanf("%d", &nasc.ano);

            printf("\n----------------------------------");
*/
            fflush(stdin);
            printf("\nE-mail: ");
            gets(paciente.email);

            fflush(stdin);
            printf("\nComorbidade: ");
            gets(paciente.comorbidade);

            fflush(stdin);
            printf("\nData de Nascimento: ");
            gets(paciente.dataNascimento);

            consulData(paciente.data);

            fwrite(&paciente, sizeof(Paciente), 1, cadastro);

            printf("\nCadastro realizado com sucesso!");
            printf("\nDeseja continuar?(s/n)");

        }while(getche() == 's');
        fclose(cadastro);
    }
}

void consulData(char entrada[]){
  int i = 0;
  long data[3];
  const char delimitador[2] = "/";
  char *token = strtok(entrada, delimitador);

  // Alimenta o vetor de inteiros
  while (token != NULL)
  {
    data[i++] = strtol(token, NULL, 10);
    token = strtok(NULL, delimitador);
  }

  // Realize suas valida��es. Se alguma n�o for atingida, retorne '0'

  printf("Dia: %d\n", data[0]);
  printf("Mes: %d\n", data[1]);
  printf("Ano: %d\n", data[2]);

  return;
}
