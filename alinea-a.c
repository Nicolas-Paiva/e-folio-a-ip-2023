#include <stdio.h>
#include <stdlib.h>

const unsigned int maxCartas = 64;
const unsigned int valorMaxCarta = 63;
const unsigned int valorMinCarta = 0;
const unsigned int tamanhoDaCarta = 4; // Leva em consideração o '\0'

// Gera uma carta de acordo com o valor introduzido
void gerarCarta(int numeroIntroduzido, char carta[4]);

int main()
{
  char carta[tamanhoDaCarta];
  int numCarta;

  scanf("%d", &numCarta);
  gerarCarta(numCarta, carta);

  printf("%s\n", carta);

  return 0;
}

void gerarCarta(int numeroIntroduzido, char carta[4])
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
