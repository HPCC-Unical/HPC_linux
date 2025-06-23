# The BASH shell

## What is a shell?

There are many different shells out there and bash is the most common one.

In the past the Bourne shell (from which Bash comes: Bash stands for "Bourne-again shell") and csh/tcsh where the most common command shells. Nowadays there are many others (fish, zsh, etc.), but Bash is still the most used and installed in many systems (see, for instance, the majority of linux distributions and apple computers), even when it is not the default shell.

Modern smartphones or router or embedded devices have some sort of reduced version of the shells, including also some other external programs (we will talk about the difference between builtin commands to the shell and external linux commands), called "busybox" or "toybox".

The shell is actually **a true programming language** that allows you to do things interactively on the command line or execute sequences of commands contained in text files called "scripts" (just like you do with python commands, that can be executed both interactively or grouped in scripts). This represents the true power of the shell, in the sense that it lets you execute system-level commands to operate on files with a few lines interactively or very complex commands by executing shell scripts.

The shell is made of COMMANDS and some modifiers that represent the arguments on which the command operates to produce some results.


## Shell editing

Editing commands: typical emacs-style bindings. It is possible also to use vim-style bindings, but that is not the default and we strive to use the default...

| Key combination | Action |
| :--- | :--- |
|`^l`|clear the screen (also the command `clear` does)|
|`^a`|go to the beginning of the line|
|`^e`|go to the end of the line|
|`^d`|erase a single character|
|`^p / cursor-up`|move up in the list of commands|
|`^n /cursor-down`|move down in the list of commands|
|`^f / cursor-left`|move the cursor left|
|`^b / cursor-right`|move the cursor right|
|`Alt-f`|move to the right of a word|
|`Alt-b`|move to the left of a word|
|`Alt-d`|erase a single word|
|`^k`|remove the part of the line from the cursor position to the end of the line|
|`^u`|remove the part of the line from the cursor position to the beginning of the line|
|`^space-bar`|starts a selection|
|`^w`|remove the selection|
|`^y`|yanks the part of the line previously removed with ^k or ^u or ^w|
|`^r`|recalls previous commands with a string|


## The echo command

The echo command just prints out the words that follow the command itself:

    $ echo Hello World

just prints:

`Hello World`

However, it is a good habit, for several reasons, to put the arguments to be printed in **single or double quotation marks**: `"` or `'`

    $ echo "Hello World"

and

    $ echo 'Hello World'

are equivalent for simple expressions to print like this, but we will see soon that there is actually a difference, given by the fact that single quotation marks print out any character independently of their special meaning, by treating all characters equivalently, while double quotes recognize the special meaning of some characters and treat them accordingly.

For instance, if you want to put part of the string to be printed in double quotes, like this:

    $ echo "I say to you: "wonderful job""

just the string:

`I say to you: wonderful job`

will be printed. Why? Because the second `"` is interpreted as the end of a first string and then there is a second string without quotes and then an empty string between `""`.

A possible solution is to use both single and double quotes:

    $ echo 'I say to you: "wonderful job"'

produces the correct result, but also:

    $ echo "I say to you: 'wonderful job'"

produces the equivalent form:

`I say to you: 'wonderful job'`

Another possibility is to use the **backslash** `\` to prevent the shell interpreter to treat the `"` in their original meaning but simply to treat them as a **normal** character.

For instance:

    $ echo "I say to you: \"wonderful job\""

works as expected.

However troubles can derive from the mixing of the single and double quotes. Consider the following example:

    $ echo 'I say to you: "It's a marvellous day"'

