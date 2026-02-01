#include <curses.h>
#include <string>
#include <vector>
#include "Attivita.h"
#include "Registro.h"
#include <iostream>
#include <cstdlib>


std::string apriPopUp() {
    int h = 5;
    int l = 40;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;
    WINDOW *win = newwin(h, l, start_y, start_x);
    refresh();

    box(win, 0, 0);
    mvwprintw(win, 1, 2, "Inserisci la data (DD-MM-YYYY): ");
    wrefresh(win);

    char bufferData[11];
    echo();
    curs_set(1);
    mvwgetnstr(win, 3, 2, bufferData, 10);
    noecho();
    curs_set(0);
    delwin(win);
    return std::string(bufferData);
};

Attivita apriFinestraNuovaAttivita() {
    int h = 20;
    int l = 40;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;
    WINDOW *win = newwin(h, l, start_y, start_x);
    refresh();

    box(win, 0, 0);
    wrefresh(win);
    char descrizione[40], inizio[10], fine[10];

    echo();
    curs_set(1);
    mvwprintw(win, 1, 2, "Inserisci la descrizione: ");
    mvwgetnstr(win, 2, 2, descrizione, 39);

    mvwprintw(win, 4, 2, "Inserisci l'orario di inizio (HH:MM): ");
    mvwgetnstr(win, 5, 2, inizio, 9);

    mvwprintw(win, 7, 2, "Inserisci l'orario di fine (HH:MM): ");
    mvwgetnstr(win, 8, 2, fine, 9);
    wrefresh(win);

    noecho();
    curs_set(0);
    delwin(win);
    return Attivita(descrizione, inizio, fine);
}
void visualizza_lista(Registro& registro, std::string data) {
    int h = 20;
    int l = 49;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;
    WINDOW *win = newwin(h, l, start_y, start_x);
    refresh();
    box(win, 0, 0);

    mvwprintw(win, 1, 2, "ATTIVITA' DEL GIORNO: %s", data.c_str());
    mvwprintw(win, 2, 2, "-----------------------------------------");

    std::vector<Attivita> lista = registro.get_attivita(data);

    if (lista.empty()) {
        mvwprintw(win, 3, 2, "Lista vuota. Per aggiungere attivita premi 'a'.");
    } else {
        for (int i = 0; i < lista.size(); i++) {
            mvwprintw(win, 4 + i, 2, "[%s] %s  %s",
                     lista[i].get_descrizione().c_str(),
                     lista[i].get_orarioinizio().c_str(),
                     lista[i].get_orariofine().c_str());
        }
    }
    wrefresh(win);
    wgetch(win);
    delwin(win);
}


int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    std::string dataCorrente = "Nessuna data";
    int ch;
    Registro r;

    while (true) {
        clear();
        box(stdscr, 0, 0);
        mvprintw(2, 2, "REGISTRO ATTIVITA'");
        mvprintw(4, 2, "Data Attuale: %s", dataCorrente.c_str());
        mvprintw(6, 2, "Premi 'd' per cambiare data");
        mvprintw(7, 2, "Premi 'q' per uscire");
        mvprintw(8, 2, "Premi 'a' per aggiungere una attivita' al registro");
        mvprintw(9, 2, "Premi 'l' per visualizzare le attivita'.");

        refresh();

        ch = getch();

        if (ch == 'q') {
            break;
        }
        else if (ch == 'd') {
            std::string nuovaData = apriPopUp();
            if (!nuovaData.empty()) {
                dataCorrente = nuovaData;
            }
        }
        else if (ch == 'a') {
            if (dataCorrente == "Nessuna data") {
                mvprintw(11, 2, "ERROR: data non trovata. Premi 'd' per selezionarla.");
                getch();
            }
            else {
                Attivita nuovaAttivita = apriFinestraNuovaAttivita();
                if (nuovaAttivita.orarioValido()) {
                    r.add_attivita(nuovaAttivita, dataCorrente);
                    mvprintw(11, 2, "Attivita' aggiunta con successo");
                }
                else {
                    mvprintw(11,2, "ERROR: orario non valido (inizio>fine).");
                }
                getch();
            }
        }
        else if (ch == 'l') {
            if (dataCorrente == "Nessuna data") {
                mvprintw(10, 2, "ERROR: data non selezionata. Per selezionare la data premi 'd'.");
                getch();
            }
            else {
                visualizza_lista(r, dataCorrente);
            }
        }

    }
        endwin();
        return 0;
    }




