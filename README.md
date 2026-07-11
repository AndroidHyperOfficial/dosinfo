# dosinfo 

A lightweight, multi-architecture 16-bit real-mode system information tool written in C. Optimized for legacy x86 machines, retro hardware configurations, and modern emulators (QEMU, DOSBox).

## Compiling the App

### Natively on Arch Linux (with Open Watcom V2)

```bash
# Compile the native 64-bit Linux terminal fallback version
gcc dosinfo.c -o dosinfo

# Compile the authentic 16-bit DOS real-mode binary asset
wcl -bt=dos -l=dos dosinfo.c -fe=dosinfo.exe
```

### On macOS (ARM64 / Apple Silicon)

```bash
clang dosinfo.c -o dosinfo
```

### On Debian / Ubuntu / Mint

```bash
sudo apt update && sudo apt install build-essential -y
gcc dosinfo.c -o dosinfo
```

## Running the App

For standard usage on your active operating system prompt environment:

```bash
./dosinfo
```

To force a specific retro profile layout via direct terminal argument overrides:

```bash
./dosinfo msdos
./dosinfo freedos
./dosinfo apple
./dosinfo c64
./dosinfo atari
```

On real MS-DOS hardware or inside emulators, execute the compiled 16-bit binary directly:
```cmd
dosinfo.exe
```
