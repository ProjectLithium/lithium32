#include "shell.h"
#include <std/stdio.h>
#include <std/string.h>
#include <drivers/devices/time/pit.h>
#include <drivers/devices/time/rtc.h>
#include <drivers/io/cpuid.h>
#include "util.h"

const char* ascii_art[] = {
    "                    ~G7        ",
    "                .~JB@@P        ",
    "            :!JG&@@@@@7        ",
    "         .7G&@@@@@@&P!         ",
    "        ~#@# @@@@@##Y          ",
    "     :GGGP  &@@@@@@@5.         ",
    "    ~&#  G@@@@@@@&P~           ",
    "   :G? G@@@@&#GY!:             ",
    "   ~^ #####B57:                ",
    "   ##J: ...                    ",
    "  # .                          ",
    NULL
};


static const char* months[] = {
    "January",   // Index 0
    "February",  // Index 1
    "March",     // Index 2
    "April",     // Index 3
    "May",       // Index 4
    "June",      // Index 5
    "July",      // Index 6
    "August",    // Index 7
    "September", // Index 8
    "October",   // Index 9
    "November",  // Index 10
    "December"   // Index 11
};

uint8_t handle_command(char* cmd)
{
    char** parsed = split(cmd);
    
    char* command = parsed[0];

    if (!command || strlen(command) == 0)
    {
        return 1;
    }

    if (strcmp(command, "echo"))
    {
        printf("%s\n", join(parsed, ' '));
    } else if (strcmp(command, "help")) {
        printf("\nList of commands:\n\thelp \t\t\t - get this text\n\techo [text]  - print some text\n\ttime \t\t\t - get current date and time\n\tslobodafetch - just like neofetch but as dumb as sloboda is\n\tclear \t\t\t - clear screen\n\n");
    } else if (strcmp(command, "time")) {
        rtc_time_t time = rtc_get_time();
        uint8_t day, month, year, hours, minutes, seconds;

        printf("%d %s 20%d\t\t%d:%d:%d\n", 
            time.day, months[time.month - 1], time.year, time.hours, time.minutes, time.seconds);
    } else if (strcmp(command, "slobodafetch")) {
        char* cpu_name = cpuid_get_cpu_name();
        const char* info_prefixes[] = {
            "OS: ",
            "Shell: ",
            "CPU: ",
            NULL
        };
        const char* info[] = {
            "LithiumOS x86_32",
            "LithiumOS built-in shell v0.0.1",
            cpu_name,
            NULL
        };
        printf("\n");
        bool stop = false;
        for (int i = 0; ascii_art[i] != NULL; i++)
        {
            if (info_prefixes[i] == NULL)
            {
                stop = true;
            }
            if (!stop)
                printf("%s%s%s\n", ascii_art[i], info_prefixes[i], info[i]);
            else
                printf("%s\n", ascii_art[i]);
        }
        printf("\n");
    } else if (strcmp(command, "clear")) {
        clear();
    } else {
        printf("Unknown command %s\n", command);
        return 1;
    }
    return 0;
}

void shell_run()
{
    printf("\nLithiumOS built-in shell v0.0.1\nType help for list of commands\n\n");
    while (1)
    {
        if (pit_get_time() % 2 == 0)
        {
            printf("shell# ");
            char* cmd = scan();
            handle_command(cmd);

            uint32_t start = pit_get_time();
            while (pit_get_time() - start < 3) {
                // busy-wait
            }
        }
    }
}