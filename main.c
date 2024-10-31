#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Zmienne zawierające kody kolorów i innych operacji konsoli
const char COLOR_WHITE[] = "\033[97m";
const char COLOR_GRAY[] = "\033[37m";
const char COLOR_GREEN[] = "\033[92m";
const char COLOR_BLUE[] = "\033[94m";
const char COLOR_RESET[] = "\033[0m";
const char CLEAR_SCREEN[] = "\033[2J\033[1;1H";

// Nagłówek (czemu się nie pochwalić :D)
const char HEADER_TEXT[] = 
" /$$      /$$ /$$$$$$$  /$$       /$$$$$$  /$$$$$$  /$$$$$$$$\n"
"| $$$    /$$$| $$__  $$| $$      |_  $$_/ /$$__  $$|__  $$__/\n"
"| $$$$  /$$$$| $$  \\ $$| $$        | $$  | $$  \\__/   | $$   \n"
"| $$ $$/$$ $$| $$$$$$$/| $$        | $$  |  $$$$$$    | $$   \n"
"| $$  $$$| $$| $$____/ | $$        | $$   \\____  $$   | $$   \n"
"| $$\\  $ | $$| $$      | $$        | $$   /$$  \\ $$   | $$   \n"
"| $$ \\/  | $$| $$      | $$$$$$$$ /$$$$$$|  $$$$$$/   | $$   \n"
"|__/     |__/|__/      |________/|______/ \\______/    |__/   \n"
"\033[37m"
"        Implementacja listy dwukierunkowej w jezyku C        \n"
"                 Autor: Michal Pazurek\n\n";

// Funkcja wypisująca zawartość całej listy według kolejności (indeksu danej figury w liście)
void wypiszListe(struct List *list) {
    printf("%s", CLEAR_SCREEN);
    printf("%sZawartosc listy:%s\n", COLOR_GREEN, COLOR_GRAY);
    if (getSize(list) == 0) {
        printf("Lista jest pusta\n\n");
        return;
    }

    for (uint32_t i = 0; i < getSize(list); i++) {
        printf("%d: Nazwa - %s, Pole - %f, Obwod - %f\n", i, get(list, i).name, get(list, i).area, get(list, i).perimiter);
    }
    printf("%s\n", COLOR_WHITE);
}

// Funkcja drukująca menu główne
void mainMenu() {
    printf("------------------------------------------\n");
    printf("| 1. Wypisz liste                        |\n");
    printf("| 2. Dodaj figure na poczatek            |\n");
    printf("| 3. Dodaj figure na koniec              |\n");
    printf("| 4. Usun figure o podanym indeksie      |\n");
    printf("| 5. Usun pierwsza figure                |\n");
    printf("| 6. Usun ostatnia figure                |\n");
    printf("| 7. Wyswietl figure o podanym indeksie  |\n");
    printf("| 0. Wyjscie                             |\n");
    printf("------------------------------------------\n\n");
    printf("Wybierz opcje: ");
}

// Punkt startowy programu (funkcja main)
int main() {
    struct List list = { 0 };    // Inicjalizacja listy

    printf("%s%s", CLEAR_SCREEN, COLOR_BLUE);
    printf("%s%s", HEADER_TEXT, COLOR_WHITE);

    // Pętla programu, w której użytkownik wybiera, którą operację chce wykonać
    while (1) {
        printf("%s", COLOR_WHITE);
        mainMenu();

        // Pobieramy, którą opcję wybrał użytkownik
        int choice;
        scanf("%d", &choice);
        
        // Sprawdzamy wybrana opcję i wykonujemy odpowiedni kod
        switch (choice) {
            // Wypisanie zawartości listy
            case 1: {
                wypiszListe(&list);
                break;
            }

            // Dodanie nowej figury na początek lub koniec listy
            case 2:
            case 3: {
                printf("%s", CLEAR_SCREEN);
                printf("Kreator figury:\n");

                // Urzytkownik tworzy nową figurę
                printf("Podaj nazwe figury: ");             // Nazwa
                char *name = calloc(1, 64 * sizeof(char));
                scanf("%s", name);
                printf("Podaj pole figury: ");              // Pole
                double area;
                scanf("%lf", &area);
                printf("Podaj obwod figury: ");             // Obwód
                double perimiter;
                scanf("%lf", &perimiter);
                Figure data = { name, area, perimiter };

                // Wywołujemy odpowiednią funkcję aby dodać element na początek lub na koniec 
                if (choice == 2) {
                    pushFront(&list, data);
                } else {
                    pushBack(&list, data);
                }

                // Wyświetlenie komunikatu zwrotnego
                printf("%s%s", CLEAR_SCREEN, COLOR_GREEN);
                printf("Dodano: %s, Pole: %f, Obwod: %f\033[0m\n\n", data.name, data.area, data.perimiter);
                printf("%s", COLOR_WHITE);
                break;
            }

            // Usuwanie figury o podanym indeksie
            case 4: {
                printf("%s", CLEAR_SCREEN);
                printf("Podaj indeks figury: ");
                uint32_t index;
                scanf("%d", &index);            // Pobieramy indeks

                printf("%s", CLEAR_SCREEN);
                Figure usunieta = pop(&list, index);    // Usuwamy element
                printf("%sUsunieto: %s%s\n\n", COLOR_GREEN, usunieta.name, COLOR_WHITE);
                free((void*)usunieta.name);
                break;
            }

            // Usuwanie figury z początku listy
            case 5: {
                printf("%s", CLEAR_SCREEN);
                Figure usunieta = popFront(&list);
                printf("%sUsunieto: %s%s\n\n", COLOR_GREEN, usunieta.name, COLOR_WHITE);
                free((void*)usunieta.name);
                break;
            }

            // Usuwanie figury z końca listy
            case 6: {
                printf("%s", CLEAR_SCREEN);
                Figure usunieta = popBack(&list);
                printf("%sUsunieto: %s%s\n\n", COLOR_GREEN, usunieta.name, COLOR_WHITE);
                free((void*)usunieta.name);
                break;
            }

            // Wypisanie danych figury
            case 7: {
                printf("%s", CLEAR_SCREEN);
                printf("Podaj index figury: ");
                uint32_t index;
                scanf("%d", &index);

                printf("%s%s", CLEAR_SCREEN, COLOR_GREEN);
                printf("Nazwa - %s, Pole - %f, Obwod - %f\n\n", get(&list, index).name, get(&list, index).area, get(&list, index).perimiter);
                printf("%s", COLOR_WHITE);
                break;
            }

            // Zakończenie działania programu
            case 0:
                printf("%s%s", CLEAR_SCREEN, COLOR_RESET);
                exit(EXIT_SUCCESS);

            // Jeżeli wybrano niepoprawną opcję wychodzimy z switcha i wracamy do pętli while
            default:
                break;
        }
    }

    return 0;
}