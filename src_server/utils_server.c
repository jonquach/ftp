/*
** utils.c for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 19:39:11 2015 Jonathan Quach
** Last update Sat Mar 21 16:13:26 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "server.h"

void	safe_write(int fd, char *str)
{
  if (write(fd, str, strlen(str)) == -1)
    {
      write(1, str, strlen(str));
      if (write(1, "Error : write failed\n", 22) == -1)
	exit(EXIT_FAILURE);
      exit(EXIT_FAILURE);
    }
}

void	exit_write(char *str)
{
  safe_write(STDOUT, str);
  exit(EXIT_FAILURE);
}

void	xclose(int fd)
{
  if (close(fd) == -1)
    {
      safe_write(STDERR, "Error : close failed\n");
      printf("%d\n", fd);
      exit(EXIT_FAILURE);
    }
}

void	xclose_exit_nwrite(int fd, char *str)
{
  xclose(fd);
  exit_write(str);
}
