# Text file manipulation commands (cut, tr, head, tail, sort, paste, sed, awk)

All of the following commands (and several others that are, in my
personal opinion, less useful!) manipulate the content of text files.

These are often useful to extract part of the files (rows, columns,
etc.), show different files one aside the other, and definitely change
their content. I put them in a "logical" order (according to my
personal criteria) of powerfulness, in the sense that `awk` is the
most powerful command in absolute, and therefore it should be
preferentially learnt, though it is also the slowest one, being the
most powerful. Thus, sometimes also less powerful commands can be
simpler and useful, and therefore worth learning!

## The `cut` command

The `cut` command literally extracts characters or columns (by
specifying a separator) from a file.

Its simplest form is:

    cut -c num1-num2 file

that simply prints the characters in the range num1-num2 in the file.

Example:

    cut -c 3-10 ~/.bashrc

prints the characters from 3 to 10 in the file ".bashrc".

**Note**: one of the ranges can be omitted, like, for instance, in:
  `cut -c -10 ~/.bashrc`, that prints the first 10 characters of each
  line, or: `cut -c 5- ~/.bashrc`, that prints each line from the
  character number 5 up to the end of the line.

However, the most powerful use of `cut` is the fact that it can be
used to extract **fields** from a file organized in columns. The
format of the command, in this case, is:

    cut -f num -d char file

where `num` is the field number (starting from 1) and `char` is a
single character separating the columns in the `file`.

For instance, with reference to the file `grep_file.txt` that we used
in a previous lecture, the command:

    cut -f 1 -d ' ' grep_file.txt

prints **only** the first column in the file (field 1), interpreting
the whitespace as a field separator.

In the same way, we can print all the users present in the system, with:

    cut -f 1 -d ':' /etc/passwd

because that file is organized in various fields separated by a
colon "`:`".

In the same way, for instance the second column of a **csv** (comma
separated values) file can be printed with the command:

    cut -f 2 -d ',' mycsvfile.csv

An important **note**:

the `cut` command accepts **only one single character** for the
separator `-d`. This may yield wrong or unexpected results if the
separator consists of multiple characters. For instance, the command:

    echo "This is a text line" | cut -f 2 -d ' '

works as expected, namely it produces the string: `is`.

However, a command like:

    echo "This   is   a   text   line" | cut -f 2 -d ' '

in which the words are separated with multiple whitespaces, produces a
whitespace, since the first whitespace between `This` and `is` is
followed by another space, that is then interpreted as the second
field!

We will see how the command `awk`, which is **much more powerful**,
allows to bypass this difficulty.


## The `tr` command

The `tr` command stand for **translate**. The command operates on
**single characters** and converts them to another character. It
**does not** operate on strings!

The typical format of `tr` is:

    tr char1 char2

that changes all characters `char1` into `char2`.

**Note**: `tr` does not work on files, but on pipelines, that is, if
  you want to translate all characters in a file you should `cat` it
  and pipe the content into `tr`!

For instance, a command like:

    cat grep_file.txt | tr 'a' 'A'

changes all lowercase `a` in the file grep_file.txt to uppercase `A`.

It is possible also to specify more than one character to translate,
for instance it is possible to use a sequence of characters. However,
of course, the second sequence must contain the same number of
corresponding characters as the first!

Example:

    cat grep_file.txt | tr 'aeiou' 'AEIOU'

will capitalize all wovels in the file.

It is possible, other than **changing** characters, also to **delete**
characters, with the flag `-d`. For instance:

    cat grep_file.txt | tr -d 'aeiou'

will delete all wovels from the file. Note that it does not actually
**delete** the characters, but it changes into spaces! To finally
remove the spaces you can include a space inside the sequence of
characters, like:

    cat grep_file.txt | tr -d 'aeiou '

The flag `-cd` **complements** the `-d` flag, in the sense that it
removes everything (including whitespaces and carriage-returns) except
the specified sequence of characters!

Moreover, the flag `-s` **squeezes** repeated character from a
text. For example:

    echo "I haaveee   a veeeeery straaange liiiiine heeree..." | tr -s 'aeiou '

produces: `I have a very strange line here...`

A quite interesting aspect of `tr` is that it can translate, delete,
etc., not only ordinary characters, but also **escape sequences**,
like `\a`, `\t` (for tabs), `\n` (for newlines), etc.

