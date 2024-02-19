#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define OPTIONS_LIST_LENGTH         255
#define OPTION_NAME_LENGTH          25
enum errorCodes
{
    NO_ARGUMENTS = 1,
};
struct __args
{
    bool filename_specified;
    char filename[255];
    bool option_provided;
}arguments;
struct _opt
{
    bool help_opt_provided;
    bool version_opt_provided;
    // Bit-wise to track which option is provided
    uint32_t first_opt_word;

}options;
enum opt_enum
{
    OPT_HELP = 0,
    OPT_VERSION = 1,
    OPT_EXTENDED_REGEXP = 2,
    OPT_FIXED_STRINGS = 3,
    OPT_BASIC_REGEXP = 4,
    OPT_PERL_REGEXP = 5,  
};
const char options_list[OPTIONS_LIST_LENGTH][OPTION_NAME_LENGTH] =
{       //Generic Program Information
        "--help",                           // 0            -> 0
        "-V", "--version",                  // 1,2          -> 1
        // Pattern Syntax
        "-E", "--extended-regexp",          // 3,4          -> 2
        "-F", "--fixed-strings",            // 5,6          -> 3
        "-G", "--basic-regexp",             // 7,8          -> 4
        "-P", "--perl-regexp",              // 9,10         -> 5
        // Matching Control
        "-e", "--regexp=",
        "-f", "--file="
        "-i", "--ignore-case",
        "--no-ignore-case",
        "-v", "--invert-match",
        "-w", "--word-regexp",
        "-x", "--line-regexp",
        // General Output Control
        "-c", "--count",
        "--color[=never]", "--color[=always]", "-color[=auto]", "--colour[=never]", "--colour[=always]", "colour[=auto]",
        "-L", "--files-without-match",
        "-l", "--files-with-matches",
        "-m", "--max-count=",
        "-o", "--only-matching",
        "-q", "--quiet", "--silent",
        "-s", "--no-messages",
        // Output Line Prefix Control
        "-b", "--byte-offset",
        "-H", "--with-filename",
        "-h", "--no-filename",
        "-label=",
        "-n", "--line-number",
        "-T", "--initial-tab",
        "-Z", "--null",
        // Control Line Control
        "-A", "--after-context=",
        "-B", "--before-context=",
        "-C", "--context=",
        "--group-separator=",
        "--no-group-separator",
        // FILE and Directory Selection
        "-a", "--text",
        "--binary-files=",
        "-D", "--devices=",
        "-d", "--directories",
        "--exclude",
        "--exclude-from",
        "-I",
        "--include",
        "-r", "--recursive",
        "-R", "--deference-recursive",
        // Other options
        "--line-buffered",
        "-U", "--binary",
        "-z", "--null-data",
}; 
void parse_input_args(int argc, char *argv[])
{
    if(argc < 2)
    {
        printf("Usage: grep [OPTION]... PATTERNS [FILE]...\n");
        printf("Try 'grep --help' for more information.\n");
        exit(NO_ARGUMENTS);
    }
    for(int i = 1; i < argc; i++)
    {
        for(int j = 0; j < OPTIONS_LIST_LENGTH; j++)
        {
            if(strcmp(options_list[j], argv[i]) == 0)
            {
                options.first_opt_word |= (1 << j -2);
                if(j == 0)
                    printf("Help asked\n");
                printf("%u", options.first_opt_word);
            }
        }
    }
    //check_options();
    //check_files();
}

int main(int argc, char *argv[])
{
    parse_input_args(argc, argv);
    //handle_input_args();
    //grep_and_print();
    //return_from_grep();
}