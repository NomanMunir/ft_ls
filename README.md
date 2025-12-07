# ft_ls

A custom implementation of the `ls` command in C.

## Description

`ft_ls` is a project from the 42 school curriculum. The goal is to recreate the functionality of the `ls` command, which is used to list files and directories. This implementation supports the following options: `-l`, `-R`, `-a`, `-r`, and `-t`.

## Usage

```bash
./ft_ls [options] [file ...]
```

### Options

*   `-l`: List in long format.
*   `-R`: Recursively list subdirectories.
*   `-a`: Include directory entries whose names begin with a dot (`.`).
*   `-r`: Reverse the order of the sort.
*   `-t`: Sort by time modified (most recently modified first).

## Installation

To use `ft_ls`, you must first compile it from the source code.

### Building from source

1.  Clone the repository:
    ```bash
    git clone https://github.com/nomanmunir/ft_ls.git
    cd ft_ls
    ```
2.  Compile the project using the provided `Makefile`:
    ```bash
    make
    ```
    This will create an executable file named `ft_ls`.

## Contributing

This project was created as part of the 42 school curriculum. Therefore, contributions are not expected. However, if you find a bug or have a suggestion, feel free to open an issue.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
