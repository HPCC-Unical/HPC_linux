# Regular Expressions and file searching

## What is a regular expression (regexp)

Sometimes one needs to search for a particular combination of several characters inside a file or in a directory tree.

Regexp may help in this by searching for sofisticated combinations or sequences of characters.

First of all, let us introduce a command, **`grep`** which allows to search for a regular expression in a file.

To make examples about the command grep, we need a file containing some words. You can download the file by clicking **here**: <https://github.com/HPCC-Unical/HPC_linux/tree/main/grep_file.txt>.

**Please, put the file in your current working directory.**

Before starting using `grep`, we may define an alias to make `grep` always show the matching results in colors.

We can define:

    $ alias grep='grep --color=always'

For instance, we may use the following command:

    $ grep "command" grep_file.txt

that will return all the lines in the file containing the word "command". Note that, for single word, the double quotes can be omitted!

If we want to search for the plural form, we can use of course:

    $ grep "commands" grep_file.txt

Notice how the result now contains less lines, since the lines containing the "command" word are missing.

Summarizing, any word in itself is a regular expression, so searching for a word will return the lines containing that word.

Now, let us suppose we want to find all words containing a "w":

    $ grep "w" grep_file.txt

will give the correct result.

However, what if we want to search for a character "o", followed by any character, then by another "o"?

We can use the following expression:

    $ grep "o.o" grep_file.txt

**The symbol "." matches any single character.**

If we want to match a string containing more characters in between the two "o", we can use the syntax:

    $ grep "o.*o" grep_file.txt

**The "`*`" means: take the previous character and repeat it any number of times, including zero times**!

Therefore, in this case, we will have a lot of sentences which present two "o" in them!

And, notice how also the word "woosh" is present in the list, because the "`*`" matches the `.` character any number of times, including **zero** times.

Note how the expression:

    $ grep "o*" grep_file.txt

will return all lines containing an "o", independently if it appears zero or more times...

If one wants the lines that match a character more times, but at least once, the **`+`** character can be used:

    $ grep "o.\+o" grep_file.txt

In this case, the "woosh" word has been removed from the list, since the request is to contain at least one character between the 2 "o".

Therefore, the **`+` means: take the previous character and repeat it any number of times, greater than zero!**

Note that, since the `+` sign is a special character for the shell, it **has to be escaped** in order for the command to work.
Not putting the `\` in front of the `+` would not produce an error but simply nothing is printed on the screen...

Now, let us suppose that we want all lines in the file ending with the "`y`" character.

**The character `$` matches any occurrence of the preceding character *at the end of the line*!**

    $ grep "y$" grep_file.txt

If we want to print all the lines beginning with the "`y`" character, we can use:

    $ grep "^y" grep_file.txt

**The "`^`" character (caret) matches the following character at the beginning of the line!**

In a previous example:

    $ grep "o.*o" grep_file.txt

we have seen as entire words between two "o", even belonging to different words, match the regexp.

What if I want to avoid this and include only lines where any character in between the two "o" is included, except whitespaces (namely, to include only lines in which the two "o" are in the same word!)?

**The "`\S`" character matches any non-whitespace character!**

Therefore, the command:

    $ grep "o\S*o" grep_file.txt

will return only the lines containing words having two "o" inside...

It exist a regexp to do the opposite, namely matching the whitespaces, tabs, and so on:

**The "`\s`" character matches whitespaces, tabs, etc.**

Example:

    $ grep "w\S\+\s" grep_file.txt

matches all lines containing a word starting with "w" but ending with a whitespace, therefore practically any word beginning with "w" in a sentence, not isolated!

Sometimes, one does not know whether a character will be present in a string or not, namely it is an "optional" character.

**The "`\?`" character indicates that the preceding character is optional**

Example:

    $ grep "https" grep_file.txt

will match all lines containing the string "https". But if we want to match all URLs, even those containing "http" only, without the "s", we can use:

    $ grep "https\?" grep_file.txt

that will include also lines containing "http" only!

If we want to get all the lines containing an URL, we could add to the previous instruction:

    $ grep "https\?://" grep_file.txt

but this would match also the comment concerning google in the file.

We can match exactly the URLs by adding any not whitespace character after that:

    $ grep "https\?://\S\+" grep_file.txt

However, one can see clearly that also the malformed URL: `http://mysite` would be matched!

What if we want to match correct URLs only, namely the URLs containing at least the site and the domain name?

We could want to have any number of non whitespace characters, followed by a dot, then followed by at least a sequence of characters from "a" to "z":

    $ grep "https\?://\S\+\.[a-z]\+" grep_file.txt

This is still not perfect, since, for instance, the last line contains a "`/`" at the end of the URL. Finally, this can be matched by a regexp like:

    $ grep "https\?://\S\+\.[a-z]\+/\?" grep_file.txt

