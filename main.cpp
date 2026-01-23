#include <curses.h>
#include <string>
#include <vector>

int main() {
    initscr();
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
    std::vector<std::string> settimana = {"Lun 3", "Mar 4", "Mer 5", "Gio 6", "Ven 7", "Sab 8", "Dom 9"};
    std::vector<std::string> orario_iniziale = {"8:00", "9:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00", "18:00", "19:00", "20:00", "21:00"};
   while (true){
       clear();
    for (int i=0; i<=6; i++) {
       int posizione_giorni = 8 + (i * 10);
       mvprintw(1, posizione_giorni, "%s", settimana[i].c_str());
       mvvline(2, posizione_giorni-0.5, '|', 30);
   }


   int y = 2;
    for (int i=0; i<=13; i++) {
       mvprintw(y, 0, "%s", orario_iniziale[i].c_str());
        y = y + 2;
        mvhline(3, 0, '-', 80);
        mvhline(y+1, 0, '-', 80 );
   }
       for (h=0; h<14; h++) {
            for (g=0; g<7; g++) {
                y_schermo = 2 + (h * 2);
                x_schermo = 8 + (g * 10);

                if (h == ora_selezionata && g == giorno_selezionato) {
                    attron(A_REVERSE);
                }
                mvprintw(y_schermo, x_schermo, "  .  ");
                attroff(A_REVERSE);
            }
        }
       refresh();
        int tasto = getch();
        if (tasto == 'q') break;
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
    }

    endwin();
    return 0;
}