But it also accepts special characters, like the following, enclosed
in `[::]`:

| Sequence | Meaning |
| :--- | :--- |
| [:alnum:] | all letters and digits |
| [:alpha:] | all letters |
| [:blank:] | all whitespaces |
| [:digits:] | all digits |
| [:graph:] | all printable characters, excluding spaces |
| [:print:] | all printable characters, including spaces |
| [:lower:] | all lowercase letters |
| [:upper:] | all uppercase letters |

and some others (see the man page for a complete list!).

For example, to translate all whitespaces in underscores:

    echo "linux does not like filenames with spaces" | tr '[:blank:]' '_'

or to translate all lowercase letters in uppercase:

    echo "This is another sentence, with most lowercase characters..." | tr '[:lower:]' '[:upper:]'

produces: `THIS IS ANOTHER SENTENCE, WITH MOST LOWERCASE CHARACTERS...`


## The `head` command

The `head` command is very simple, it just prints a given number of
lines or characters from the specified file:

    head -n num file

prints `num` lines from `file`.

**Note:** `n` can be a **negative number**, in that case all the
  lines, except the first `num` lines, are printed!

With the flag `-c`, it prints the first `num` character in the
file. Also in this case, a negative value prints everything except the
last `num` characters.

This is a useful example in which we use `head`, `tr` and `cut` to
generate a random sequence of 25 characters, that can be used, for
instance, as a password:

     head -c 100 /dev/random | tr -cd '[:graph:]' | cut -c -25

In this case, `head -c 100 /dev/random` extracts 100 random bytes from
the file /dev/random (which is the random number generator of the
CPU), passes this sequence to `tr -cd '[:graph:]'` that prints all
non-printable characters from the result (remember that the flag `-cd`
negates the deletion of the graphical characters!) and, finally, `cut
-c -25` cuts the first 25 character of the remaining string.


## The `tail` command

The `tail` command, as it is easy to understand, does the opposite of
what `head` does, namely:

    tail -n num file

prints the last `num` lines in `file`, or:

    tail -c num file

prints the last `num` character in `file`. It is also possible to use
a **positive** number `+num` with the flags `-c` and `-n` to output
the file since its `num` character or line!

A very useful flag of `tail` is the `-f` flag, that continues
displaying the tail of the file until `CTRL+C` is pressed. This is
particularly useful, for instance, to examine the last part of a file
that changes in time, for instance a log file of some command!


## The `sort` command

The `sort` command just sorts lines of text in a file. A typical use
is:

    sort file

which sorts alphabetically the lines of `file`.

The flag `-r` just **reverses** the order of the sorting.

Example:

    sort ~/.bashrc

sorts all lines of the file .bashrc.

It is also possible to sort numerically with the flag: `-n`.

For instance:

    cat grep_file.txt | tail -n 12
    cat grep_file.txt | tail -n 12 | sort -n

the first command extracts the last 12 lines from the file
`grep_file.txt`, which contain only numbers, the second sorts them
numerically.

There are several flags that modify the sorting behavior:

- `-f` &nbsp;&nbsp;&nbsp;&nbsp; ignore case
- `-i` &nbsp;&nbsp;&nbsp;&nbsp; ignore non-printable characters
- `-u` &nbsp;&nbsp;&nbsp;&nbsp; each sorted line is printed just **once**!
- `-o` &nbsp;&nbsp;&nbsp;&nbsp; output the sorted lines in the file specified after the flag

It is possible to indicate to sort a `field separator` and then to
indicate a column to sort the lines. For instance:

    sort -t : -k 3n /etc/passwd

sorts the file /etc/passwd (in which the columns are separated by
semicolons) through the third column, namely the number associated to
the user.


## The `paste` command

The `paste` command joins (vertically or horizontally) two or more files.

This can be useful when one wants to compare the content of different
files line-by-line:

    paste file1 file2 ...

Example:

    seq 1 21 > test1.dat
    seq 0.0 0.25 5.0 > test2.dat
    paste test1.dat test2.dat > test.dat

creates two files containing one column with the numbers from 1 to 21
(`test1.dat`), another column with the numbers from 0.0 to 5.0 in
steps of 0.25 (`test2.dat`), then the `paste` command merges the two
files into `test.dat`, that will now contain two columns.

