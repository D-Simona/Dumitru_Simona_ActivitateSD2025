
//10 mai -> prima lucrare - practica la calculator
// 23 mai a doua lucrare - practica la calculator
//examen scris la calculator
//commit in fiecare saptamana
//structura examenului (scris sau grila) va fi decisa in urmatoarele saptamani (cel tarziu cu o luna inainte de examen)

#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


//adaugare in vector
//citire din fisier
//lista simplu inlantuita

struct Client {
	int id;
	int varsta;
	char* nume;
	float buget;
	char initialaTata; //nu exista bool in limbajul C
};
struct Client initializare(int id, int varsta, const char* nume, float buget, char initiala) {
	struct Client c;
	c.id = id;
	c.varsta = varsta;;
	c.nume = (char*)malloc((strlen(nume) + 1)*sizeof(char));
	strcpy_s(c.nume, strlen(nume) + 1, nume);
	c.buget = buget;
	c.initialaTata = initiala;
	return c;
}

void afisare(struct Client c) {
	printf("ID: %d, varsta: %d\n", c.id, c.varsta);//functie cu numar variabil de paramaetri; nr minim de prametri 1
	printf("Nume: %s\n", c.nume);
	printf("Buget: %.2f\n", c.buget);
	printf("Initiala tata: %c\n", c.initialaTata);
}

void afisareVector(struct Client* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

float calculVarstaMedie(struct Client* clienti, int nrElemente) {
	float suma = 0;
	for (int i = 0; i < nrElemente; i++) {
		suma += clienti[i].varsta;
	}
	return suma / nrElemente;
}

struct Client* copiazaPrimeleNElemente(struct Client* vector, int nrElemente, int nrElementeCopiate) {
		
	struct Client* v=NULL;
	if (nrElementeCopiate < nrElemente) {
		v = (struct Client*)malloc(sizeof(struct Client) * nrElementeCopiate);
		for (int i = 0; i < nrElementeCopiate; i++) {
			v[i] = vector[i];
			v[i].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s(v[i].nume, strlen(vector[i].nume) + 1, vector[i].nume);//deep copy
		}
	}
	return v;
}

void dezalocare(struct Client** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].nume);
	}
	free(*vector);
	*nrElemente = 0;
	*vector = NULL;
}

void copiazaClientiCuBugetMare(struct Client* vector, char nrElemente, float bugetMinim, struct Client** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget >= bugetMinim) {
			(*dimensiune)++;
		}
	}
	*vectorNou = (struct Client*)malloc(sizeof(struct Client) * (*dimensiune));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget >= bugetMinim) {
			(*vectorNou)[k] = vector[i];
			(*vectorNou)[k].nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s((*vectorNou)[k].nume, strlen(vector[i].nume) + 1, vector[i].nume);
			k++;
		}
	}
}

struct Client getPrimulClientDupaNume(struct Client* vector, int nrElemente, const char* numeCautat) {
	
	struct Client c;
	for (int i = 0; i < nrElemente; i++) {
		if (strcmp(vector[i].nume, numeCautat)== 0){
			c = vector[i];
			c.nume = (char*)malloc(strlen(vector[i].nume) + 1);
			strcpy_s(c.nume, strlen(vector[i].nume) + 1, vector[i].nume);
			return c;//pt ca vrem primul element
		}
	}
	//return c;//daca vrem ultimul element
}

void inserareInVector(struct Client** vector, int* dim, struct Client client) {
	struct Client* aux = (struct Client*)malloc(sizeof(struct Client) * ((*dim) + 1));
	for (int i = 0; i < *dim; i++) {
		aux[i] = (*vector)[i];
	}
	aux[(*dim)] = client;
	aux[*dim].nume = (char*)malloc(strlen(client.nume) + 1);
	strcpy_s(aux[*dim].nume, strlen(client.nume) + 1, client.nume);
	free(*vector);//dezalocare memorie
	*vector = aux; //pointeaza catre noua zona de memoorie
	(*dim)++;
}
	
struct Client citireClientFisier(FILE* f) {
	struct Client c;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, f);
	c.id = atoi(strtok(buffer, sep));
	c.varsta = atoi(strtok(NULL, sep));
	char *aux;
	aux = strtok(NULL, sep);
	c.nume = (char*)malloc(strlen(aux) + 1);
	strcpy_s(c.nume, strlen(aux) + 1, aux);
	c.buget = atof(strtok(NULL, sep));
	c.initialaTata = strtok(NULL, sep)[0];
	return c;
}

