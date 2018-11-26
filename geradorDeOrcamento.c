/*
 * Faculdade Mauricio de Nassau
 * Professor: Douglas Santiago Kridi
 * Disciplina: Programacao de Computadores
 * Trabalho Avaliativo para segunda nota resgatando conteudos antes discutidos
 *
 */


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(WIN32)
#define LIMPA system("cls")
#else
#define LIMPA system("clear")
#endif

#define CONTROLE 's'
#define TAM_NOME 70
#define TAM_TAB 100
#define TAM 20
#define ESPACO ' ' // auxilia na disposicao dos espacos em branco

// struct para representar cada linha da tabela
struct LinhaTabela {
  char prod[TAM];
  char uni[TAM];
  int cod;
  int qtd;
  float valorUni;
  float valorTot;
};

void flush() {
  int ch;
    while((ch = fgetc(stdin)) != EOF && ch != '\n') { }
}

float calcValTotParcial(float valorUni, int qtd) {
  return valorUni * qtd;
}

float calcValTot(struct LinhaTabela* linha, int n) {
  float tot = 0;
  for(int i = 0; i < n; i++)
    tot += linha[i].valorTot;
  return tot;
}

char* insereIgual(int n) {
  char* igual = malloc(sizeof(n + 1) / sizeof(int));
  for(int i = 0; i < n; i++)
    igual[i] = '=';
  igual[n] = '\0';
  return igual;
}

void mostraLinha(struct LinhaTabela* linha, int i) {
  // um printf para cada campo por questao de organizacao
  printf("|%4c%03d ", ESPACO, linha[i].cod);
  printf("|%13s ", linha[i].prod);
  printf("|%11s ", linha[i].uni);
  printf("|%11d ", linha[i].qtd);
  printf("| R$%8.2f ", linha[i].valorUni);
  printf("| R$%10.2f |\n", linha[i].valorTot);
}

void mostraTabela(struct LinhaTabela* linha, char nome[],  int n) {
  printf(" %s\n", insereIgual(77));
  printf("%2cSolicitante: %s\n", ESPACO, nome);
  printf(" %s\n", insereIgual(77));
  printf("%2cDescricao do Servico: gerador de orcamento\n", ESPACO);
  printf(" %s\n", insereIgual(77));

  printf("+%s Orcamento por servico ", insereIgual(25));
  printf("%s+\n", insereIgual(29));
  printf("| Codigo |    Produto   |   Unidade  | Quantidade |  Val. Uni  |  Val. Total  |\n");

  for(int i = 0; i < n; i++)
    mostraLinha(linha, i);

  printf("+%s+\n", insereIgual(77));
  printf("|%50cVALOR TOTAL | R$%10.2f |\n", ESPACO, calcValTot(linha, n));
  printf("+%s+\n\n\n", insereIgual(77));
}

int main() {
  char nomeSolicitante[TAM_NOME];
  struct LinhaTabela linha[TAM_TAB];

  LIMPA;

  while(1) {
    printf("Insira seu nome: ");
    scanf("%[^\n]s", nomeSolicitante);
    flush();

    if(strlen(nomeSolicitante) > 65) {
      printf("Opss! Nome muito extenso!\n");
      continue;
    }
    else
      break;
  }

  int n;
  char outroMaterial = CONTROLE;
  for(int i = 0; outroMaterial == CONTROLE; i++, n = i) {
    while(1) {
      printf("\n\tInforme um material: ");
      scanf("%[^\n]s", linha[i].prod);
      flush();

      // nao pode ter mais q 12 caracteres
      if(strlen(linha[i].prod) > 12) {
        printf("\tInforme um nome menor!!\n");
        continue;
      }
      else
        break;
    }

    for(; ; printf("\tOpss!!\n")) {
      printf("\n\tInforme um codigo de 3 digitos para o(a) %s: ", linha[i].prod);
      scanf("%d", &linha[i].cod);
      flush();

      if(linha[i].cod >= 1000)
        continue;
      else
        break;
    }

    for(; ; printf("\tUnidade muito extensa!!\n")) {
      printf("\n\tInforme a unidade do(a) %s: ", linha[i].prod);
      scanf("%[^\n]s", linha[i].uni);
      flush();

      if(strlen(linha[i].uni) > 10)
        continue;
      else
        break;
    }

    printf("\n\tInforme a quantidade dele(a): ");
    scanf("%d", &linha[i].qtd);
    flush();

    printf("\n\tValor por unidade: ");
    scanf("%f", &linha[i].valorUni);
    flush();

    // com os devidos valores informados pode-se calcular o
    // valor total de cada material e adicioanar na nossa struct
    linha[i].valorTot = calcValTotParcial(linha[i].valorUni, linha[i].qtd);

    // apenas 's' sera considerado como desejo de continuar
    do {
      printf("\n\tInserir outro material? [ s/n ] ");
      scanf("%c", &outroMaterial);
      flush();
      outroMaterial = tolower(outroMaterial);
    } while(outroMaterial != 's' && outroMaterial != 'n');
  }

  printf("\n\n\n");
  mostraTabela(linha, nomeSolicitante, n);

  return 0;
}