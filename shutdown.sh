#!/bin/bash

#######################################
# Functions Using tput for BOLD, BLINK
# RESET, GREEN, WHITE & Yellow Colors
# GLOBALS:
#   Nothing
# ARGUMENTS:
#   Nothing
# OUTPUTS:
#   Nothing
# RETURN:
#   Nothing
#######################################

bold() {
    tput bold;
}
blink() {
    tput blink;
}
reset_format() {
    tput sgr0;
}
green_fg() {
    tput setaf 2;
}
cyan_fg() {
    tput setaf 6;
}
white_fg() {
    tput setaf 7;
}
yellow_fg() {
    tput setaf 3;
}
red_fg() {
    tput setaf 1;
}

display_landing_page() {
    clear
    red_fg 
    bold
    tput cup 6; 
    figlet -c 'BYE !';
    reset_format
    tput cup 12 10; 
    green_fg
    for (( i = 0; i < 55; i++ )); do
        sleep 0.05
        echo -n -e '*'
    done
     y=$((51/2 - 1)) 
    x=$((165/2 - 15))
    tput cup $y $x;
    blink
    echo  "++++++++++ SYSTEM IS Shutting Down ++++++++++"
    sleep 4
    reset_format
    white_fg
    clear
}

display_landing_page