With the flag `-s`, the `paste` command creates two or more lines
superposed, instead of parallel columns!


## The `sed` command

`sed` is a shortcut for **stream editor**.

The `sed` command can search and transform text, namely search for
text sequence, that may be a **regular expression**, and execute
operations on that sequence.

The most used and very basic usage of `sed` is to replace text!

This can be done by using the `s` command (which stands for **substitution**):

    sed 's/string1/string2/' file

that substitutes in the file `string1` with `string2`. Note that
actually `sed` does not change anything in the file, unless the option
`-i` (we will see in detail later on) is used. The command simply
prints to the screen the result of the substitution.

**Note**: only **the first occurrence** of string1 for each line is
  replaced!

If you want to save the result of the operation, you can simply
redirect the result to a file, like in:

    sed 's/r/R/' /etc/passwd > my_passwd

that changes all first occurrencies of lowercase `r` into an uppercase
`R`.

In order to change **all occurrencies** of a string to another one,
the `g` flag (for **global**) can be used at the end of the
substitution, as in:

    sed 's/string1/string2/g' file

Of course, `sed` can be used also in a pipeline to make changes to a
string:

    echo "My name is Bond, James Bond..." | sed 's/Bond/Tont/g'

which prints:

    My name is Tont, James Tont...

The `-i` flag (that stands for **inline**!) performes the operations
directly in the file passed on the command line, so that one does not
need to redirect the result to a new file.

Example:

    echo "Dear all, I believe that the sed command is very useful!" > my_file.txt
    sed -i 's/a/A/g' my_file.txt

will make all substitutions directly in the file.

The power of `sed` is in its hability to manage **regular
expressions** and operate only on the lines that match that
**regexp**. All other lines are simply printed to the screen.

Example:

    sed '/^r/ s/r/R/' /etc/passwd

prints the whole file with the lines starting with `r` capitalized.

It is possible not only to **substitute** lines, but also to
**delete** lines containing a pattern, therefore keeping only the
lines that do not contain it. This is possible with the option `d`:

    sed '/^r/ d' /etc/passwd

will print all lines, except those starting with `r`!

It is possible to match more than one single string, by specifying the
`-e` option multiple times.

For instance, the file `/etc/shells` contains all the shells installed
on the system. Then the sequence:

    sed -e 's/bin//' -e 's/usr//' /etc/shells

substitutes **both** strings `bin` and `usr` with nothing!

The character `/` that separates the strings is not strictly
necessary, in the sense that any other character can be used. This is
useful, for instance, when you want to substitute a string containing
a `/` character.

Example:

    sed -e 's%/bin%%' -e 's%/usr%%' /etc/shells

keeps only the names of the shells and removes the directories.

However, keep in mind that using any character instead of `/` is
possible **for substitutions only**, **NOT** for searching patterns
(or regexp!). In any case, it is possible to escape the `/` character
with a `\`, to use the `/` as a normal character.

For instance, if we want to substitute the string `/bin/` with nothing
and remove all strings starting with `/usr`, we can use:

    sed -e 's%^/bin/%%' -e '/^\/usr/ d' /etc/shells

It is possible to avoid putting too many `-e` flags and give all
commands in just one line separated by a semicolon (`;`) or a newline.

Example:

    sed 's%^/bin/%%; /^\/usr/ d' /etc/shells

Other than substituting and deleting strings, it is possible also to
**print** the strings that match a string or a regexp, with the `p`
flag at the end:

    sed '/string/ p' file

However, this will print not only the lines containing the string (or
regexp) `string` in `file`! This happens because by default `sed`
prints anyway the line. This can be avoided with the option `-n`,
which suppresses the printing of the line that do not match the
specified pattern:

    sed -n '/string/ p' file

This will print **only** the lines matching the string (or regexp)
`string`. In this sense, **`sed` can be used as a replacement for
`grep`**, that we have already examined last time!

Example:

    sed -n '/^\/usr/ p' /etc/shells

will print **only** the lines starting with `/usr` in the files
`/etc/shells`.

Some more complicated examples:

    echo -e 'This is a long string\n\n\ncontaining some empty lines\n\n...' | sed '/^$/ d'

suppresses the empty lines in the file.

    echo -e 'This is a long string    \nwith some final extra spaces...   \n\n' | sed 's/ *$//' > temp.txt
    vim temp.txt

this removes all extra spaces at the end of the lines. If one edits
`temp.txt` it is easy to verify that the final spaces have been
removed.

Another cool thing of `sed` is that it can operate on special kind of
characters, just like we have seen for `tr`. The difference is that in
`sed` the special character are embedded into **two** `[[::]]` and not
**single** `[::]` as for `tr`!

Example:

    sed 's/[[:digit:]]//g' grep_file.txt
    sed 's/[[:alpha:]]//g' grep_file.txt
    sed 's/[[:space:]]//g' grep_file.txt

substitutes any digit, alphanumeric character or spaces/tabs in the
file with nothing!

In the same way, `[[:lower:]]` and `[[:upper:]]' identify lowercase
and uppercase characters!

