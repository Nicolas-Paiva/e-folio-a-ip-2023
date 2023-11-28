#include <stdio.h>

const unsigned int maxCartas = 64;
const unsigned int valorMaxCarta = 63;
const unsigned int valorMinCarta = 0;
const unsigned int tamanhoDaCarta = 4; // Leva em consideração o '\0'
const unsigned int maxPosicoes = 4;

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
void mostrarBaralho(char baralho[64][4], int posicoesX[], int posicoesY[]);

// Mostra a linha superior
void mostrarLinhaSuperior();

// Pede as posições ao usuário e as armazena no vetor de posições. Caso sejam introduzidos valores inválidos, a função armazena os valores como 0, e futuramente não são utilizados pela função "mostrarBaralho"
void pedirPosicoes(int posicoes[maxPosicoes]);

// Ordena os valores recebidos pelo valor "Y" (a direita), para que possamos mostrar os valores na função "mostrarBaralho"
void ordenarPorY(int posicoes[]);

// Recebe o vetor "posicoes" ja ordenado, e armazena os valores X e Y nos vetores correspondentes
void separarPosicoes(int posicoes[maxPosicoes], int posicoesX[maxPosicoes], int posicoesY[maxPosicoes]);

// Diminui os valores dentro dos vetores posicoesX e Y para serem usados na função "mostrarBaralho"
void diminuirPosicoes(int posicoesX[maxPosicoes], int posicoesY[maxPosicoes]);

int main(void)
{
  char carta[tamanhoDaCarta];
  char baralho[maxCartas][tamanhoDaCarta];
  int posicoes[maxPosicoes];
  int posicoesX[maxPosicoes];
  int posicoesY[maxPosicoes];

  desperdicar();

  criarBaralho(baralho);

  baralhar(baralho, maxCartas);

  pedirPosicoes(posicoes);

  ordenarPorY(posicoes);

  separarPosicoes(posicoes, posicoesX, posicoesY);

  diminuirPosicoes(posicoesX, posicoesY);

  mostrarBaralho(baralho, posicoesX, posicoesY);

  return 0;
}

void gerarCarta(int numeroIntroduzido, char carta[tamanhoDaCarta])
{
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

void mostrarBaralho(char baralho[maxCartas][tamanhoDaCarta], int posicoesX[], int posicoesY[])
{
  mostrarLinhaSuperior();

  // Para que possamos mostrar as cartas 0, 8, 16, 24...
  int multiplos[8] = {0, 8, 16, 24, 32, 40, 48, 56};
  int k = 1;
  int l = 0, m = 0;
  for (int i = 0; i < 8; i++)
  {
    printf("[%d] ", k++);
    for (int j = 0; j < 8; j++)
    {
      if (posicoesY[l] == -1 || posicoesX[m] == -1)
      {
        l++, m++;
        printf("### ");
        multiplos[j]++; // Temos que mover pelas cartas do baralho na mesma
      }
      else if (i == posicoesY[l] && j == posicoesX[m])
      {
        printf("%s ", baralho[multiplos[j]++]);
        l++, m++;
      }
      else
      {
        printf("### ");
        multiplos[j]++; // Temos que mover pelas cartas do baralho na mesma
      }
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

void pedirPosicoes(int posicoes[maxPosicoes])
{
  int i = 0;
  for (int i = 0; i < maxPosicoes; i++)
  {
    scanf("%d", &posicoes[i]);
  }

  // Se passarmos um número fora dos limites do vetor, as posições dali em diante serão 0
  for (int i = 0; i < maxPosicoes; i++)
  {
    if (posicoes[i] > 88 || posicoes[i] < 11)
    {
      while (i < maxPosicoes)
      {
        posicoes[i] = 0;
        i++;
      }
    }
  }
}

void ordenarPorY(int posicoes[])
{
  int aux;
  for (int i = 0; i < maxPosicoes - 1; i++)
  {
    int sorting = 0;
    for (int j = i; j < maxPosicoes; j++)
    {
      if ((posicoes[i] % 10) > (posicoes[j] % 10))
      {
        sorting = 1;
        aux = posicoes[j];
        posicoes[j] = posicoes[i];
        posicoes[i] = aux;
      }
    }
    if (sorting == 0)
    {
      break;
    }
  }
}

void separarPosicoes(int posicoes[maxPosicoes], int posicoesX[maxPosicoes], int posicoesY[maxPosicoes])
{
  for (int i = 0; i < maxPosicoes; i++)
  {
    posicoesX[i] = posicoes[i] / 10; // Pega o valor da esquerda (63) -> 6
    posicoesY[i] = posicoes[i] % 10; // Pega o valor da direita
  }
}

void diminuirPosicoes(int posicoesX[maxPosicoes], int posicoesY[maxPosicoes])
{
  for (int i = 0; i < maxPosicoes; i++)
  {
    posicoesX[i] = posicoesX[i] - 1;
    posicoesY[i] = posicoesY[i] - 1;
  }
}