which matches also the eventual optional "`/`" at the end of the URL!

**Several notes:**
- in order to match for the "`.`", since it has a special meaning for the regexp, it **must be escaped** with the `\`...
- the sequence `[a-z]` matches any character in the interval from "a" to "z";
- for capital letters you can use: `[A-Z]`
- for both lowercase and uppercase letters: `[a-zA-Z]` or, equivalently: `[a-Z]`

Finally, to match an email, one could use the following regexp:

    $ grep "\S\+@\S\+\.[a-zA-Z]\+" grep_file.txt

It is possible to specify a list of characters that **MUST** be matched by enclosing them into square brackets `[]`.

For instance:

    $ grep "^[LT].*" grep_file.txt

matches any line beginning with "L" or "T". Note that one can specify also an interval of values different from `[a-z]` or `[A-Z]`

In the same way, it is possible to match digits as the sequence of characters: `[0-9]`.

For instance:

    $ grep "[0-9]\+" grep_file.txt

that matches a sequence of at least one digit, while:

    $ grep "[0-9]*\.[0-9]\+" grep_file.txt

matches only the floating point numbers, including those beginning with "."

**It is possible to specify the number of times a character or whitespace appears.**

This can be done with the sequences:
- \{n\} &nbsp;&nbsp;&nbsp;&nbsp; The preceding item is matched exactly n times.
- \{n,\} &nbsp;&nbsp;&nbsp;&nbsp; The preceding item is matched n or more times.
- \{,m\} &nbsp;&nbsp;&nbsp;&nbsp; The preceding item is matched at most m times.  This is a GNU extension.
- \{n,m\} &nbsp;&nbsp;&nbsp;&nbsp; The preceding item is matched at least n times, but not more than m times.

Example: print the lines containing the numbers made of at least 4 digits

    $ grep "[0-9]\{4\}" grep_file.txt


## The `grep` command

The **`grep`** command, other than accepting regexp, accepts **many flags** that modify its behavior.

The following are some of the most important ones:
- `-w` &nbsp;&nbsp;&nbsp;&nbsp; matches exact words (it can be simulated with regexp)
- `-i` &nbsp;&nbsp;&nbsp;&nbsp; makes the search case-insensitive
- `-v` &nbsp;&nbsp;&nbsp;&nbsp; matches the lines that **DO NOT** fulfill the regexp
- `--color=...` &nbsp;&nbsp;&nbsp;&nbsp; colorizes the matching words
- `-m NUM` &nbsp;&nbsp;&nbsp;&nbsp; stops reading the files after `m` successful matches
- `-R` &nbsp;&nbsp;&nbsp;&nbsp; reads recursively in subdirectories
- `-A NUM` &nbsp;&nbsp;&nbsp;&nbsp; prints the `NUM` lines following each matching
- `-B NUM` &nbsp;&nbsp;&nbsp;&nbsp; prints the `NUM` lines preceding each matching
- `-C NUM` &nbsp;&nbsp;&nbsp;&nbsp; prints the `NUM` lines both before and after each matching
- `-n` &nbsp;&nbsp;&nbsp;&nbsp; prints the line number corresponding to each matching
- `-c` &nbsp;&nbsp;&nbsp;&nbsp; prints the number of occurrencies of the matching

The `grep` command can not only search into files, but thanks to the pipelining, it can search files in directories, and so on...

For instance:

    $ touch myfile_{1..10}.txt
    $ touch newfile_{1..10}.dat
    $ ls | grep "\S\+_[1-5]\."

prints all file names starting with any string, an underscore and one digit between 1 and 5, followed by a dot...

Of course the result can be put into a variable and used, for instance, to remove those files or perform other file operations...

    $ my_list=$(ls | grep --color=never "\S\+_[1-5]\.") && rm $my_list

Note the option `--color=never` to remove the color escape sequences from the file names!

## The `find` command

The `find` command helps you find files by name.

The usual way in which one uses it is:

    $ find dir_name -name "file_name"

Example: recursively descent the `/etc` dir  to find all files containing the word `console` in their names

    $ find /etc -name "*console-setup*"

**The flag `-iname` finds the file matches in a case-insensitive form!**

To find only files of a specific type, for instance a **directory**, one can use the flag `-type`

For instance:

    $ find /etc -type d

shows all subdirectories in the directory /etc

To find all **regular files** in a directory, one can search for `-type f`

Example:

    $ find . -type f

basically will give all files which are not directories or special files.

Analogously, `find dir -type l` searches for symbolic links, etc.

It is interesting how `find` can search for files not only based on the name or type, but also on other kind of conditions:

### access times

| Flag | Meaning |
|:---|:---|
| `-amin N` | File was last accessed less than, more than or exactly n minutes ago |
| `-anewer file` | File that are newer than `file` |
| `-atime N` | File was last accessed N days ago |
| `-cmin N` | File's status was last changed less than, more than or exactly n minutes ago |
| `-cnewer file` | File's status that have been changed more recently than `file` |
| `-ctime N` | File's status was last changed less than, more than or exactly N days ago |
| `-empty` | Matches empty files |
| `-executable` | Matches executable files or accessible directories |
| `-mmin N` | File's content was modified less than, more than or exactly N minutes ago |
| `-mtime N` | File's content was modified less than, more than or exactly N days ago |
| `-newer file` | File's content is newer than that of `file` |
| `-perm mode` | File's permissions are given by `mode` |
| `-size N[ckMG]` | File's size is less, more or exactly N bytes (c), kB (k), MB (M), GB (G) |
| `-user name` | File belongs to the specified user |
| `-group name` | File belongs to the specified group |

To specify a quantity greater, equal or lesser than `N`, you can use:
- `+N` &nbsp;&nbsp;&nbsp;&nbsp; greater then `N`
- `-N` &nbsp;&nbsp;&nbsp;&nbsp; lesser than `N`
- `N` &nbsp;&nbsp;&nbsp;&nbsp; exactly `N`

Examples:

    $ find /home -user student    # finds the files belonging to "student" in the /home dir
    $ find ~ -mmin -3600          # finds files modified within the last hour
    $ find ~ -perm u=rwx          # finds files and directories with permissions rwx for the user
    $ find ~ -size -100c          # finds files with dimension lesser than 100 bytes

**A very powerful feature of `find` is the hability to execute a command on each file matching the pattern.**

This is realized through the commands:

    $ find dir -exec command {} +

or:

    $ find dir -exec command {} \;

The first form produces a list of files matching the pattern and then it executes `command` on the whole list.

The second form executes `command` on each file, one by one.

For instance:

    $ find ~ -name "m*" -size +1M -exec echo {} +

prints the name of the files (all on one line) whose name begins with "m" and size is greater than 1 MB.

A particularly useful case is that you can execute, for instance, a `rm` command on a lot of files one by one, in the case in which the simple command `rm *` does not work because the files to remove are too many! In this case, `find` can solve the problem with:

    $ find . -name "myfiletodelete*" -exec rm {} \;

Many other **actions** are available, other than `-exec`:

- `-delete` &nbsp;&nbsp;&nbsp;&nbsp; delete the files matching the pattern
- `-ok` &nbsp;&nbsp;&nbsp;&nbsp; like `-exec`, but ask to confirm the operation
- `-printf format` &nbsp;&nbsp;&nbsp;&nbsp; prints the file name in a specific format

Note that also specific information about the file can be included, like **size**, **access time**, and so on...

Example:

    $ find ~ -size +100M -printf "%p\t%s\n"

prints the file names (`%p`)and the size (`%s`), with a `TAB` in the middle, for files larger than 100 MB.

See the man page for the meaning of the many possible flags.


# The `fzf` command

The **`fzf`** command stands for **fuzzy finder**!

We have seen a use of this command as a way to select an item for a list of possibilities. However, its main scope is to **find files** quickly in the current directory.

Example:

    $ fzf

builds up and show you a list of all the files present in the current directory. You may select one of them with the cursors, or just press `ESC` to abort the choice. On output, the selected file name is printed.

**However, `fzf` does much more than this!** For instance, instead of directly selecting a file, you can start a **fuzzy search** by typing some letters and it will show you all the files whose name matches that letters not necessarily contiguous.

If you want an **exact** matching, put a **`'`** character at the beginning of the search! This can be enabled since the beginning with: `fzf --exact` or `fzf -e`.

A particularly useful option is **`-m`** or **`--multi`**, which allows to select multiple options by using the `TAB` key. All the selected files are printed as the result of the search.

Another very useful option is the **`--preview=COMMAND`** which allows you to interactively preview the content of a file with a specified `COMMAND`.

For example:

    $ fzf --preview='head -n 10 {}'

shows the first 10 lines of a file through the command `head` (we will see that in next lectures)...

Of course even more sofisticated previews are possible, like:

    $ ls *.pdf | fzf --preview='zathura {}'

`zathura` is a powerful pdf-viewer. Of course, you need a graphical environment to use it! Alternatively, you can use `pdftotext` to see the text version of the pdf file.

**Note:**

**`fzf`** is **NOT** often preinstalled on linux distributions, but it is in the repositories of the majority of them. However, it may not be installed on remote clusters, but it is downloadable from: <https://github.com/junegunn/fzf/releases>
