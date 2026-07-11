#include <stdio.h>
#include <string.h>
#include <time.h>

#if defined(__MSDOS__) || defined(__DOS__) || defined(_M_I86) || defined(__I86__)
    #include <dos.h>
    #define REAL_MODE_DOS 1
#endif

#if !defined(REAL_MODE_DOS)
    #define stricmp strcasecmp
#endif

/* Foreground ANSI Text Colors */
#define CLR_RESET   "\x1b[0m"
#define CLR_WHITE   "\x1b[1;37m"
#define CLR_GRAY    "\x1b[0;37m"
#define CLR_BLUE    "\x1b[1;34m"
#define CLR_GREEN   "\x1b[1;32m"
#define CLR_RED     "\x1b[1;31m"
#define CLR_CYAN    "\x1b[1;36m"
#define CLR_YELLOW  "\x1b[1;33m"
#define CLR_MAGENTA "\x1b[1;35m"

/* 1. ORIGINAL CLEAN BLUE MS-DOS TEXT LOGO */
void print_msdos() {
    printf("  " CLR_BLUE " __  __  ____        _____   ____   ____ \n");
    printf("  " CLR_BLUE "|  \\/  |/ ___|      |  __ \\ / __ \\ / ___|\n");
    printf("  " CLR_BLUE "| \\  / | (___ ______| |  | | |  | | (___ \n");
    printf("  " CLR_BLUE "| |\\/| |\\___ \\______| |  | | |  | |\\___ \\\n");
    printf("  " CLR_BLUE "| |  | |____) |     | |__| | |__| |____) |\n");
    printf("  " CLR_BLUE "|_|  |_|____/       |_____/ \\____/|____/ \n\n" CLR_RESET);
}

void print_freedos() {
    printf("  " CLR_GREEN " _______              _____   ____   _____\n");
    printf("  " CLR_GREEN "|  ____|            |  __ \\ / __ \\ / ____|\n");
    printf("  " CLR_GREEN "| |__ _ __ ___  ___ | |  | | |  | | (___\n");
    printf("  " CLR_GREEN "|  __| '__/ _ \\/ _ \\| |  | | |  | |\\___ \\\n");
    printf("  " CLR_GREEN "| |  | | |  __/  __/| |__| | |__| |____) |\n");
    printf("  " CLR_GREEN "|_|  |_|  \\___|\\___||_____/ \\____/|_____/\n\n" CLR_RESET);
}

void print_generic_dos() {
    printf("  " CLR_BLUE "  _____   " CLR_RED "____   " CLR_YELLOW "_____\n");
    printf("  " CLR_BLUE " |  __ \\ / " CLR_RED "__ \\ / " CLR_YELLOW "____|\n");
    printf("  " CLR_BLUE " | |  | | |  | | " CLR_YELLOW "(___\n");
    printf("  " CLR_BLUE " | |  | | |  | |" CLR_YELLOW "\\___ \\\n");
    printf("  " CLR_BLUE " | |__| | |__| |" CLR_YELLOW "____) |\n");
    printf("  " CLR_BLUE " |_____/ \\____/" CLR_YELLOW "|_____/\n\n" CLR_RESET);
}

void print_appledos() {
    printf("  " CLR_GREEN "        ,----.\n");
    printf("  " CLR_GREEN "       /   _  \\\n");
    printf("  " CLR_YELLOW "    .-'   '--'---.\n");
    printf("  " CLR_YELLOW "   /              \\\n");
    printf("  " CLR_RED "  |   .--------.   |\n");
    printf("  " CLR_RED "   \\  '--------'  /\n");
    printf("  " CLR_MAGENTA "    '-.________.-'\n\n" CLR_RESET);
}

void print_ataridos() {
    printf("  " CLR_CYAN "       /\\    /\\\n");
    printf("  " CLR_CYAN "      /  \\  /  \\\n");
    printf("  " CLR_BLUE "     / /\\ \\/ /\\ \\\n");
    printf("  " CLR_BLUE "    / /  \\  /  \\ \\\n");
    printf("  " CLR_WHITE "  /_/_/  \\_/  \\_\\_\\\n\n" CLR_RESET);
}

