*This project has been created as part of the 42 curriculum by drhaouha.*

# get_next_line

## Description

get_next_line is a C function that reads one line at a time from a file descriptor. Repeated calls return successive lines until EOF or an error, at which point it returns `NULL`. It works on both regular files and standard input, and can be integrated into any 42 project via libft once validated.

## Instructions

### Compilation

No Makefile is required. Compile directly with your project files:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

`BUFFER_SIZE` controls how many bytes are read per `read()` call. The project must compile with any value, including extreme ones (`1`, `9999`, `10000000`).

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Function prototype

```c
char *get_next_line(int fd);
```

Returns the next line (including the terminating `\n` if present), or `NULL` on EOF or error. The caller is responsible for freeing the returned string.

### Files

| File | Role |
|---|---|
| `get_next_line.c` | Core function |
| `get_next_line_utils.c` | Helper functions |
| `get_next_line.h` | Header — contains prototype and `BUFFER_SIZE` default |

### Forbidden

- `libft` — not allowed in this project
- `lseek()` — forbidden
- Global variables — forbidden

## Bonus Features

- Single static variable for the entire implementation
- Simultaneous management of multiple file descriptors (each fd keeps its own read state across interleaved calls)

Bonus files: `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`

## Algorithm

### Core idea: static buffer per fd

The central challenge of `get_next_line` is that `read()` may return more data than one line, or less. The function must therefore remember what it read but did not yet return — across calls. A `static` variable is the natural tool: it retains its value between calls without being visible outside the function.

**Mandatory** uses one `static char *` (a "leftover" string for the single fd). **Bonus** uses a `static char *stash[OPEN_MAX]` (one leftover slot per fd), which is why only one static variable is still needed.

### Step-by-step

1. **Read into a fixed-size buffer** (`BUFFER_SIZE` bytes at a time) and append each chunk to `stash[fd]` until either a `\n` is found in the accumulated string or `read()` returns 0 (EOF).
2. **Extract the line**: everything up to and including the first `\n` (or the entire stash if EOF was reached without one).
3. **Update the leftover**: whatever remains after the `\n` is kept in `stash[fd]` for the next call.
4. **Return the extracted line**; return `NULL` if stash is empty and `read()` returned 0 or an error.

### Why this approach

Reading `BUFFER_SIZE` bytes at a time amortizes the cost of `read()` syscalls while keeping memory usage bounded. Storing only the unprocessed remainder (not the entire file) ensures memory stays proportional to the longest line, not the file size. This directly satisfies the subject's requirement: *"try to read as little as possible each time `get_next_line()` is called — don't read the whole file and then process each line."*

### Effect of BUFFER_SIZE

- **BUFFER_SIZE = 1**: correct but slow — one `read()` syscall per character.
- **BUFFER_SIZE = 9999 or 10000000**: correct; the buffer is stack-allocated per call, so very large values may cause a stack overflow on constrained systems. The algorithm's correctness is independent of the value.

## Resources

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html)
- [C static variables — cppreference](https://en.cppreference.com/w/c/language/storage_duration)
- [man 3 malloc / free](https://man7.org/linux/man-pages/man3/malloc.3.html)

## N.B.
This version of get_next_line is different because it does not keep still reachable memory

## Compilation command
gcc -g -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -I./
