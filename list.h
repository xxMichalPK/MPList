#ifndef MP_LIST_H
#define MP_LIST_H

#include <stdint.h>
#include "figure.h"

// Struktura węzła listy, przechowująca dane i wskaźniki na następny i poprzedni węzeł
struct Node {
    Figure data;        // Dane
    struct Node *next;  // Poprzedni węzeł
    struct Node *prev;  // Następny węzeł
};

// Struktura listy
struct List {
    struct Node *head;  // Początkowy węzeł listy
    struct Node *tail;  // Konńowy węzeł listy
    uint32_t size;      // Rozmiar listy (ilość elementów)
};

// Funkcje używane do działań na liście
void pushBack(struct List *list, Figure data);  // Dodawanie nowego elementu na koniec listy
void pushFront(struct List *list, Figure data); // Dodawanie nowego elementu na początek listy
Figure pop(struct List *list, uint32_t index);  // Usuwa element o danym indeksie
Figure popBack(struct List *list);              // Usuwanie ostatniego elementu listy
Figure popFront(struct List *list);             // Usuwanie pierwszego elementu listy
Figure get(struct List *list, uint32_t index);  // Zwraca element o danym indeksie
uint32_t getSize(struct List *list);            // Zwraca rozmiar listy

#endif