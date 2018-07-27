#include "global.h"

int main() {
    char filename[] = "test";
    MapGrid* map = mkMapGrid(filename);
    CreatureGrid* creaturegrid = mkCreatureGrid();

    Creature* player = map->player;
    creaturegrid->grid[player->c_pos.x][player->c_pos.y] = player;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    printMapGrid(map);
    printCreatureGrid(creaturegrid);
    refresh();

    int ch;

    while((ch = getch()) != KEY_F(1)) {

        switch(ch) {
            case KEY_LEFT:
                if(map->grid[player->c_pos.x-1][player->c_pos.y]->passable) {
                    creaturegrid->grid[player->c_pos.x--][player->c_pos.y] = NULL;
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y] = player;
                }
                break;
            case KEY_RIGHT:
                if(map->grid[player->c_pos.x+1][player->c_pos.y]->passable) {
                    creaturegrid->grid[player->c_pos.x++][player->c_pos.y] = NULL;
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y] = player;
                }
                break;
            case KEY_UP:
                if(map->grid[player->c_pos.x][player->c_pos.y-1]->passable) {
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y--] = NULL;
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y] = player;
                }
                break;
            case KEY_DOWN:
                if(map->grid[player->c_pos.x][player->c_pos.y+1]->passable) {
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y++] = NULL;
                    creaturegrid->grid[player->c_pos.x][player->c_pos.y] = player;
                }
                break;
        }
        printMapGrid(map);
        printCreatureGrid(creaturegrid);
        refresh();
    }


    endwin();

    return 0;
}
