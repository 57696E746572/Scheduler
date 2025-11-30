#include <ncurses.h>
#include <stddef.h>
#include "ui.h" 
#include "utils.h" 

int main(void) {
    initscr();          
    start_color();      
    noecho();           
    curs_set(0); 
    
    utils_path0_02_020_0x2E0x63_data_1("data");
    utils_path0_02_020_0x2E0x63_file_1_data_1("data/config");
    process_colors_file("data/config");
        
    
    ui_path0_02_010_0x2E0x63_clear_1(); 
    ui_path0_02_010_0x2E0x63_strip_1(); 
    ui_path0_02_010_0x2E0x63_logo_1();
    ui_path0_02_010_0x2E0x63_menu_1(); 
    ui_path0_02_010_0x2E0x63_terminal_1(); 
    ui_path0_02_010_0x2E0x63_date_1();
    ui_path0_02_010_0x2E0x63_time_1(); 
    

        

    while (1) {
        utils_terminal_input_handler();
    }

    endwin();
    return 0;
}
