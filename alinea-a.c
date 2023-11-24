/*

OBJETIVO:

Gerar carta do baralho de acordo com o número introduzido pelo usuário. As cartas devem estar entre 0 e 64


Soluções passo a passo:

1. Garantir que o número introduzido pelo usuário esteja dentro dos limites

2. Desenvolver a lógica necessária para gerar a carta correta.


*/

// Verifica se o valor introduzido pelo usuário está dentro dos limites
int verificarValor(int valorIntroduzido, int valorMinimo, int valorMaximo);

// Gera a carta do usuário de acordo com o valor introduzido
void gerarCarta(int numeroIntroduzido, char carta[4]);

void gerarCartaOperacao(int numeroIntroduzido, char carta[4], char operacao);

#include <stdio.h>

int main(void)
{
  char carta[4];
  int numeroDaCarta;
  scanf("%d", &numeroDaCarta);

  gerarCarta(numeroDaCarta, carta);

  return 0;
}

int verificarValor(int valorIntroduzido, int valorMinimo, int valorMaximo)
{
  if (valorIntroduzido < valorMinimo)
  {
    return 0;
  }
  else if (valorIntroduzido > valorMaximo)
  {
    return 0;
  }
  return 1;
}

void gerarCarta(int numeroIntroduzido, char carta[4])
{
  // Variaveis defiidas dentro da funcao mostrar carta, pois caso os limites precisem ser alterados, podemos modificar apenas aqui...
  int cartaMinima = 0;
  int cartaMaxima = 63;
  if (verificarValor(numeroIntroduzido, cartaMinima, cartaMaxima) == 0)
  {
    printf("Carta invalida\n");
    return;
  }

  // Se o valor introduzido estiver entre 0 e 15, geramos uma carta com a operacao soma.
  if (verificarValor(numeroIntroduzido, 0, 15) == 1)
  {
    gerarCartaOperacao(numeroIntroduzido, carta, '+');
  }
  else if (verificarValor(numeroIntroduzido, 16, 31))
  {
    gerarCartaOperacao(numeroIntroduzido, carta, '-');
  }
}

void gerarCartaOperacao(int numeroIntroduzido, char carta[4], char operacao)
{
  char operacaoDaCarta = operacao;
  int numeroDaCarta = '1';
  char letraDaCarta = 'A';

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
    if (i == numeroIntroduzido)
    {
      printf("Carta %d: %c%c%c\n", i, operacaoDaCarta, numeroDaCarta, letraDaCarta);
      carta[0] = operacaoDaCarta;
      carta[1] = numeroDaCarta;
      carta[2] = letraDaCarta;
      carta[3] = '\0';
    }
  }
}
