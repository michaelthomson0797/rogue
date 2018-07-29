#include "global.h"

int main() {
    MapGrid* map = mkMapGrid();


    Creature* player = map->player;


    map->grid[player->c_pos.x][player->c_pos.y]->creature = player;

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
                if(map->grid[player->c_pos.x-1][player->c_pos.y]->tile->passable) {
                    mvCreature(map, player, player->c_pos.x-1, player->c_pos.y);
                }
                break;
            case KEY_RIGHT:
                if(map->grid[player->c_pos.x+1][player->c_pos.y]->tile->passable) {
                    mvCreature(map, player, player->c_pos.x+1, player->c_pos.y);
                }
                break;
            case KEY_UP:
                if(map->grid[player->c_pos.x][player->c_pos.y-1]->tile->passable) {
                    mvCreature(map, player, player->c_pos.x, player->c_pos.y-1);
                }
                break;
            case KEY_DOWN:
                if(map->grid[player->c_pos.x][player->c_pos.y+1]->tile->passable) {
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
