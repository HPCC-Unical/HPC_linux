
# 📚 Advanced Linux Commands Lecture (with Flags & Examples)

## 🧭 File and Directory Management

### `ls` – List Directory Contents

| Flag | Description | Example | Output / Use Case |
|------|-------------|---------|--------------------|
| `-l` | Long listing | `ls -l` | Shows details (permissions, size, date) |
| `-a` | All files (including hidden) | `ls -a` | Shows `.bashrc`, etc. |
| `-h` | Human-readable sizes | `ls -lh` | Displays `1.2K`, `2M`, etc. |
| `-t` | Sort by time modified | `ls -lt` | Recent files first |
| `-S` | Sort by file size | `ls -lS` | Largest to smallest |
| `-R` | Recursive listing | `ls -R` | Lists subdirectories too |

### `cp` – Copy Files and Directories

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `-r` | Recursive copy | `cp -r dir1 dir2` | Copy full directory |
| `-i` | Prompt before overwrite | `cp -i file.txt backup/` | Prevents accidental overwrite |
| `-u` | Copy only if newer | `cp -u a.txt b/` | Keeps b/ up to date |
| `-v` | Verbose output | `cp -v *.txt docs/` | Shows what's being copied |
| `--backup` | Create backup if file exists | `cp --backup file.txt /tmp/` | Preserves previous version |

### `mv` – Move/Rename Files

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `-i` | Prompt before overwrite | `mv -i file.txt existing.txt` | Avoid overwriting |
| `-u` | Move only if newer | `mv -u report.txt /reports/` | Update report only if new |
| `-v` | Verbose | `mv -v *.log /var/logs/` | Show each file being moved |

### `rm` – Remove Files and Directories

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `-r` | Recursive | `rm -r folder/` | Deletes folder and contents |
| `-f` | Force delete | `rm -f file.txt` | No prompt even if write-protected |
| `-i` | Interactive mode | `rm -i *.txt` | Ask before each delete |
| `-v` | Verbose | `rm -v *.bak` | Show what’s being deleted |

### `mkdir` – Make Directories

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `-p` | Create parent directories | `mkdir -p a/b/c` | No error if `a/` or `b/` missing |
| `-v` | Verbose | `mkdir -v newdir` | Output each created dir |

### `rmdir` – Remove Empty Directories

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `-p` | Remove parent dirs | `rmdir -p a/b/c` | If all are empty |
| _(no flags)_ | Basic remove | `rmdir test` | Only works if empty |

### `cd` – Change Directory

| Shortcut | Description | Example | Use Case |
|----------|-------------|---------|----------|
| `cd -` | Previous dir | `cd -` | Toggle last dir |
| `cd ~` | Home directory | `cd ~` | Quick access to home |
| `cd ..` | Up one level | `cd ..` | Move up one directory |
| `cd ../..` | Two levels up | `cd ../..` | Jump two levels |

## 🔐 Permissions and Ownership

### `chmod` – Change File Mode

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `+x` | Add execute | `chmod +x script.sh` | Make script runnable |
| `-w` | Remove write | `chmod -w file.txt` | Prevent editing |
| `u/g/o` | User/group/others | `chmod g+w report.txt` | Allow group write |
| `755` | Full access to user | `chmod 755 file.sh` | Typical for scripts |
| `-R` | Recursive | `chmod -R 755 mydir` | Change all inside folder |

### `chown` – Change File Owner

| Flag | Description | Example | Use Case |
|------|-------------|---------|----------|
| `user:group` | Set both | `chown alice:dev file` | Assign to `alice` in `dev` group |
| `-R` | Recursive | `chown -R www-data:www /var/www` | For web server folders |
| `--reference` | Copy ownership from another file | `chown --reference=ref.txt target.txt` | Match permissions exactly |

## 📂 Path Operations

### `basename` – Extract Filename

| Use | Example | Output |
|-----|---------|--------|
| Basic | `basename /path/to/file.txt` | `file.txt` |
| Strip suffix | `basename file.txt .txt` | `file` |
| In scripts | `basename "$0"` | Shows script name |

### `dirname` – Extract Directory Path

| Use | Example | Output |
|-----|---------|--------|
| Basic | `dirname /home/user/file.txt` | `/home/user` |
| Nested | `dirname ./a/b/c/file.txt` | `./a/b/c` |

## 📈 Monitoring and Help

### `top` – Real-time System Monitor

| Key/Flag | Description | Example | Use Case |
|----------|-------------|---------|----------|
| `top` | Start monitor | `top` | Show live CPU/mem |
| `-u user` | Filter by user | `top -u root` | Only root processes |
| Press `M` | Sort by memory | – | Find memory hogs |
| Press `P` | Sort by CPU | – | See CPU-heavy tasks |
| Press `k` | Kill process | – | Enter PID to terminate |

### `man` – Manual Pages

| Use | Example | Description |
|-----|---------|-------------|
| View man page | `man ls` | Shows usage, options |
| Section search | `man 5 passwd` | View config file format |
| Search term | `/pattern` | Search inside man page |
| Next match | `n` | Jump to next search match |

### `cheat.sh` – Quick CLI Cheatsheets

| Use | Example | Description |
|-----|---------|-------------|
| Show examples | `curl cheat.sh/rsync` | Practical command guide |
| Search subtopic | `curl cheat.sh/find~name` | Filter by keyword |
| Quiet curl | `curl -s cheat.sh/grep` | No progress bar |
| Local tool | `cht.sh grep` (with shell setup) | Interactive CLI helper |

## ✅ Summary Quick Reference Table

| Command | Common Flags | Use Case |
|---------|--------------|----------|
| `ls` | `-l, -a, -h, -R` | View files, hidden, recursive |
| `cp` | `-r, -u, -v, --backup` | Safe, recursive copying |
| `mv` | `-i, -u, -v` | Rename/move with safety |
| `rm` | `-r, -f, -i, -v` | Force or interactive delete |
| `mkdir` | `-p, -v` | Nested directory creation |
| `chmod` | `+x, -R, 755` | Set permissions easily |
| `chown` | `user:group, -R` | Change ownership recursively |
| `basename` | – | Get file from path |
| `dirname` | – | Get directory path |
| `top` | `-u, M, P, k` | Monitor & manage processes |
| `man` | `/search, n` | Learn command usage |
| `cheat.sh` | `curl cheat.sh/cmd` | Fast reference for any command |
