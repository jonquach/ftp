/*
** utils.c for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 19:39:11 2015 Jonathan Quach
** Last update Fri Mar 20 21:39:24 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client.h"

void	safe_write(int fd, char *str)
{
  if (write(fd, str, strlen(str)) == -1)
    {
      if (write(1, "Error : write failed\n", 22) == -1)
	return;
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
      exit(EXIT_FAILURE);
    }
}
