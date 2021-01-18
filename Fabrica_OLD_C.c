#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <Windows.h>

typedef struct {
    int zi, luna, an;
}data;

typedef struct {
    char nume[100];
    data data_fabricatiei;
    int pret;
    struct produs* urm;
}produs;

void underscoreInSpatiu(char nume[]);
void spatiuInUnderscore(char nume[]);
void citire(produs** lista);
void salvareInFisier(produs** lista);
void pauzaSiClearScreen();
void afisarePeEcran(produs* lista);
void adaugareProdus(produs** lista);
void stergereProdus(produs** lista);
int compNume(char a[], char b[], int tipSortare);
void gasestePozPuneProdNume(produs** lista, produs* nod, int tipSortare);
void sortareNume(produs** lista, int tipSortare);
int datacmp(data x, data y);
int compData(data a, data b, int tipSortare);
int decideTipulSortarii();
void gasestePozPuneProdData(produs** lista, produs* nod, int tipSortare);
void sortareData(produs** lista, int tipSortare);
int pretcmp(int pretx, int prety);
void gasestePozPuneProdPret(produs** lista, produs* nod, int tipSortare);
void sortarePret(produs** lista, int tipSortare);
void ecrandei();
void meniu(produs* lista);


int main() {
    produs* lista = NULL;
      meniu(lista);

    return 0;
}

void underscoreInSpatiu(char nume[]) {
    int n = strlen(nume), i;
    for (i = 0; i < n; i++)
        if (nume[i] == '_')
            nume[i] = ' ';
}

void spatiuInUnderscore(char nume[]) {
    int n = strlen(nume), i;
    for (i = 0; i < n; i++)
        if (nume[i] == ' ')
            nume[i] = '_';
}

void citire(produs** lista) {

    produs* p, * q;
    FILE* f = fopen("fabrica.in", "r");
    char nume[100];
    data d;
    int pret;

    while (fscanf(f, "%s %d %d %d %d", nume, &d.zi, &d.luna, &d.an, &pret) != EOF) {
        underscoreInSpatiu(nume);
        p = (produs*)malloc(sizeof(produs));
        if (*lista == NULL) {
            strcpy(p->nume, nume);
            p->data_fabricatiei = d;
            p->pret = pret;
            p->urm = NULL;
            *lista = p;
        }
        else {
            q = (produs*)malloc(sizeof(produs));
            strcpy((q)->nume, nume);
            q->data_fabricatiei = d;
            q->pret = pret;
            q->urm = NULL;
            p->urm = q;
            p = q;
        }
    }

    fclose(f);
}

void salvareInFisier(produs** lista) {
    if (lista == NULL) {
        printf("Nu exista elemente, lista de produse nu poate fi salvata\n");
        return;
    }
    produs* p;
    p = lista;
    FILE* g = fopen("fabrica.in", "w");
    while (p) {
        spatiuInUnderscore(p->nume);
        fprintf(g, "%s %d %d %d %d\n", p->nume, p->data_fabricatiei.zi, p->data_fabricatiei.luna, p->data_fabricatiei.an, p->pret);
        underscoreInSpatiu(p->nume);
        p = p->urm;
    }
    fclose(g);
}

void pauzaSiClearScreen() {
    system("pause");
    system("cls");
}

void afisarePeEcran(produs* lista) {
    produs* p;
    p = lista;
    while (p) {
        printf("Nume produs: %s\n", p->nume);
        printf("Data fabricatiei: %d %d %d\n", p->data_fabricatiei.zi, p->data_fabricatiei.luna, p->data_fabricatiei.an);
        printf("Pretul(lei): %d\n", p->pret);
        printf("\n");

        p = p->urm;
    }
    pauzaSiClearScreen();
}

