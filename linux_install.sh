#!/bin/bash

#**********************************************************************#
#                                                                      #
#               This is an installer script for grcarma                #
#                                                                      #
#**********************************************************************#

# If the user is not root when running the
# script prompt for password and run script
# as 'sudo ./linux_install'

if (( EUID != 0 )); then
   printf "\033[1m\nYou must be root to run this script.\n\033[0m" 1>&2
   sudo "$0"
   exit 0
fi

# Determine bitness and whether a carma bin
# exists in /usr/local/bin

BitNess=`dpkg --print-architecture`
carma_location="$(command -v carma)"

if [[ $OSTYPE =~ 'linux' ]]; then
    if [[ $BitNess =~ 64 ]]; then
        # If running on 64bit linux and a carma executable
        # is found in /usr/local/bin ask the user if the
        # previous executable should be replaced by the
        # latest contained in the grcarma tarball
        if [ $carma_location ]; then
            printf "\nA carma executable has been found in the folder $carma_location"
            printf "\nWould you like to replace it with version (1.2) [Y/n]?"
            read
            if [[ $REPLY != [Nn] ]]; then
                command cp carma/bin/linux/carma64 /usr/local/bin
                command mv /usr/local/bin/carma64 /usr/local/bin/carma
                printf "\nUpdated carma executable to version 1.2\n"
            fi
        else
            command cp carma/bin/linux/carma64 /usr/local/bin
            command mv /usr/local/bin/carma64 /usr/local/bin/carma
            printf "\nCopied carma executable to /usr/local/bin\n"
        fi
    else
        # Likewise for 32bit linux
        if [ $carma_location ]; then
            printf "\nA carma executable has been found in the folder $carma_location"
            printf "\nWould you like to replace it with version (1.2) [Y/n]?"
            read
            if [[ $REPLY != [Nn] ]]; then
                command cp carma/bin/linux/carma /usr/local/bin
                printf "\nUpdated carma executable to version 1.2\n"
            fi
        else
            command cp carma/bin/linux/carma /usr/local/bin
            printf "\nCopied carma executable to /usr/local/bin\n"
        fi
    fi
else
    # Likewise for MacOSX
    if [ $carma_location ]; then
        printf "\nA carma executable has been found in the folder $carma_location"
        printf "\nWould you like to replace it with version (1.2) [Y/n]?"
        read
        if [[ $REPLY != [Nn] ]]; then
            command cp carma/bin/macosx/carma /usr/local/bin
            printf "\nUpdated carma executable to version 1.2\n"
        fi
    else
        command cp carma/bin/macosx/carma /usr/local/bin
        printf "\nCopied carma executable to /usr/local/bin\n"
    fi
fi

# Prompt the user about the installation of
# the manual of carma

printf "\nWould you like to install the manual of carma [Y/n]?"
read
if [[ $REPLY != [Nn] ]]; then
    command cp carma/doc/man/carma.n /usr/share/man/man8
    command mv /usr/share/man/man8/carma.n /usr/share/man/man8/carma.8
    command gzip /usr/share/man/man8/carma.8
    printf "\nInstalled carma manual to /usr/share/man/man8\n"
fi

# Copy the grcarma executable to /usr/local/bin
# and prompt the user about the creation of a
# shortcut to grcarma to be placed on the desktop

command cp bin/linux/grcarma /usr/local/bin
printf "\nCopied grcarma executable to /usr/local/bin. "
printf "Would you like to create a sym-link to grcarma "
printf "and place it in your desktop [Y/n]?"
read
if [[ $REPLY != [Nn] ]]; then
    command ln -s /usr/local/bin/grcarma ~/Desktop
    printf "\nCreated shortcut to grcarma\n\n"
fi
