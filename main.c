#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define SIZE 9

int *build();

void zeiger();

int timer(int, int, int, int, int, int);

void spiel();

void check();

int fehlerAnzahl();

int alleAusgefuellt();

int end();


int gitter[SIZE][SIZE] = {{4, 1, 0, 0, 6, 5, 0, 0, 7},
                          {0, 0, 6, 0, 0, 7, 4, 8, 0},
                          {2, 0, 7, 4, 9, 0, 0, 0, 6},
                          {0, 6, 0, 0, 7, 0, 1, 0, 0},
                          {3, 0, 1, 5, 0, 0, 0, 7, 2},
                          {0, 9, 0, 0, 4, 2, 3, 0, 8},
                          {1, 0, 8, 6, 0, 0, 0, 2, 9},
                          {0, 2, 0, 0, 1, 8, 6, 4, 0},
                          {6, 0, 0, 3, 0, 0, 0, 1, 0}
};
int antwort[SIZE][SIZE];
int resultat[SIZE][SIZE] = {{0},
                            {0}};


int main() {
    spiel();
    return 0;
}


//int *build(int difficulty) {
//    int gitter[9][9];  //Definieren das Gitter
//    int *pointer_to_gitter = &gitter;   //Der Zeiger zum Gitter für Rückgabe
//    for (int i = 0; i < 10; i++) {
//        // Definieren 4 Randomzahlen, die leere Plätze zeigen und zwischen 1 und 9 sind
//        randA:
//        int a = rand() % 10;
//        if (a == 0)
//            goto randA;
//        randB:
//        int b = rand() % 10;
//        if (b == 0)
//            goto randB;
//        randC:
//        int c = rand() % 10;
//        if (c == 0)
//            goto randC;
//        randD:
//        int d = rand() % 10;
//        if (d == 0)
//            goto randD;
//        for (int j = 0; j < 10; j++) {
//            if (j == a || j == b || j == c || j == d)
//                gitter[i][j]=0;
//            gitter[i][j] = rand() % 10;
//        }
//    }
//}

int timer(int startSekunde, int startMinute, int startStunde, int neuSekunde, int neuMinute, int neuStunde) {
    int restStde = 0, restMin = 0, restSek = 0, sekundenSumme = 0;
    time_t now;
    struct tm *tm;
    if ((tm = localtime(&now)) == NULL) {
        printf("Error extracting time stuff\n");
        return -1;
    }
    if ((neuSekunde - startSekunde) >= 0)
        restSek = neuSekunde - startSekunde;
    else {
        startMinute -= 1;
        startSekunde += 60;
        restSek = neuSekunde - startSekunde;
    }
    if ((neuMinute - startMinute) >= 0)
        restMin = neuMinute - startMinute;
    else {
        startStunde -= 1;
        startMinute += 60;
        restMin = neuMinute - startMinute;
    }
    if ((neuStunde - startStunde) >= 0)
        restStde = neuStunde - startStunde;
    else
        return -1;
    sekundenSumme = restSek + (restMin * 60) + ((restStde * 60) * 60);
    return sekundenSumme;
}

void zeiger() {
    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0) {
            ///// prints a horizontal line
            for (int k = 0; k < 30; ++k) {
                printf("%c", '-');
            }
            printf("\n");
        }
        for (int j = 0; j < SIZE; ++j) {
            if (j % 3 == 0)
                printf("%c", '|');
            if (antwort[i][j] != 0)
                if (gitter[i][j] == 0)
                    printf(ANSI_COLOR_BLUE" %d " ANSI_COLOR_RESET, antwort[i][j]);
                else
                    printf(" %d ", antwort[i][j]);
            else if (antwort[i][j] == 0)
                printf("   ");
        }
        printf("%c\n", '|');
    }

    ///// prints a horizontal line
    for (int k = 0; k < 30; ++k) {
        printf("%c", '-');
    }
}

void spiel() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            antwort[i][j] = gitter[i][j];
        }
    }
    ////////counting time
    time_t now;
    struct tm *tm;
    now = time(0);
    if ((tm = localtime(&now)) == NULL) {
        printf("Error extracting time stuff\n");
    }
    int startStunde = tm->tm_hour;
    int startMin = tm->tm_min;
    int startSek = tm->tm_sec;
    printf(ANSI_COLOR_CYAN"\nChronometer startet. %d Sekunden\n"ANSI_COLOR_RESET,
           timer(startSek, startMin, startStunde, tm->tm_sec, tm->tm_min, tm->tm_hour));
    ////////
    zeiger();
    int wert, zeile, spalte;
    while (!end()) {
        eingeben:
        printf("\nWert: ");
        scanf("%d", &wert);
        /////
        if (wert == 1000) {
            check();
            goto eingeben;
        }
        //////
        printf("\nZeile: ");
        scanf("%d", &zeile);
        printf("\nSpalte: ");
        scanf("%d", &spalte);
        if (wert == 0) {
            antwort[zeile - 1][spalte - 1] = 0;
            ////////counting time
            now = time(0);
            tm = localtime(&now);
            printf(ANSI_COLOR_CYAN"\nZeit: %d Sekunden\n"ANSI_COLOR_RESET,
                   timer(startSek, startMin, startStunde, tm->tm_sec, tm->tm_min, tm->tm_hour));
            ////////
            zeiger();
            goto eingeben;
        }
        if (wert < 0 || wert > 9 || zeile < 1 || zeile > 9 || spalte < 1 || spalte > 9) {
            printf("Die Eingaben muessen zwischen 1 und 9 sein! ");
            goto eingeben;
        } else {
            if (gitter[zeile - 1][spalte - 1] != 0) {
                printf("Default Werte dürfen nicht übergeschrieben werden!\n\n");
                ////////counting time
                now = time(0);
                tm = localtime(&now);
                printf(ANSI_COLOR_CYAN"\nZeit: %d Sekunden\n"ANSI_COLOR_RESET,
                       timer(startSek, startMin, startStunde, tm->tm_sec, tm->tm_min, tm->tm_hour));
                ////////
                zeiger();
                goto eingeben;
            }
        }
        antwort[zeile - 1][spalte - 1] = wert;
        ////////counting time
        now = time(0);
        tm = localtime(&now);
        printf(ANSI_COLOR_CYAN"\nZeit: %d Sekunden\n"ANSI_COLOR_RESET,
               timer(startSek, startMin, startStunde, tm->tm_sec, tm->tm_min, tm->tm_hour));
        ////////
        zeiger();
    }
}