However, notice that all these work only in the **searching pattern**,
and **NOT in the replacement pattern**!!!

For instance, if I want to substitute all lowercase characters in
uppercase, the following command:

    sed 's/[[:lower:]]/[[:upper:]]/g' grep_file.txt

**does not work**, in the sense that it substitutes any lowercase
character with the string "`[[:upper:]]`"!

The correct form of the substitution is:

    sed 's/[[:lower:]]/\U&/g' grep_file.txt

which does the correct thing, namely it changes the letters from
lowercase to uppercase.

Analogously, to change the letters from uppercase to lowercase, the
correct form is:

    sed 's/[[:upper:]]/\L&/g' grep_file.txt

Another useful command of `sed` is the `l` command, which prints all
characters in the file in an **unambiguous** way, that is any
non-printable character is printed in its octal code, newlines are
printed as `$`, and so on...

Example:

    head -c 20 /dev/random > temp.dat
    sed 'l' temp.dat

will print the characters that cannot be printed in their octal form.

This is handy if you suspect your file contains some special or
non-printable character that are not directly visualized by `cat` or
`less`!

There are many other commands in `sed` to insert strings among lines
(`i`), append text to each line (`a`), print the lines satisfying a
certain expression (`p`), etc. One of the most used one is to **quit**
(`<num>q`) the file stream after a certain number of lines, for
instance:

    sed '11q' grep_file.txt

prints the first 10 lines of the file and exits. So, in this case
`sed` works as a replacement for `head`.

However, one can also quit the file when one line matches a given
pattern, like in:

    sed '/[[:digit:]]/ q' grep_file.txt

stops printing when a line has a digit, or:

    sed -n '/[[:digit:]]/ p' grep_file.txt

prints only the lines containing a digit (note the suppression of the
printing of the pattern space with the `-n` flag!).

Another interesting example to get rid of comments and empty lines in
a file:

    sed 's/#.*//g; /^$/ d' file

removes all characters to the right of the `#` symbol (comments) and
all blank lines in the file;

Finally, it is possible to group all commands in scripts and execute
them with the `-f script` command!


# The `awk` command

The `awk` command is a stream editor that searches for patterns,
replaces them, and make complicated manipulations. Just like `sed`,
but in a much more powerful way! It is **a true programming
language**, able to manage variables, arrays, functions, and much
more...

As such, however, it is considerably slower than other alternatives we
have seen until now. This is generally not a big problem, but working
with `awk` on large files may become not so easy!

Generally, `awk` is able to do much better and much more than the
other commands we have seen until now, but sometimes in a more
convoluted way. This makes all previous commands worth using for
simpler things, even if `awk` can do the same things, generally in a
better way.

In its basic usage, `awk` can read a file and separate it into columns
and print some of the columns. This is equivalent to what `cut -f`
does, but awk does it in a better way.

The format of `awk` on the command line is:

    awk '{commands}' file_name

Each line of `file_name` is read and the sequence of commands is
executed for each line.

For instance, the `print` command prints a string, or a
variable. There are some special variables that start with a `$`:
- `$0` &nbsp;&nbsp;&nbsp;&nbsp; represents the whole line read from the file
- `$1..$9` &nbsp;&nbsp;&nbsp; represents the columns from the first to the nineth

Moreover, there are some other variables that have a special meaning:
- `NR` &nbsp;&nbsp;&nbsp;&nbsp; the current number of records (lines) read
- `NF` &nbsp;&nbsp;&nbsp;&nbsp; the current number of fields (columns) read
- `FS` &nbsp;&nbsp;&nbsp;&nbsp; the field separator among the columns
- `OFS` &nbsp;&nbsp;&nbsp;&nbsp; the output field separator (default is a blank space)

