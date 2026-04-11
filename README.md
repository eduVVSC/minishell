# Minishell

*As beautiful as a shell*

## 📖 Overview

Minishell is a 42 school project focused on creating a simple Unix shell in C. It serves as a deep dive into the inner workings of a shell, exploring process creation, file descriptors, signal handling, and complex string parsing. The goal is to build a program that mimics the basic functionalities of `bash`.

## ✨ Features

Our Minishell successfully implements the following core features:

* **Interactive Prompt**: Displays a prompt and waits for user input, complete with command history support.
* **Command Execution**: Searches and launches executables either via the `$PATH` environment variable or by specifying relative/absolute paths.
* **Built-in Commands**:
    * `echo` (supports the `-n` flag)
    * `cd` (supports relative or absolute paths)
    * `pwd` (prints current working directory)
    * `export` (sets environment variables)
    * `unset` (removes environment variables)
    * `env` (prints environment variables)
    * `exit` (exits the shell with an optional exit status)
* **Redirections**:
    * `<` : Redirects input.
    * `>` : Redirects output (truncate).
    * `>>` : Redirects output in append mode.
    * `<<` : Here-document (reads input until a given delimiter is seen).
* **Pipes (`|`)**: Connects the standard output of one command directly to the standard input of the next.
* **Expansions**:
    * Resolves environment variables (e.g., `$USER`, `$PATH`).
    * Resolves `$?` to the exit status of the most recently executed foreground pipeline.
* **Quote Handling**:
    * Single quotes (`'`): Prevents interpretation of all metacharacters within the quoted sequence.
    * Double quotes (`"`): Prevents interpretation of metacharacters, except for the `$` (dollar sign) for variable expansion.
* **Signal Handling**: 
    * `ctrl-C`: Displays a new prompt on a new line.
    * `ctrl-D`: Exits the shell.
    * `ctrl-\`: Does nothing.

## 🛠️ Prerequisites

To compile and run this project, you will need:
* A C compiler (e.g., `cc` or `gcc`)
* `make`
* The `readline` library installed on your system.
    * **Debian/Ubuntu**: `sudo apt install libreadline-dev`
    * **macOS**: `brew install readline`

## 🚀 Compilation and Usage

Clone the repository and run `make` at the root directory to compile the project.

```bash
# Compile the executable
make

# Run Minishell
./minishell