doesn't work, because of the `'` of the `It's` and the shell will expect some closing `'` and will print a `>` to continue the command.

However, this is not the only case. Some other character have a special meaning that may render very strange results.

For instance, the command:

    $ echo "Hello World!"

prints just:

`Hello World!`

but a subsequent:

    $ echo "Hello World!!"

would produce:

    echo "Hello Worldecho "Hello World!""
    Hello worldecho Hello World!

because the symbol `!!` has a special meaning (it recalls the last command in the history list!).

However, if one uses single quotes, it prints just the regular sentence:

    $ echo 'Hello World!!'

prints:

`Hello World!!`

Another character "special" to the shell is the `$` sign, which identifies a variable.

For instance, if I want to say:

    $ echo "I paid $10 for a usb stick"

this produces:

`I paid 0 for a usb stick`

Why? Because any symbol preceded by a "$" is considered a variable in bash and since we did not define a variable with the name "1" it substitutes nothing to "$1" and prints just the subsequent "0".

As usual, the solution is to use double quotes or the "\" symbol to prevent the interpretation of the special character:

    $ echo 'I paid $10 for a usb stick'

or

    $ echo "I paid \$10 for a usb stick"

will give the correct result!


## A short introduction to variables

I take the opportunity of this example to show you how to define a shell variable. Keep in mind that the **shell treats both numeric integer variables and strings and even one-dimensional arrays**. For the moment I just show you how to define a simple variable and use it.

To define a variable with name "name" in bash you use the syntax:

    $ name="Leonardo Primavera"

then to use the value of the variable you precede it with the symbol "$":

    $ echo "My name is: $name"

prints:

`My name is: Leonardo Primavera`

Note how if we don't use the quotes (single or double), this gives an error:

    $ name=Leonardo Primavera

produces:

`-bash: Primavera: command not found`

Why? Because the shell syntax allows you to execute a command immediately after a variable definition (for instance to execute that command with a different value of the variable) and therefore the value "Leonardo" would be assigned to the variable "name" but then the shell would understand that "Primavera" is a command to execute and produces the error "command not found"...

Moreover, note that you shouldn't use spaces between the name and definition of the variable!

For instance, the instruction:

    $ name = "Leonardo Primavera"

yields an error:

`-bash: name: command not found`

because name is interpreted as a command by the shell. Also:

    $ name= "Leonardo Primavera"

yields an error:

`-bash: Leonardo Primavera: command not found`

because nothing is assigned to the variable "name" and the string is interpreted as a command following the variable assignment!

We will come back to variable use and assignments very soon during the lecture...


## More on `echo`

Going back to the `echo` statement, there are some flags that can be used:

- -n &nbsp;&nbsp;&nbsp;&nbsp; does not print the final newline;
- -e &nbsp;&nbsp;&nbsp;&nbsp; allows the interpretation of escape sequences, namely special sequences of characters that assume a special meaning when printed.

Example:

    $ echo -n "Hello World!"

prints:

`Hello World!$`

namely prints the prompt after the string, because the final newline was not printed!

    $ echo "Hello\nWorld!"

prints:

`Hello\nWorld!`

but:

    $ echo -e "Hello\nWorld!"

prints:

    Hello
    World!

because `\n` is the newline escape sequence. Other escape sequences are like in C language:

|Escape sequence|Meaning|
|:---|:---|
|`\t`|horizontal tab|
|`\v`|vertical tab|
|`\xNN`|hexadecimal character NN|
|`\0xxx`|octal character xxx|
|`\\`|backslash character|
|`\a`|alert bell|
|`\b`|backspace|
|`\r`|carriage return|
|`\f`|form feed|

Note how it is possible to add **colors** to what it is printed through the use of the escape sequences.

Example: a sequence of characters like:

    $ echo -e "\033[3xmSome string"

will print `Some string` in a different foreground color identified by the numerical code "`x`". Up to 7 colors can be used:

| Color code | Actual color |
|:---|:---|
|0|Black|
|1|Red|
|2|Green|
|3|Yellow|
|4|Blue|
|5|Magenta|
|6|Cyan|
|7|White|

Instead, a sequence like:

    $ echo -e "\033[4xmSome String"

prints `Some string` with the background color specified by the color code "`x`". The color codes are the same as in the table above.

Example:

    $ echo -e "Please, \033[31mHit \033[42many key\033[40m to continue\033[37m..."

will print the string <font style="color: red">`Hit any key to continue`</font> in red and <font style="color:red;background-color:green">`any key`</font> on a green background...

Note that there are other ways to print strings in color, for instance the commands `tput` and `setterm`, which are easier to use than escape sequences, though less standard!


## read command

We have seen how to print strings and variable values on the screen. How about reading some input and assign it to a string?

We can use the built-in command `read` to achieve that result. For instance:

    $ read name

wait for an input and assign it to the variable name. If we input "Leonardo" and then we execute:

    $ echo $name

it will print:

`Leonardo`

The option `-p` prints a prompt and then waits for the input. Example:

    $ read -p "Please, insert your name: " name


## Several commands on a single line

It is possible to execute multiple commands in sequence on a single line, by separating them with a semicolon: "`;`".

For instance:

    $ echo "Please, insert your name: "; read name; echo "Hello $name"

The only difference is that in this case the first echo is on a different line with respect to the input of "name".

**Note**: blank spaces before or after the semicolon are ignored!

**Note**: there are some pre-defined values in the shell, for instance:

- `$0` is the name of the invoked shell. If we print:

    `echo $0`

    we obtain:

    `-bash`

- `$1` ... `$9` are the arguments passed on the command line to the shell invoked

and several others that we will see later on.


## Internal (built-in) and external commands

There are **internal** and **external** commands: internal means that those commands are built-in the shell and so no external executable is invoked when they are typed and are directly executed by the shell. External commands are external executables that are invoked by the shell when the typed command cannot be interpreted as an internal command.

The command `type` tells us if the command is a "built-in" command or an "external" command:

    $ type echo
    echo is a shell builtin

    $ type read
    read is a shell builtin

    $ type ls
    cat is hashed (/usr/bin/cat)

    $ type type
    type is a shell builtin

Note how:

    $ type ls
    ls is aliased to `ls --color=auto'

