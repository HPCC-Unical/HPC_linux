# Introduction to Vim

## Overview

**Vim** (Vi IMproved) is a highly configurable, powerful text editor built for efficient text editing. It is an improved version of the Unix editor `vi` and is ubiquitous on Unix systems.

While Vim has a steep learning curve, its efficiency and speed make it a favorite among programmers, sysadmins, and power users.

### A Brief History

Vim was created in 1991 by Bram Moolenaar as an extended version of the `vi` editor, which originated in 1976 as part of the early Unix operating system. The name "Vim" originally stood for "Vi IMitation," but it was later changed to "Vi IMproved" to reflect its added features and flexibility. Over the years, Vim has developed a loyal user base and an ecosystem of plugins and configurations, making it a robust choice for text editing.

Vim is included with many Unix-like systems and is available on all major operating systems, including Linux, macOS, and Windows.

### Use Cases for Vim

* **Software Development**: Write and edit code with syntax highlighting, macros, and powerful text manipulation commands.
* **System Administration**: Quickly edit configuration files over SSH sessions with minimal system resources.
* **Remote Editing**: Ideal for editing files on servers or embedded systems where GUI tools are unavailable.
* **Scripting**: Automate editing tasks using Vimscript or integrate with shell scripts.
* **Writing and Markdown Editing**: Many writers use Vim with plugins to write articles, books, and documentation.

### Why Learn Vim?

* **Always available:** Installed by default on most Unix-based systems.
* **Efficient:** Designed for minimal keystrokes and maximum speed.
* **Customizable:** Supports scripting, plugins, and extensive configuration.
* **Modal editing:** Enables powerful commands with fewer keys.
* **Lightweight:** Consumes minimal system resources, making it ideal for low-powered or remote environments.

---

# 1. Vim Basics

## Opening and Creating Files

```bash
vim filename.txt
```

* Opens `filename.txt` if it exists.
* If it doesn’t exist, a new file is created.
* Vim starts in **Normal mode**, so typing immediately won't insert text until you switch modes.

To open Vim in read-only mode:

```bash
vim -R filename.txt
```

To open multiple files:

```bash
vim file1.txt file2.txt
```

Use `:n` and `:prev` to switch between them.

### Starting with Vim

You may see a welcome screen if you open Vim without a filename:

```bash
vim
```

To exit this screen, press `:q` + `Enter`.

It's good practice to use `vimtutor` when you're starting out. Just type `vimtutor` in your terminal for an interactive tutorial.

## Modes in Vim

Vim is a **modal editor**, which means it operates in different modes:

| Mode        | Purpose                                | Enter with         |
| ----------- | -------------------------------------- | ------------------ |
| **Normal**  | Navigate, delete, copy/paste, run cmds | `Esc`              |
| **Insert**  | Insert text (typing mode)              | `i`, `a`, `o`      |
| **Visual**  | Select and manipulate blocks of text   | `v`, `V`, `Ctrl-v` |
| **Command** | Enter commands like save, quit, search | `:`                |

### More on Modes

* **Normal mode** is where you perform actions: move the cursor, delete lines, copy and paste, etc.
* **Insert mode** allows you to type text, like any traditional editor.
* **Visual mode** lets you highlight text to manipulate blocks.
* **Command-line mode** (triggered by `:`) is used for operations like saving, quitting, searching, or global substitutions.

### Example Workflow

1. Open a file: `vim myfile.txt`
2. Press `i` to enter Insert mode and type something.
3. Press `Esc` to return to Normal mode.
4. Type `:w` to save, then `:q` to quit.

### Tip:

If Vim ever feels "stuck," press `Esc` repeatedly to return to Normal mode. You'll do this often!

You can also visualize your current mode in some enhanced Vim environments or when using certain configurations/plugins.

---

# 2. Basic Navigation

Understanding how to move around a file quickly is one of the most important skills in Vim.

### Cursor Movement

| Key | Action     |
| --- | ---------- |
| `h` | Move left  |
| `l` | Move right |
| `j` | Move down  |
| `k` | Move up    |

These keys correspond to the left, right, down, and up arrows but allow your hands to stay on the home row.

### Word and Line Navigation

| Key | Action                                                  |
| --- | ------------------------------------------------------- |
| `w` | move forward to the beginning of the next word          |
| `e` | move forward to the end of the current/next word        |
| `b` | move backward to the beginning of the word              |
| `0` | move to the beginning of the line                       |
| `^` | move to the first non-whitespace character of the line  |
| `$` | move to the end of the line                             |

### Screen Navigation

| Key | Action                            |
| --- | --------------------------------- |
| `H` | move to the top of the screen     |
| `M` | move to the middle of the screen  |
| `L` | move to the bottom of the screen  |

### Scrolling

| Key      | Action                         |
| -------- | -------------------------------|
| `Ctrl-d` | scroll down half a screen      |
| `Ctrl-u` | scroll up half a screen        |
| `Ctrl-f` | scroll forward a full screen   |
| `Ctrl-b` | scroll backward a full screen  |

### Jumping to Specific Locations

| Key | Action                                                |
| --- | ----------------------------------------------------- |
| `gg`| go to the beginning of the file                       |
| `G` | go to the end of the file                             |
| `:n`| go to line number `n` (e.g., `:42` jumps to line 42)  |
| `nG`| go to line `n` (same as `:n`)                         |

