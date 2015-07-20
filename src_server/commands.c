/*
** commands.c for  in /home/quach_a/rendu/PSU_2014_myftp/test
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 18:57:44 2015 Jonathan Quach
** Last update Fri Mar 27 12:33:58 2015 Jonathan Quach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include "server.h"

void		exec_cd(char *buffer, int client_fd, char *root)
{
  char          path[BUFFER_SIZE];

  memset(path, 0, BUFFER_SIZE);
  if (strncmp(buffer, "CD", 2) == 0)
    buffer += 3;
  else if (strncmp(buffer, "CWD", 3) == 0)
    buffer += 4;
  if (getcwd(path, BUFFER_SIZE) != NULL)
    {
      strcat(path, "/");
      strcat(path, buffer);
      if (access(path, F_OK) != 0)
	safe_write(client_fd, CD_FAIL);
      else
	try_to_cd(buffer, client_fd, root);
    }
}

void		exec_pwd(int client_fd)
{
  char		pwd[1024];
  char		msg[BUFFER_SIZE];

  memset(msg, 0, BUFFER_SIZE);
  if ((getcwd(pwd, 1024)) == NULL)
    exit_write("Error : getcwd failed\n");
  strcat(msg, "257\t You are here :\r\n");
  strcat(msg, pwd);
  strcat(msg, "\n");
  safe_write(client_fd, msg);
}

void		exec_ls(int client_fd)
{
  int		i;
  DIR		*d;
  char		*str;
  struct dirent	*dir;

  i = 0;
  if ((d = opendir(".")) != NULL)
    {
      i = get_ls_len() + 1;
      if ((str = malloc(sizeof(char) * i)) == NULL)
	exit_write("Error : malloc failed\n");
      memset(str, 0, i);
      strcat(str, LS_SEND);
      while ((dir = readdir(d)) != NULL)
	{
	  strcat(str, dir->d_name);
	  strcat(str, "\n");
	}
      strcat(str, LS_OK);
      safe_write(client_fd, str);
    }
  else
    safe_write(client_fd, "Error : command ls failed\n");
  if (closedir(d))
    safe_write(STDERR, "Error : closedir failed\n");
}

void		exec_quit(int client_fd, char *client_ip)
{
  safe_write(STDOUT, "Client with IP : ");
  safe_write(STDOUT, client_ip);
  safe_write(STDOUT, " disconnected\n");
  safe_write(client_fd, "quit");
}

void		exec_help(int client_fd, char *buffer)
{
  if (strncmp(buffer, "HELP", 4) == 0)
    buffer += 5;
  if (strcmp(buffer, "") == 0)
    write_help(client_fd);
  else if (strcmp(buffer, "CD") == 0 || strcmp(buffer, "CWD") == 0)
    safe_write(client_fd, CD_HELP);
  else if (strcmp(buffer, "CDUP") == 0)
    write_cdup(client_fd);
  else if (strcmp(buffer, "LS") == 0 || strcmp(buffer, "LIST") == 0)
    safe_write(client_fd, LS_HELP);
  else if (strcmp(buffer, "HELP") == 0)
    safe_write(client_fd, HELP_HELP);
  else if (strcmp(buffer, "PWD") == 0)
    safe_write(client_fd, PWD_HELP);
  else if (strcmp(buffer, "QUIT") == 0)
    safe_write(client_fd, QUIT_HELP);
  else
    safe_write(client_fd, "?Invalid help command.\n");
}
