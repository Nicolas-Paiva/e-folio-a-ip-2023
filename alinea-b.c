#include <stdio.h>
#include <stdlib.h>

const unsigned int maxCartas = 64;
const unsigned int valorMaxCarta = 63;
const unsigned int valorMinCarta = 0;
const unsigned int tamanhoDaCarta = 4; // Leva em consideração o '\0'

// Gera a carta aleatória de acordo com o número introduzido
void gerarCarta(int numeroIntroduzido, char carta[4]);

// Cria o baralho, armazenando as cartas no vetor "baralho"
void criarBaralho(char baralho[64][4]);

// Gera números aleatórios
unsigned int randaux();

// Pede por input e invoca randaux um dado número de vezes
void desperdicar();

// Versão modificada para strings do algoritmo "baralhar" fornecido na alínea
void baralhar(char baralho[64][4], int n);

// Mostra o baralho
void mostrarBaralho(char baralho[64][4]);

// Mostra a linha superior
void mostrarLinhaSuperior();

int main(void)
{
  char carta[tamanhoDaCarta];
  char baralho[maxCartas][tamanhoDaCarta];

  desperdicar();

  criarBaralho(baralho);

  baralhar(baralho, maxCartas);

  mostrarBaralho(baralho);

  return 0;
}

void gerarCarta(int numeroIntroduzido, char carta[tamanhoDaCarta])
{
  if (numeroIntroduzido < valorMinCarta || numeroIntroduzido > valorMaxCarta)
  {
    printf("Carta invalida\n");
    exit(1); // Para não mostrar nenhuma carta
  }

  char letrasDasCartas[4] = {'A', 'B', 'C', 'D'};
  char operacoesDasCartas[4] = {'+', '-', '*', '/'};
  char operacaoDaCarta;
  char numeroDaCarta;
  char letraDaCarta;

  int indexOperacoes = numeroIntroduzido / 16; // Determina a operacao
  int indexLetra = numeroIntroduzido % 4;      // Determina a letra

  operacaoDaCarta = operacoesDasCartas[indexOperacoes];

  letraDaCarta = letrasDasCartas[indexLetra];

  // A cada 4 numeros, o número da carta aumenta, mas a cada 16, volta a '1'
  numeroDaCarta = '1' + ((numeroIntroduzido % 16) / 4);

  carta[0] = operacaoDaCarta;
  carta[1] = numeroDaCarta;
  carta[2] = letraDaCarta;
  carta[3] = '\0';
}

void criarBaralho(char baralho[maxCartas][tamanhoDaCarta])
{
  for (int i = 0; i < maxCartas; i++)
  {
    gerarCarta(i, baralho[i]);
  }
}

unsigned int randaux()
{
  static long seed = 1;
  return (((seed = seed * 214013L + 2531011L) >> 16) & 0x7fff);
}

void desperdicar()
{
  int desperdicio;
  scanf("%d", &desperdicio);
  if (desperdicio < 0)
  {
    desperdicio = 0;
  }

  for (int i = 0; i < desperdicio; i++)
  {
    randaux();
  }
}

void baralhar(char baralho[maxCartas][tamanhoDaCarta], int maxCartas)
{
  int i, j, k;
  int aux[tamanhoDaCarta]; // string auxiliar

  for (i = 0; i < maxCartas - 1; i++)
  {
    j = i + randaux() % (maxCartas - i);

    for (k = 0; k < 4; k++)
    {
      aux[k] = baralho[i][k];
      baralho[i][k] = baralho[j][k];
      baralho[j][k] = aux[k];
    }
  }
}

void mostrarBaralho(char baralho[maxCartas][tamanhoDaCarta])
{
  mostrarLinhaSuperior();

  int k = 1;

  // Para que possamos mostrar as cartas 0, 8, 16, 24...
  int multiplos[8] = {0, 8, 16, 24, 32, 40, 48, 56};

  for (int i = 0; i < 8; i++)
  {
    printf("[%d] ", k++);
    for (int j = 0; j < 8; j++)
    {
      printf("%s ", baralho[multiplos[j]++]); // Aumenta o valor do vetor de multiplos
    }
    putchar('\n');
  }
}

void mostrarLinhaSuperior()
{
  for (int i = 0; i < 4; i++) // Linha na esquerda
  {
    putchar(' ');
  }

  for (int i = 0; i < 8; i++)
  {
    printf("[%d] ", i + 1);
  }
  putchar('\n');
}