#include<stdio.h>
#include<malloc.h>

struct Telefon {
	int id;
	int RAM;
	char* producator;
	float pret;
	char serie;
};

struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {//similar constructor cu parametri
	struct Telefon t;
	t.id = id;
	t.RAM = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(t.producator, (strlen(producator) + 1), producator); //strcpy_s(destinatia, lungimea, sursa)
	t.pret = pret;
	t.serie = serie;
	return t;
}

void afisare(struct Telefon t) {
	if (t.producator != NULL) {
		printf("%d. Telefonul %s seria %c are %d Gb RAM si costa %5.2f RON.\n", t.id, t.producator, t.serie, t.RAM, t.pret);

	}
	else {
		printf("%d. Telefonul din seria %c are %d Gb RAM si costa %5.2f RON.\n", t.id, t.serie, t.RAM, t.pret);
	}
}

void afisareVector(struct Telefon* vector, int nrElemente) {
	//afisarea elementelor din vector apeland functia afisare
	//trb sa parcurgem vectorul printr-un for
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
	}
}

struct Telefon* copiazaPrimeleNElemente(struct Telefon* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care il vom returna primele nrElementeCopiate
	struct Telefon*vectorNou=NULL;
	vectorNou = (struct Telefon*)malloc(sizeof(struct Telefon) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = vector[i];
		vectorNou[i].producator=(char*)malloc()
	}

	return vectorNou;
}

void dezalocare(struct Telefon** vector, int* nrElemente) {
	//dezalocam elementele din vector si vectorul
}

void copiazaAnumiteElemente(struct Telefon* vector, char nrElemente, float prag, struct Sablon** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
}

struct Telefon getPrimulElementConditionat(struct Telefon* vector, int nrElemente, const char* conditie) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Telefon t;
	t.id = 1;

	return t;
}
	

int main() {

	//ne declaram un vector de telefoane = un pointer a structura Telefon si sa ii alocam spatiu
	struct Telefon* telefoane = NULL;
	int nrTelefoane = 3;
	telefoane = (struct Telefon*)malloc(sizeof(struct Telefon) * nrTelefoane);
	telefoane[0] = initializare(1, 256, "Samsung", 2000, 'S');
	telefoane[1] = initializare(2, 512, "Motorola", 1500, 'M');
	telefoane[2] = initializare(3, 256, "Apple", 2200, 'A');

	afisareVector(telefoane, nrTelefoane);

	return 0;
}