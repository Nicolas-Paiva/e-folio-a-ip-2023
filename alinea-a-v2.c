#include <stdio.h>
#include <stdlib.h>

// Gera a carta, colocando a string no vetor "carta"
void gerarCarta(int numeroIntroduzido, char carta[4]);

int main(void)
{
  char carta[4];
  int numeroDaCarta;
  int scanfResult = scanf("%d", &numeroDaCarta);

  // Caso o usuário introduza um valor que não seja um número
  if (scanfResult != 1)
  {
    printf("Carta invalida\n");
    exit(1);
  }

  gerarCarta(numeroDaCarta, carta);
  printf("%s\n", carta);

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
