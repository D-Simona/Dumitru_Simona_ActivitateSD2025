#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	printf("ID:%d\n", masina.id);
	printf("Numar usi:%d\n", masina.nrUsi);
	printf("Pret:%.2f\n", masina.pret);
	printf("Model:%s\n", masina.model);
	printf("Nume sofer:%s\n", masina.numeSofer);
	printf("Serie:%c\n\n", masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru - ATENTIE! - se modifica numarul de masini din vector;
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = (*masini)[i]; //asta e shallow-copy, nu este nevoie sa facem deep-copy
	}
	aux[(*nrMasini)] = masinaNoua;//shallow copy
	free(*masini);
	(*masini) = aux; //adresa pe care o retinem in aux o transmitem vectorului masini
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un stream deja deschis; masina citita este returnata;
	Masina m;
	char buffer[100];
	char separatoare[4] = ",;\n";
	fgets(buffer, 100, file);
	m.id = atoi(strtok(buffer, separatoare)); //atoi = o functie care transforma ascii to integer
	m.nrUsi = atoi(strtok(NULL, separatoare));
	m.pret = atof(strtok(NULL, separatoare)); //atof = functie care transforma ascii to float
	char* aux;
	aux = strtok(NULL, separatoare);
	m.model = (char*)malloc(strlen(aux) + 1);
	strcpy(m.model, aux);
	aux = strtok(NULL, separatoare);
	m.numeSofer = (char*)malloc(strlen(aux) + 1);
	strcpy(m.numeSofer, aux);
	m.serie = strtok(NULL, separatoare)[0];
	return m;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier - !!ATENTIE - la final inchidem fisierul/stream-ul
	FILE* file = fopen(numeFisier, "r");
	Masina* masini = NULL;
	(*nrMasiniCitite) = 0;
	while (!feof(file)) {
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < *nrMasini; i++) {
		if ((*vector)[i].model != NULL) {
			free((*vector)[i].model);
		}
		if ((*vector)[i].numeSofer != NULL) {
			free((*vector)[i].numeSofer);
		}
	}
	free(*vector);
	(*vector) = NULL;
	(*nrMasini) = 0;
}

int main() {
	int nrMasini = 0;
	Masina* masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);
	dezalocareVectorMasini(&masini, &nrMasini);


	return 0;
}