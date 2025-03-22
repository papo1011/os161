# What is OS161?

OS161 is a lightweight educational operating system designed for teaching operating system concepts. Developed by Harvard University, it runs on a MIPS-based simulator called sys161. The system includes basic kernel functionality such as threading, interrupts, traps, and a minimal file system. However, many features, such as system calls, virtual memory, and advanced process management, need to be implemented by students as part of their coursework.

### OS161 Development Environment

OS161 requires Ubuntu 20.04 for proper execution. To simplify the setup process, you can use a preconfigured Docker container that includes all necessary dependencies. This container includes all necessary dependencies for OS161 development.

### Using the OS161 Docker Container

A Docker container has been prepared to facilitate the development of OS161. You can find it at the following repository:

➡️ [polito-os161-docker](https://github.com/marcopalena/polito-os161-docker)

## Navigating the OS161 File Structure

Once inside the container, the OS161 file structure is as follows:

- `$HOME/os161/src` → Contains all OS161 source files.
- `$HOME/os161/src/kern` → Contains kernel configuration files.
- `$HOME/os161/root` → This is the directory from which OS161 should be executed.

### DOCS
Install the extension Live Server in Visual Studio Code and open the file `src/man/index.html` to view the documentation.

## Compiling and Running OS161

### Use OPTIONS for Compilation

1. Navigate to the configuration file:
   ```sh
   cd $HOME/os161/src/kern/conf/conf.kern
   ```
2 Add the following line to the configuration file:
   ```
   defoption myoption
   optfile myoption main/new_file.c
   ```
3 Add the following line to the include/new_file.h:
   ```
   #if OPT_MYOPTION

   void my_function(void);

   #endif
   ```
4 Add the following line to the main/example.c:
   ```
   #if OPT_MYOPTION

   void my_function(void) {
       // Your code here
   }

   #endif
   ```

### Building the Kernel

1. Navigate to the configuration directory:
   ```sh
   cd $HOME/os161/src/kern/conf
   ```
2. Create a new kernel configuration:
   ```sh
   ./config MYKERNEL
   ```
3. Compile the kernel:
   ```sh
   cd $HOME/os161/src/kern/compile/MYKERNEL
   bmake depend
   bmake
   bmake install
   ```

### Running OS161

1. Open a terminal in the root directory:
   ```sh
   cd $HOME/os161/root
   ```
2. Run OS161 using the MIPS simulator:
   ```sh
   sys161 kernel
   ```
   If multiple configurations exist, run a specific one:
   ```sh
   sys161 kernel-MYKERNEL
   ```

## Debugging OS161

OS161 can be debugged using multiple tools. The recommended approach involves using two terminals:

1. **In the first terminal**, start OS161 in debug mode:
   ```sh
   sys161 -w kernel
   ```
2. **In the second terminal**, launch the debugger:
   ```sh
   mips-harvard-os161-gdb -tui kernel
   ```
   Alternative debugger options:
   ```sh
   ddd --debugger mips-harvard-os161-gdb kernel
   emacs &
   ```

If using `emacs`, navigate to **Tools -> Debugger** and set the debugger command:

```sh
mips-harvard-os161-gdb -i=mi kernel
```

# System Calls in OS161

## Executing a User Process
To execute a user program in OS161:
```sh
p <program_path>
```
Example:
```sh
p /testbin/palin
p /bin/cat
```
> **Note:** Not all programs can be executed correctly due to the lack of support for certain functionalities (e.g., virtual memory management, `argc/argv` arguments).

## System Call Implementation (read, write, exit)
System calls must be implemented in:
```
/kern/syscall
```
- `read` and `write` can be based on `getch()` and `putch()`, initially limited to STDIN, STDOUT, and STDERR.
- `exit` must remove the **address space** and destroy the process thread.

> **Warning:**  
> - Every new system call must be added in `/kern/arch/mips/syscall/syscall.c`.  
> - The parameters to be passed must be manually defined.  
> - The list of system calls and their identifiers can be found in:  
  ```
  /kern/include/kern/syscall.h
  ```
  Note: `SYS__exit` has a double underscore.

## Reference Files
- **System call handling:** `/kern/arch/mips/syscall/syscall.c`
- **List of system calls:** `/kern/include/kern/syscall.h`

