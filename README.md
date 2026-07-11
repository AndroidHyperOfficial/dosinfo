# dosinfo

A lightweight, multi-architecture system information utility designed to bring modern 'fetch' aesthetics directly to 16-bit real-mode DOS and vintage emulation environments. 

## Features
- **Auto-Detection:** Automatically scans system memory to detect if running under MS-DOS or FreeDOS.
- **Retro Emulation Overrides:** Pass arguments (`apple`, `atari`, `c64`) to force-render classic 8-bit/16-bit disk operating system environments.
- **Pure 16-Bit Real Mode:** Uses native BIOS interrupt handlers (`int86`, `intdos`) to poll baseline memory blocks, ROM signatures, and partition sizing structures cleanly.
- **Cross-Platform Compatibility:** Gracefully falls back to simulation mode if compiled natively on modern Linux, macOS, or Windows terminal environments.

## Supported Architectures
- **16-Bit Real Mode:** Intel 8086 / 186 / 286 / 386 / 486 / Pentium targets running under raw DOS or DOSBox setups.
- **32-Bit Protected Mode:** DOS4GW extenders.
- **64-Bit Modern Desktops:** Native x86_64 / AMD64 platforms.
- **ARM Architectures:** Native AArch64 (Apple Silicon M-series Macs / UTM / Raspberry Pi execution).

## Compiling From Source

### Natively on Arch Linux (with Open Watcom V2)
```bash
# Compile the native 64-bit Linux terminal version
gcc dosfetch.c -o dosfetch

# Compile the 16-bit DOS real-mode binary
wcl -bt=dos -l=dos dosfetch.c -fe=dosfetch16.exe
```

### On macOS (ARM64 / Apple Silicon)
```bash
clang dosfetch.c -o dosfetch
```

### On Debian / Ubuntu / Mint
```bash
sudo apt update && sudo apt install build-essential -y
gcc dosfetch.c -o dosfetch
```

## Running the App
For standard usage on your active operating system:
```bash
./dosfetch
```

To larp or force a specific retro profile layout via argument overrides:
```bash
./dosfetch apple
./dosfetch c64
./dosfetch atari
```