tells that the command `ls` is actually an `alias`, namely a shortened version, of a more complicated command. We will discuss the definition of "aliases" later on.

A rather confusing thing comes, for instance, from the fact that the `echo` command is defined (generally with identical capabilities!) both as a built-in command (as indicated by "type") and an external command in "/usr/bin/echo". When invoking `echo` the built-in command is invoked, if you want to use the external one you have to call with the whole pathname (/usr/bin/echo).

There is another way to print values through the built-in command `printf` that works in a similar way to the C construct:

    $ name="Leonardo"
    $ printf "%s\n" $name

prints:

`Leonardo`

Note, however, that the variable should be enclosed into quotes to avoid problems. For instance:

    $ name="Leonardo Primavera"
    $ printf "%s\n" "$name"

prints:

`Leonardo Primavera`

but

    $ printf "%s\n" $name

prints:

    Leonardo
    Primavera

because `Leonardo Primavera` is interpreted as a list of strings and each string is then followed by the `\n`.
Note however as:

    $ printf "%s %s\n" $name

would print the correct string.


## Brace expansion

An interesting and very useful feature that can be done in the shell is the so-called **BRACE EXPANSION**, namely the possibility to execute some kind of "implicit loops" on data, both numerical and literal.
For instance, an instruction in curly braces like the following:

    $ echo {1..10}

will print all numbers between 1 and 10 included!

Analogously, an expression like:

    $ echo {1..10..2}

will print: `1 3 5 7 9` (namely the numbers between 1 and 10 in steps of 2!).

Note the result of the following:

    $ echo {01..10..2}

that prints: `01 03 05 07 09`

The same can be done with letters:

    $ echo {A..Z}

will print all letters between A and Z. It is possible to jump some letters, like in:

    $ echo {a..z..5}

that will print: `a f k p u z` (namely the letters from a to z jumping each five letters!)

Instead, putting in braces a set of values separated by commas, as:

    $ echo Myfile_{a,b,c}.txt

will print:

`Myfile_a.txt Myfile_b.txt Myfile_c.txt`

Also, it is possible to couple the different expansions to obtain quite complicated results, like:

    $ echo Myfile_{a..d..2}_{1..3}.{cpp,exe}

produces:
`Myfile_a_1.cpp Myfile_a_1.exe Myfile_a_2.cpp Myfile_a_2.exe Myfile_a_3.cpp Myfile_a_3.exe Myfile_c_1.cpp Myfile_c_1.exe Myfile_c_2.cpp Myfile_c_2.exe Myfile_c_3.cpp Myfile_c_3.exe`