For instance, in a file with several lines and columns:

    awk '{print $1, $3}' file

prints the columns 1 and 3 in the file,

    awk '{print NR}' file

prints the current number of line read from the file,

    awk '{print NF}' file

prints the current number of columns read from the file.

**Note**: the simple `print` command is equivalent to `print $0`, so
  it just prints the line as it is read from the file!

The **field separator** (`FS`) is usually one space or a `TAB` or a
sequence of spaces. It can be changed, however. For instance:

    awk -F ":" '{print $1, $3, $4}' /etc/passwd

prints the first, third and fourth columns of the file `/etc/passwd`,
which are separated by colons (`:`).

If the command string is preceded by a syntax like: `BEGIN{}` and/or
followed by: `END{}`, the commands in the curly braces are executed at
the beginning of the script or at the end.

Therefore, the command:

    awk 'BEGIN{FS=":"}{print $1, $3, $4}' /etc/passwd

is equivalent to:

    awk -F ":" '{print $1, $3, $4}' /etc/passwd

because before analyzing any line of the file it changes the field
separator `FS` to the colon (`:`) and then it executes the commands.

In the same way, the command:

    awk '{}END{print NR}' grep_file.txt

counts the number of lines in the file `grep_file.txt` (it does
nothing for each line, but just prints the total number of lines at
the end of the file!)

Another example: the file `/etc/shells` contains some comments and the
pathname of all shells installed in the system. If I want **only** the
names of the shells, without further information, I can use:

    awk -F "/" '/^\// {print $NF}' /etc/shells

This commands sets the column separator to "/", then it executes the
following command (`print $NF`, that prints the last column on the
line) only for the lines having a `/` at the beginning of the
line. **Note** that the `/` **MUST** be escaped, to not confuse it
with the `/` beginning and closing the regexp!

Moreover, note that when trying to match for a given pattern, the
command string is in the form:

    '/pattern_matching/ {commands}'

Another example: suppose that we want to use the `df` command, that
stands for **disk free**, that tells us how much space we have on
mounted disks, but we want to print the information **only for real
devices** listed in `/dev/`. Then we could use:

    df | awk '/\/dev\// {print $1, $4}'

this will print the disks and the available space in them.

Now, let us suppose we want to print at the end how much space we have
on all those devices. We could use the form:

    df | awk 'BEGIN{tsp=0}/\/dev\// {print $1, $4; tsp+=$4}END{print "Total space left: ", tsp}'

Basically, what we did was to declare a new (numeric) variable `tsp`
at the beginning and then, for each line matching the pattern, we
cumulated in it the content of the free space in the fourth column of
the file. Then, at the end, we printed the value of such variable.

The `awk` command has many built-in functions that can be used to
execute operations. For instance, the function `length(string)` gives
the length of the string. Then, for instance:

    awk 'length($0) > 10' /etc/shells

will print only the lines whose length is greter than 10 characters.

It is possible to examine conditional operations with the `if`
statement, like in:

    ps -ef | awk '{if (substr($NF,0,8)=="[kworker") {print $0}}'

this prints all the processes active in the system and prints only
those that have in the last column the string: "[kworker".

It is possible to execute some basic mathematics operations, like in:

    awk 'BEGIN{tpi=2.0*atan2(0.0,-1.0); for (i=0; i<101;i++) {x=i*tpi/100; print x, sin(x)}}'

which will print two columns with `x` and `sin(x)` between 0 and two-pi.

Another interesting function is `match(string,regexp)` that matches a
string against a regexp and returns in the variable `RSTART` the
character where the string matches.

Example:

    awk 'match($0,/sh/) {print $0, "| matches the string sh at character number: ", RSTART}' /etc/shells

One can match a condition based on an interval of lines, like in:

    awk 'NR==7, NR==10 {print $0}' /etc/shells

prints all lines between the 7th and the 10th.

Finally, this just scratches the surface of what `awk` does. The
hability to manipulate files, but also to execute mathematical
operations make it invaluable for scientific computing when often one
needs a fast way to compute an average or a statistical quantity on
some data organized in columns, etc. That makes `awk` a truly
fundamental tool.
