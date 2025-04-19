# 42 Pipex

This project emulates the shell’s redirection and piping (`|`) behaviour in C. It introduces key system-level concepts — **process forking**, **file descriptor duplication**, and **inter-process communication** — and serves as a solid exercise in low-level I/O and execution flow.


## Status

- ✅ Validated: 20.12.2024.
- 🎓 Grade: 125/100.
- 🚦 Compliant with [42 Norm](#note) rules.

## Usage

### Main part

The main `pipex` program takes an input file, runs a command on it, pipes the output into a second command, and writes the final result to an output file. It essentially mimics the shell behaviour of:

```
< infile command1 | command2 > outfile
```

##### Compilation:

To compile, use `make` or `make all`.

##### Execution:

`pipex` supports two commands and is executed as follows:

```
./pipex infile command1 command2 outfile
```

The result of the final command will be written to the specified output file. If the file doesn’t exist, it will be created. If it does, it will be overwritten — the same way the shell handles `>` operator.

🗒️ **Note**: Command arguments or flags must be wrapped in quotes.

```
./pipex infile.txt "cat" "wc -l" outfile.txt
```

### Bonus part:

The bonus part of `pipex` supports multiple commands, replicating the shell behaviour of:

```
< infile command1 | command2 | ... | commandN > outfile
```

It also handles heredocs (`<<`), prompting the user for input and feeding it into the first command.

🗒️ **Note**: When using heredoc, the final result is redirected in append mode (`>>`). This means the output file won't be overwritten, but appended to — equivalent to the following shell behaviour:

```
<< EOF command1 | command2 | ... | commandN >> outfile
```

##### Compilation:

Compile the bonus version with `make bonus`.

##### Execution:

To run pipex with a heredoc, use `here_doc` keyword instead of the infile, followed by a `delimiter` of choice as an extra argument:

```
./pipex here_doc EOF command1 command2 ... commandN outfile
```

### Constraints

The program does **not** support advanced shell syntax such as nested quotes, parentheses, or complex expressions in command arguments like: `awk 'BEGIN { for(i=1;i<=6;i++) print "square of", i, "is", i*i; }'
`

<a id="note"></a>

> 🛠️ **Note:**
> 42 project requirements that impact structure and readability:
> - Functions must be no longer than 25 lines.
> - A file may contain a maximum of 5 functions.
> - `for`, `do..while`, `switch`, ternary operators, and VLAs are forbidden.
> - Standard C library functions are not allowed (unless a few specific ones are explicitly permitted for a project).
> - Variables cannot be declared and assigned in the same line.

⚠️ P.S. Don't copy, learn!

Made by: nkhamich@student.codam.nl | LinkedIn: [nkhamichonak](https://www.linkedin.com/in/nkhamichonak/)