The brace expansion **does not work only with the "echo" command**, but with **any command** that accepts parameters.

A further example: the external command `touch` produces new empty files if those do not exist, or updates the dates if they already exist.

Therefore a command like:

    $ touch my_document.{tex,aux,log,pdf}

produces 4 files.

The external command `rm` removes the files:

    $ rm my_document.{tex,aux,log,pdf}

Another useful example:

    $ touch Myfile_{001..100}.dat

produces 100 files in the current directory, named `Myfile_001.dat, Myfile_002.dat, ..., Myfile_100.dat`

The instruction:

    $ rm Myfile_{001..100..2}.dat

removes all the files with the odd numbers!

Later on, we will see how to achieve similar results with the "`for`" command in bash and an analogous sequence of files with the (external) command `seq`...


## Print to a file

We have just seen how to print to the screen. If we want to print a string in a file, instead of the screen we can use the "shell redirection" commands:

- `echo "string" > file_name` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; prints the string in the file `file_name`, by erasing it if it exists
- `echo "string" >> file_name` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; appends the string in the file `file_name`

Example:

    $ read -p "Insert name: " name
    $ echo "$name" > test_file.txt
    $ read -p "Telephone number: " phone
    $ echo "$phone" >> test_file.txt
    $ cat test_file.txt

prints the strings you typed.

The (external) `cat` command concatenates several files into one by printing the whole content on the screen. If used with one single file, it just displays the content of the file.

    > Note: any command and file name can be completed by typing some characters of the command or of the file name and then press TAB, if the completion is unique.
    > If it is not, the shell shows you the possible completions.

Note how it is possible to **read from a file** with the command `read`. However, this is seldom used, since there are more effective ways to read elements from a file and eloborating them. We will se many examples later on...


## Shell scripts

Now that we understood how to use some basic commands, we can start writing a script, namely a collection of commands that can be executed, eventually invoked with different parameters, like a program.

To create a script, we need to use a file editor. You will see the details of the use of the editor `vim` later on in another lecture, but we can start using it for basic editing purposes.

When editing a shell script, suppose that we call the file as:

`myscript.sh`

The suffix `.sh` means nothing, calling it simply `myscript` would work as well. It is just for us to remember that it is a shell script, but the shell uses a different way to determine what kind of script it is going to execute, in particular, to tell the shell that we want to execute a shell script we have to put the so-called **sha-bang** at the beginning of the file:

    #!/bin/bash

The `#` symbol indicates a comment normally, but when it is found in the first line of the file followed by an exclamation point "`!`", the shell understands that the executable following that sequence (in this case the bash shell itself!) must be invoked as an interpreter for the script.

Note that, in this way, a NEW SHELL is created to execute the script!

This is different from what happens when the command is "sourced" by the shell with the instruction:

    source ./myscript.sh

or

    . ./myscript.sh

in which the **sha-bang** is interpreted as a comment and the shell commands are executed INSIDE the current shell!

Finally, notice that, in order to execute the script as a command, we have to make it executable by changing the permissions (this will be explained later on during the course!):

    chmod u+x myscript.sh

or, more simply:

    chmod +x myscript.sh


## Local and global variables

When we define a variable inside the shell, for instance:

    $ MY_NAME="Leonardo Primavera"

and we call a script, for instance, `myscript.sh`, containing the following lines:

    #!/bin/bash
    echo $MY_NAME

prints nothing, because a new sub-shell is created, in which the variable `MY_NAME` is **NOT** defined!

In order the script to know the value of that variable, we can use the keyword:

`export`

that means that the variable created in the shell must be **exported** to the invoked shells, therefore its values are known to all of them!

Therefore, if we use the syntax:

    $ export MY_NAME="Leonardo Primavera"

and we invoke the script `myscript.sh` with:

    $ ./myscript.sh

this time the correct value will be printed, since `MY_NAME` was exported.

Note, however, that just sourcing the script with:

    $ source ./myscript.sh

