/*
** client.h for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 19:37:12 2015 Jonathan Quach
** Last update Sat Mar 21 16:16:09 2015 Jonathan Quach
*/

#ifndef _CLIENT_H_
# define _CLIENT_H_

#define BUFFER_SIZE 4096
#define STDERR 2
#define STDOUT 1
#define STDIN 0

/*
** signal.c
*/
void	sig_handler(int);

/*
** utils.c
*/
void	safe_write(int, char *);
void	exit_write(char *);
void	xclose(int);

/*
** client.c
*/
int	init_client(char *, int);
int	handle_result(int);
int	client_loop(int);

#endif /* !_CLIENT_H_ */
