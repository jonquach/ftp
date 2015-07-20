/*
** loop.c for  in /home/quach_a/rendu/PSU_2014_myftp/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sat Mar 21 16:22:03 2015 Jonathan Quach
** Last update Fri Mar 27 13:00:40 2015 Jonathan Quach
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

void			client_loop(int client_fd, char *client_ip)
{
  int			ret;
  char			pwd[1024];
  char			buffer[BUFFER_SIZE];

  if ((getcwd(pwd, 1024)) == NULL)
    exit_write("Error : getcwd failed\n");
  memset(buffer, 0, BUFFER_SIZE);
  handle_client(client_fd);
  while ((ret = read(client_fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
      buffer[ret - 1] = '\0';
      safe_write(STDOUT, "[Server]> Get command : ");
      safe_write(STDOUT, buffer);
      safe_write(STDOUT, "\n");
      exec_command(buffer, client_fd, client_ip, pwd);
      memset(buffer, 0, BUFFER_SIZE);
    }
  xclose(client_fd);
  exit(EXIT_SUCCESS);
}

void			server_loop(int fd, char *client_ip)
{
  int			client_fd;
  socklen_t		socket_size;
  struct sockaddr_in	socket_client;

  socket_size = sizeof(socket_client);
  while (1)
    {
      client_fd = accept(fd, (struct sockaddr *)&socket_client, &socket_size);
      client_ip = inet_ntoa(socket_client.sin_addr);
      if (client_fd == -1)
	xclose_exit_nwrite(fd, "Error : accept failed\n");
      if (fork() == 0)
	{
	  xclose(fd);
	  client_loop(client_fd, client_ip);
	}
      else
	xclose(client_fd);
    }
}

void			write_help(int client_fd)
{
  char			buffer[BUFFER_SIZE];

  memset(buffer, 0, BUFFER_SIZE);
  strcat(buffer, "214\t Commands are :\n\ncd\ncwd\ncdup\nls\n");
  strcat(buffer, "list\nhelp\npwd\nquit\n\r\n");
  safe_write(client_fd, buffer);
}

void			write_cdup(int client_fd)
{
  char			buffer[BUFFER_SIZE];

  memset(buffer, 0, BUFFER_SIZE);
  strcat(buffer, "214\t cdup\t change remote working directory to ");
  strcat(buffer, "to parent directory\r\n");
  safe_write(client_fd, buffer);
}