struct Client* citireVectorDinfisier(const char* numeFisier, int* dim) {
	FILE* f = fopen(numeFisier, "r");
	struct Client* vector = NULL;
	(*dim) = 0;
	while (!feof(f)) {
		struct Client c= citireClientFisier(f);
		inserareInVector(&vector, dim, c);
	}
	fclose(f);
	return vector;
}

//liste simplu inlantuite
struct Nod {
	struct Client client;
	struct Nod* next;

};

void inserareListaSfarsit(struct Nod** cap, struct Client c) {
	struct Nod* nou = (struct Nod*)malloc(sizeof(struct Nod));
	nou->client = c;
	nou->client.nume = (char*)malloc(strlen(c.nume) + 1);//-> sageata folosim cand deferentiem si accesam <=> (*nou).client.nume
	strcpy_s(nou->client.nume, strlen(c.nume) + 1, c.nume);
	nou->next = NULL;

	if (*cap) {
		struct Nod* p = *cap;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
	else {
		*cap = nou;
	}
}

//inserare la inceput si in interior tema pt acasa
struct Nod* citireListaDinFisier(const char* numeFisier) {
	struct Nod* cap = NULL; //obligatoriu de initializat
	FILE* f = fopen(numeFisier, "r");
	if (f != NULL) {
		while (!feof(f)) {
			struct Client c = citireClientFisier(f);
			inserareListaSfarsit(&cap, c);
			free(c.nume);
		}
	}
	fclose(f);
	return cap;
}

void afisareLista(struct Nod* cap) {
	while (cap) {
		afisare(cap->client);
		cap = cap ->next;
	}
}

void stergereLista(struct Nod**cap) {
	while ((*cap) != NULL) {
		struct Nod* aux = *cap;
		(*cap) = (*cap)->next;
		free(aux->client.nume);
		free(aux);
	}
}

int main() {

	//struct Client client = initializare(2, 23, "Popescu", 2000, 'B');
	//afisare(client);
	////struct Client multiClienti[30]; //alocare statica
	//int numarClienti = 3;
	//struct Client* clienti;
	//clienti = (struct Client*)malloc(numarClienti * sizeof(struct Client));
	////alocare dinamica
	//clienti[0] = initializare(1, 22, "Ionescu", 100, 'J');
	//clienti[1] = initializare(2, 23, "Vasilescu", 200, 'D');
	//clienti[2] = initializare(3, 23, "Gigel", 400, 'T');
	//printf("Clientul cautat:\n");
	//struct Client c = getPrimulClientDupaNume(clienti, numarClienti, "Gigel");
	//afisare(c);
	//inserareInVector(&clienti, &numarClienti, c);
	//printf("\nAfisare vector actualizat\n");
	//afisareVector(clienti, numarClienti);
	//free(c.nume);
	//printf("Vector:\n");
	//afisareVector(clienti, numarClienti);
	//printf("%.2f", calculVarstaMedie(clienti, numarClienti));
	//int nrClientiFideli = 2;
	//struct Client* vectorScurt = copiazaPrimeleNElemente(clienti, numarClienti, nrClientiFideli);
	//printf("\n\nClienti fideli:\n");
	//afisareVector(vectorScurt, nrClientiFideli);
	//struct Client* clientiCuBugetMare = NULL;
	//int nrClientiCuBugetMare = 0;
	//copiazaClientiCuBugetMare(clienti, numarClienti, 150, &clientiCuBugetMare, &nrClientiCuBugetMare);
	//printf("\n\nClienti cu buget mare:\n");
	//afisareVector(clientiCuBugetMare, nrClientiCuBugetMare);
	//dezalocare(&clienti, &numarClienti);
	//printf("Vectorul dupa stergere:\n");
	//afisareVector(clienti, numarClienti);

	/*FILE* f = fopen("clienti.txt", "r");
	struct Client c = citireClientFisier(f);
	afisare(c);
	struct Client* clienti = NULL;
	int nrClienti = 0;
	clienti = citireVectorDinfisier("clienti.txt", &nrClienti);
	afisareVector(clienti, nrClienti);
	struct nod* cap = NULL;*/

	struct Nod* cap = NULL;
	cap = citireListaDinFisier("clienti.txt");

	afisareLista(cap);

	stergereLista(&cap);
	printf("\ndupa stergere:\n");
	afisareLista(cap);

	return 0;
}