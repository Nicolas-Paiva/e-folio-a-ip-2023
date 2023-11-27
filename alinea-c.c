#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Gera a carta aleatória
void gerarCarta(int numeroIntroduzido, char carta[4]);

void criarBaralho(char baralho[64][4]);

// Gera números aleatórios
unsigned int randaux();

// Embaralha as cartas no vetor "baralho"
void baralhar(char baralho[64][4], int n);

// Mostra o baralho, recebendo um vetor com as cartas que deve mostrar
void mostrarBaralho(char baralho[64][4], bool jogando, int posicoesX[], int posicoesY[]);

// Pede uma jogada (string) ao jogador
void pedirJogada(char jogada[], int maximoDeCartas);

// Verifica se a jogada introduzida pelo usuário está dentro dos limites
char *verificarJogada(char jogada[], char posicoes[]);

void ordenarPorPar(char posicoes[]);

int *charParaInteiro(char posicoes[], int posicoesInt[]);

int main(void)
{
  char carta[4];
  char baralho[64][4];
  int desperdicio;
  char jogada[24];
  char posicoes[64];
  int posicoesInt[64];
  bool jogando = false;

  scanf("%d", &desperdicio);
  getchar(); // para recolher o "\n" deixado por scanf

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

  pedirJogada(jogada, 4);

  verificarJogada(jogada, posicoes);
  printf("%s\n", posicoes);

  ordenarPorPar(posicoes);

  printf("%s\n", posicoes);

  charParaInteiro(posicoes, posicoesInt);

  int posicoesX[64];
  int posicoesY[64];

  int j = 0;
  int k = 0;
  for (int i = 0; i < 8; i++)
  {
    if (i % 2 == 0)
    {
      posicoesX[j++] = posicoesInt[i];
    }
    else
    {
      posicoesY[k++] = posicoesInt[i];
    }
  }

  mostrarBaralho(baralho, true, posicoesX, posicoesY);

  return 0;
}

int *charParaInteiro(char posicoes[], int posicoesInt[])
{
  for (int i = 0; posicoes[i] != '\0'; i++)
  {
    posicoesInt[i] = (posicoes[i] - '0') - 1;
  }
  return posicoesInt;
}

void ordenarPorPar(char jogada[])
{
  int len = strlen(jogada);

  // Check if the length is odd and adjust it
  if (len % 2 != 0)
  {
    len--;
  }

  // Sort the string by pairs based on the second digit
  for (int i = 0; i < len; i += 2)
  {
    // Find the maximum element in each pair starting from the second digit
    int maxIndex = i + 1;
    for (int j = i + 3; j < len; j += 2)
    {
      if (jogada[j] < jogada[maxIndex])
      {
        maxIndex = j;
      }
    }

    // Swap the maximum element with the second element in the pair
    if (i + 1 != maxIndex)
    {
      char temp = jogada[i + 1];
      jogada[i + 1] = jogada[maxIndex];
      jogada[maxIndex] = temp;

      // Swap the corresponding first element in the pair
      temp = jogada[i];
      jogada[i] = jogada[maxIndex - 1];
      jogada[maxIndex - 1] = temp;
    }
  }
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
  return;
}

void mostrarBaralho(char baralho[64][4], bool jogando, int posicoesX[], int posicoesY[])
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
  int x = 0, y = 0;
  for (int i = 0; i < 8; i++)
  {
    printf("[%d] ", i + 1);
    for (int j = 0; j < 8; j++)
    {
      if (j == posicoesX[x] && i == posicoesY[y] && jogando == true)
      {
        printf("%s ", baralho[indexBaralho[j]++]);
        j++;
        x++;
        y++;
        if (j > 7) // Para evitar o bug de mostrar "xxx" a mais
        {
          break;
        }
      }
      // printf("%s ", baralho[indexBaralho[j]++]);
      printf("### ");
      indexBaralho[j]++;
    }
    printf("\n");
  }
  putchar('\n');
  return;
}

void criarBaralho(char baralho[64][4])
{
  for (int i = 0; i < 64; i++)
  {
    gerarCarta(i, baralho[i]);
  }
  return;
}

void pedirJogada(char jogada[], int maximoDeCartas)
{
  int tamanhoDaString = 12;
  fgets(jogada, tamanhoDaString, stdin);
  return;
}

char *verificarJogada(char jogada[], char posicoes[])
{
  char delimitador = ' ';

  // Divide a string em várias strings:
  char *posicao = strtok(jogada, &delimitador);

  int i = 0;
  while (posicao != NULL)
  {
    int tamanho = strlen(posicao);
    if (tamanho < 3 && (posicao[0] >= '1' && posicao[1] >= '1') && (posicao[0] <= '8' && posicao[1] <= '8'))
    {
      int j = 0;
      while (posicao[j] != '\0') // Passsando as strings para "posicoes"
      {
        posicoes[i++] = posicao[j++];
      }
    }
    else
    {
      break;
    }

    posicao = strtok(NULL, &delimitador);
  }
  posicoes[i] = '\0';
  return posicoes;
}
