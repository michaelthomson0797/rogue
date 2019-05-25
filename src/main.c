#include "global.h"

void handleInput(int ch) {
    switch (ch)
    {
        case KEY_LEFT:
            if (isPassable(map->grid[player->pos.x - 1][player->pos.y]))
            {
                mvCreature(map, player, player->pos.x - 1, player->pos.y);
            }
            break;
        case KEY_RIGHT:
            if (isPassable(map->grid[player->pos.x + 1][player->pos.y]))
            {
                mvCreature(map, player, player->pos.x + 1, player->pos.y);
            }
            break;
        case KEY_UP:
            if (isPassable(map->grid[player->pos.x][player->pos.y - 1]))
            {
                mvCreature(map, player, player->pos.x, player->pos.y - 1);
            }
            break;
        case KEY_DOWN:
            if (isPassable(map->grid[player->pos.x][player->pos.y + 1]))
            {
                mvCreature(map, player, player->pos.x, player->pos.y + 1);
            }
            break;
    }
}

int main()
{
    map = mkMapGrid();

    player = map->player;

    map->grid[player->pos.x][player->pos.y]->creature = player;

    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    updateVisibility(map);
    printMapGrid(map);
    refresh();

    int ch;

    while ((ch = getch()) != KEY_F(1))
    {
        handleInput(ch);
        
        updateVisibility(map);
        printMapGrid(map);
        refresh();
    }

    endwin();

    return 0;
}