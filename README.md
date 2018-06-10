# OSExperiment

Operating system experiment, NUAA

## Table of Contents

- [OS Experiment](#osexperiment)
    1. [Shell](#shell)
    1. [File Operating](#file-operating)
    1. [File Descriptor](#file-descriptor)
    1. [Multi-process Management](#multi-process-management)
    1. [Multi-thread Management](#multi-thread-management)

## Shell

```shell
ls
pwd
cd
touch
cat
cp
rm
mv
```

## File Operating

- open file
    ```c
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags);
    ```
- create file
    ```c
    #include <sys/stat.h>
    #include <fcntl.h>

    int creat(const char *pathname, mode_t mode);
    int open(const char *pathname, int flags, mode_t mode);
    ```
- close file
    ```c
    #include <unistd.h>

    int close(int fd);  
    ```
- read file
    ```c
    #include <unistd.h>

    int read(int fd, void *buf, size_t count);
    ```
- write file
    ```c
    #include <unistd.h>

    int write(int fd, void *buf, size_t count);
    ```
- seek file
    ```c
    #include <unistd.h>

    off_t lseek(int fd, off_t offset, int whence);
    ```

## File Descriptor

- dup
    ```c
    #include <unistd.h>

    int dup(int oldfd);
    ```
- dup2
    ```c
    #include <unistd.h>

    int dup2(int oldfd, int newfd);
    ```
- pipe
    ```c
    #include <unistd.h>

    int pipe(int fd[2]);
    ```

## Multi-process Management

## Multi-thread Management