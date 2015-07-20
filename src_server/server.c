/*
** server.c for  in /home/quach_a/rendu/PSU_2014_myftp/test
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Fri Mar 13 19:20:53 2015 Jonathan Quach
** Last update Fri Mar 27 12:57:48 2015 Jonathan Quach
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int			new_socket(int port)
{
  int			fd;
  struct protoent	*pe;
  struct sockaddr_in	s_in;

  if ((pe = getprotobyname("TCP")) == 0)
    exit_write("Error : getprotobyname failed\n");
  if ((fd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    exit_write("Error : socket failed\n");
  s_in.sin_family = AF_INET;
  s_in.sin_port = htons(port);
  s_in.sin_addr.s_addr = INADDR_ANY;
  if (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      xclose(fd);
      exit_write("Error : bind failed\n");
    }
  if (listen(fd, 42) == -1)
    {
      xclose(fd);
      exit_write("Error : listen failed\n");
    }
  return (fd);
}

void			handle_client(int client_fd)
{
  char			msg[BUFFER_SIZE];

  memset(msg, 0, BUFFER_SIZE);
  strcat(msg, WELCOME);
  safe_write(client_fd, msg);
}

void			exec_command(char *buffer, int client_fd,
				     char *client_ip, char *root)
{
  if (strcmp(buffer, "PWD") == 0)
    exec_pwd(client_fd);
  else if (strcmp(buffer, "LS") == 0 || strcmp(buffer, "LIST") == 0)
    exec_ls(client_fd);
  else if (strcmp(buffer, "QUIT") == 0)
    exec_quit(client_fd, client_ip);
  else if (strcmp(buffer, "") == 0)
    exec_prompt(client_fd);
  else if (strcmp(buffer, "CDUP") == 0)
    exec_cdup(client_fd, root);
  else if (strncmp(buffer, "CD", 2) == 0 ||
	   strncmp(buffer, "CWD", 3) == 0)
    exec_cd(buffer, client_fd, root);
  else if (strncmp(buffer, "HELP", 4) == 0)
    exec_help(client_fd, buffer);
  else if (strncmp(buffer, "USER", 4) == 0)
    exec_user(client_fd);
  else if (strncmp(buffer, "PASS", 4) == 0)
    exec_pass(client_fd);
  else
    exec_not_found(client_fd);
}

int			main(int ac, char **av)
{
  int			fd;
  char			*client_ip;

  client_ip = "\0";
  if (ac != 2)
    {
      safe_write(STDERR, "Usage : ./server [PORT]\n");
      return (EXIT_FAILURE);
    }
  if ((fd = new_socket(atoi(av[1]))) < 0)
    return (EXIT_FAILURE);
  server_loop(fd, client_ip);
  xclose(fd);
  return (EXIT_SUCCESS);
}