### Searching

| Key        | Action                                 |
| ---------- | -------------------------------------- |
| `/pattern` | search forward for 'pattern'           |
| `?pattern` | search backward for 'pattern'          |
|     `n`    | repeat search in the same direction    |
|     `N`    | repeat search in the opposite direction|

### Example Navigation Exercise

1. Open a file with multiple lines of text.
2. Use `w`, `b`, `e` to navigate between words.
3. Try `0`, `^`, and `$` to jump within lines.
4. Use `gg` and `G` to jump to top and bottom of the file.
5. Search for a word using `/yourword` and navigate with `n` and `N`.

Mastering these movements is essential for becoming efficient with Vim.

---

# 3. Insert Mode

Insert mode is used for adding and editing text, similar to typing in any standard text editor. 
There are multiple ways to enter insert mode, depending on where and how you want to start typing:

| Key | Description          |
| --- | -------------------- |
| `i` | Insert before cursor |
| `I` | Insert at line start |
| `a` | Insert after cursor  |
| `A` | Insert at line end   |
| `o` | New line below       |
| `O` | New line above       |


### Examples:

Assume the current line is:

```text
Hello, world!
       ^ (cursor here)
```

- Pressing `i` lets you insert **before** the comma.
- Pressing `a` lets you append **after** the comma.
- Pressing `A` puts your cursor at the **end of the line**.
- Pressing `o` creates a **new line below**, and you're placed into Insert mode on the new line.
- Pressing `O` creates a **new line above**.

### Exiting Insert Mode

To return to Normal mode, press:

- `Esc` – This is the most common way.
- `Ctrl-[` – An alternative for `Esc`. 

### Practical Exercise 

1. Open a file: `vim test.txt` 
2. Press `o` to create a new line below and type something.
3. Press `Esc` to return to Normal mode.
4. Move to a different line and press `A` to append text.
5. Try using `I` to insert text at the start of a line.
6. Use `O` to open a line above the current one and write something.

Practicing these variations builds your speed and fluency with text entry in Vim.

---

# 4. Saving and Quitting

Use command mode (start with `:` from Normal mode):

| Command | Description                |
| ------- | -------------------------- |
| `:w`    | Save the file              |
| `:q`    | Quit Vim                   |
| `:wq`   | Save and quit              |
| `:q!`   | Quit without saving        |
| `:x`    | Save and quit (like `:wq`) |

### Example:

- Edit a file, then type `:wq` + Enter to save and quit.

---

# 5. Deleting, Copying, and Pasting

## Deleting

| Command | Action                        |
| ------- | ----------------------------- |
| `x`     | Delete character under cursor |
| `dd`    | Delete entire line            |
| `dw`    | Delete word                   |
| `d$`    | Delete to end of line         |

## Copying (Yanking)

| Command | Action            |
| ------- | ----------------- |
| `yy`    | Yank current line |
| `yw`    | Yank word         |

## Pasting

| Command | Action              |
| ------- | ------------------- |
| `p`     | Paste after cursor  |
| `P`     | Paste before cursor |

### Example:

1. Use `yy` to copy a line.
2. Move down and press `p` to paste it.

---

# 6. Searching and Replacing

## Searching

| Command | Action                      |
| ------- | --------------------------- |
| `/word` | Search forward for "word"   |
| `?word` | Search backward for "word"  |
| `n`     | Repeat last search forward  |
| `N`     | Repeat last search backward |

## Replacing

```vim
:%s/old/new/g
```

- Replace all occurrences of "old" with "new" in the file.
- Add `c` to confirm each: `:%s/old/new/gc`

---

# 7. Simple Configuration

Create or edit a `.vimrc` file in your home directory to customize Vim.

### Example Configuration:

```vim
set number          " Show line numbers
syntax on           " Enable syntax highlighting
set expandtab       " Use spaces instead of tabs
set tabstop=4       " Number of spaces per tab
set shiftwidth=4    " Indentation width
set autoindent      " Maintain indent on new lines
```

To apply changes, restart Vim or run `:source ~/.vimrc`.

---

# 8. Exercises

## Beginner

1. Open a file `example.txt` in Vim.
2. Enter Insert mode and type 3 lines of text.
3. Save with `:w` and quit with `:q`.

## Intermediate

1. Open the same file.
2. Move around using `hjkl`, `w`, `$`, `gg`.
3. Delete the second line with `dd`.
4. Copy the first line with `yy` and paste it with `p`.
5. Search for a word using `/`.

## Advanced

1. Turn on line numbers with `:set number`.
2. Use Visual mode to select a paragraph (`vip`) and yank it (`y`).
3. Replace a word throughout the file with `:%s/old/new/g`.
4. Edit your `.vimrc` to enable syntax highlighting.

---

# Resources

- **Vimtutor** (Run `vimtutor` in terminal)
- [Vim Adventures](https://vim-adventures.com/)
- [Vim Cheatsheet](https://vim.rtorr.com/)
- [OpenVim](https://openvim.com/)

---

# Summary

- Vim is powerful but requires practice.
- Master Normal and Insert modes.
- Learn navigation, editing, and search basics.
- Use `vimtutor` daily for a week to build muscle memory.

