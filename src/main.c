#include "global.h"

int main() {
    MapGrid* map = mkMapGrid();

    Creature* player = map->player;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);


    updateVisibility(map);
    printMapGrid(map);
    refresh();

    int ch;

    while((ch = getch()) != KEY_F(1)) {

        switch(ch) {
            case KEY_LEFT:
                if(isPassable(map->grid[player->c_pos.x-1][player->c_pos.y])) {
                    mvCreature(map, player, player->c_pos.x-1, player->c_pos.y);
                }
                break;
            case KEY_RIGHT:
                if(isPassable(map->grid[player->c_pos.x+1][player->c_pos.y])) {
                    mvCreature(map, player, player->c_pos.x+1, player->c_pos.y);
                }
                break;
            case KEY_UP:
                if(isPassable(map->grid[player->c_pos.x][player->c_pos.y-1])) {
                    mvCreature(map, player, player->c_pos.x, player->c_pos.y-1);
                }
                break;
            case KEY_DOWN:
                if(isPassable(map->grid[player->c_pos.x][player->c_pos.y+1])) {
                    mvCreature(map, player, player->c_pos.x, player->c_pos.y+1);
                }
                break;
        }
        updateVisibility(map);
        printMapGrid(map);
        refresh();
    }


    endwin();

    return 0;
}
