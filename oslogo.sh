#!/bin/bash



clear

tput cup 4 10; 
tput setaf 2;#for green
for (( i = 0; i < 55; i++ )); do
sleep 0.05
echo -n "_"
done
tput setaf 6;#for cyan color
tput bold;
tput cup 6; 
figlet -c 'Nova OS';
tput cup 12 10; 
tput setaf 2;#for green
for (( i = 0; i < 55; i++ )); do
sleep 0.05
echo -n "_"
done
echo -e "\\n\\t    By Abdul Muizz and Muhammad Usman"
y=$((51/2 - 1)) 
x=$((165/2 - 15))
tput cup $y $x;
tput blink;
echo  ">>>>>>>>>> SYSTEM IS BOOTING UP <<<<<<<<<"
sleep 4
tput sgr0;# fro reset all settings
clear