void print_commodoredos() {
    printf("  " CLR_BLUE "     .--------.\n");
    printf("  " CLR_BLUE "    /   ______\\   " CLR_RED "======\n");
    printf("  " CLR_BLUE "   /   /          " CLR_WHITE "======\n");
    printf("  " CLR_BLUE "  |   |           " CLR_RED "======\n");
    printf("  " CLR_BLUE "   \\   \\______/   " CLR_WHITE "======\n");
    printf("  " CLR_BLUE "    \\         /\n");
    printf("  " CLR_BLUE "     '--------'\n\n" CLR_RESET);
}

int main(int argc, char *argv[]) {
    unsigned int conventional_ram = 640;
    unsigned char major_ver = 0, minor_ver = 0;
    unsigned long total_disk_bytes = 0;
    unsigned long free_disk_bytes = 0;
    char *detected_os = "Generic DOS Workspace";
    char *model_string = "Generic Hardware Environment";
    int os_type = 0;
    int hour = 0, minute = 0, second = 0;
    int year = 2026, month = 7, day = 11;
    char *display_mode = "Standard Text Canvas";
    char *mouse_status = "Not Detected (Missing INT 33h)";
    char *cdrom_status = "No CD Support (MSCDEX Loaded: No)";
    char *shell_string = "COMMAND.COM Standard Executive";

#ifdef REAL_MODE_DOS
    union REGS regs;
    struct diskfree_t disk_info;
    unsigned char pc_model_byte = 0xFF;
    unsigned char video_mode = 0;

    regs.h.ah = 0x30;
    intdos(&regs, &regs);
    major_ver = regs.h.al;
    minor_ver = regs.h.ah;

    regs.x.ax = 0x4451;
    intdos(&regs, &regs);
    if (regs.x.ax == 0x4453) {
        detected_os = "FreeDOS Kernel Engine";
        os_type = 2;
    } else if (major_ver > 0) {
        detected_os = "MS-DOS System Core";
        os_type = 1;
    }

    regs.h.ah = 0x2A;
    intdos(&regs, &regs);
    year = regs.x.cx; month = regs.h.dh; day = regs.h.dl;

    regs.h.ah = 0x2C;
    intdos(&regs, &regs);
    hour = regs.h.ch; minute = regs.h.cl; second = regs.h.dh;

    int86(0x12, &regs, &regs);
    conventional_ram = regs.x.ax;

    if (_dos_getdiskfree(3, &disk_info) == 0) {
        total_disk_bytes = (unsigned long)disk_info.bytes_per_sector * 
                           disk_info.sectors_per_cluster * disk_info.total_clusters;
        free_disk_bytes = (unsigned long)disk_info.bytes_per_sector * 
                          disk_info.sectors_per_cluster * disk_info.avail_clusters;
    }

    regs.h.ah = 0x0F;
    int86(0x10, &regs, &regs);
    video_mode = regs.h.al;
    
    if (video_mode == 3) display_mode = "VGA Color Text Mode (80x25)";
    else if (video_mode == 7) display_mode = "Monochrome Text Mode (80x25)";
    else if (video_mode == 1) display_mode = "CGA Color Text Mode (40x25)";
    else display_mode = "EGA Legacy Custom Video Layout";

    regs.x.ax = 0x0000;
    int86(0x33, &regs, &regs);
    if (regs.x.ax == 0xFFFF) {
        mouse_status = "CuteMouse / PS/2 Driver Active";
    }

    regs.x.ax = 0x1500;
    regs.x.bx = 0x0000;
    intdos(&regs, &regs);
    if (regs.x.bx > 0) {
        cdrom_status = "MSCDEX Driver Loaded (CD-ROM OK)";
    }

    pc_model_byte = *(unsigned char __far *)MK_FP(0xF000, 0xFFFE);
    switch(pc_model_byte) {
        case 0xFF: model_string = "IBM PC (Original 1981)"; break;
        case 0xFE: model_string = "IBM PC/XT Model Layout"; break;
        case 0xFC: model_string = "IBM PC/AT Architecture"; break;
        default:   model_string = "Compatible x86 Rig / QEMU Emulator"; break;
    }
#else
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    hour = timeinfo->tm_hour; minute = timeinfo->tm_min; second = timeinfo->tm_sec;
    day = timeinfo->tm_mday; month = timeinfo->tm_mon + 1; year = timeinfo->tm_year + 1900;
    display_mode = "Modern Resizable Terminal Viewport";
    mouse_status = "X11/Wayland Desktop Pointer Embedded";
    cdrom_status = "Virtual IsoFS Kernel Mount System Layer";
    shell_string = "/bin/bash Custom Terminal Profile";
    detected_os = "DOS Environment Simulation Host";
    model_string = "Modern Local Virtual Subsystem";
#endif

    if (argc > 1) {
        if (stricmp(argv[1], "msdos") == 0) { os_type = 1; detected_os = "MS-DOS System Core"; }
        else if (stricmp(argv[1], "freedos") == 0) { os_type = 2; detected_os = "FreeDOS Kernel Engine"; }
        else if (stricmp(argv[1], "apple") == 0) { os_type = 3; detected_os = "Apple DOS (ProDOS Mode)"; }
        else if (stricmp(argv[1], "atari") == 0) { os_type = 4; detected_os = "Atari DOS (800 Simulation)"; }
        else if (stricmp(argv[1], "c64") == 0) { os_type = 5; detected_os = "Commodore DOS (C64 Emulator)"; }
    }

    switch(os_type) {
        case 1: print_msdos(); break;
        case 2: print_freedos(); break;
        case 3: print_appledos(); break;
        case 4: print_ataridos(); break;
        case 5: print_commodoredos(); break;
        default: print_generic_dos(); break;
    }

    printf("  " CLR_WHITE "OS:" CLR_GRAY "          %s\n", detected_os);
    if (major_ver > 0) {
        printf("  " CLR_WHITE "Version:" CLR_GRAY "     %d.%02d\n", major_ver, minor_ver);
    } else {
        printf("  " CLR_WHITE "Version:" CLR_GRAY "     Staged Runtime Interface Line\n");
    }
    printf("  " CLR_WHITE "Shell:" CLR_GRAY "       %s\n", shell_string);
    printf("  " CLR_WHITE "PC Model:" CLR_GRAY "    %s\n", model_string);
    printf("  " CLR_WHITE "Display:" CLR_GRAY "     %s\n", display_mode);
    printf("  " CLR_WHITE "Date/Time:" CLR_GRAY "   %04d-%02d-%02d @ %02d:%02d:%02d\n", year, month, day, hour, minute, second);
    printf("  " CLR_WHITE "Pointing:" CLR_GRAY "    %s\n", mouse_status);
    printf("  " CLR_WHITE "CD-ROM:" CLR_GRAY "      %s\n", cdrom_status);
    printf("  " CLR_WHITE "Base RAM:" CLR_GRAY "    %u KB / 640 KB Standard\n", conventional_ram);
    
    if (total_disk_bytes > 0) {
        printf("  " CLR_WHITE "Storage (C:):" CLR_GRAY " %lu MB Free / %lu MB Total\n", free_disk_bytes / 1024 / 1024, total_disk_bytes / 1024 / 1024);
    } else {
        printf("  " CLR_WHITE "Storage (C:):" CLR_GRAY " 16 MB Free / 32 MB Total (Virtual Map Array)\n");
    }
    printf("  " CLR_WHITE "Engine:" CLR_GRAY "      Open Watcom Multi-Arch Release v1.1 - dosinfo Engine\n" CLR_RESET);

    return 0;
}
