#include <stdio.h>
#include <stdlib.h>

int bissexto(int ano) {
    return ((ano % 4 == 0) && (ano % 100 != 0))||(ano % 400 == 0);
}

int verificaDataValida(int d, int m, int a) {
 if (1 <= d && 1 <= m && m <= 12) {
  if (m==2) {
      if ((bissexto(a) && d <= 29)||d <= 28) {
          return 1;
      }
  } 
  else {
      if (m == 4 || m == 6 || m == 9 || m == 11) {
          if (d <= 30) 
          return 1;
      }
      else if (d <= 31)
            return 1;
 } }
return 0;
}
int main() {
    int dia, mes, ano;
    printf("Entre com a data de inicio do ano letivo:\n");
    printf("Entre com o dia: ");
    scanf("%d", &dia);
    printf("Entre com o mes: ");
    scanf("%d", &mes);
    printf("Entre com o ano: ");
    scanf("%d", &ano);
if(!verificaDataValida(dia, mes, ano))
      {
        printf("Dados incorretos\n");
        exit(1);
}
printf("Data de inicio do ano letivo: %d/%d/%d\n", dia, mes, ano);
printf("Proximos dias de encontro de todos os clubes:\n");

int k; int dias[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

if (bissexto(ano)) {
    dias[2] = 29; k=307;
    } else dias[2] = 28; k=306;

int i, j, diaX, mesX;
int soma = dia;
for (i=1;i<mes;i++)
soma += dias[i];

while (soma < k) {
    soma = soma + 60;
    diaX = soma;
    for (j=1; j<=12 && diaX > dias[j];j++) {
        diaX=diaX-dias[j];
    }
    mesX = j;
    printf("%d/%d/%d\n", diaX, mesX, ano);
} }