or

    $ . ./myscript.sh

would have worked as well, even if the variable would not have been **exported** since the script would be invoked in the current shell, without creating a new one!

**Note**: to see **ALL** the **exported variables** defined in the shell, one can use the command:

    $ env

    > All the variables are equal but some are more equal than others

Note that there are some global variables that are especially important. Here is a list:

|Variable|Use|
|:---|:---|
|PATH| sequence of directories, separated by colons "`:`", where the executables are searched for |
|PS1| represents the prompt used in the shell |
|HOME| the main directory of the current user |
|USER| the login name of the current user |
|EDITOR| your preferred editor |
|BROWSER| your preferred browser |

and many others. A particularly important global variable is the:

    LD_LIBRARY_PATH

variable, that contains the **`PATH`** where compilers (in particular, the **linker**, called **`ld`** in Unix) search for the libraries. This variable is often changed when using different compilers which require different libraries or by the **system modules**, when available.

**Very important notice:**
When there is the possibility of confusion, but also to improve readability of a script, it is recommandable to enclose the name of a variable in **curly braces** "`{}'".

Example:

    $ touch mylatexfile.{tex,aux,log,pdf}
    $ FILE_NAME="mylatex"
    $ rm ${FILE_NAME}file.{aux,log,pdf}

**Note that this is mandatory when dealing with arrays!** (see below)


## `if` construct

A very important thing in both interactive workflows or when building up scripts is the possibility to evaluate expressions.

We can compare in the shell the logical status **True/False** of an expression with the operator:

   [[ expression ]]

**Note**: the blank spaces separating the expression from `[[` and `]]` are mandatory!

This can be used to build up complicated evaluation expressions when combined with the `if` construct:

    if [[ expr1 ]]
    then
       block_instructions_1
    elif [[ expr2 ]]
    then
       block_instructions_2
    ...
    else
       block_instructions_n
    fi

**Note**: the indentation is optional! In fact everything can be condensed in a single line by using the line separator `;`:

    if [[ expr1 ]]; then block_instructions_1; elif [[ expr2 ]]; then block_instructions_2; else block_instructions_n; fi

This second form is generally used on the command line. The first is preferred in scripts to increase readability!

For instance, a typical thing in scripts is to pass parameters on the command line when invoking the script, just like happens in C language with `argc` and the vector of strings `argv[]`, through the parameters:

- `$1` .. `$9` &nbsp;&nbsp;&nbsp;&nbsp; positional parameters from 1 to 9 (equivalent to `argv[]` in C)
- `$0` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; name of the script
- `$#` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; number of positional parameters passed to the script (equivalent to the variable `argc` in C)
- `$*` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; represents all the positional parameters passed to the script

