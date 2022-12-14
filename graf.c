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

void introducere_arc(int x,int y,int pondere) {
	int i, j,val1,val2;
	for (i = 0; i < nod; i++) {
		if (noduri[i] == x)
			val1 = i;
		if (noduri[i] == y)
			val2 = i;
	}
	mat[val1][val2] = pondere;
	mat[val2][val1] = pondere;
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
				noduri[j] = noduri[j + 1];
			}
		}
	i = x;
	j = x;
	for (i = x; i < nod; i++) {
		for (j = 0; j < nod; j++)
			mat[i][j] = mat[i + 1][j];
	}
	for (j = x; j < nod; j++) {
		for (i = 0; i < nod; i++)
			mat[i][j] = mat[i][j+1];
	}
	nod--;
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
		sp[noduri[i]] = NULL;
	}
	timp = 0;
	for (i = 0; i < nod; i++) {
		if (culori[noduri[i]] == -1)
			CautareInAdancime(noduri[i]);
	}
}

void prim(int start) {
	int vizitat[N], i,j,suma=0,nr_vizitate=1,pos=-1,min=99999;
	for (i = 0; i < nod; i++) {
		vizitat[i] = -1;
		if (noduri[i] == start)
			pos = i;
	}
	if (pos == -1) {
		printf("\nNu exista nodul specificat.");
		return;
	}
	vizitat[pos] = 1;
	printf("%d ", noduri[start]);
	while (nr_vizitate < nod) {
		min = 99999;
		for (i = 0; i < nod; i++)
			for (j = 0; j < nod; j++)
				if (vizitat[i] == 1 && vizitat[j] == -1 && mat[i][j] < min && i != j && mat[i][j] != -1){
					pos = j;
					min = mat[i][j];
				}
	vizitat[pos] = 1;
	nr_vizitate++;
	if (min != 99999)
		suma += min;
	printf("%d ", noduri[pos]);
	}
	printf("\nSuma ponderiilor este: %d", suma);
}


int main() {
	int opt,val,val1,val2,sters,pondere,start;
	while (1) {
		printf("MENIU: \n");
		printf("1.Initializare.\n");
		printf("2.Introducere nod.\n");
		printf("3.Introducere arc.\n");
		printf("4.Afisare matrice.\n");
		printf("5.Stergere nod.\n");
		printf("6.Stergere arc.\n");
		printf("7.Parcurgere.\n");
		printf("8.Prim.\n");
		printf("9.Exit.\n");
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
			printf("Introduceti ponderea arcului: ");
			scanf("%d", &pondere);
			introducere_arc(val1, val2,pondere);
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
			printf("\nIntroduceti valoarea nodului de la care doriti sa incepeti: ");
			scanf("%d", &start);
			prim(start);
		case 9:
			exit(0);
			break;
		default:
			printf("\nOptiunea gresita.\n");
			break;
		}
	}
}