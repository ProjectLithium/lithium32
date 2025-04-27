#include "version.h"
#include <std/stdio.h>

const char* arch = "x86_32";
const char* version = "indev";
const char* edition = "git";

void print_version()
{
    printf("Lithium32 core %s-%s-%s\n", version, arch, edition);
}