Example script:

    #!/bin/bash
    if [[ $# == 0 ]]
    then
       echo "You didn't give any parameter!"
       echo "Try again!"
       exit
    else
       echo "You typed the parameters: $*"
    fi

**Note the keyword `exit` to quit the script!**

More examples:

    #!/bin/bash
    if [[ $# != 1 ]]
    then
       echo "Format of the command: $0 file_name"
       echo "Try again!"
       exit
    else
       echo "Creating file_name: $1"
       touch $1
    fi

Possible conditional checks are:

| Conditional statement | Meaning |
|:---|:---|
|`==`| equality |
|`!=`| inequality |
|`>`| greater then (alphanumerically!) |
|`<`| lesser than (alphanumerically!) |
|-eq| equal to (numerically!) | 
|-gt| greater then (numerically!) | 
|-lt| lesser then (numerically!) | 
|`&&`| logical AND |
|`||`| logical OR |

**Important note**:

The execution of a command should always return a value that is **`0` in case of success** or something different otherwise.

Also the `[[ expr ]]` evaluation operator has a return value of success (`0`) if the `expr` is `true` or something different if it is `false`. That means that it is possible to construct much more compact evaluations using simply the `[[ ]]` operator and the logical `&&` and `||`.

Example:

    $ name="Leonardo Primavera"
    $ if [[ $name == "Leonardo Primavera" ]]; then echo "Hello Leonardo!"; else echo "Hello Mr. X!"; fi

can be substituted by:

    $ name="Leonardo Primavera"
    $ [[ $name == "Leonardo Primavera" ]] && echo "Hello Leonardo!" || echo "Hello Mr. X!"

because if the first evaluation is true the first command is executed, otherwise the second command.

There are some special conditional operators that can be used to check if a file exists, if it is readable, if it is a directory, and so on!

This is an incomplete list:

| Flag | Meaning |
|:---|:---|
|`-a` or `-e`| true if file exists |
|`-f`| true if it exists and it is a regular file |
|`-d`| true if the file is a directory |
|`-s`| true if the file exists and has a non-zero size |
|`-x`| true if file is executable |

and many others. Please, check the man page of bash for further conditions!

Example:

    $ touch myfile.txt
    $ if [[ -f myfile.txt ]]; then echo "The file exists!"; fi
    $ [[ -x myfile.txt ]] && echo "The file is executable!" || echo "The file is NOT executable!"


## `while` statement

Other than the `if` command, also the `while` command can execute a loop while a given conditional operation is satisfied.

Format of the command:

    while [[ expr ]]
    do
       block_instructions
    done

For instance:

    a=0; while [[ $a -lt 10 ]]; do echo $a; (( a++ )); done

prints the number from 0 to 9.

**Note that, in this case, the variable `a` is a number!**

The shell accepts also **integer variables, not only strings**!

**the operators `-lt`, `-eq`, `-gt`, `-ne` compare numbers**, while `<`, `==`, `>`, `!=` **compare strings**!

Arithmetic expressions **must** be evaluated by enclosing them in the double parentheses: `(( ))`. We will see more examples later on...

## `case` statemement

It is possible to execute also a `case` statement, which allows cleaner writing for checking several conditions, especially in scripts.

Format of the command:

    case variable in
       val1)
          block_instructions1
	  ;;
       val2)
          block_instructions2
	  ;;
       ...
    esac

**Note**: if the block of instructions ends with the statement **`;;`**, all subsequent evaluations are ignored, otherwise if also some successive conditions are satisfied, both blocks of instructions are executed!

**Note**: it is possible to use `*)` to check for a default case.

Example:

    #!/bin/bash
    
    if [[ ! $1 ]]
    then
       echo "Format of the command: $0 parameter"
       exit
    fi
    
    case "$1" in
       "1")
          echo "You have selected the case 1"
          ;;
       "2")
          echo "You have selected the case 2"
          ;;
       *)
          echo "You have selected no case!"
          ;;
    esac

Note that, in the example, we could have not used the initial check of the presence of the parameter and used the `case` statement to deal also with that situation:

    #!/bin/bash
    
    case "$1" in
       "1")
          echo "You have selected the case 1"
          ;;
       "2")
          echo "You have selected the case 2"
          ;;
       *)
          echo "Format of the command: $0 parameter"
          ;;
    esac


## `for` statement

It is possible to execute loops with the `for` statement. There are two forms:

1. execute a `for` on a **list of values** (eventually contained in a variable!)
2. execute a **numeric loop**

The first form is:

    for var in list
    do
       block_instructions
    done

where the `block_instructions` can evaluate the different assignments of `var` in the list. The items in the list must be separated by blanks.

Example:

    $ for var in "myfile_1.txt" "myfile_2.txt" "myfile_3.txt"; do echo $var; done

The second form is:

    for ((int_var=istart; int_var<=iend; int_var++))
    do
        block_instructions
    done

Example: creates myfile.{tex,aux,log,pdf} and remove the .aux, .log, .pdf files

    $ touch myfile.{tex,aux,log,pdf}
    $ for ext in aux log pdf; do rm myfile.${ext}; done

Other example: bulk rename of 100 files

    $ touch myfile_{1..100}.dat
    $ for ((nn=1; nn<=100; nn++)); do mv myfile_${nn}.dat newfile_${nn}.dat; done

Note an equivalent of this example by using the first form and the **brace expansion**:

    $ touch myfile_{1..10}.dat
    $ for nn in {1..10}; do mv myfile_${nn}.dat newfile_${nn}.dat; done

