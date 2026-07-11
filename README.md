# dosstat 

A lightweight, multi-architecture 16-bit real-mode system information utility written in C. Optimized for legacy x86 machines, retro hardware configurations, and modern emulators (QEMU, DOSBox).

## Compiling the App

### Natively on Arch Linux (with Open Watcom V2)

```bash
# Export Watcom path links if needed
export PATH=/opt/watcom/binl64:\$PATH
export WATCOM=/opt/watcom
export INCLUDE=/opt/watcom/h

# Compile the authentic 16-bit DOS real-mode binary asset
wcl -bt=dos -l=dos dosstat.c -fe=dosstat.exe
```

### On macOS / Linux (Native Terminal Fallback)

```bash
gcc dosstat.c -o dosstat
```

## Running the App

For standard usage on an emulator or real MS-DOS hardware:

```cmd
dosstat.exe
```

To force a specific retro profile layout via terminal argument overrides:

```cmd
dosstat msdos
dosstat freedos
dosstat apple
dosstat c64
dosstat atari
```
