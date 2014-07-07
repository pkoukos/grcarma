# Installation instructions for grcarma #

Administator privileges are required for linux, macOSX and windows OS's 
( XP and newer ).

Most of the files that are produced by grcarma are PDB or postscript
files. grcarma depends on external programs in order to open these
files. More info is available in the [documentation] 
(https://github.com/pkoukos/grcarma/wiki/grcarma%20documentation#results).

## GNU/Linux ##

In order to obtain the archive specific for your platform you should follow
this [link](https://github.com/pkoukos/grcarma/blob/master/linux/grcarma_linux.tar.gz?raw=true)
and then save the file. The file download should begin.

After the download is complete you will need to open a terminal to the location the files 
were downloaded and extract the binary files from their archives.

The terminal commands that will accomplish this are :

    tar -zxvf grcarma_linux.tar.gz
    
After that change your current working directory to the newly created one by running :

    cd grcarma_linux
    
Copy the grcarma executable and the carma executable to a location included in the path like :

    /usr/local/bin

The terminal command that will accomplish this is :

    sudo cp grcarma /usr/local/bin       , for grcarma and 
    sudo cp carma /usr/local/bin         , for 32-bit carma or
    sudo cp carma64 /usr/local/bin/carma , for 64-bit carma

If the file permissions don't allow the execution of the files then you
need to change their permissions with a command like :

    sudo chmod 755 /usr/local/bin/grcarma , for grcarma and 
    sudo chmod 755 /usr/local/bin/carma   , for carma

provided of course that you copied the executables to that folder.

## macOSX ##

In order to obtain the archive specific for your platform you should follow
this [link](https://github.com/pkoukos/grcarma/blob/master/macosx/grcarma_macosx.tar.gz?raw=true)
and then save the file. The file download should begin.

After the download is complete you will need to open a terminal to the location the files 
were downloaded and extract the binary files from their archives.

The terminal commands that will accomplish this are :

    tar -zxvf grcarma_macosx.tzr.gz
    
After that change your current working directory to the newly created one by running :

    cd grcarma_macosx
    
Copy the grcarma executable and the carma executable to a location included in the path like :

    /usr/local/bin

The terminal command that will accomplish this is :

    sudo cp grcarma /usr/local/bin       , for grcarma and 
    sudo cp carma /usr/local/bin         , for carma

If the file permissions don't allow the execution of the files then you
need to change their permissions with a command like :

    sudo chmod 755 /usr/local/bin/grcarma , for grcarma and 
    sudo chmod 755 /usr/local/bin/carma   , for carma

provided of course that you copied the executables to that folder.

## Windows ##

It is _strongly_ recommended that windows users use the installer located
in the windows subfolder of the top directory. You can download the installer
by following this [link] (https://github.com/pkoukos/grcarma/blob/master/windows/grcarma_installer.exe?raw=true)
and then save the file. The file download should begin.

The installer will guide you through each step of the installation process and automatically
export the location that will be specified for the installation of the program to the path.
