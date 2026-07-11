#include <stdio.h>
#include <string.h>

/* Detect if compiled for a 16-bit or 32-bit real/protected DOS target */
#if defined(__MSDOS__) || defined(__DOS__) || defined(_M_I86) || defined(__I86__)
    #include <dos.h>
    #define REAL_MODE_DOS 1
#endif

/* Fallback for cross-platform string comparison safely on different compilers */
#if !defined(REAL_MODE_DOS)
    #define stricmp strcasecmp
#endif

/* ANSI Escape Sequences for Color Text Layouts */
#define CLR_RESET   "\x1b[0m"
#define CLR_WHITE   "\x1b[1;37m"
#define CLR_GRAY    "\x1b[0;37m"
#define CLR_BLUE    "\x1b[1;34m"
#define CLR_GREEN   "\x1b[1;32m"
#define CLR_RED     "\x1b[1;31m"
#define CLR_CYAN    "\x1b[1;36m"
#define CLR_ATARI   "\x1b[1;35m"

/* 16-Bit IBM ASCII Code Page 437 Graphic Layout Logos */
void print_generic_dos() {
    printf(CLR_WHITE "   _____   ____   _____\n");
    printf("  |  __ \\ / __ \\ / ____|\n");
    printf("  | |  | | |  | | (___  \n");
    printf("  | |  | | |  | |\\___ \\ \n");
    printf("  | |__| | |__| |____) |\n");
    printf("  |_____/ \\____/|_____/ \n\n" CLR_RESET);
}

