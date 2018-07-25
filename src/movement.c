#include<curses.h>

int xpos;
int ypos;

int main() {

    int ch;
    xpos = 0;
    ypos = 0;

    initscr();
    cbreak();
    noecho();
    curs_set(0);

    keypad(stdscr, TRUE);

    mvaddch(ypos, xpos, '@');

    while((ch = getch()) != KEY_F(1))
    {
        switch(ch)
        {
            case KEY_LEFT:
                if(xpos-1 < 0) break;
                mvdelch(ypos, xpos);
                mvaddch(ypos, --xpos, '@');
                break;
            case KEY_RIGHT:
                if(xpos+1 > 49) break;
                mvdelch(ypos, xpos);
                mvaddch(ypos, ++xpos, '@');
                break;
            case KEY_UP:
                if(ypos-1 < 0) break;
                mvdelch(ypos, xpos);
                mvaddch(--ypos, xpos, '@');
                break;
            case KEY_DOWN:
                if(ypos+1 > 24) break;
                mvdelch(ypos, xpos);
                mvaddch(++ypos, xpos, '@');
                break;
        }
        refresh();
    }
    
    endwin();
    return 0;
}


