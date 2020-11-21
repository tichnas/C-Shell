# Custom C Shell

## Sanchit Arora | 2019101047

---

## Requirements

- GCC compiler
- Linux OS (preferably Ubuntu)

## Running Shell

From the root directory of project, run `make` followed by `./main`

## File & Functions

### Supporting Files

###### Files containing functions required for proper functioning of the shell.

- `main.c`

  - Run Shell Loop
  - Extract Arguments from command
  - Bind functions from different files together

- `prompt.c`

  - Print prompt
  - Checks for terminated child processes

- `command.c`

  - Takes input from user
  - Tokenize input to separate commands

- `runner.c`

  - Runs command in foreground or background

- `history.c`

  - Adds command to history
  - Stores maximum 20 commands

### Command Files

###### Files containing functions to run a particular command.

- `env.c`

  - Contains commands `setenv` and `unsetenv`.
  - Used to set/unset an environment variable.

- `jobs.c`

  - Prints all currently running background processes.

- `kjob.c`

  - Used to send signal to a process by job number.
  - Also used in a loop to implement `overkill`.

- `fg.c`

  - Brings a process to foreground and changes it state to Running.

- `bg.c`

  - Changes status of background process from Stopped to Running.

- `pwd.c`

  - Prints the working directory

- `echo.c`

  - Prints user input after removing excess spaces/tabs

- `cd.c`

  - Navigate to different directories

- `ls.c`

  - Prints all files/sub-directories in a location
  - Flags implemented: `a` and `l`
  - Multiple directories supported

- `pinfo.c`

  - Prints info about process with given PID (current process if none is given)

- `history.c`

  - Prints last _n_ commands, where n is the number given or 10.

### Other Implementations

###### Commands/functions which don't have a separate file.

- Signals

  - `Ctrl+Z` Sends current foreground process to background.
  - `Ctrl+C` Stops current foreground process.

- I/O Redirection and Pipes

  - Parsing is done in `command.c`.
  - `main.c` handles everything else.

- Background Processes Manipulations

  - Implementation of background processes list, removing/adding them from/to the list is done in `main.c`.

- Exit Codes

  - Depending on whether last command was successful or not, **:')** or **:'(** will appear before the prompt.
  - A background process will ONLY fail if the forking fails. All other situations will result in command success.

- Exiting from the Shell
  - `Ctrl+D` on an empty prompt.
  - `quit` command.

## Assumptions

- Reasonable assumptions are made for things like length of current path, number of commands, command length, etc. The shell will work perfectly for all "day to day work".

- `user` and `hostname` will be constant throughout the life of current shell instance.

- `echo` will treat everything as normal character.

- File and directory names shouldn't contain spaces or special characters. (Some commands may work even without this.)

- `pinfo` may break on systems not running Ubuntu. This command uses `/proc` files which may not be same for other OS.

- Every user input will be stored as it is in history, given it is not same as the last input and contains at least one character other than space or tab.

- Prompt will display only _terminated normally_ or _terminated abnormally_ when a background process ends.

- Prompt will check exist status of background processes only after user inputs a command (possibly empty). The same happens in actual Bash shell.

- Any error while running a command will result in aborting the command after printing an error message.

- `&` (used for running process in background) can come anywhere in command.

- A hidden file (`.history`) is used to store history in a readable format. Any changes explicitly done in this file may result in unexpected output of `history` command.

- **<**, **>**, **>>** and **|** will always have their special meanings and will be used correctly. This means that for I/O redirection, a file (may be an invalid name) will always come after the arrow. Similary, a command (may be an invalid) will always come after a pipe.

> Will try to implement more features soon, Wish me luck!
