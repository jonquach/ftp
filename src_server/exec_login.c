/*
** exec_login.c for  in /home/quach_a/rendu/PSU_2014_myftp/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Thu Mar 26 22:39:34 2015 Jonathan Quach
** Last update Thu Mar 26 22:47:07 2015 Jonathan Quach
*/

#include "server.h"

void	exec_user(int client_fd)
{
  safe_write(client_fd, "331\t Please specify the password\r\n");
}

void	exec_pass(int client_fd)
{
  safe_write(client_fd, "230\t Password ?\r\n");
  safe_write(client_fd, "332\t Password OK\r\n");
}
