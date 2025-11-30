#include "utils.h"
#include "ui.h" 
#include <sys/stat.h>
#include <sys/types.h>  
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>
#include <ncurses.h>

/*
0_02_020_0x2E0x63 //scheduler/src/utils.c
utils_path0_02_010_0x2E0x63_fun_1_requires_1

ROOT: 0 (scheduler) //root-dir
SRC:  02 (src) 
MOD:  020 (utils)
EXT:  0x2E0x63 (.c)
FUNC: fun_1 (function block 1)
REQ:  requires_1 (requirements block 1)
*/



bool utils_path0_02_020_0x2E0x63_data_1(const char *x0_data_1) {
    struct stat cd = {0};
    if (stat(x0_data_1, &cd) == -1) {
        if (mkdir(x0_data_1, 0755) != 0) return false;
    }
    return true;
}

/*
utils_path0_02_020_0x2E0x63_dir_1
requires - data_1 , data_..
*/



bool utils_path0_02_020_0x2E0x63_file_1_data_1(const char *x0_data_1_file_1) {
    FILE *cf = fopen(x0_data_1_file_1, "a");
    fclose(cf);
    return true;
    
}

/*
utils_path0_02_020_0x2E0x63_file_1_data_1
requires - file_1 , file_.. 
*/


char COLOR_STRIP1[64];
char COLOR_MENU1[64];
char COLOR_TERMINAL1[64];
char COLOR_LOGO1[64];
char COLOR_DATE1[64];
char COLOR_TIME1[64];
char LOGO_TEXT[256]; 

static void trim(char *s) {
    char *p = s;
    while (*p && isspace(*p)) p++;
    char *q = p + strlen(p) - 1;
    while (q > p && isspace(*q)) *q-- = '\0';
    memmove(s, p, strlen(p) + 1);
}

static void sanitize_value(char *val) {
    if (strcmp(val, "DEFAULT") != 0 &&
        strcmp(val, "RED") != 0 &&
        strcmp(val, "WHITE") != 0)
    {
        strcpy(val, "DEFAULT");
    }
}

bool process_colors_file(const char *filepath) {
    FILE *f = fopen(filepath, "r");
    if (!f) return false;

    char buffer[4096] = {0};
    size_t n = fread(buffer, 1, sizeof(buffer)-1, f);
    buffer[n] = '\0';
    fclose(f);

    char original[4096];
    memcpy(original, buffer, n+1);

    char strip_val[64] = "DEFAULT";
    char logo_val[64]  = "DEFAULT";
    char menu_val[64]  = "DEFAULT";
    char term_val[64]  = "DEFAULT";
    char date_val[64]  = "DEFAULT";
    char time_val[64]  = "DEFAULT";
    char logo_text_val[256] = "loooggo"; 


    char *line = strtok(buffer, "\n");
    while (line) {
        char *l = strchr(line, '[');
        char *r = strchr(line, ']');
        if (l && r && r > l) {
            char tmp[256]; 
            snprintf(tmp, sizeof(tmp), "%.*s", (int)(r - l - 1), l + 1);
            trim(tmp);

            if (strncmp(line, "strip", 5) == 0) {
                sanitize_value(tmp);
                strcpy(strip_val, tmp);
            }
            else if (strncmp(line, "logo", 4) == 0 && strstr(line, "logo_text") == NULL) {
                sanitize_value(tmp);
                strcpy(logo_val, tmp);
            }
            else if (strncmp(line, "logo_text", 9) == 0) {
                strcpy(logo_text_val, tmp);
            }
            else if (strncmp(line, "menu", 4) == 0) {
                sanitize_value(tmp);
                strcpy(menu_val, tmp);
            }
            else if (strncmp(line, "terminal", 8) == 0) {
                sanitize_value(tmp);
                strcpy(term_val, tmp);
            }
            else if (strncmp(line, "date", 4) == 0) {
                sanitize_value(tmp);
                strcpy(date_val, tmp);
            }
            else if (strncmp(line, "time", 4) == 0) {
                sanitize_value(tmp);
                strcpy(time_val, tmp);
            }
        }
        line = strtok(NULL, "\n");
    }

    // обновляем глобалы
    snprintf(COLOR_STRIP1,    sizeof(COLOR_STRIP1),    "COLOR_%s", strip_val);
    snprintf(COLOR_LOGO1,     sizeof(COLOR_LOGO1),     "COLOR_%s", logo_val);
    snprintf(COLOR_MENU1,     sizeof(COLOR_MENU1),     "COLOR_%s", menu_val);
    snprintf(COLOR_TERMINAL1, sizeof(COLOR_TERMINAL1), "COLOR_%s", term_val);
    snprintf(COLOR_DATE1,     sizeof(COLOR_DATE1),     "COLOR_%s", date_val);
    snprintf(COLOR_TIME1,     sizeof(COLOR_TIME1),     "COLOR_%s", time_val);
    strcpy(LOGO_TEXT, logo_text_val);

    char new_text[4096];
    snprintf(new_text, sizeof(new_text),
             "logo_text = [%s]\n"
             "strip = [%s]\n"
             "logo = [%s]\n"
             "menu = [%s]\n"
             "terminal = [%s]\n"
             "date = [%s]\n"
             "time = [%s]\n",       
             logo_text_val, strip_val, logo_val, menu_val, term_val, date_val, time_val);

    if (strcmp(original, new_text) != 0) {
        f = fopen(filepath, "w");
        if (!f) return false;
        fputs(new_text, f);
        fclose(f);
    }

    return true;
}

