# OS161: An Educational Operating System

OS161 is a lightweight educational operating system developed at Harvard University to help students dive into the inner workings of operating systems. It runs on a MIPS based simulator called System161, which provides a simplified yet realistic environment for OS development and experimentation.

## Why OS161?

OS161 is designed to hit that sweet spot between simplicity and realism, making it a great playground for learning OS fundamentals. It comes with the basics threading, interrupts, traps, and a minimal file system but the real challenge (and fun) comes from implementing missing features like system calls, virtual memory, and process management yourself. It’s hands on learning at its best, pushing you to tackle real world OS development problems.

**Fun fact**: Mark Zuckerberg worked on OS161 assignments during his last semester at Harvard, while also busy launching Facebook.

## System161: The Simulator

System161 is the virtual machine built specifically for OS161. It simulates a 32 bit MIPS based system and supports up to 32 processors, making it a solid testing ground for OS development. Some key features include:

- Remote debugging with GDB
- Built in kernel profiling and statistical monitoring
- Event tracing down to individual machine instructions
- The ability to network multiple instances using a hub program

## OS161 Development Environment

Setting up OS161 is easiest on Ubuntu 20.04. To save time and headaches, there’s a preconfigured Docker container that includes all the necessary dependencies, so you can jump straight into coding without worrying about installation issues.
➡️ [polito-os161-docker](https://github.com/marcopalena/polito-os161-docker)

## Navigating the OS161 File Structure

Once inside the container, the OS161 file structure is as follows:

- `$HOME/os161/src` → Contains all OS161 source files.
- `$HOME/os161/src/kern` → Contains kernel configuration files.
- `$HOME/os161/root` → This is the directory from which OS161 should be executed.

## Start Coding

If you want to have this repository inside the container, you will need to install git. Then, once inside the src folder, you should perform the following steps:
   ```sh
   git init
   git remote add origin git@github.com:papo1011/os161.git
   git fetch origin
   git reset --hard origin/main
   ```

### DOCS

Install the extension Live Server in Visual Studio Code and open the file `src/man/index.html` to view the documentation.

## Compiling and Running OS161

### Use OPTIONS for Compilation

1. Navigate to the configuration file:
   ```sh
   cd kern/conf/conf.kern
   ```
2. Add the following line to the configuration file:
   ```
   defoption myoption
   optfile myoption main/new_file.c
   ```
3. Add the following line to the include/new_file.h:
   ```
   #if OPT_MYOPTION

   void my_function(void);

   #endif
   ```
4. Add the following line to the main/example.c:
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
   cd kern/conf
   ```
2. Create a new kernel configuration:
   ```sh
   ./config MYKERNEL
   ```
3. Compile the kernel:
   ```sh
   cd kern/compile/MYKERNEL
   bmake depend
   bmake
   bmake install
   ```

### Running OS161 (Docker Container Folder Structure)

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

## Debugging OS161 (Docker Container Folder Structure)

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

## Reference Files
- **System call handling:** `/kern/arch/mips/syscall/syscall.c`
- **List of system calls:** `/kern/include/kern/syscall.h`

