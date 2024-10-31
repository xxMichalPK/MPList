#include "list.h"
#include <stdlib.h>
#include <stdio.h>

// Funkcja wstawiająca element na koniec listy
void pushBack(struct List *list, Figure data) {
    list->size++;     // Zwiekszamy rozmiar listy o jeden

    // Jeżeli lista jest pusta tworzymy pierwszy węzeł i dodajemy dane
    if (list->head == 0) {
        list->head = calloc(1, sizeof(struct Node));
        list->head->data = data;
        list->tail = list->head;
        return;
    }

    // W przeciwnym wypadku dodajemy nowy węzeł na koniec listy
    struct Node *newNode = calloc(1, sizeof(struct Node));
    newNode->data = data;

    // Jeżeli lista jak dotąd składała sie z jednego węzła to nowy węzeł jest ostatnim węzłem
    if (list->tail == list->head) {
        newNode->prev = list->head;
        list->head->next = newNode;
        list->tail = newNode;
        return;
    }

    // Inaczej dodajemy nowy węzeł na koniec listy
    list->tail->next = newNode;
    newNode->prev = list->tail;
    list->tail = newNode;
}

// Funkcja wstawiająca element na początek listy
void pushFront(struct List *list, Figure data) {
    list->size++;     // Zwiekszamy rozmiar listy o jeden

    // Jeżeli lista jest pusta tworzymy pierwszy węzeł i dodajemy dane
    if (list->head == 0) {
        list->head = calloc(1, sizeof(struct Node));
        list->head->data = data;
        list->tail = list->head;
        return;
    }

    // W przeciwnym wypadku dodajemy nowy węzeł na początek listy
    struct Node *newNode = calloc(1, sizeof(struct Node));
    newNode->data = data;

    // Jeżeli lista jak dotąd składała sie z jednego węzła to nowy węzeł jest pierwszym węzłem
    if (list->tail == list->head) {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->tail = list->head;
        list->head = newNode;
        return;
    }

    // Inaczej dodajemy nowy węzeł na początek listy
    list->head->prev = newNode;
    newNode->next = list->head;
    list->head = newNode;
}

// Funkcja usuwająca element o danym indeksie - zwraca dane usuniętego elementu
Figure pop(struct List *list, uint32_t index) {
    // Jeżeli indeks wychodzi poza listę, zwracamy błąd
    if (index >= list->size) {
        printf("\033[91;1merr: Podany indeks jest poza zakresem listy\033[0m\n");
        exit(EXIT_FAILURE);
    }

    // Szukamy wskazanego węzła
    // Jeżeli index znajduje się w drugiej połowie listy to szukamy go od końca inaczej od początku
    struct Node *current = (index > list->size / 2) ? list->tail : list->head;
    if (index > list->size / 2) {
        for (uint32_t i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
    } else {
        for (uint32_t i = 0; i < index; i++) {
            current = current->next;
        }
    }
    
    // Podmieniamy wskaźniki poprzedniego i następnego węzła
    if (current->prev != 0) {
        current->prev->next = current->next;
    }
    if (current->next != 0) {
        current->next->prev = current->prev;
    }
    
    list->size--;     // Zmniejszamy rozmiar listy o jeden
    Figure data = current->data;   // Pobieramy dane
    free(current);    // Usuwamy węzeł
    return data;      // Zwracamy dane
}

// Funkcja usuwająca element z końca listy - zwraca dane usuniętego elementu
Figure popBack(struct List *list) {
    // Jeżeli lista jest pusta, zwracamy błąd
    if (list->tail == 0) {
        printf("\033[91;1merr: Lista jest pusta\033[0m\n");
        exit(EXIT_FAILURE);
    }

    list->size--;                 // Zmniejszamy rozmiar listy o jeden

    Figure data = list->tail->data;   // Pobieramy dane

    // Podmieniamy końcówkę listy
    struct Node *newTail = list->tail->prev;
    if (newTail != 0) {
        newTail->next = 0;
    } else {
        list->head = 0;
    }

    free(list->tail);    // Usuwamy węzeł
    
    list->tail = newTail; // Ustawiamy nowy koniec listy
    return data;    // Zwracamy dane
}

// Funkcja usuwająca element z początku listy - zwraca dane usuniętego elementu
Figure popFront(struct List *list) {
    // Jeżeli lista jest pusta, zwracamy błąd
    if (list->head == 0) {
        printf("\033[91;1merr: Lista jest pusta\033[0m\n");
        exit(EXIT_FAILURE);
    }

    list->size--;                 // Zmniejszamy rozmiar listy o jeden
    Figure data = list->head->data;   // Pobieramy dane

    struct Node *newHead = list->head->next;
    if (newHead != 0) {
        newHead->prev = 0;
    } else {
        list->tail = 0;
    }

    free(list->head);    // Usuwamy węzeł
    list->head = newHead; // Ustawiamy nowy początek listy
    return data;    // Zwracamy dane
}

// Funkcja zwracająca dane elementu o danym indeksie
Figure get(struct List *list, uint32_t index) {
    // Jeżeli indeks wychodzi poza listę, zwracamy błąd
    if (index >= list->size) {
        printf("\033[91;1merr: Podany indeks jest poza zakresem listy\033[0m\n");
        exit(EXIT_FAILURE);
    }

    // Jeżeli index znajduje się w drugiej połowie listy to szukamy go od końca
    if (index > list->size / 2) {
        struct Node *current = list->tail;
        for (uint32_t i = list->size - 1; i > index; i--) {
            current = current->prev;
        }
        return current->data;
    }

    // W innym przypadku szukamy od początku
    struct Node *current = list->head;
    for (uint32_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

// Funkcja zwracająca rozmiar listy (ilość elementów)
uint32_t getSize(struct List *list) {
    return list->size;
}