short parse_color(const char *color_str) {
    if (strcmp(color_str, "COLOR_WHITE") == 0) return COLOR_WHITE;
    if (strcmp(color_str, "COLOR_RED") == 0)   return COLOR_RED;
    return COLOR_WHITE;
}


void utils_terminal_input_handler(void) {
    char input[256] = {0};
    
    echo();
    curs_set(1);
    
    move(LINES - 1, 0);
    clrtoeol();
    printw(">");
    refresh();
    
    getnstr(input, sizeof(input) - 1);
    
    curs_set(0);
    noecho();
    
    if (strlen(input) > 0) {
        utils_terminal_parse_command(input);
    }
}

void utils_terminal_parse_command(const char *input) {
    if (strcmp(input, "help") == 0) {
        mvprintw(LINES - 2, 0, "Commands: help, clear, :q, :notes, :c name, :de name description");
        refresh();
        getch();
    }
    else if (strcmp(input, "clear") == 0) {
        clear();
        refresh();
    }
    else if (strcmp(input, ":q") == 0 || strcmp(input, "quit") == 0) {
        endwin();
        exit(0);
    }
    else if (strcmp(input, ":notes") == 0) {
        endwin();
        int ret = system("vim data/notes");
        (void)ret;
        printf("Returning to scheduler...\n");
        execlp("./scheduler", "./scheduler", NULL);
    }
    else if (strncmp(input, ":c ", 3) == 0) {
        const char *category_name = input + 3;
        
        if (strlen(category_name) == 0) {
            mvprintw(LINES - 2, 0, "Error: Enter category name after :c");
            refresh();
            getch();
            return;
        }
        
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);
        char date_str[20];
        strftime(date_str, sizeof(date_str), "[%Y-%m-%d]", tm_info);
        
        FILE *file = fopen("data/points", "r");
        int next_id = 1;
        
        if (file != NULL) {
            char line[256];
            int last_id = 0;
            
            while (fgets(line, sizeof(line), file)) {
                if (sscanf(line, "[%d]", &last_id) == 1) {
                    next_id = last_id + 1;
                }
            }
            fclose(file);
        }
        
        file = fopen("data/points", "a");
        if (file == NULL) {
            mvprintw(LINES - 2, 0, "Error: Cannot open data/points");
            refresh();
            getch();
            return;
        }
        
        fprintf(file, "[%d] %s %s\n", next_id, category_name, date_str);
        fclose(file);
        
        mvprintw(LINES - 2, 0, "Category '%s' added with ID %d", category_name, next_id);
        refresh();
        getch();
    }
else if (strncmp(input, ":de ", 4) == 0) {
    const char *args = input + 4;
    char category_name[100];
    char description[200];
    
    if (sscanf(args, "%99s %199[^\n]", category_name, description) != 2) {
        mvprintw(LINES - 2, 0, "Error: Use: :de name description");
        refresh();
        getch();
        return;
    }
    
    FILE *file = fopen("data/points", "r");
    if (file == NULL) {
        mvprintw(LINES - 2, 0, "Error: No categories found");
        refresh();
        getch();
        return;
    }
    
    char lines[100][512];
    int line_count = 0;
    int found = 0;
    
    while (fgets(lines[line_count], sizeof(lines[0]), file) && line_count < 100) {
        if (strstr(lines[line_count], category_name) != NULL) {
            char id_str[10], existing_date[20], existing_name[100];
            
            if (sscanf(lines[line_count], "[%9[^]]] %99s %19s", id_str, existing_name, existing_date) == 3) {
                if (strcmp(existing_name, category_name) == 0) {
                    snprintf(lines[line_count], sizeof(lines[0]), "[%s] %s (%s) %s\n", 
                            id_str, category_name, description, existing_date);
                    found = 1;
                }
            }
        }
        line_count++;
    }
    fclose(file);
    
    if (!found) {
        mvprintw(LINES - 2, 0, "Error: Category '%s' not found", category_name);
        refresh();
        getch();
        return;
    }
    
    file = fopen("data/points", "w");
    if (file == NULL) {
        mvprintw(LINES - 2, 0, "Error: Cannot write to data/points");
        refresh();
        getch();
        return;
    }
    
    for (int i = 0; i < line_count; i++) {
        fputs(lines[i], file);
    }
    fclose(file);
    
    mvprintw(LINES - 2, 0, "Description added to '%s'", category_name);
    refresh();
    getch();
    }
    else {
        mvprintw(LINES - 2, 0, "Unknown command: %s", input);
        refresh();
        getch();
    }
}