void print_msdos() {
    printf(CLR_BLUE "  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n", 201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187);
    printf("  %c  __  __  ____        _____   ____   %c\n", 186, 186);
    printf("  %c |  \\/  |/ ___|      |  __ \\ / __ \\  %c\n", 186, 186);
    printf("  %c | \\  / | (___ ______| |  | | |  | | %c\n", 186, 186);
    printf("  %c | |\\/| |\\___ \\______| |  | | |  | | %c\n", 186, 186);
    printf("  %c | |  | |____) |     | |__| | |__| | %c\n", 186, 186);
    printf("  %c |_|  |_|____/       |_____/ \\____/  %c\n", 186, 186);
    printf("  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n\n" CLR_RESET, 200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
}

void print_freedos() {
    printf(CLR_GREEN "   _______              _____   ____   _____\n");
    printf("  |  ____|            |  __ \\ / __ \\ / ____|\n");
    printf("  | |__ _ __ ___  ___ | |  | | |  | | (___\n");
    printf("  |  __| '__/ _ \\/ _ \\| |  | | |  | |\\___ \\\n");
    printf("  | |  | | |  __/  __/| |__| | |__| |____) |\n");
    printf("  |_|  |_|  \\___|\\___||_____/ \\____/|_____/\n\n" CLR_RESET);
}

void print_appledos() {
    printf(CLR_RED "             .----.\n");
    printf("           /   _   \\\n");
    printf("          |   / \\   |\n");
    printf("      .---'   '---'---.\n");
    printf("     /                 \\\n");
    printf("    |     .-------.     |\n");
    printf("    |    /         \\    |\n");
    printf("    |   |           |---|\n");
    printf("     \\   \\         /   /\n");
    printf("      \\   '-------'   /\n");
    printf("       '--._______..--'\n\n" CLR_RESET);
}

void print_ataridos() {
    printf(CLR_ATARI "         /\\\n");
    printf("        /  \\\n");
    printf("       / /\\ \\\n");
    printf("      / /  \\ \\\n");
    printf("     / / /\\ \\ \\\n");
    printf("    / / /  \\ \\ \\\n");
    printf("   /_/_/    \\_\\_\\\n");
    printf("  [__ __    __ __]\n\n" CLR_RESET);
}

void print_commodoredos() {
    printf(CLR_CYAN "      .--------.\n");
    printf("    /   ______  \\ \n");
    printf("   /   /      \\  \\     ======\n");
    printf("  |   |        |  |    ======\n");
    printf("  |   |     ======     ======\n");
    printf("  |   |        |  |    ======\n");
    printf("   \\   \\______/  /     ======\n");
    printf("    \\           /\n");
    printf("      '--------'\n\n" CLR_RESET);
}

int main(int argc, char *argv[]) {
    unsigned int conventional_ram = 640;
    unsigned char major_ver = 0, minor_ver = 0;
    unsigned long total_disk_bytes = 0;
    unsigned long free_disk_bytes = 0;
    
    char *detected_os = "Generic DOS Workspace";
    char *model_string = "Generic Hardware Environment";
    int os_type = 0; /* 0=Generic, 1=MSDOS, 2=FreeDOS, 3=Apple, 4=Atari, 5=Commodore */

#ifdef REAL_MODE_DOS
    union REGS regs;
    struct diskfree_t disk_info;
    unsigned char pc_model_byte = 0xFF;

    /* Extract Real DOS Version bits via INT 21h, AH=30h */
    regs.h.ah = 0x30;
    intdos(&regs, &regs);
    major_ver = regs.h.al;
    minor_ver = regs.h.ah;

    /* FreeDOS Multiplex Hook Check: INT 21h, AX=4451h returns 0x4453 if true */
    regs.x.ax = 0x4451;
    intdos(&regs, &regs);
    if (regs.x.ax == 0x4453) {
        detected_os = "FreeDOS Kernel Engine";
        os_type = 2;
    } else if (major_ver > 0) {
        detected_os = "MS-DOS System Core";
        os_type = 1;
    }

    /* Extract base hardware memory layout via BIOS INT 12h */
    int86(0x12, &regs, &regs);
    conventional_ram = regs.x.ax;

    /* Gather Storage Space metrics for active C: drive partition */
    if (_dos_getdiskfree(3, &disk_info) == 0) {
        total_disk_bytes = (unsigned long)disk_info.bytes_per_sector * 
                           disk_info.sectors_per_cluster * disk_info.total_clusters;
        free_disk_bytes = (unsigned long)disk_info.bytes_per_sector * 
                          disk_info.sectors_per_cluster * disk_info.avail_clusters;
    }

    /* Map physical BIOS Model Segments */
    pc_model_byte = *(unsigned char __far *)MK_FP(0xF000, 0xFFFE);
    switch(pc_model_byte) {
        case 0xFF: model_string = "IBM PC (Original 1981)"; break;
        case 0xFE: model_string = "IBM PC/XT"; break;
        case 0xFD: model_string = "IBM PCjr"; break;
        case 0xFC: model_string = "IBM PC/AT"; break;
        case 0xF8: model_string = "IBM PS/2 Model 80"; break;
        default:   model_string = "Compatible x86 Clone / DOSBox"; break;
    }
#else
    /* Mock simulation text outputs used natively under modern non-DOS hosts */
    detected_os = "DOS Environment Emulator";
    model_string = "Modern Local System Interface";
#endif

    /* Handle specific manual platform switches via command arguments */
    if (argc > 1) {
        if (stricmp(argv[1], "msdos") == 0) { os_type = 1; detected_os = "MS-DOS System Core"; }
        else if (stricmp(argv[1], "freedos") == 0) { os_type = 2; detected_os = "FreeDOS Kernel Engine"; }
        else if (stricmp(argv[1], "apple") == 0) { os_type = 3; detected_os = "Apple DOS (ProDOS Simulation)"; }
        else if (stricmp(argv[1], "atari") == 0) { os_type = 4; detected_os = "Atari DOS (Atari 800 Simulation)"; }
        else if (stricmp(argv[1], "c64") == 0) { os_type = 5; detected_os = "Commodore DOS (C64 1541 Simulation)"; }
    }

    /* Output Logo Sequence rendering */
    switch(os_type) {
        case 1: print_msdos(); break;
        case 2: print_freedos(); break;
        case 3: print_appledos(); break;
        case 4: print_ataridos(); break;
        case 5: print_commodoredos(); break;
        default: print_generic_dos(); break;
    }

    /* Dashboard Text Readouts */
    printf("  " CLR_WHITE "OS:" CLR_GRAY "          %s\n", detected_os);
    if (major_ver > 0) {
        printf("  " CLR_WHITE "Version:" CLR_GRAY "     %d.%02d\n", major_ver, minor_ver);
    } else {
        printf("  " CLR_WHITE "Version:" CLR_GRAY "     Cross-Compiled Runtime Layer\n");
    }

    /* Compile-Time Architectural Logic Parsing Flags */
    printf("  " CLR_WHITE "Arch:" CLR_GRAY "        ");
#if defined(__M_I86__) || defined(__I86__) || defined(_M_I86)
    printf("16-Bit Real Mode (i8086 / i186 / i286 Classic)\n");
#elif defined(__i386__) || defined(__I386__) || defined(_M_IX86) || defined(__i386)
    printf("i386 / i486 / i686 (32-Bit Protected Mode Target)\n");
#elif defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)
    printf("x86_64 / AMD64 (Native 64-Bit Desktop Terminal)\n");
#elif defined(__aarch64__) || defined(_M_ARM64) || defined(__arm64__)
    printf("AArch64 (ARM 64-Bit Host Ecosystem)\n");
#elif defined(__arm__) || defined(_M_ARM)
    printf("ARMv6 / ARMv7 (32-Bit Legacy Mobile Micro-Architecture)\n");
#else
    printf("Universal Cross-Compiled System Executable Object\n");
#endif

    printf("  " CLR_WHITE "PC Model:" CLR_GRAY "    %s\n", model_string);
    printf("  " CLR_WHITE "Motherboard:" CLR_GRAY " ISA/NE2000 System Bus Architecture\n");
    printf("  " CLR_WHITE "Base RAM:" CLR_GRAY "    %u KB / 640 KB Standard\n", conventional_ram);
    printf("  " CLR_WHITE "Swap:" CLR_GRAY "        0 KB (Disabled - Real-Mode Managed)\n");
    
    if (total_disk_bytes > 0) {
        printf("  " CLR_WHITE "Storage (C:):" CLR_GRAY " %lu MB Free / %lu MB Total\n", free_disk_bytes / 1024 / 1024, total_disk_bytes / 1024 / 1024);
    } else {
        printf("  " CLR_WHITE "Storage (C:):" CLR_GRAY " 16 MB Free / 32 MB Total (Virtual Clone Array)\n");
    }

    printf("  " CLR_WHITE "Local IP:" CLR_GRAY "    192.168.1.42 (via Packet Driver)\n");
    printf("  " CLR_WHITE "Engine:" CLR_GRAY "      Multi-Arch Source Cross-Compiler Toolchain\n" CLR_RESET);

    return 0;
}

