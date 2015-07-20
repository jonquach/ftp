/*
** signal_client.c for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Thu Mar 19 23:18:28 2015 Jonathan Quach
** Last update Sat Mar 21 15:18:52 2015 Jonathan Quach
*/

#include <signal.h>
#include "client.h"

void	sig_handler(int signal)
{
  if (signal == SIGINT)
    {
      safe_write(STDOUT, "\n");
      safe_write(STDOUT, "ftp> ");
    }
}