Another very useful external linux command that can be used in loops is `seq`:

    $ seq start inc stop

where `start`, `inc` and `stop` are the starting values (**Note that also floating point numbers are possible!**).

For instance:

    $ seq 0.0 0.2 1.0

gives the list of numbers from 0.0 to 1.0 in steps of 0.2.

Also, a sequence can be reversed:

    $ seq 10 -1 1

prints the numbers from 10 to 1 in inverse order.


## Put the results of a command into variables

It is possible to put the result of the execution of a command into a variable, to use in conditional expressions or loops:

    var_name=$(command)

The old form of the expression is still possible, `` `command` ``, but it is deprecated, nowadays!

This is very useful when one wants to execute, for instance, a for loop on a sequence of files that fulfill some special characteristics.

For instance:

    $ touch myfile_{00..50}.txt
    $ my_files=$(ls myfile_?5.txt)
    $ echo $my_files

The variable `my_files` now contains: `myfile_05.txt`, `myfile_15.txt`, `myfile_25.txt`, `myfile_35.txt`, `myfile_45.txt`.

**Note**: the `?` character matches **any single letter** between `myfile_` and `5.txt`. We will see more examples of wildcard characters when introducing the **Regular Expressions** (RegExpr) in next lectures!

A subsequent command like:

    $ for fn in $my_files; do rm $fn; done

will remove all those files. Note as the simple command:

    $ rm $my_files

would have been equivalent!


## Aliases

It is possible to define an **`alias`** of a command, namely a simplified version of a more complicated command.

For instance, the instruction:

    $ alias lst='ls -ltr --color=auto'

defines the command `lst` as a shortcut of the (more complicated!) command: `ls -tr --color=auto` (which prints a colored version of the list of files, in long format, in inverse order of time creation).

It is possible to **`unalias`** a command, to remove the created alias, like:

    $ unalias lst

Note as **it is possible to define an alias with the same name as a command**, like in:

    $ alias rm='rm -i'

which asks for confirmation before removing a file!

Note that if one does not want to use the **aliased** version of the command, but the **original** one, this can be obtained by simply putting a backslash "`\`" in front of the command. For instance:

    $ \rm file_name

would execute the **standard** `/bin/rm` command, instead of the **aliased** name `rm`. Of course also using directly:

    $ /bin/rm file_name

would yield the same result!


## Functions

One can define functions by enclosing a block of instructions into braces:

    function_name()
    {
       block_instructions
    }

Functions are called simply with the name of the function (`help` in this case! No `()`!).

Notice that a function can be defined also on the command line, like:

    $ help() { echo "List of commands:"; for str in "command1" "command2" "command3"; do echo $str; done }

Invoking:

    $ help

will then print:

    List of commands:
    command1
    command2
    command3


## Arrays

It is possible to define both **numerical** and **associative** arrays.

The former are indexed through a numerical value (like lists, in python):

    declare -I array_name_num_ind

while the latter, through a string index (like dictionaries, in python):

    declare -A array_name_assoc

and then initialize the arrays as:

    array_name_num_ind=(val1 val2 ...)

for the numerical indexed arrays, or:

    array_name_assoc=([key1]=val1 [key2]=val2 ...)
    array_name_assoc=(key1 val1 key2 val2 ...)

for the associative arrays.

