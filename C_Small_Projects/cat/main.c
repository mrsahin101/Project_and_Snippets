#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define OPTION_LIST_LENGTH                      25
#define OPTION_LIST_CHARACTER_LENGTH            25
#define SUPPORTED_MAX_FILE_COUNT                25
#define SUPPORTED_MAX_FILENAME_LENGTH           255
enum errCodes
{
    NO_ARGUMENTS = 1,
    UNKNOWN_ARGUMENT = 2,
    FILE_DOESNT_EXIST = 3,
    IT_IS_DIRECTORY = 4,
    NO_SUCH_FILE_OR_DIRECTORY = 5,
    HELP_OPT_CALLED = 6,
    VERSION_OPT_CALLED = 7,
    ERR_OCCRED_DURING_FILE_OPENING = 8,

};
const char option_list[OPTION_LIST_LENGTH][OPTION_LIST_CHARACTER_LENGTH] =
{
    "-A", "--show-all", "-vET",         // 0, 1, 2              -> 0        // opt_show_all
    "-b", "--number-nonblank",          // 3, 4                 -> 1        // opt_numbers_nonblank
    "-e", "-vE",                        // 5, 6                 -> 2        // opt_show_ends1
    "-E", "--show-ends",                // 7, 8                 -> 3        // opt_show_ends2
    "-n", "--number",                   // 9, 10                -> 4        // opt_number_all_lines
    "-s", "--squeeze-blank",            // 11, 12               -> 5        // opt_suppress_empty_lines
    "-t", "-vT",                        // 13, 14               -> 6        // opt_display_tab1
    "-T", "--show-tabs",                // 15, 16               -> 7        // opt_display_tab2
    "-u",                               // 17                   -> 8        // opt_u_ignored
    "-v", "--show-nonprinting",         // 18, 19               -> 9        // opt_show_no_printing
    "--help",                           // 20                   -> 10       // opt_help
    "--version",                        // 21                   -> 11       // opt_version
};
struct __opt
{
    bool opt_show_all;
    bool opt_numbers_nonblank;
    bool opt_show_ends1;
    bool opt_show_ends2;
    bool opt_number_all_lines;
    bool opt_suppress_empty_lines;
    bool opt_display_tab1;
    bool opt_display_tab2;
    bool opt_u_ignored;
    bool opt_show_no_printing;
    bool opt_help;
    bool opt_version;
    uint32_t opts_status_word;
    char fileArray[SUPPORTED_MAX_FILE_COUNT][SUPPORTED_MAX_FILENAME_LENGTH];
    int fileCountIndex;
}options_status;
void option_handler(int index)
{
    switch(index)
    {
        case 0:
        case 1:
        case 2:
            options_status.opt_show_all = true;
            break;
        case 3:
        case 4:
            options_status.opt_numbers_nonblank = true;
            options_status.opt_number_all_lines = false;
            break;
        case 5:
        case 6:
            options_status.opt_show_ends1 = true;
            break;
        case 7:
        case 8:
            options_status.opt_show_ends2 = true;
            break;
        case 9:
        case 10:
            options_status.opt_number_all_lines = true;
            break;
        case 11:
        case 12:
            options_status.opt_suppress_empty_lines = true;
            break;
        case 13:
        case 14:
            options_status.opt_display_tab1 = true;
            break;
        case 15:
        case 16:
            options_status.opt_display_tab2 = true;
            break;
        case 17:
            options_status.opt_u_ignored = true;
            break;
        case 18:
        case 19:
            options_status.opt_show_no_printing = true;
            break;
        case 20:
            options_status.opt_help = true;
            break;
        case 21:
            options_status.opt_version = true;
            break;
    }   
}
void check_if_file_exist(char *path)
{
    struct stat pathInfo;
    stat(path, &pathInfo);
    if(access(path, F_OK) == 0)
    {
        if(S_ISREG(pathInfo.st_mode))
        {
            memcpy(options_status.fileArray[options_status.fileCountIndex++], path, strlen(path) + 1);
        }
        else
        {
            printf("cat : \'%s\':Is a directory\n",path);
            exit(IT_IS_DIRECTORY);
        }
    }
    else
    {
        printf("cat: \'%s\':No such file or directory\n", path);
        exit(NO_SUCH_FILE_OR_DIRECTORY);
    }

}
void parse_input_args(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage : cat [OPTION]... [FILE]...\n");
        printf("Try 'cat --help' for more information\n");
        exit(NO_ARGUMENTS);
    }
    for(int i = 1; i < argc; i++)
    {
        bool matchFound = false;
        // search for options
        if(argv[i][0] == '-')   // its option
        {
            for(int j = 0; j < OPTION_LIST_LENGTH; j++)
            {
                if(strcmp(argv[i], option_list[j]) == 0)
                {
                    matchFound = true;
                    option_handler(j);
                }
            }
            if(matchFound == false)
            {
                printf("cat: Invalid option \'%s\'\n", argv[i]);
                printf("Try 'cat --help' for more information\n");
                exit(UNKNOWN_ARGUMENT);
            }
        }
        else    // it must be file name
        {   
            check_if_file_exist(argv[i]);
        }
    }
}
void option_struct_init(void)
{
    options_status.opt_show_all = false;
    options_status.opt_numbers_nonblank = false;
    options_status.opt_show_ends1 = false;
    options_status.opt_show_ends2 = false;
    options_status.opt_number_all_lines = false;
    options_status.opt_suppress_empty_lines = false;
    options_status.opt_display_tab1 = false;
    options_status.opt_display_tab2 = false;
    options_status.opt_u_ignored = false;
    options_status.opt_show_no_printing = false;
    options_status.opt_help = false;
    options_status.opt_version = false;
    options_status.opts_status_word = 0x0;
    options_status.fileCountIndex = 0;
    for(int i = 0; i < SUPPORTED_MAX_FILE_COUNT; i++)
    {
        for(int j = 0; j < SUPPORTED_MAX_FILENAME_LENGTH; j++)
        {
            options_status.fileArray[i][j] = ' ';
        }
    }
}
void print_version(void)
{
    printf("cat (myUtils) 1.00\n");
    printf("Copyright (C) 2023 Free Software\n");
    printf("There is no license.\n");
    printf("This is free software: you are free to change and redistribute it\n");
    printf("There is NO WARRANTY, to the extend permitted by myself:D\n\n");
    printf("Written by mrsahin101\n");
}
void print_help(void)
{
    printf("Usage : cat [OPTION]...[FILE]...\n");
    printf("Concatenate FILE(s) to standart output.\n\n");
    printf("With no FILE, or when FILE is -, read standart input.\n\n");
    printf("  %-20s\t\t\tequivalent to -vET\n", "-A, --show-all");
    printf("  %-20s\t\t\tnumber nonempty output lines, overrides -n\n", "-b, --number-nonblank");
    printf("  %-20s\t\t\tequivalent to -vE\n","-e");
    printf("  %-20s\t\t\tdisplay $ at end of each line\n", "-E, --show-ends");
    printf("  %-20s\t\t\tnumber all output lines\n", "-n, --number");
    printf("  %-20s\t\t\tsuppress repeated empty output lines\n", "-s, --squeeze-blank");
    printf("  %-20s\t\t\tequivalent to -vT\n", "-t");
    printf("  %-20s\t\t\tdisplay TAB characters as ^I\n", "-T, --show-tabs");
    printf("  %-20s\t\t\t(ignored)\n", "-u");
    printf("  %-20s\t\t\tuse ^ and M- notation, except for LFD and TAB\n", "-v, --show-noprinting");
    printf("       %-16s\t\t\tdisplay the help and exit\n", "--help");
    printf("       %-16s\t\t\toutput version information and exit\n", "--version");

    printf("Examples:\n");
    printf("  %-20s\t\t\tOutput f's contents, then standart input, then g's contents.\n", "cat f - g");
    printf("  %-20s\t\t\tCopy standart input to standart output\n\n", "cat");

    printf("Unfourtunately there is no documentation or Online help\n");

}
void handle_options(void)
{
    if(options_status.opt_version)
    {
        print_version();
        exit(VERSION_OPT_CALLED);
    }
    if(options_status.opt_help)
    {
        print_help();
        exit(HELP_OPT_CALLED);
    }
    
}
void handle_files()
{
    for(int i = 0; i < options_status.fileCountIndex; i++)
    {
        FILE *f = fopen(options_status.fileArray[i], "r");
        if(f == NULL)
        {
            printf("Unexpected error occured during opening %s file\n", options_status.fileArray[i]);
            exit(ERR_OCCRED_DURING_FILE_OPENING);
        }
        int n = 1;
        bool isblankline = false;
        bool isprevnewline = true;
        int nb = 1;
        do
        {
            if(n == 1 && options_status.opt_number_all_lines == true && options_status.opt_numbers_nonblank == false)
                printf("%6d  ", n++);
            
            char c = fgetc(f);
            // if(nb == 1 && options_status.opt_numbers_nonblank == true && c != '\n')
            //     printf("%6d  ", nb++);
            if(feof(f))
                break;
            switch(c)
            {
                case '\n':
                    if(options_status.opt_show_all || options_status.opt_show_ends1 || options_status.opt_show_ends2)
                        printf("%c", '$');
                    printf("\n");

                    
                    if(options_status.opt_numbers_nonblank == false && options_status.opt_number_all_lines == true)
                    {
                        printf("%6d  ", n++);
                    }
                    isprevnewline = true;
                    break;
                case '\t':
                    if(options_status.opt_show_all == true|| options_status.opt_display_tab1 == true || options_status.opt_display_tab2  == true)
                        printf("^I");
                    else
                        printf("\t");
                    break;
                default:
                    if(options_status.opt_numbers_nonblank == true && isprevnewline == true)
                        printf("%6d  ", nb++);
                    printf("%c",c);
                    isblankline = false;
                    isprevnewline = false;
            }
            
        } while (1);
    }
}
void handle_status()
{
    handle_options();
    handle_files();
}
int main(int argc, char *argv[])
{
    option_struct_init();
    parse_input_args(argc, argv);
    handle_status();
}