void adaugareProdus(produs** lista) {
    char nume[100];
    data data_fabricatiei;
    int pret;
    int luni[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    printf("Nume: ");
    getchar();
    gets(nume);
    if (nume[0] == '\0') {
        printf("Numele produsului nu a fost introdus\n");
        pauzaSiClearScreen();
        return;
    }
    printf("Ziua: ");
    scanf("%d", &data_fabricatiei.zi);
    printf("Luna (1-12): ");
    scanf("%d", &data_fabricatiei.luna);
    printf("Anul: ");
    scanf("%d", &data_fabricatiei.an);
    if ((data_fabricatiei.an % 4 == 0 && data_fabricatiei.an % 100 != 0) || data_fabricatiei.an % 400 == 0)
        luni[1]++;
    if (data_fabricatiei.luna < 1 || data_fabricatiei.luna > 12)
    {
        printf("Luna nevalida\n");
        pauzaSiClearScreen();
        return;
    }
    if (data_fabricatiei.zi<0 || data_fabricatiei.zi > luni[data_fabricatiei.luna - 1])
    {
        printf("Zi nevalida\n");
        pauzaSiClearScreen();
        return;
    }
    printf("Pretul(lei): ");
    scanf("%d", &pret);
    if (pret < 1)
    {
        printf("Pret nevalid\n");
        pauzaSiClearScreen();
        return;
    }
    produs* p = (produs*)malloc(sizeof(produs));
    strcpy(p->nume, nume);
    p->data_fabricatiei = data_fabricatiei;
    p->pret = pret;
    p->urm = NULL;
    produs* q;
    q = *lista;
    if (*lista == NULL) {
        *lista = p;
    }
    else {
        while (q->urm)
            q = q->urm;
        q->urm = p;
    }
    printf("Produsul a fost adaugat cu succes\n");
    pauzaSiClearScreen();
}

void stergereProdus(produs** lista) {
    if (*lista == NULL) {
        printf("Nu exista elemente in lista\n");
        pauzaSiClearScreen();
        return;
    }
    printf("Nume produs sters: ");
    char nume[100];
    getchar();
    gets(nume);
    if (nume[0] == '\0') {
        printf("Numele produsului nu a fost introdus\n");
        pauzaSiClearScreen();
        return;
    }
    produs* p, * ant;
    ant = p = (*lista);
    if (strcmp((*lista)->nume, nume) == 0) {
        p = *lista;
        *lista = (*lista)->urm;
        printf("Produsul a fost sters cu succes\n");
        pauzaSiClearScreen();
        free(p);
    }
    else {
        p = p->urm;
        while (p) {
            if (strcmp(p->nume, nume) == 0) {
                ant->urm = p->urm;
                free(p);
                printf("Produsul a fost sters cu succes\n");
                pauzaSiClearScreen();
                return;
            }
            p = p->urm;
            ant = ant->urm;
        }
        printf("Produsul cautat nu a fost gasit\n");
        pauzaSiClearScreen();
        return;
    }
}

int compNume(char a[], char b[], int tipSortare) {
    if (tipSortare == 1)
        return strcmp(a, b);
    return -strcmp(a, b);
}

void gasestePozPuneProdNume(produs** lista, produs* nod, int tipSortare) {
    produs* p, * q;
    if (*lista == NULL) {
        *lista = nod;
        return;
    }
    if (compNume(nod->nume, (*lista)->nume, tipSortare) < 0) {
        nod->urm = *lista;
        *lista = nod;
        return;
    }
    if ((*lista)->urm == NULL) {
        (*lista)->urm = nod;
        return;
    }
    p = *lista;
    q = (*lista)->urm;
    while (q && compNume(q->nume, nod->nume, tipSortare) < 0) {
        q = q->urm;
        p = p->urm;
    }
    nod->urm = q;
    p->urm = nod;
}

void sortareNume(produs** lista, int tipSortare) {
    produs* listaNoua, * p;
    listaNoua = NULL;
    p = *lista;
    while (p) {
        p = p->urm;
    }
    while (*lista) {
        p = *lista;
        (*lista) = (*lista)->urm;
        p->urm = NULL;
        gasestePozPuneProdNume(&listaNoua, p, tipSortare);
    }
    *lista = listaNoua;
    printf("Sortarea dupa nume a fost realizata cu succes\n");
    pauzaSiClearScreen();
}

int datacmp(data x, data y) {
    if (x.an < y.an)
        return -1;
    if (x.an == y.an) {
        if (x.luna < y.luna)
            return -1;
        if (x.luna == y.luna) {
            if (x.zi < y.zi)
                return -1;
            if (x.zi == y.zi)
                return 0;
        }
    }
    return 1;
}

int compData(data a, data b, int tipSortare) {
    if (tipSortare == 1)
        return datacmp(a, b);
    return -datacmp(a, b);
}

int decideTipulSortarii() {
    printf("Alegeti tipul sortarii:\n");
    printf("1. Sortare crescatoare/lexicografica\n");
    printf("2. Sortare descrescatpare/invers lexicografica\n");
    int tip;
    do {
        scanf("%d", &tip);
    } while (tip != 1 && tip != 2);
    return tip;
}

void gasestePozPuneProdData(produs** lista, produs* nod, int tipSortare) {
    produs* p, * q;
    if (*lista == NULL) {
        *lista = nod;
        return;
    }
    if (compData(nod->data_fabricatiei, (*lista)->data_fabricatiei, tipSortare) < 0) {
        nod->urm = *lista;
        *lista = nod;
        return;
    }
    if ((*lista)->urm == NULL) {
        (*lista)->urm = nod;
        return;
    }
    p = *lista;
    q = (*lista)->urm;
    while (q && compData(q->data_fabricatiei, nod->data_fabricatiei, tipSortare) < 0) {
        q = q->urm;
        p = p->urm;
    }
    nod->urm = q;
    p->urm = nod;
}

void sortareData(produs** lista, int tipSortare) {
    produs* listaNoua, * p;
    listaNoua = NULL;
    p = *lista;
    while (p) {
        p = p->urm;
    }
    while (*lista) {
        p = *lista;
        *lista = (*lista)->urm;
        p->urm = NULL;
        gasestePozPuneProdData(&listaNoua, p, tipSortare);
    }
    *lista = listaNoua;
    printf("Sortarea dupa data a fost realizata cu succes\n");
    pauzaSiClearScreen();
}

int pretcmp(int pretx, int prety) {
    if (pretx < prety)
        return -1;
    else if (pretx == prety)
        return 0;
    return 1;
}

int compPret(int x, int y, int tipSortare) {
    if (tipSortare == 1)
        return pretcmp(x, y);
    return -pretcmp(x, y);
}

void gasestePozPuneProdPret(produs** lista, produs* nod, int tipSortare) {
    produs* p, * q;
    if (*lista == NULL) {
        *lista = nod;
        return;
    }
    if (compPret(nod->pret, (*lista)->pret, tipSortare) < 0) {
        nod->urm = *lista;
        *lista = nod;
        return;
    }
    if ((*lista)->urm == NULL) {
        (*lista)->urm = nod;
        return;
    }
    p = *lista;
    q = (*lista)->urm;
    while (q && compPret(q->pret, nod->pret, tipSortare) < 0) {
        q = q->urm;
        p = p->urm;
    }
    nod->urm = q;
    p->urm = nod;
}

void sortarePret(produs** lista, int tipSortare) {
    produs* listaNoua, * p;
    listaNoua = NULL;
    p = *lista;
    while (p) {
        p = p->urm;
    }
    while (*lista) {
        p = *lista;
        *lista = (*lista)->urm;
        p->urm = NULL;
        gasestePozPuneProdPret(&listaNoua, p, tipSortare);
    }
    *lista = listaNoua;
    printf("Sortarea dupa pret a fost realizata cu succes\n");
    pauzaSiClearScreen();
}

void ecrandei() {
    printf("Fabrica de ciocolata\n");
    printf("Student: Preda Radu Alexandru\n");
    printf("Grupa: CEN 4.S2A\n");
    pauzaSiClearScreen();
}

void meniu(produs* lista) {
    int optiune;
    ecrandei();
    printf("Bun venit\n");
    printf("Meniu fabrica de dulciuri\n");

    do {
        printf("Alegeti optiunea:\n");
        printf("1.Citire\n");
        printf("2.Afisare\n");
        printf("3.Adaugare produs\n");
        printf("4.Stergere produs\n");
        printf("5.Sortare dupa nume\n");
        printf("6.Sortare dupa data\n");
        printf("7.Sortare dupa pret\n");
        printf("8.Salvare\n");
        printf("9.Iesire\n");
        scanf("%d", &optiune);
        system("cls");
        switch (optiune) {
        case 1:
            citire(&lista);
            break;
        case 2:
            if (lista == NULL)
                printf("Fisierul de intrare nu a fost citit sau toate produsele au fost sterse\n");
            else {
                afisarePeEcran(lista);
            }
            break;
        case 3:
            adaugareProdus(&lista);
            break;
        case 4:
            stergereProdus(&lista);
            break;
        case 5:
            sortareNume(&lista, decideTipulSortarii());
            break;
        case 6:
            sortareData(&lista, decideTipulSortarii());
            break;
        case 7:
            sortarePret(&lista, decideTipulSortarii());
            break;
        case 8:
            salvareInFisier(lista);
            printf("Modificarile au fost salvate\n");
            break;
        case 9:
            printf("Va mai asteptam!\n");
            return;
        default:
            printf("Va rugam alegeti o optiune din cele prezentate\n");
            optiune = 4;
            scanf("%d", &optiune);
        }
    } while (optiune);
}
