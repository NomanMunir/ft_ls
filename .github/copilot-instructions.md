# ft_ls Project Instructions

## Project Overview
Recreation of the Unix `ls` command as a 42 school project (v3.1). Must implement mandatory options: `-l` (long format), `-R` (recursive), `-a` (all/hidden), `-r` (reverse), `-t` (time sort). Output must match system `ls` behavior exactly (LC_ALL=C).

## Architecture
- **Modular C design**: Core logic split across 4 source files
  - `main.c`: Entry point, orchestrates option parsing and execution
  - `options.c`: Command-line argument parsing for flags  
  - `ft_ls.c`: Core directory reading and listing logic
  - `utils.c`: Custom implementations of string/memory functions
- **Header-only interface**: All types and prototypes in `include/ft_ls.h`
- **ONLY 18 allowed functions**: `write`, `opendir`, `readdir`, `closedir`, `stat`, `lstat`, `getpwuid`, `getgrgid`, `listxattr`, `getxattr`, `time`, `ctime`, `readlink`, `malloc`, `free`, `perror`, `strerror`, `exit`
- **Everything else must be reimplemented**: No `printf`, `puts`, `strlen`, `strcmp`, `strcpy`, etc. - create `ft_*` versions

## Data Structures
```c
t_options  // Bitflags for -l, -R, -a, -r, -t options (all mandatory)
t_file     // Linked list node for file info with stat data (needed for sorting/formatting)
```

## Critical Requirements from Subject

### Option Behavior (Must Match System `ls`)
- **-l**: Long format with permissions, links, owner, group, size, date, name
- **-R**: Recursive directory traversal (design for this EARLY - affects architecture)
- **-a**: Show hidden files (entries starting with '.')
- **-r**: Reverse sort order
- **-t**: Sort by modification time (newest first)
- **Multi-column format NOT required** unless `-l` is specified
- **ACL/extended attributes NOT required** for mandatory part
- **Padding/pagination**: Be lenient but no missing information

### Error Handling Rules
- Match `ls` error behavior exactly
- No segfaults, bus errors, or double frees allowed
- No memory leaks permitted
- Use `perror()` or `strerror()` for system call failures

## Critical Conventions

### Custom Standard Library Functions
All standard functions are reimplemented with `ft_` prefix:
- `ft_malloc()`: Wrapper that exits on allocation failure (no NULL checks needed at call site)
- `ft_strdup()`, `ft_strlen()`, `ft_strcmp()`: Drop-in replacements for standard functions
- **Never use standard library equivalents directly** (project requirement)
- **Use only `write()` for output** - no `printf()`, `puts()`, `putchar()`, etc.

### Allowed vs Forbidden Functions
✅ **Allowed (18 functions only)**:
- I/O: `write`
- Directory: `opendir`, `readdir`, `closedir`
- File info: `stat`, `lstat`, `getpwuid`, `getgrgid`, `listxattr`, `getxattr`, `readlink`
- Time: `time`, `ctime`
- Memory: `malloc`, `free`
- Errors: `perror`, `strerror`, `exit`

❌ **Forbidden (must reimplement)**:
- String functions: `strlen`, `strcmp`, `strcpy`, `strdup`, `strcat`, etc.
- Output functions: `printf`, `puts`, `putchar`, `putstr`
- Any other libc function not in the allowed list

### Error Handling Pattern
```c
// Allocation: ft_malloc() handles errors internally via exit(1)
ptr = ft_malloc(size);  // No NULL check needed

// System calls: Use perror() and return error code
if (opendir(path) == NULL) {
    perror(path);
    return (1);
}
```

### Code Style (Norminette Compliance)
- **Variable declarations**: All at function start, no mixed declarations
- **Brace style**: Opening brace on same line for functions
- **Indentation**: Tabs only, no spaces
- **Line length**: Max 80 characters (enforced by -Wextra)
- **Function length**: Max 25 lines per function

## Build System
```bash
make          # Build ft_ls binary
make clean    # Remove object files
make fclean   # Remove objects + binary
make re       # Full rebuild (fclean + all)
```

Compiler flags: `-Wall -Wextra -Werror -std=c99` (all warnings are errors)

## Current Implementation Status
<<<<<<< HEAD
- ✅ Basic directory listing with `-a` option
- ✅ Option parsing for all 5 mandatory flags
- ⚠️ `-l` (long format): Needs stat(), permissions, owner/group lookup
- ⚠️ `-R` (recursive): Architecture must handle nested directories
- ⚠️ `-r` (reverse): Needs sorting implementation first
- ⚠️ `-t` (time sort): Needs stat() and comparison logic
- ⚠️ `t_file` linked list: Defined but not used (needed for sorting)
=======
✅ **ALL MANDATORY OPTIONS COMPLETE**:
- `-a`: Show hidden files (including . and ..)
- `-l`: Long format with permissions, owner, group, size, date
- `-R`: Recursive directory traversal
- `-r`: Reverse sort order
- `-t`: Time-based sorting (newest first)
- All options work in combination: `-lRart`, `-la`, `-Rl`, etc.
- Zero memory leaks (valgrind verified)
- Output matches system `ls` behavior
>>>>>>> 393ce036c2c9384019b617c2f51a290bccba727d

## Testing Strategy
```bash
# Compare output with system ls (LC_ALL=C for consistency)
LC_ALL=C ls -la /path
LC_ALL=C ./ft_ls -la /path

# Test edge cases
./ft_ls /nonexistent        # Error handling
./ft_ls -lRart /etc         # Combined options
./ft_ls file.txt dir/       # Mix of files and directories
./ft_ls                     # No args (current directory)
```

## Development Workflow
1. Modify source in `src/`
2. Run `make` to compile (creates `obj/` automatically)
3. Test with `./ft_ls [options] [paths]`
4. Ensure no compiler warnings (build fails on any warning)
<<<<<<< HEAD
=======
5. Check for memory leaks: `valgrind --leak-check=full ./ft_ls -lRa`

## Git Workflow
```bash
# Check status and changes
git status
git diff

# Stage changes
git add .                    # Add all files
git add src/ft_ls.c         # Add specific file

# Commit with descriptive message
git commit -m "feat: implement -l option with permissions and owners"
git commit -m "fix: handle memory leak in file list cleanup"
git commit -m "refactor: improve sorting algorithm efficiency"

# Push to remote repository
git push origin main         # Push to main branch
git push origin <branch>     # Push to specific branch

# Common scenarios
git log --oneline           # View commit history
git checkout -b feature     # Create new branch
git merge feature           # Merge branch into current
```

**Commit Message Conventions**:
- `feat:` New feature implementation
- `fix:` Bug fix
- `refactor:` Code restructuring without behavior change
- `docs:` Documentation updates
- `test:` Testing additions/changes
- `style:` Formatting, whitespace (norminette fixes)
>>>>>>> 393ce036c2c9384019b617c2f51a290bccba727d

## Key Files
- `include/ft_ls.h`: All function prototypes and structures
- `Makefile`: Build rules with automatic object directory creation
<<<<<<< HEAD
- `src/ft_ls.c`: Main listing logic (currently 43 lines, needs expansion for full feature set)
=======
- `src/ft_ls.c`: Main listing logic with file list management and recursion
- `src/utils.c`: Custom string/memory functions (ft_strlen, ft_strcmp, etc.)
- `src/options.c`: Command-line flag parsing
- `src/main.c`: Entry point and argument handling
>>>>>>> 393ce036c2c9384019b617c2f51a290bccba727d
