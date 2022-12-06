#include <stdio.h>
#include <stdlib.h>
#define N 100
int mat[N][N], noduri[N], nod, culori[N], ti[N], tf[N],sp[N],timp;
//vectorul culori:  -1 - alb , 0 - gri , 1 - negru

void initializare() {
	int i, j;
	for (i = 0; i < N; i++)
		noduri[i] = -1;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			mat[i][j] = -1;
	nod = 0;
}

void introducere_nod(int nr) {
	noduri[nod] = nr;
	nod++;
}

void introducere_arc(int x,int y) {
	int i, j,val1,val2;
	for (i = 0; i < nod; i++) {
		if (noduri[i] == x)
			val1 = i;
		if (noduri[i] == y)
			val2 = i;
	}
	mat[val1][val2] = 1;
	mat[val2][val1] = 1;
}

void afisare() {
	int i, j;
	for (i = 0; i < nod; i++)
		printf("%d ", noduri[i]);
	printf("\n\n");
	for (i = 0; i < nod; i++) {
		for (j = 0; j < nod; j++)
			printf("%2d ", mat[i][j]);
		printf("\n");
	}
}

void stergere(int valoare) {
	int i, j,x;
	for (i = 0; i < nod; i++)
		if (noduri[i] == valoare) {
			x = i;
			for (j = i; j < nod - 1; j++) {
				noduri[j] = noduri[j + 1]; // mutam elementele din vector la stanga cu o pozitie
			}
		}
	for (i = x; i < nod; i++) {
		for (j = 0; j < nod; j++)
			mat[i][j] = mat[i + 1][j]; 
	}
	for (j = x; j < nod; j++) {
		for (i = 0; i < nod; i++)
			mat[i][j] = mat[i][j+1];  // mutam liniile si coloanele din matrice pentru a obtine matricea noua fara nodul sters
	}
	nod--; // scadem numarul de noduri
}

void stergere_arc(int x,int y) {
	int i, j, val1, val2;
	for (i = 0; i < nod; i++) {
		if (noduri[i] == x)
			val1 = i;
		if (noduri[i] == y)
			val2 = i;
	}
	mat[val1][val2] = -1;
	mat[val2][val1] = -1;
}
// algoritm de parcurgere in adancime
void CautareInAdancime(int x) {
	int i=0, j, v;
	culori[x] = 0;
	timp++;
	ti[x] = timp;
	for(i=0;i<nod;i++)
		for (j = 0; j < nod; j++)
			if (mat[i][j] == 1) {
				v = noduri[i];
				if (culori[v] == -1) {
					sp[v] = x;
					CautareInAdancime(v);
				}
			}
	culori[x] = 1;
	timp++;
	tf[x] = timp;
	printf("\n%d %d\n", x, tf[x] - ti[x]);
}

void TraversareInAdancime() {
	int i;
	for (i = 0; i < nod; i++) {
		culori[noduri[i]] = -1;
		sp[noduri[i]] = -1;
	}
	timp = 0;
	for (i = 0; i < nod; i++) {
		if (culori[noduri[i]] == -1)
			CautareInAdancime(noduri[i]);
	}
}

int main() {
	int opt,val,val1,val2,sters;
	while (1) {
		printf("MENIU: \n");
		printf("1.Initializare.\n");
		printf("2.Introducere nod.\n");
		printf("3.Introducere arc.\n");
		printf("4.Afisare matrice.\n");
		printf("5.Stergere nod.\n");
		printf("6.Stergere arc.\n");
		printf("7.Parcurgere.\n");
		printf("8.Exit.\n");
		printf("Introduceti optiunea dorita: ");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1:
			initializare();
			break;
		case 2:
			printf("\nIntroduceti valoarea pe care doriti sa o introduceti in nod: ");
			scanf("%d", &val);
			introducere_nod(val);
			break;
		case 3:
			printf("Introduceti prima valoare: ");
			scanf("%d", &val1);
			printf("Introduceti a doua valoare: ");
			scanf("%d", &val2);
			introducere_arc(val1, val2);
			break;
		case 4:
			afisare();
			break;
		case 5:
			printf("Introduceti valoarea pe care doriti sa o stergeti: ");
			scanf("%d", &sters);
			stergere(sters);
			break;
		case 6:
			printf("Introduceti prima valoare: ");
			scanf("%d", &val1);
			printf("Introduceti a doua valoare: ");
			scanf("%d", &val2);
			stergere_arc(val1, val2);
			break;
		case 7:
			TraversareInAdancime();
			break;
		case 8:
			exit(0);
			break;
		default:
			printf("\nOptiunea gresita.\n");
			break;
		}
	}
}
