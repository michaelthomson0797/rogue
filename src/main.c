#include "global.h"

int main() {
    char filename[] = "test";
    MapGrid* map = mkMapGrid(filename);
    //printMapGrid(map);

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    int running = 1;
    int playerx = 1;
    int playery = 1;
    map->grid[playerx][playery]->playerPresent=1;
    printMapGrid(map);
    refresh();

    int ch;

    while((ch = getch()) != KEY_F(1)) {

        switch(ch) {
            case KEY_LEFT:
                map->grid[playerx][playery]->playerPresent=0;
                map->grid[--playerx][playery]->playerPresent=1;
                break;
            case KEY_RIGHT:
                map->grid[playerx][playery]->playerPresent=0;
                map->grid[++playerx][playery]->playerPresent=1;
                break;
            case KEY_UP:
                map->grid[playerx][playery]->playerPresent=0;
                map->grid[playerx][--playery]->playerPresent=1;
                break;
            case KEY_DOWN:
                map->grid[playerx][playery]->playerPresent=0;
                map->grid[playerx][++playery]->playerPresent=1;
                break;
        }
        printMapGrid(map);
        refresh();
    }


    endwin();

    return 0;
}
