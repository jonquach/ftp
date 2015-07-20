/*
** exec_utils.c for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Fri Mar 20 15:14:40 2015 Jonathan Quach
** Last update Fri Mar 27 12:47:55 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "server.h"

int		get_ls_len()
{
  int		i;
  DIR		*d;
  struct dirent *dir;

  i = 0;
  if ((d = opendir(".")) != NULL)
    {
      while ((dir = readdir(d)) != NULL)
	i += strlen(dir->d_name) + 1;
    }
  i += strlen(LS_SEND) + strlen(LS_OK);
  return (i);
}

void		try_to_cd(char *buffer, int client_fd, char *root)
{
  char          path[BUFFER_SIZE];

  memset(path, 0, BUFFER_SIZE);
  if ((getcwd(path, BUFFER_SIZE)) == NULL)
    exit_write("Error : getcwd failed\n");
  if (strncmp(root, path, strlen(root)) == 0)
    {
      if (strcmp(root, path) == 0 && strncmp(buffer, "..", 2) == 0)
	safe_write(client_fd, CD_SECURITY);
      else
	{
	  if (chdir(buffer) == 0)
	    safe_write(client_fd, CD_OK);
	  else if (strcmp(buffer, "") == 0)
	    safe_write(client_fd, CD_USAGE);
	  else
	    safe_write(client_fd, CD_FAIL);
	}
    }
  else
    safe_write(client_fd, CD_FAIL);
}

void		exec_cdup(int client_fd, char *root)
{
  try_to_cd("..", client_fd, root);
}

void		exec_prompt(int client_fd)
{
  safe_write(client_fd, "200\t Noop command okay.\r\n");
}

void		exec_not_found(int client_fd)
{
  safe_write(client_fd, "?Invalid command.\r\n");
}
