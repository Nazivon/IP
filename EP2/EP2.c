#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes * NumeroMaxRodadas


typedef struct auxtime {
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int Empates;
  int Derrotas;
  float GolAverage;
  char nome[31];
} time;


typedef struct auxjogo {
  char local[30];
  char visitante[30];
  int golslocal;
  int golsvisitante;
} jogo;


void lenometime(char * s) {
  int i;
  s[0] = '\0';
  char c;
  c = getchar();
  for(i = 0; c != ',' && i < 30;++i)
    {
      s[i] = c;
      c = getchar();
    }
  s[i] = '\0';
}


void ordenaPontos(time * timescampeonato, int notimes) {
int i, j; 
struct auxtime key;
for (i=1;i<notimes;i++) {
key=timescampeonato[i];
j=i-1;
 while (j>=0 && (timescampeonato[j].PontosGanhos < key.PontosGanhos || (timescampeonato[j].PontosGanhos == key.PontosGanhos && timescampeonato[j].SaldoDeGols < key.SaldoDeGols))) {
timescampeonato[j+1]=timescampeonato[j]; 
j--;
 } timescampeonato[j+1]=key;
} }


void ordenaSaldoGols(time * timescampeonato, int notimes) {
int i, j, t;
struct auxtime key;
for (i=1;i<notimes;i++) {
if (timescampeonato[i].PontosGanhos==timescampeonato[i-1].PontosGanhos) {
key=timescampeonato[i];
j=i-1;
 while (j>=0 && timescampeonato[j].SaldoDeGols < key.SaldoDeGols) {
 timescampeonato[j+1] = timescampeonato[j]; 
 j--;
} timescampeonato[j+1]=key; } }
}


int encontratime(time *timescampeonato, char * nome, int notimes) {
int i;
for (i=0;i<notimes;i++) {
    if (strcmp(timescampeonato[i].nome,nome)==0) {
        return i;
} }
  return -1;
}


int crialistatimes(time *timescampeonato, jogo *dadosjogos, int numerojogos) {
    int i, j;
    int notimes = 0;
    int copianome;


    for (i = 0; i < numerojogos; i++) {
        copianome = 0;
        for (j = 0; j < notimes; j++) {
            if (strcmp(dadosjogos[i].local, timescampeonato[j].nome) == 0) {
                copianome = 1;
                break;
            }
        }
        if (!copianome) {
            strcpy(timescampeonato[notimes].nome, dadosjogos[i].local);
            timescampeonato[notimes].Vitorias = 0;
            timescampeonato[notimes].Derrotas = 0;
            timescampeonato[notimes].Empates = 0;
            timescampeonato[notimes].GolsMarcados = 0;
            timescampeonato[notimes].GolsSofridos = 0;
            notimes++;
        }


        copianome = 0;
        for (j = 0; j < notimes; j++) {
            if (strcmp(dadosjogos[i].visitante, timescampeonato[j].nome) == 0) {
                copianome = 1;
                break;
            }
        }
        if (!copianome && strcmp(dadosjogos[i].visitante, dadosjogos[i].local) != 0) {
            strcpy(timescampeonato[notimes].nome, dadosjogos[i].visitante);
            timescampeonato[notimes].Vitorias = 0;
            timescampeonato[notimes].Derrotas = 0;
            timescampeonato[notimes].Empates = 0;
            timescampeonato[notimes].GolsMarcados = 0;
            timescampeonato[notimes].GolsSofridos = 0;
            notimes++;
        }
    }


    return notimes;
}


void computadadostimes(time *timescampeonato, int notimes, jogo *dadosjogos, int numerojogos) {
    int i;
    for (i = 0; i < numerojogos; i++) {
        int indiceTimeLocal = encontratime(timescampeonato, dadosjogos[i].local, notimes);
        int indiceTimeVisitante = encontratime(timescampeonato, dadosjogos[i].visitante, notimes);


        if (indiceTimeLocal != -1 && indiceTimeVisitante != -1) {
            timescampeonato[indiceTimeLocal].GolsMarcados += dadosjogos[i].golslocal;
            timescampeonato[indiceTimeLocal].GolsSofridos += dadosjogos[i].golsvisitante;
            timescampeonato[indiceTimeVisitante].GolsMarcados += dadosjogos[i].golsvisitante;
            timescampeonato[indiceTimeVisitante].GolsSofridos += dadosjogos[i].golslocal;


            if (dadosjogos[i].golslocal > dadosjogos[i].golsvisitante) {
                timescampeonato[indiceTimeLocal].Vitorias++;
                timescampeonato[indiceTimeVisitante].Derrotas++;
            } else if (dadosjogos[i].golslocal < dadosjogos[i].golsvisitante) {
                timescampeonato[indiceTimeLocal].Derrotas++;
                timescampeonato[indiceTimeVisitante].Vitorias++;
            } else {
                timescampeonato[indiceTimeLocal].Empates++;
                timescampeonato[indiceTimeVisitante].Empates++;
            }
        }
    }


    for (i = 0; i < notimes; i++) {
        timescampeonato[i].PontosGanhos = 3 * timescampeonato[i].Vitorias + timescampeonato[i].Empates;
        timescampeonato[i].SaldoDeGols = timescampeonato[i].GolsMarcados - timescampeonato[i].GolsSofridos;
        timescampeonato[i].GolAverage = (float) timescampeonato[i].GolsMarcados / timescampeonato[i].GolsSofridos;
    }
}


void imprimeclassificacao(time *timescampeonato, int notimes) {
    ordenaPontos(timescampeonato, notimes);
    ordenaSaldoGols(timescampeonato, notimes);
    printf("Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");
    for (int i = 0; i < notimes; i++) {
        printf("%d,%s,%d,%d,%d,%d,%d,%2.3f\n", i + 1, timescampeonato[i].nome, timescampeonato[i].PontosGanhos, timescampeonato[i].Vitorias, timescampeonato[i].Empates, timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols, timescampeonato[i].GolAverage);
    }
}


int main() {
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30],visitante[30];


  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for(i = 0; i < NumeroMaxJogos; ++i) {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d",&golslocal,&golsvisitante);
    getchar();
    if (golslocal < 0)
      break;


    if(strcmp(local,visitante) == 0)
      continue;


    strncpy(jogos[i].local,local,30);
    strncpy(jogos[i].visitante,visitante,30);


    jogos[i].golslocal = golslocal;
    jogos[i].golsvisitante = golsvisitante;
  }
  nojogos = i;




  int notimes = crialistatimes(times,jogos,nojogos);


  computadadostimes(times,notimes,jogos,nojogos);


  imprimeclassificacao(times,notimes);
}

