/*
** client.c for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 19:37:00 2015 Jonathan Quach
** Last update Fri Mar 27 12:48:56 2015 Jonathan Quach
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
#include <signal.h>
#include "client.h"

int			init_client(char *ip, int port)
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
  if ((s_in.sin_addr.s_addr = inet_addr(ip)) == INADDR_NONE)
    {
      xclose(fd);
      exit_write("Error : inet_addr failed\n");
    }
  if (connect(fd, (const struct sockaddr *)&s_in, sizeof(s_in)) == -1)
    {
      xclose(fd);
      exit_write("Error : connect failed\n");
    }
  return (fd);
}

int			handle_result(int server_fd)
{
  int			ret;
  char			buffer[BUFFER_SIZE];

  memset(buffer, 0, BUFFER_SIZE);
  if ((ret = read(server_fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
      buffer[ret] = '\0';
      if (strcmp(buffer, "quit") == 0)
	return (EXIT_SUCCESS);
      safe_write(STDOUT, buffer);
      memset(buffer, 0, BUFFER_SIZE);
    }
  return (EXIT_FAILURE);
}

int			client_loop(int server_fd)
{
  int			ret;
  char			buffer[BUFFER_SIZE];

  memset(buffer, 0, BUFFER_SIZE);
  handle_result(server_fd);
  safe_write(STDOUT, "ftp> ");
  if (signal(SIGINT, sig_handler) == SIG_ERR)
    exit_write("Error : can not catch SIGINT\n");
  while ((ret = read(STDIN, buffer, BUFFER_SIZE - 1)) > 0)
    {
      buffer[ret] = '\0';
      safe_write(server_fd, buffer);
      if (handle_result(server_fd) == EXIT_SUCCESS)
	return (EXIT_SUCCESS);
      safe_write(STDOUT, "ftp> ");
      memset(buffer, 0, BUFFER_SIZE);
    }
  return (EXIT_FAILURE);
}

int			main(int ac, char **av)
{
  int			fd;
  int			port;
  char			*ip;

  if (ac != 3)
    {
      safe_write(STDERR, "Usage : ./client [IP] [PORT].\n");
      return (EXIT_FAILURE);
    }
  ip = av[1];
  port = atoi(av[2]);
  if ((fd = init_client(ip, port)) == -1)
    return (EXIT_FAILURE);
  if (client_loop(fd) == EXIT_FAILURE)
    {
      safe_write(STDOUT, "Error : read failed\n");
      return (EXIT_FAILURE);
    }
  xclose(fd);
  safe_write(STDOUT, "221\t Bye bye!\r\n");
  return (EXIT_SUCCESS);
}
