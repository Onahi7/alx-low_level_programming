#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);


/**
 * print_elf_header - Prints ELF header information of an ELF file. 
 * @filename: Name of the ELF file.
 */
void print_elf_header(const char *filename)
{
  int fd;
  unsigned char e_ident[EI_NIDENT];

  fd = open(filename, O_RDONLY); 
  if (fd == -1)
    exit(98);

  if (read(fd, e_ident, EI_NIDENT) == -1)
    exit(98);

  if (e_ident[EI_MAG0] != ELFMAG0 || e_ident[EI_MAG1] != ELFMAG1 || 
      e_ident[EI_MAG2] != ELFMAG2 || e_ident[EI_MAG3] != ELFMAG3)
  {
    dprintf(STDERR_FILENO, "Error: %s is not an ELF file\n", filename);
    exit(98);
  }

  print_magic(e_ident);

  Elf64_Ehdr header;
  if (read(fd, &header, sizeof(header)) == -1)
    exit(98);

  print_class(e_ident);
  print_data(e_ident);
  print_version(e_ident);
  print_osabi(e_ident);
  print_abiversion(e_ident);
  print_type(header.e_type);
  print_entry(header.e_entry);

  close(fd);
}

/**
 * main - Displays ELF header information.
 * @argc: Argument count. 
 * @argv: Argument vector.
 *
 * Return: 0 on success, non-zero on failure.
 */
int main(int argc, char **argv)
{
  if (argc != 2)
  {
    dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
    exit(98);
  }

  print_elf_header(argv[1]);
  return (0);
}
