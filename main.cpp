#include <curses.h>
#include <string>
#include <vector>
#include "Attivita.h"
#include "Registro.h"
#include <iostream>
#include <cstdlib>

int main() {
    system("mode con: cols=120 lines=50");
    initscr();
    resize_term(50, 120);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);



    int giorno_selezionato = 0;
    int ora_selezionata = 0;
    int h=0;
    int g=0;
    std::string tabella[14][7];

    int larg_colon = 10;
    int spazio_orari = 8;
    int y_schermo;
    int x_schermo;
    Attivita* new_attivita;
    int h_win = 10;
    int l_win = 40;
    int y_win = 4;
    int x_win = 80;


    std::vector<std::string> settimana = {"Lun 3", "Mar 4", "Mer 5", "Gio 6", "Ven 7", "Sab 8", "Dom 9"};
    std::vector<std::string> orario_iniziale = {"8:00", "9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00"};
   while (true) {
       clear();
       for (int i=0; i<=6; i++) {
           int posizione_giorni = 8 + (i * 10);
           mvprintw(1, posizione_giorni, "%s", settimana[i].c_str());
           mvvline(2, posizione_giorni-0.5, '|', 24);
       }


       int y = 2;
       mvhline(3, 0, '-', 80);
       for (int i=0; i<=11; i++) {
           mvprintw(y, 0, "%s", orario_iniziale[i].c_str());
           mvhline(y+1, 0, '-', 80 );
           y = y + 2;
       }
       for (h=0; h<12; h++) {
           for (g=0; g<7; g++) {
               y_schermo = 2 + (h * 2);
               x_schermo = 8 + (g * 10);

               if (h == ora_selezionata && g == giorno_selezionato) {
                   attron(A_REVERSE);
               }
               if (tabella[h][g] == "") {
                   // Se la casella è vuota, disegno il puntino
                   mvprintw(y_schermo, x_schermo, "  .  ");
               } else {
                   // Se c'è testo salvato, disegno un asterisco o un simbolo!
                   mvprintw(y_schermo, x_schermo, "[ * ]");
               }

               attroff(A_REVERSE);
           }
       }
       refresh();
       int tasto = getch();
       if (tasto == 27) break;
       if (tasto == KEY_RIGHT) {
           giorno_selezionato++;
       }
       if (tasto == KEY_LEFT) {
           giorno_selezionato--;
       }
       if (tasto == KEY_DOWN) {
           if (ora_selezionata<12) ora_selezionata++;
       }
       if (tasto == KEY_UP) {
           if (ora_selezionata>0) ora_selezionata--;
       }

       std:: string current_activity = tabella[ora_selezionata][giorno_selezionato];
       WINDOW *win = newwin(h_win, l_win, y_win, x_win);
       box(win, 0, 0);
       if (tasto == 10) {
           if (current_activity == " . " || current_activity == "") {
               echo();
               curs_set(1);
               char buffer[100];

               mvwprintw(win, 1, 1 , "Aggiungi descrizione attivita':");
               wrefresh(win);
               mvwgetnstr(win, 2, 2, buffer, 99);

               std::string testo_finale = std::string(buffer);

               if (!testo_finale.empty()) {
                   tabella[ora_selezionata][giorno_selezionato] = testo_finale;
               }
               noecho();
               curs_set(0);
           } else {

                   mvwprintw(win, 1, 2, "Dettagli attivita':");
                   mvwprintw(win, 2, 2, "%s", current_activity.c_str());
                   wrefresh(win);
                   wgetch(win);
               }
               delwin(win);
               clear();
           }
       }



    endwin();
    return 0;
}


