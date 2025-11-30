
#include <ncurses.h>
#include "ui.h" //0_01_010_0x2E0x68
#include "utils.h" //0_01_020_0x2E0x68
#include <string.h> 
#include <time.h>
#include <unistd.h>

//0_02_010_0x2E0x63

//ui_path0_02_010_0x2E0x63_fun_1
/*
0 = root-dir
02 = src
010 = ui
0x2E0x63 = .c
fun = fun  
1 = block(fun)
*/

//ui_path0_02_010_0x2E0x63_clear_1
void ui_path0_02_010_0x2E0x63_clear_1(void) {
    clear();
    refresh();
}

//ui_path0_02_010_0x2E0x63_strip_1
void ui_path0_02_010_0x2E0x63_strip_1(void) {
    short c = parse_color(COLOR_STRIP1);
    init_pair(1, c, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    mvhline(1, 0, ' ', COLS);
    mvhline(1, 0, ACS_HLINE, COLS);

    attroff(COLOR_PAIR(1));
    refresh();
}



void ui_path0_02_010_0x2E0x63_logo_1(void) {
    short c = parse_color(COLOR_LOGO1);
    init_pair(2, c, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    int left_margin = 1;
    int top_margin = 1;

    mvprintw(top_margin, left_margin, "[%s]", LOGO_TEXT);

    refresh();
}




static const char *MENU[] = {"categories", "statistics", "Notes"};
#define MENU_SIZE 3

void ui_path0_02_010_0x2E0x63_menu_1(void) {
    short c = parse_color(COLOR_MENU1);
    init_pair(3, c, COLOR_BLACK);
    attron(COLOR_PAIR(3));

    int max_len = 0;
    for (int i = 0; i < MENU_SIZE; i++) {
        int len = strlen(MENU[i]);
        if (len > max_len) max_len = len;
    }
    
    int left_margin = (COLS - max_len) / 2;
    int top_margin = LINES / 2 - MENU_SIZE / 2;

    for (int i = 0; i < MENU_SIZE; i++) {

        int current_len = strlen(MENU[i]);
        int padding = (max_len - current_len) / 2;
        mvprintw(top_margin + i, left_margin + padding, "%s", MENU[i]);
    }

    attroff(COLOR_PAIR(3));
    refresh();
}

static const char *TERMINAL[] = {">"};
#define TERMINAL_SIZE 1

void ui_path0_02_010_0x2E0x63_terminal_1(void) {
    short c = parse_color(COLOR_TERMINAL1);
    init_pair(4, c, COLOR_BLACK);
    attron(COLOR_PAIR(4));

    int start_y = LINES - TERMINAL_SIZE;

    for (int i = 0; i < TERMINAL_SIZE; i++) {
        mvprintw(start_y + i, 0, "%s", TERMINAL[i]);
    }

    refresh();
}



void ui_path0_02_010_0x2E0x63_date_1(void) {
    short c = parse_color(COLOR_DATE1);
    init_pair(5, c, COLOR_BLACK);
    attron(COLOR_PAIR(5));
    
    time_t raw_time;
    struct tm *time_info;
    char date_str[100];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(date_str, sizeof(date_str), "[%d.%m.%Y]", time_info);
    

    mvprintw(1, COLS - strlen(date_str) - 12, "%s", date_str);
    
    attroff(COLOR_PAIR(5));
    refresh();
} 

void ui_path0_02_010_0x2E0x63_time_1(void) {
    short c = parse_color(COLOR_TIME1);
    init_pair(6, c, COLOR_BLACK);
    attron(COLOR_PAIR(6));
    
    time_t raw_time;
    struct tm *time_info;
    char time_str[100];
    
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(time_str, sizeof(time_str), "[%H:%M:%S]", time_info);

    
    mvprintw(1, COLS - strlen(time_str) - 1, "%s", time_str);
    
    attroff(COLOR_PAIR(6));
    refresh();
}