void check() {
    int wuerfelZeile, wuerfelSpalte;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            resultat[i][j] = 0;
        }
    }
    for (int zeile = 0; zeile < SIZE; ++zeile) {
        for (int spalte = 0; spalte < SIZE; ++spalte) {
            if (gitter[zeile][spalte] == 0)
                if (antwort[zeile][spalte] != 0) {
                    for (int counter = 0; counter < SIZE; ++counter) {
                        if (antwort[counter][spalte] == antwort[zeile][spalte] && counter != zeile) {
                            resultat[zeile][spalte] = 1;
                            continue;
                        }
                    }
                    for (int counter = 0; counter < SIZE; ++counter) {
                        if (antwort[zeile][counter] == antwort[zeile][spalte] && counter != spalte) {
                            resultat[zeile][spalte] = 1;
                            continue;
                        }
                    }
                    wuerfelZeile = zeile / 3;
                    wuerfelSpalte = spalte / 3;
                    for (int i = wuerfelZeile * 3; i < wuerfelZeile * 3 + 3; ++i) {
                        for (int j = wuerfelSpalte * 3; j < wuerfelSpalte * 3 + 3; ++j) {
                            if (antwort[zeile][spalte] == antwort[i][j] && !(zeile == i && spalte == j)) {
                                resultat[zeile][spalte] = 1;
                                goto found;
                            }
                        }
                    }
                    found:;
                }
        }
    }
    ////// print
    for (int i = 0; i < SIZE; ++i) {
        if (i % 3 == 0) {
            ///// prints a horizontal line
            for (int k = 0; k < 30; ++k) {
                printf("%c", '-');
            }
            printf("\n");
        }
        for (int j = 0; j < SIZE; ++j) {
            if (j % 3 == 0)
                printf("%c", '|');
            if (gitter[i][j] != 0)  ////normale Zahlen
                printf(" %d ", antwort[i][j]);
            else if (antwort[i][j] == 0)   //// leere Plaetze
                printf("   ");
            else if (resultat[i][j] == 1)   //// falsch
                printf(ANSI_COLOR_RED" %d " ANSI_COLOR_RESET, antwort[i][j]);
            else    //// nicht ueberprueft
                printf(ANSI_COLOR_GREEN" %d " ANSI_COLOR_RESET, antwort[i][j]);
        }
        printf("%c\n", '|');
    }

    ///// prints a horizontal line
    for (int k = 0; k < 30; ++k) {
        printf("%c", '-');
    }
}

int alleAusgefuellt() {  // gibt 0: Es gibt noch leere Plaetze  1: alle ausgefuellt
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (gitter[i][j] == 0)
                if (antwort[i][j] == 0)
                    return 0;
        }
    }
    return 1;
}

int fehlerAnzahl() {
    int fehler = 0, wuerfelZeile, wuerfelSpalte;
    for (int zeile = 0; zeile < SIZE; ++zeile) {
        for (int spalte = 0; spalte < SIZE; ++spalte) {
            if (gitter[zeile][spalte] == 0)
                if (antwort[zeile][spalte] != 0) {
                    for (int counter = 0; counter < SIZE; ++counter) {
                        if (antwort[counter][spalte] == antwort[zeile][spalte] && counter != zeile) {
                            fehler++;
                            continue;
                        }
                    }
                    for (int counter = 0; counter < SIZE; ++counter) {
                        if (antwort[zeile][counter] == antwort[zeile][spalte] && counter != spalte) {
                            fehler++;
                            continue;
                        }
                    }
                    wuerfelZeile = zeile / 3;
                    wuerfelSpalte = spalte / 3;
                    for (int i = wuerfelZeile * 3; i < wuerfelZeile * 3 + 3; ++i) {
                        for (int j = wuerfelSpalte * 3; j < wuerfelSpalte * 3 + 3; ++j) {
                            if (antwort[zeile][spalte] == antwort[i][j] && !(zeile == i && spalte == j)) {
                                fehler++;
                                goto found;
                            }
                        }
                    }
                    found:;
                }
        }
    }
    return fehler;
}

int end() {
    if (alleAusgefuellt())
        if (fehlerAnzahl() == 0)
            return 1;
        else return 0;
    else return 0;
}