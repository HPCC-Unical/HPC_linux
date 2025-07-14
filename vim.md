# Introduction to Vim

## Overview

**Vim** (Vi IMproved) is a highly configurable, powerful text editor built for efficient text editing. It is an improved version of the Unix editor `vi` and is ubiquitous on Unix systems.

While Vim has a steep learning curve, its efficiency and speed make it a favorite among programmers, sysadmins, and power users.

### Why Learn Vim?

- **Always available:** Installed by default on most Unix-based systems.
- **Efficient:** Designed for minimal keystrokes and maximum speed.
- **Customizable:** Supports scripting, plugins, and extensive configuration.
- **Modal editing:** Enables powerful commands with fewer keys.

---

# 1. Vim Basics

## Opening and Creating Files

```bash
vim filename.txt
```

- Opens `filename.txt` if it exists.
- If it doesn’t exist, a new file is created.

### Starting with Vim

You may see a welcome screen if you open Vim without a filename:

```bash
vim
```

To exit this screen, press `:q` + `Enter`.

## Modes in Vim

Vim is a **modal editor**, which means it operates in different modes:

| Mode        | Purpose                                | Enter with         |
| ----------- | -------------------------------------- | ------------------ |
| **Normal**  | Navigate, delete, copy/paste, run cmds | `Esc`              |
| **Insert**  | Insert text (typing mode)              | `i`, `a`, `o`      |
| **Visual**  | Select and manipulate blocks of text   | `v`, `V`, `Ctrl-v` |
| **Command** | Enter commands like save, quit, search | `:`                |

### Tip:

If Vim ever feels "stuck," press `Esc` repeatedly to return to Normal mode.

---

# ⌨️ 2. Basic Navigation

Navigation is key to using Vim effectively. Here are the most commonly used commands in **Normal mode**.

## Character Navigation

| Key | Action     |
| --- | ---------- |
| `h` | Move left  |
| `l` | Move right |
| `j` | Move down  |
| `k` | Move up    |

### Example:

Use `jjjj` to move down 4 lines.

## Word Navigation

| Key | Action              |
| --- | ------------------- |
| `w` | Next word           |
| `b` | Previous word       |
| `e` | End of current word |

### Example:

In a sentence, repeatedly pressing `w` jumps to each next word.

## Line Navigation

| Key | Action                    |
| --- | ------------------------- |
| `0` | Start of line             |
| `^` | First non-blank character |
| `$` | End of line               |

## File Navigation

| Key  | Action                  |
| ---- | ----------------------- |
| `gg` | Go to beginning of file |
| `G`  | Go to end of file       |
| `:n` | Go to line number `n`   |

### Example:

Type `:10` + Enter to go to line 10.

---

# 3. Insert Mode

Use insert mode to type text. Enter it from Normal mode using the following keys:

| Key | Description          |
| --- | -------------------- |
| `i` | Insert before cursor |
| `I` | Insert at line start |
| `a` | Insert after cursor  |
| `A` | Insert at line end   |
| `o` | New line below       |
| `O` | New line above       |

### Example:

- Press `o` to open a new line below and start typing.

## Exiting Insert Mode

- Press `Esc` to return to Normal mode.

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

# 🔍 6. Searching and Replacing

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

# 7. Simple Configuration (`~/.vimrc`)

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

# 🧪 8. Exercises

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

