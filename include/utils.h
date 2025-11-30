#ifndef UTILS_H
#define UTILS_H


#include <stdbool.h>
#include <stddef.h>

//0_01_020_0x2E0x68
/*
0 = root-dir
01 = include
020 = utils
0x2E0x68 = .h
*/

void utils_terminal_input_handler(void);
void utils_terminal_parse_command(const char *input);

bool utils_path0_02_020_0x2E0x63_data_1(const char *x0_data_1);
bool utils_path0_02_020_0x2E0x63_file_1_data_1(const char *x0_data_1_file_1);
bool process_colors_file(const char *filepath);

short parse_color(const char *color_str);

extern char COLOR_STRIP1[64]; 
extern char COLOR_LOGO1[64];
extern char COLOR_MENU1[64];
extern char COLOR_TERMINAL1[64];
extern char COLOR_TIME1[64];
extern char COLOR_DATE1[64];
extern char LOGO_TEXT[256];

#endif


