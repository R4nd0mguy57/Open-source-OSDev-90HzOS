## Open Source OSDev Project made by a random GD French Player btw
This is the begining of my project _90HzOS_. (Sorry for bad english)

## How To compile
**PLZ NOTE THAT SOME COMMANDS WONT WORK ON WINDOWS, SO I RECOMMEND USING A UNIX/GNULinux SYSTEM**
- 1. First you will need an emulator like qemu to run the 'OS' and an assembler:
- **On Arch Linux** (btw)
- Run these two commands below:
    - ``sudo pacman -Suy  # update packages & packages list``
    - ``sudo pacman -S nasm qemu-common``
- **On Ubuntu or any Debian based Linux Distro**
    - ``sudo apt update && sudo apt full-upgrade -y``
    - ``sudo apt intall nasm qemu-common``
- **On Windows**
- Download the following files (you can also use curl with the link in PS):
  - ``https://www.nasm.us/pub/nasm/releasebuilds/3.02rc7/win64/nasm-3.02rc7-installer-x64.exe``
  - ``https://qemu.weilnetz.de/w64/2026/qemu-w64-setup-20260422.exe``

- 2. Then create an **OSDev** folder in your **HOME DIRECTORY**
- 3. Move all the content you downloaded from this repo into *~/OSDev*
- 4. Then you will need a cross-compiler and a linker:
    - Install gnu binutils:
         - ``mkdir /tmp/src``
         - ``cd /tmp/src``
         - ``curl -O https://ftp.gnu.org/gnu/binutils/binutils-with-gold-2.46.tar.xz``
         - ``tar xfv binutils-with-gold-2.46.tar.xz``
         - ``mkdir binutils-build``
         - ``cd binutils-build``
         - ``../binutils-with-gold-2.46.tar.xz/configure --target=i386-elf --enable-multilib --disable-nls --disable-werror --prefix=/usr/var/i386elfgcc 2>&1 | tee configure.log``
         - ``sudo make all install 2>&1 | tee make.log``
    - Install gcc cross compiler:
         - ``cd /tmp/src``
         - ``curl -O https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.xz``
         - ``tar xfv gcc-15.2.0.tar.xz``
         - ``mkdir gcc-build``
         - ``cd gcc-build``
         - ``../gcc-15.2.0/configure --target=i386-elf --prefix=/usr/var/i386elfgcc --disable-nls --disable-libssp --enable-language=c++ --without-headers``
         - ``sudo make all-gcc -j$(nproc)``
         - ``sudo make all-target-libgcc -j$(nproc)``
         - ``sudo make install-gcc -j$(nproc)``
         - ``sudo make install-taget-libgcc -j$(nproc)``
- 5. Add cross compilers to the **PATH**:
         - On **UNIX/GNULinux**:
             - **TEMP**:
                 - To add the compilers to the PATH **temporarily** *(disapeare after closing bash session)*:
                     - ``export PATH="/usr/var/i386elfgcc:$PATH"``
             - To add it **permanantly**, you can edit your ~/.bashrc file:
                 - ``nano ~/.bashrc``
                 - Add this line at the end if file:
                     - ``export PATH="/usr/var/i386elfgcc:$PATH"``
         - On **Windows NT**:
             - Search for: *Edit environment variables*
             - Click on _edit environment variables_
             - Click on **PATH**
             - Then click  _edit_
             - Then add the PATH to your cross compilers directory at the end
             - Then apply changes and _reboot your computer_
- 6. **END**
     - If you did the previous steps correctly (sorry if didn't work) you can do: ``cd ~/OSDev`` then execute: ``make all``
     - If you are on Windows, try to adapt the code of the Makefile!
    
## HOW TO RUN ON QEMU
**RUN THIS COMMAND**:
    - ``qemu-system-x86_64 -monitor stdio -hda ~/OSDev/90HzOS/OS/90HzOS.bin``
     
     
     
     
     
   
