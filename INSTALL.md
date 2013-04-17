# Installation instructions for grcarma #

Adinistator privileges are required for linux, macOSX and windows OS's 
( Vista and newer ).

If your OS supports unzipping then the easiest way to obtain grcarma is
to click on the ZIP button in the home page of this git. This will
download an archive named grcarma-master.zip to your machine. After extracting
the files, change directory to the subfolder of your OS. At this point you will
need to extract the binary files from their archives. Linux and macOSX users can
accomplish this using the command line. Windows users can use a [7-zip] 
(http://www.7-zip.org/), a freely available open source program that can handle
zip, tar, and gz files.

## GNU/Linux ##

Obtain the executables for your platform from the relevant subfolder of
the top directory. Copy the grcarma executable and the carma executable
to a location included in the path like :

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

Obtain the executables for your platform from the relevant subfolder of
the top directory. Copy the grcarma executable and the carma executable
to a location included in the path like :

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

It is strongly recommended that windows users use the installer located
in the windows subfolder of the top directory. The installer will guide
you through each step of the installation process and automatically
export the location that will be specified for the installation of the 
program to the path.

Most of the files that are produced by grcarma are PDB or postscript
files. grcarma depends on external programs in order to open these
files. More info is available in the [documentation] 
(https://github.com/pkoukos/grcarma/wiki/grcarma%20documentation#results).
