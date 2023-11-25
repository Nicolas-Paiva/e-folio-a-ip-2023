#include <stdio.h>
#include <stdlib.h>

void gerarCarta(int numeroIntroduzido, char carta[4]);

void criarBaralho(char baralho[62][4]);

unsigned int randaux();

void baralhar(char baralho[64][4], int n);

void mostrarBaralho(char baralho[64][4]);

int main(void)
{
  char carta[4];
  char baralho[64][4];
  int desperdicio;

  scanf("%d", &desperdicio);

  for (int i = 0; i < desperdicio; i++)
  {
    randaux();
  }

  // Preenchendo todos os elementos do baralho com as respectivas cartas (em ordem)
  for (int i = 0; i < 64; i++)
  {
    gerarCarta(i, baralho[i]);
  }

  baralhar(baralho, 64);

  mostrarBaralho(baralho);

  return 0;
}

void gerarCarta(int numeroIntroduzido, char carta[4])
{
  if (numeroIntroduzido < 0 || numeroIntroduzido > 63)
  {
    printf("Carta invalida\n");
    exit(2);
  }

  int numeroDaCarta = '1';
  char letraDaCarta = 'A';
  char operacoes[4] = {'+', '-', '*', '/'};
  char operacaoDaCarta;

  int index = (numeroIntroduzido) / 16; // Para definir o sinal da carta

  operacaoDaCarta = operacoes[index];

  for (int i = 0; i <= numeroIntroduzido; i++)
  {
    if (i > 0)
    {
      letraDaCarta++;
    }
    if (i % 4 == 0 && i != 0)
    {
      numeroDaCarta++;
      letraDaCarta = 'A';
    }
    if (i % 16 == 0 && i != 0)
    {
      numeroDaCarta = '1';
    }
    if (i == numeroIntroduzido) // Quando alcançamos o número da carta desejada
    {
      carta[0] = operacaoDaCarta;
      carta[1] = numeroDaCarta;
      carta[2] = letraDaCarta;
      carta[3] = '\0';
    }
  }
}

unsigned int randaux()
{
  static long seed = 1;
  return (((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

// Versão modificada da função baralhar (para suportar strings)
void baralhar(char baralho[64][4], int n)
{
  int i, j, k;
  int aux[4]; // string auxiliar

  for (i = 0; i < n - 1; i++)
  {
    j = i + randaux() % (n - i);

    for (k = 0; k < 4; k++)
    {
      aux[k] = baralho[i][k];
      baralho[i][k] = baralho[j][k];
      baralho[j][k] = aux[k];
    }
  }
}

void mostrarBaralho(char baralho[64][4])
{
  // Espaço na esquerda
  for (int i = 0; i < 4; i++)
  {
    putchar(' ');
  }

  // Linha superior
  for (int i = 1; i <= 8; i++)
  {
    printf("[%d] ", i);
  }
  putchar('\n');

  int indexBaralho[8] = {0, 8, 16, 24, 32, 40, 48, 56};
  for (int i = 0; i < 8; i++)
  {
    printf("[%d] ", i + 1);
    for (int j = 0; j < 8; j++)
    {
      // Uma vez que mostramos baralho[0], 0 se torna 1, mas baralho[1] só é mostrado na proxuma linha
      printf("%s ", baralho[indexBaralho[j]++]);
    }
    printf("\n");
  }
}
