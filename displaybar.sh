#!/bin/bash

(
  echo 25
  echo "# Setting up OS..."
  sleep 2

  echo 30
  echo "# Reading files from Bootloader..."
  sleep 2

  echo 70
  echo "# Checking Resources"
  sleep 1

  echo 99
  echo "# OS LOADED SUCCESSFULLY!"
  sleep 1
) | zenity --title "OS Loading..." --progress --auto-close --width=400 --height=150
