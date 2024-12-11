# **Get Next Line**

The "Get Next Line" (GNL) project provides a C function to read a file, standard input (stdin), or other file descriptors line by line. This project focuses on mastering advanced C programming techniques such as dynamic memory allocation, file handling, and the use of static variables.

---

## **Features**
- **Line-by-Line Reading:** Allows reading from files or standard input one line at a time.
- **Customizable Buffer Size:** The reading buffer size is controlled using the `BUFFER_SIZE` macro.
- **Multiple File Descriptor Support:** In the bonus part, multiple file descriptors can be handled simultaneously.
- **Error-Resilient Design:** Handles invalid file descriptors and memory allocation failures gracefully.

---

## **Project Structure**
The project includes the following files:

1. **`get_next_line.h`**  
   - Contains function prototypes and macros used throughout the project.

2. **`get_next_line.c`**  
   - Implements the main functions: `get_next_line`, `next_line`, `new_line`, and `parse`.

3. **`get_next_line_utils.c`**  
   - Includes utility functions: `ft_strlen`, `ft_strjoin`, and `ft_strchr`.

4. **`get_next_line_bonus.c`**  
   - Adds support for handling multiple file descriptors.

5. **`get_next_line_utils_bonus.c`**  
   - Provides utility functions for the bonus implementation.

---

## **Setup**
1. Clone the repository:
   ```bash
   git clone https://github.com/username/get_next_line.git
   cd get_next_line
   ```

2. Compile using the **Makefile**:
   - **Mandatory Part:**
     ```bash
     make
     ```
   - **Bonus Part:**
     ```bash
     make bonus
     ```

3. Use the library in your projects:
   - Link the compiled `get_next_line.a` library:
     ```bash
     gcc main.c get_next_line.a -o gnl
     ```

---

## **Usage**

### **`get_next_line` Function**
```c
char *get_next_line(int fd);
```

- **Parameters:**
  - `fd`: The file descriptor to read from.

- **Return Value:**
  - Returns a pointer to a string containing a single line.
  - Returns `NULL` at EOF or on error.

- **Example Usage:**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("example.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### **Bonus Usage (Multiple File Descriptors)**
Handle multiple file descriptors simultaneously:
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);

printf("File1: %s", line1);
printf("File2: %s", line2);

free(line1);
free(line2);
close(fd1);
close(fd2);
```

---

## **Testing BUFFER_SIZE**
You can test the project with different `BUFFER_SIZE` values. Example:
```bash
gcc -D BUFFER_SIZE=1 main.c get_next_line.a -o gnl
./gnl
```

Observe the performance and behavior with various `BUFFER_SIZE` values.

---

## **Technical Highlights**
1. **Static Variables:**
   - Static variables are used to store the state of each file descriptor.
2. **Dynamic Memory Allocation:**
   - Buffers and return values are dynamically allocated using `malloc`.
3. **Multiple File Descriptors:**
   - The bonus part uses a `static char *line[4096]` array to maintain states for multiple file descriptors.

---

## **Enhancements**
- Improved error handling.
- Potential support for Unicode or wide characters.
- Optimization for performance with very large files.

---

## **Testing Scenarios**
To test the project, prepare sample files and run the following commands:

### **File Input**
- Create a sample file `example.txt`:
```
Line 1
Line 2
Line 3
```

- Compile and test:
```bash
gcc -D BUFFER_SIZE=32 main.c get_next_line.a -o gnl
./gnl
```

### **Standard Input (STDIN)**
- Test with standard input in the terminal:
```bash
gcc main.c get_next_line.a -o gnl
./gnl
```
- Each line you type will be read and printed until EOF (Ctrl+D).

---

## **Troubleshooting**
- **Memory Leaks:**
  - Use Valgrind to identify leaks:
    ```bash
    valgrind --leak-check=full ./gnl
    ```
- **Segmentation Fault:**
  - Ensure valid file descriptors.
  - Verify `malloc` calls and null pointer checks.

---

## **License**
This project is licensed under the MIT License. See the `LICENSE` file for details.
