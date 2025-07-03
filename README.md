# Simple Shell (hsh)

A comprehensive UNIX command line interpreter written in C that replicates the functionality of `/bin/sh`. This project implements a fully functional shell with command parsing, PATH resolution, built-in commands, and proper process management with accurate exit status handling.

## Table of Contents

1. [Authors](#authors)
2. [Project Description](#project-description)
3. [Features](#features)
4. [Installation](#installation)
5. [Usage](#usage)
6. [File Structure](#file-structure)
7. [Function Documentation](#function-documentation)
8. [Built-in Commands](#built-in-commands)
9. [Command Resolution](#command-resolution)
10. [Exit Status Handling](#exit-status-handling)
11. [Error Handling](#error-handling)
12. [Memory Management](#memory-management)
13. [Testing](#testing)
14. [Examples](#examples)
15. [Technical Implementation](#technical-implementation)
16. [Standards and Compliance](#standards-and-compliance)
17. [Known Limitations](#known-limitations)
18. [Troubleshooting](#troubleshooting)

## Authors

- **Farah Almozaini** - [farahmzini@gmail.com](mailto:farahmzini@gmail.com)
- **Haifa bin hasher** - [Haifahasher@gmail.com](mailto:Haifahasher@gmail.com)

## Project Description

This simple shell is a command-line interpreter that provides a basic interface between the user and the operating system. It reads commands from the user, interprets them, and executes the appropriate programs. The shell supports both interactive and non-interactive modes, implements essential built-in commands, handles command resolution through the PATH environment variable, and properly manages process exit statuses.

### Key Objectives

- Understand how shells work internally
- Implement process creation and management with proper exit status handling
- Handle system calls and error conditions
- Manage memory allocation and deallocation
- Parse and tokenize user input
- Implement command search algorithms
- Handle both interactive and non-interactive modes

## Features

### Core Functionality
- **Interactive Command Line**: Displays a prompt and waits for user input
- **Non-Interactive Mode**: Executes commands from pipes, files, or scripts
- **Command Parsing**: Tokenizes input into commands and arguments
- **Process Management**: Creates child processes to execute commands
- **PATH Resolution**: Automatically searches for commands in PATH directories
- **Built-in Commands**: Implements essential shell built-ins (`exit`, `env`)
- **Error Handling**: Comprehensive error reporting and handling
- **Memory Management**: Proper allocation and deallocation of resources
- **Exit Status Management**: Accurate handling and propagation of command exit statuses

### Advanced Features
- **Environment Variable Access**: Full access to environment variables
- **Signal Handling**: Proper handling of child process termination
- **Line Counting**: Tracks line numbers for error reporting
- **Command Validation**: Checks command existence before execution
- **Interactive Detection**: Automatically detects interactive vs non-interactive mode

## Installation

### Prerequisites
- GCC compiler (version 4.8 or higher)
- UNIX-like operating system (Linux, macOS, Unix)
- Standard C library

### Compilation

#### Method 1: Direct Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

#### Method 2: Individual File Compilation
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -c main.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -c shell.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -c builtin.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -c path.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -c prompt.c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.o -o hsh
```

#### Method 3: With Debug Information
```bash
gcc -g -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

### Installation Options
```bash
# Make executable
chmod +x hsh

# Install to system directory (optional)
sudo cp hsh /usr/local/bin/

# Create symbolic link (optional)
sudo ln -s /path/to/hsh /usr/local/bin/hsh
```

## Usage

### Interactive Mode

Start the shell:
```bash
./hsh
```

The shell will display a prompt (`$ `) and wait for commands:
```bash
$ ls -la
$ pwd
$ echo "Hello, World!"
$ /bin/ls
$ env
$ exit
```

### Non-Interactive Mode

#### Using Pipes
```bash
echo "ls -la" | ./hsh
echo -e "pwd\nls\necho test" | ./hsh
```

#### Using Input Redirection
```bash
./hsh < commands.txt
```

#### Using Here Documents
```bash
./hsh << EOF
ls -la
pwd
whoami
EOF
```

## File Structure

```
simple_shell/
├── AUTHORS              # Contributors list
├── README.md           # This documentation file
├── .gitignore          # Git ignore rules
├── shell.h             # Header file with prototypes and includes
├── main.c              # Entry point and main shell loop
├── shell.c             # Core shell functions
├── builtin.c           # Built-in command implementations
├── path.c              # PATH resolution and command search
├── prompt.c            # Prompt display functionality
└── hsh                 # Compiled executable (after compilation)
```

### File Descriptions

- **shell.h**: Contains all function prototypes, includes, and external declarations
- **main.c**: Entry point with the main shell loop and program initialization
- **shell.c**: Core functions for reading input, parsing, and executing commands
- **builtin.c**: Implementation of built-in commands like `exit` and `env`
- **path.c**: Functions for finding commands in PATH directories
- **prompt.c**: Simple prompt display function
- **.gitignore**: Specifies files to ignore in version control (hsh executable, *.o files, .*.c files)

## Function Documentation

### main.c Functions

#### `int main(int ac, char **av)`
**Purpose**: Entry point for the shell program
**Parameters**: 
- `ac`: Argument count (unused but required by main signature)
- `av`: Argument vector (program name used for error messages)
**Return**: 0 on success, exit status on error
**Description**: 
- Implements the main shell loop
- Handles interactive mode detection using `isatty(STDIN_FILENO)`
- Manages line counting for error reporting
- Tracks last command exit status for proper exit handling
- Handles memory cleanup and graceful termination

**Key Features**:
- Automatic prompt display in interactive mode
- Proper cleanup of resources (line and args)
- Built-in command handling with appropriate exit behavior
- Exit status propagation from child processes

### shell.c Functions

#### `char *read_line(void)`
**Purpose**: Reads a line of input from stdin
**Parameters**: None
**Return**: Pointer to allocated string containing the line, NULL on EOF
**Description**: 
- Uses `getline()` to read input dynamically
- Handles EOF conditions properly
- Manages memory allocation automatically
- Returns NULL on EOF or read error

#### `char **split_line(char *line)`
**Purpose**: Tokenizes input line into array of arguments
**Parameters**: 
- `line`: Input string to tokenize
**Return**: NULL-terminated array of string pointers
**Description**: 
- Splits input on whitespace characters (space, tab, carriage return, newline)
- Dynamically allocates memory for token array
- Starts with buffer size of 64 and grows by 64 as needed
- Returns NULL-terminated array for easy iteration

#### `int execute(char **args, char *argv0, int line_count)`
**Purpose**: Executes a command with given arguments
**Parameters**: 
- `args`: Array of command arguments
- `argv0`: Program name for error messages
- `line_count`: Current line number for error reporting
**Return**: 
- 127 for command not found
- Child process exit status for successful execution
- 1 for fork failure or other errors
**Description**: 
- Resolves command path using `find_path()`
- Forks child process for command execution
- Uses `execve()` to replace child process with command
- Properly waits for child completion and extracts exit status
- Handles memory cleanup for dynamically allocated paths

**Key Improvements**:
- Proper exit status extraction using `WIFEXITED()` and `WEXITSTATUS()`
- Enhanced error handling for fork failures
- Proper memory management for command paths

### builtin.c Functions

#### `int handle_builtin(char **args)`
**Purpose**: Checks and executes built-in commands
**Parameters**: 
- `args`: Array of command arguments
**Return**: 
- 1 if built-in was executed successfully
- 0 if not a built-in command
- -1 for exit command
**Description**: 
- Identifies built-in commands by comparing first argument
- Executes appropriate built-in function
- Returns special code for exit to signal shell termination

#### `void print_env(void)`
**Purpose**: Prints all environment variables
**Parameters**: None
**Return**: void
**Description**: 
- Iterates through global `environ` array
- Prints each environment variable on separate line
- Format: `VARIABLE=value`

### path.c Functions

#### `char *find_path(char *command)`
**Purpose**: Finds full path of a command
**Parameters**: 
- `command`: Command name to search for
**Return**: 
- Full path string (must be freed) for PATH commands
- Original command string for absolute/relative paths
- NULL if not found
**Description**: 
- Handles absolute and relative paths (containing '/')
- Searches PATH directories for command
- Uses `stat()` to verify file existence
- Returns dynamically allocated path that must be freed

#### `char *search_path_dirs(char *path, char *command)`
**Purpose**: Searches specific PATH directories for command
**Parameters**: 
- `path`: PATH environment variable string
- `command`: Command to search for
**Return**: Full path if found, NULL otherwise
**Description**: 
- Creates copy of PATH to avoid modifying original
- Tokenizes PATH on colon separators
- Constructs full path for each directory
- Uses `stat()` to check file existence
- Properly manages memory for path construction

### prompt.c Functions

#### `void prompt(void)`
**Purpose**: Displays the shell prompt
**Parameters**: None
**Return**: void
**Description**: 
- Writes prompt string (`$ `) to stdout
- Uses `write()` system call for direct output
- Simple and efficient prompt display

## Built-in Commands

### `exit`
**Syntax**: `exit [status]`
**Description**: Exits the shell with the exit status of the last executed command
**Behavior**: 
- Terminates the shell process immediately
- Uses the exit status from the most recent command
- Frees all allocated memory before exiting
- Does not accept status arguments in current implementation

**Examples**:
```bash
$ exit
# Exits with status of last command
```

**Return Value**: Does not return (terminates shell)

### `env`
**Syntax**: `env`
**Description**: Prints all environment variables
**Behavior**: 
- Displays each environment variable on a separate line
- Format: `VARIABLE=value`
- Accesses global `environ` array directly
- No sorting or filtering applied

**Examples**:
```bash
$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
USER=user
SHELL=/bin/bash
PWD=/current/directory
```

**Return Value**: Always returns 0 (success)

## Command Resolution

### Path Resolution Algorithm

1. **Direct Path Check**: If command contains '/', treat as absolute/relative path
   - Use `stat()` to verify file exists
   - Return original command string if valid
   - Return NULL if file doesn't exist

2. **PATH Search**: For commands without '/', search PATH directories
   - Extract PATH from environment variables
   - Split PATH into individual directories
   - For each directory, construct full path
   - Check file existence with `stat()`
   - Return first valid path found

3. **Error Handling**: Return NULL if command not found anywhere

### Search Order

1. Absolute paths (starting with `/`)
2. Relative paths (containing `/`)
3. PATH directories (left to right order)
4. Current directory (only if `.` is in PATH)

### Path Validation

- Uses `stat()` system call to check file existence
- Verifies file is a regular file
- Does not explicitly check execute permissions (handled by `execve()`)
- Properly handles symbolic links

## Exit Status Handling

### Exit Status Codes
- **0**: Success
- **1-125**: Command-specific error codes
- **126**: Command found but not executable
- **127**: Command not found
- **128+n**: Command terminated by signal n

### Exit Status Management
- **Last Status Tracking**: Shell tracks exit status of last executed command
- **Built-in Exit**: `exit` command uses last command's exit status
- **Proper Extraction**: Uses `WIFEXITED()` and `WEXITSTATUS()` macros
- **Signal Handling**: Distinguishes between normal exit and signal termination

### Status Propagation
```c
// In execute() function
if (WIFEXITED(status))
    return (WEXITSTATUS(status));  // Normal exit
else
    return (1);                    // Abnormal termination
```

## Error Handling

### Error Types and Messages

#### Command Not Found
```bash
./hsh: 1: invalidcommand: not found
```
**Exit Status**: 127
**Cause**: Command not found in PATH or specified location

#### Fork Failure
```bash
fork: Resource temporarily unavailable
```
**Exit Status**: 1
**Cause**: System cannot create new process

#### Memory Allocation Failure
**Behavior**: Function returns NULL, handled gracefully
**Cause**: Insufficient memory for operations

### Error Reporting Format

All errors follow the format:
```
program_name: line_number: command: error_message
```

Where:
- `program_name`: Name of the shell executable (`av[0]`)
- `line_number`: Line number where error occurred
- `command`: Command that caused the error
- `error_message`: Descriptive error message

## Memory Management

### Allocation Strategy

- **Dynamic Allocation**: Uses `malloc()`, `realloc()`, and `strdup()`
- **Growth Strategy**: Token array grows in chunks of 64 elements
- **Cleanup**: Comprehensive cleanup after each command
- **Error Handling**: Checks all allocation return values

### Memory Lifecycle

1. **Input Reading**: `getline()` allocates memory for input line
2. **Token Parsing**: `malloc()` allocates array for arguments
3. **Path Resolution**: `malloc()` and `strdup()` for path strings
4. **Cleanup**: `free()` releases all allocated memory

### Memory Leak Prevention

- **Consistent Cleanup**: Frees `line` and `args` after each command
- **Early Exit Handling**: Cleanup even when continuing to next iteration
- **Error Condition Cleanup**: Proper cleanup in error paths
- **Path String Management**: Distinguishes between allocated and static strings

```c
// Example cleanup pattern
free(line);
free(args);
if (builtin_status == -1)
    exit(last_status);
```

## Testing

### Test Categories

#### Basic Functionality Tests
```bash
# Test basic commands
$ ls
$ pwd
$ echo "test"
$ whoami
$ date
```

#### Built-in Command Tests
```bash
# Test built-ins
$ env
$ exit
```

#### Path Resolution Tests
```bash
# Test different path formats
$ /bin/ls          # Absolute path
$ ./hsh            # Relative path
$ ls               # PATH search
$ /usr/bin/whoami  # Absolute path
```

#### Error Condition Tests
```bash
# Test error handling
$ nonexistentcommand
$ /path/to/nonexistent
$ ""               # Empty command
$                  # Empty line
```

#### Non-Interactive Mode Tests
```bash
# Test piped input
echo "ls" | ./hsh
echo -e "pwd\nls\necho test" | ./hsh

# Test input redirection
./hsh < test_commands.txt

# Test here documents
./hsh << EOF
ls
pwd
echo "Hello"
EOF
```

#### Exit Status Tests
```bash
# Test exit status handling
echo "ls" | ./hsh; echo $?          # Should be 0
echo "invalidcmd" | ./hsh; echo $?  # Should be 127
```

### Test Script Example

```bash
#!/bin/bash
# Comprehensive test script

echo "=== Testing Basic Commands ==="
echo "ls" | ./hsh
echo "pwd" | ./hsh
echo "echo 'Hello World'" | ./hsh

echo "=== Testing Built-ins ==="
echo "env" | ./hsh | head -5
echo "exit" | ./hsh

echo "=== Testing Error Conditions ==="
echo "nonexistentcommand" | ./hsh
echo "/bin/nonexistent" | ./hsh

echo "=== Testing Path Resolution ==="
echo "/bin/ls" | ./hsh
echo "./hsh" | ./hsh < /dev/null

echo "=== Testing Exit Status ==="
echo "ls" | ./hsh; echo "Exit status: $?"
echo "invalidcmd" | ./hsh; echo "Exit status: $?"
```

## Examples

### Interactive Session Example
```bash
$ ./hsh
$ ls -la
total 32
drwxr-xr-x 2 user user 4096 Mar 15 10:30 .
drwxr-xr-x 3 user user 4096 Mar 15 10:30 ..
-rwxr-xr-x 1 user user 8760 Mar 15 10:30 hsh
-rw-r--r-- 1 user user  150 Mar 15 10:30 main.c
$ pwd
/home/user/simple_shell
$ echo "Hello, World!"
Hello, World!
$ /bin/date
Mon Mar 15 10:30:45 UTC 2024
$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/user
USER=user
SHELL=/bin/bash
$ exit
```

### Non-Interactive Example
```bash
$ echo -e "ls\npwd\necho test" | ./hsh
main.c shell.c builtin.c path.c prompt.c shell.h hsh
/home/user/simple_shell
test

$ ./hsh << EOF
ls -la
echo "Script execution"
env | grep PATH
EOF
```

### Error Handling Example
```bash
$ ./hsh
$ invalidcommand
./hsh: 1: invalidcommand: not found
$ /bin/invalidcommand
./hsh: 2: /bin/invalidcommand: not found
$ ls
main.c shell.c builtin.c path.c prompt.c shell.h
$ exit
```

## Technical Implementation

### Process Flow

1. **Initialization**: 
   - Set up variables and counters
   - Enter main loop

2. **Input Processing**:
   - Check if running interactively with `isatty()`
   - Display prompt if interactive
   - Read line using `getline()`
   - Handle EOF conditions

3. **Command Processing**:
   - Parse line into tokens
   - Handle empty lines and commands
   - Check for built-in commands
   - Execute external commands

4. **Command Execution**:
   - Resolve command path
   - Fork child process
   - Execute command with `execve()`
   - Wait for completion and extract exit status

5. **Cleanup and Loop**:
   - Free allocated memory
   - Update status tracking
   - Continue or exit based on conditions

### System Calls Used

- `fork()`: Create child processes
- `execve()`: Execute commands
- `waitpid()`: Wait for child completion with status
- `stat()`: Check file existence and permissions
- `getline()`: Read input lines dynamically
- `write()`: Output prompt and messages
- `isatty()`: Detect interactive mode

### Data Structures

- **Command Arguments**: NULL-terminated array of strings
- **Environment Variables**: External `environ` array
- **Path Components**: Tokenized PATH directories
- **Status Tracking**: Integer variables for exit codes

### Key Algorithms

- **Tokenization**: Whitespace-based parsing with dynamic growth
- **Path Resolution**: Sequential directory search with existence checking
- **Process Management**: Fork-exec-wait pattern with proper status handling
- **Memory Management**: Allocation, tracking, and cleanup patterns

## Standards and Compliance

### Coding Standards
- **Betty Style**: Follows Betty coding style guidelines
- **ANSI C**: Compatible with C89/C90 standards
- **POSIX**: Compliant with POSIX.1 standards for basic functionality
- **GNU C**: Uses GNU C extensions where appropriate

### Compiler Flags
- `-Wall`: Enable all warnings
- `-Werror`: Treat warnings as errors
- `-Wextra`: Enable extra warnings
- `-pedantic`: Strict ISO C compliance
- `-std=gnu89`: Use GNU C89 standard

### Documentation Standards
- **Function Documentation**: Complete Betty-style documentation
- **Header Guards**: Proper include guard implementation
- **External Declarations**: Proper `extern` usage for global variables
- **Error Handling**: Comprehensive error checking and reporting

## Known Limitations

### Unsupported Features
- **Pipes**: No support for `|` operator
- **Redirections**: No support for `>`, `<`, `>>` operators
- **Background Processes**: No support for `&` operator
- **Command Substitution**: No support for `$()` or backticks
- **Variables**: No support for shell variables or expansion
- **Wildcards**: No support for `*`, `?`, `[]` expansion
- **Quoting**: Limited support for quotes and escaping
- **Job Control**: No support for job management
- **History**: No command history functionality
- **Tab Completion**: No auto-completion features
- **Aliases**: No support for command aliases
- **Functions**: No support for shell functions

### Technical Limitations
- **Exit Status Arguments**: `exit` command doesn't accept status arguments
- **Signal Handling**: Limited signal handling capabilities
- **Environment Modification**: No built-in commands to modify environment
- **Working Directory**: No `cd` command implementation
- **Advanced PATH**: No support for PATH modification commands

### Implementation Constraints
- **Buffer Sizes**: Token array grows in fixed increments
- **Memory Limits**: Subject to system memory constraints
- **Path Length**: Limited by system PATH_MAX
- **Command Length**: Limited by system ARG_MAX

## Troubleshooting

### Common Issues

#### Compilation Errors
**Problem**: `gcc: command not found`
**Solution**: Install GCC compiler
```bash
# Ubuntu/Debian
sudo apt-get install gcc

# RedHat/CentOS
sudo yum install gcc

# macOS
xcode-select --install
```

**Problem**: `Permission denied` when running `./hsh`
**Solution**: Make file executable
```bash
chmod +x hsh
```

#### Runtime Errors
**Problem**: `Command not found` for valid commands
**Solution**: Check PATH environment variable
```bash
echo $PATH
export PATH="/usr/local/bin:/usr/bin:/bin:$PATH"
```

**Problem**: Memory allocation failures
**Solution**: Check available memory and system limits
```bash
ulimit -a
free -m
```

#### Interactive Mode Issues
**Problem**: No prompt displayed
**Solution**: Ensure stdin is a terminal
```bash
# Check if running interactively
test -t 0 && echo "Interactive" || echo "Non-interactive"
```

### Debug Techniques

#### Memory Debugging
```bash
# Check for memory leaks
valgrind --leak-check=full ./hsh

# Monitor memory usage
ps aux | grep hsh
```

#### Process Debugging
```bash
# Trace system calls
strace -f ./hsh

# Debug with GDB
gdb ./hsh
```

#### Error Logging
```bash
# Capture all output
./hsh 2>&1 | tee shell_output.log

# Test specific scenarios
echo "command" | ./hsh 2>&1
```

### Performance Optimization

- **PATH Optimization**: Keep PATH directories ordered by frequency of use
- **Memory Management**: Monitor allocation patterns for efficiency
- **System Calls**: Minimize unnecessary system call overhead
- **Error Handling**: Optimize error checking for common cases

---

## Additional Resources

- **POSIX Shell Specification**: IEEE Std 1003.1-2017
- **GNU Bash Manual**: https://www.gnu.org/software/bash/manual/
- **Advanced Programming in the UNIX Environment**: Stevens & Rago
- **The Linux Programming Interface**: Michael Kerrisk
- **C Programming Language**: Kernighan & Ritchie