It is possible to expand the initialization on different lines by using the `\`.

Arrays with numeric indices start from `0` (like in C)!

Note that numerical indexed arrays **do not need to be declared** with `declare -I`, they can be directly **initialized**!

Instead, **associative arrays MUST always be declared as such**!

**When the value of the array is to be printed, the name and index must be enclosed in curly braces!**

Example:

    $ ARR=( 25 28 31 )
    $ ASS=( [january]=31 \
            [february]=28 \
            [march]=31 )

    $ echo ${ARR[2]}
    $ echo ${ASS[february]}

Note that, in order to print the whole content of the array, one can use the subscripts `*` or `@`, which indicate all the elements of the array.

Note, however, that all the values of the elements are printed, but the order is not that one could expect, since an associative array, at difference with a numerical indexed array, has no pre-defined order!

The same command, for a numerical indexed array produces the values in the correct order, instead. For instance:

    $ days_of_months=(31 28 31 30 31)
    $ echo ${days_of_months[*]}

prints: `31 28 31 30 31`.


## Redirection and Pipelines

The **UNIX philosophy** can be summarized as:

*Each command should do one single, simple, thing and do it in the best possible way.

More complicated things have to be done by making the single commands communicate through a file!*

Everything in UNIX (and, therefore, in Linux!) **is a file!**

Even the terminal itself, the memory or the devices connected to the computer are seen as files (in the `/dev` directory). The current status of the devices is stored in files (in the `/sys` directory), and so on...

Like in **C language**, there are essentially 3 main default **streams** with which a program communicates with the underlying operating system or other programs:

- `stdin` &nbsp;&nbsp;&nbsp;&nbsp; input stream
- `stdout` &nbsp;&nbsp;&nbsp;&nbsp; output stream
- `stderr` &nbsp;&nbsp;&nbsp;&nbsp; error stream

This means that when a Bash (or any other process) command outputs something, like with the `echo` or `printf` commands, this is sent to the `stdout` stream, when receives some input, this is sent though the `stdin` stream, and finally, when a command produces some error, this is sent to the `stderr` stream.

We have seen briefly already how to redirect the `stdout` stream to a file, through the redirection mechanism (`>` to send the output, and `>>` to append the output to a file).

A similar thing can be done to take the input of a command from a file, through the redirection `<` or `<<`.

For instance, we can feed the value of a variable with a content of a file as:

    $ read MY_VAR < file
    $ echo $MY_VAR

will output the content of the file.

The "`<< NAME`" redirection works by reading from the stdin a sequence of strings, till a string equal to NAME is found!

Example: the command `wc` reads as input a file with multiple lines and prints the number of words (flag `-w`), the number of lines (flag `-l`) or the number of characters (flag `-c`)

    $ wc -l << EOF
    > Hi, this is a test!
    > Here is another line!
    > EOF

prints 2, the number of lines, or:

    $ wc -w << EOF
    > Hi, this is a test!
    > Here is another line!
    > EOF

prints 9, the number of words, etc.

Finally, also the error stream can be redirected through the symbol `>&` which redirects to a file both the stdout and the stderr.

Finally, it is worth mentioning a special file: `/dev/null`, which represents some kind of **rubbish bin**: whatever is sent to that file, it is lost forever. So, if one wants to drop outputs and errors from any command, he/she can redirect those streams to that file.

The redirection is very helpful, however the true power of Unix/Linux consists in the possibility to use the **Pipelines**.

With this, abbreviated with **pipe**, we mean the possibility to redirect the stdout of a command as the stdin of another command, so creating a true pipeline of commands that operate on the input of a command and pass it to subsequent commands until some different result is obtained. When the shell encounters the symbol `|` (pipe) on a line, it redirects the `stdout` of the command on the left to the `stdin` of the command on the right and the sequence may continue indefinitely! 

For example: the command

    $ echo "Hi, this is a very long string..." | wc -c

prints 34, the number of characters of the string. The meaning is that the `stdout` of the echo command is redirected as the `stdin` of the command `wc -c`, which gives the number of character read from the input.

In this way, it is possible to build up very complicated commands to do interesting things.

The external command `fzf` (which stands for **fuzzy-finder**) reads an input and allows to make a selection or a search inside a directory or a file. It can also accept an input from another command:

    $ touch myfile_{00..10}.txt        # Produces 10 files myfile_00.txt ... myfile_10.txt
    $ ls myfile_*.txt | fzf | xargs rm

The result is the selection that was made among the files and the command `xargs rm` will remove the file (the external command `xargs` allows to take a sequence of input strings and executes the specified command on each of the lines)...

Both `fzf` and `xargs` are very powerful commands and we will see more on their capabilities in next lectures. Finally, we will see many more examples of **Pipelines** too, which is one of the most powerful command of the Unix/Linux operating system.
