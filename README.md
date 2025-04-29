# MINI-OS

# Mini OS Project

## 📋 Description
This is a basic C++ and Shell Script-based mini operating system simulation developed as an academic project. It features a collection of mini applications like Calculator, Notepad, Calendar, Clock, and games, simulating a lightweight OS environment with a command-line-style interface.

## 🔧 Features
- 💻 Built-in apps: Calculator, Notepad, Calendar, Clock, Tic Tac Toe, Unit Converter, To-do List
- 🎮 Fun utilities: Tic Tac Toe, Random number generator
- 🖥️ System-like functions: Rename, Delete, Shutdown
- 🎵 Music player (basic audio simulation)
- 📜 Modular architecture using C++ for logic and shell scripts for control

## 🧰 Requirements
- Linux-based OS (Ubuntu or similar)
- `g++` compiler
- Bash shell

## 🚀 How to Run

1. **Clone the repository or download the source files.**

2. Open a terminal and navigate to the project directory:
   ```bash
   cd /path/to/project
   ```

3. **Compile the C++ source files** (example for `os.cpp`):
   ```bash
   g++ -o os os.cpp
   ```

   *(Repeat for other modules or use a Makefile if available)*

4. **Make shell scripts executable**:
   ```bash
   chmod +x *.sh
   ```

5. **Launch the main interface** (for example):
   ```bash
   ./welcometextgame.sh
   ```

6. Follow the on-screen options to access various applications.

## 📁 Project Structure
- `*.cpp` – Source code for individual modules (calculator, notepad, etc.)
- `*.sh` – Shell scripts to execute and manage modules
- `README.md` – Project overview and instructions

