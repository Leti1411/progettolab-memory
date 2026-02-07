#include <curses.h>
#include <string>
#include <vector>
#include "Attivita.h"
#include "Registro.h"
#include <iostream>
#include <cstdlib>


std::string apriPopUp() {
    int h = 10;
    int l = 50;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;
    WINDOW *win = newwin(h, l, start_y, start_x);
    box(win, 0, 0);
    refresh();

    mvwprintw(win, 1, 2, "Inserisci la data (DD-MM-YYYY): ");
    wrefresh(win);

    char bufferData[30];
    std::string dataInserita;
    bool dataValida = false;

    echo();
    curs_set(1);

    while (!dataValida) {
        mvwprintw(win, 4, 2, "                              ");


        mvwgetnstr(win, 4, 2, bufferData, 29);
        dataInserita = std::string(bufferData);

        if (dataInserita.length() != 10) {
            mvwprintw(win, 6, 2, "ERRORE: Attenzione al formato DD-MM-YY.");
            wrefresh(win);
        }
        else {
            std::string anno = dataInserita.substr(6, 4);

            if (anno == "2026") {
                dataValida = true;
            } else {
                mvwprintw(win, 6, 2, "ERRORE: Inserisci una data del 2026.");
                wrefresh(win);
            }
        }
    }

    noecho();
    curs_set(0);
    delwin(win);
    return dataInserita;
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

void EliminaAttivita(Registro& r, std::string data) {
    int h = 20;
    int l = 60;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;

    WINDOW *win = newwin(h, l, start_y, start_x);
    refresh();
    box(win, 0, 0);

    mvwprintw(win, 1, 2, "Elimina attivita' in data (%s)", data.c_str());
    mvwprintw(win, 2, 2, "----------------------------------------");

    std::vector<Attivita> lista_att = r.get_attivita(data);
    if (lista_att.empty()) {
        mvwprintw(win, 4, 2, "Nessuna attivita' da cancellare.");
        wrefresh(win);
        wgetch(win);
        delwin(win);
        return;
    }
    for (int i = 0; i < lista_att.size(); i++) {
        if (i >= h-6) break;
        mvwprintw(win, 4+i, 2, "[%d] %s [%s-%s]",
            i,
            lista_att[i].get_descrizione().c_str(),
            lista_att[i].get_orarioinizio().c_str(),
            lista_att[i].get_orariofine().c_str());
    }
    mvwprintw(win, h-4, 2, "Inserisci l'indice dell'attivita' da cancellare:");
    wrefresh(win);
    char bufferIndice[10];
    echo();
    curs_set(1);
    mvwgetnstr(win, h-4, 51, bufferIndice, 5);
    noecho();
    curs_set(0);

    int indice_scelto = atoi(bufferIndice);
    bool cancella = r.remove_attivita(indice_scelto, data);

    if (cancella) {
        mvwprintw(win, h - 2, 2, "Attivita' eliminata con successo.");
    }
    else {
        mvwprintw(win, h - 2, 2, "ERROR: Indice non valido");
    }
    wrefresh(win);
    wgetch(win);
    delwin(win);
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

void show_entireRegistro(Registro& r) {
    int h = 20;
    int l = 72;
    int start_y = (LINES - h) / 2;
    int start_x = (COLS - l) / 2;

    WINDOW *win = newwin(h, l, start_y, start_x);
    refresh();
    box(win, 0, 0);

    mvwprintw(win, 1, 2, "REGISTRO COMPLETO - 2026");
    mvwprintw(win, 2, 2, "---------------------------");

    auto tuttoregistro = r.show_tuttoRegistro();
    int riga = 3;

    if (tuttoregistro.empty()) {
        mvwprintw(win, riga, 2, "Nessuna attivita' presente. Premi 'd' per selezionare la data,");
        mvwprintw(win, riga+1, 2, "e poi premi 'a' per aggiungere attivita'." );
    }
    else {
        for (auto const& element : tuttoregistro) {
            std::string data = element.first;
            auto lista_attivita = element.second;

            if (riga >= h-2 ) {break;}

            mvwprintw(win, riga, 2, "DATA %s", data.c_str());
            riga++;

            for (auto& attivita : lista_attivita) {

                if (riga >= h-2) {break;}

                mvwprintw(win, riga, 4, "%s [%s - %s]",
                    attivita.get_descrizione().c_str(),
                    attivita.get_orarioinizio().c_str(),
                    attivita.get_orariofine().c_str());
                riga++;
            }
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
        mvprintw(2, 2, "REGISTRO ATTIVITA' - 2026");
        mvprintw(4, 2, "Data Attuale: %s", dataCorrente.c_str());
        mvprintw(6, 2, "Premi 'd' per cambiare data");
        mvprintw(7, 2, "Premi 'q' per uscire");
        mvprintw(8, 2, "Premi 'a' per aggiungere una attivita' al registro");
        mvprintw(9,2, "Premi 'r' pre rimuovere una attivita' dal registro");
        mvprintw(10, 2, "Premi 'l' per visualizzare le attivita' del giorno selezionato.");
        mvprintw(11, 2, "Premi 't' per visualizzare tutto il registro.");

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
                mvprintw(15, 2, "ERROR: data non trovata. Premi 'd' per selezionarla.");
                getch();
            }
            else {
                Attivita nuovaAttivita = apriFinestraNuovaAttivita();
                if (nuovaAttivita.orarioValido()) {
                    r.add_attivita(nuovaAttivita, dataCorrente);
                    mvprintw(15, 2, "Attivita' aggiunta con successo");
                }
                else {
                    mvprintw(15,2, "ERROR: orario non valido (inizio>fine).");
                }
                getch();
            }
        }
        else if (ch == 'l') {
            if (dataCorrente == "Nessuna data") {
                mvprintw(15, 2, "ERROR: data non selezionata. Per selezionare la data premi 'd'.");
                getch();
            }
            else {
                visualizza_lista(r, dataCorrente);
            }
        }
        else if (ch == 't') {
           show_entireRegistro(r);
        }
        else if (ch == 'r') {
            if (dataCorrente == "Nessuna data") {
                mvprintw(15, 2, "Seleziona prima una data. Per farlo premi 'd'");
                getch();
            }
            else {
                EliminaAttivita(r, dataCorrente);
            }
        }

    }
        endwin();
        return 0;
}




