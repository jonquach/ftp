/*
** server.h for  in /home/quach_a/rendu/PSU_2014_myftp
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Mar 15 19:37:12 2015 Jonathan Quach
** Last update Fri Mar 27 12:57:40 2015 Jonathan Quach
*/

#ifndef _SERVER_H_
# define _SERVER_H_

/*
** macros
*/
# define BUFFER_SIZE 4096
# define STDERR 2
# define STDOUT 1
# define STDIN 0
# define WELCOME "220\t Welcome !\r\n"
# define VERSION "\nVersion (myFTP v1.0)\r\n"
# define LOGIN_ANO "\n220 Login anonymous successful.\n"
# define LOGIN_OK "\n230 Login successful.\n"
# define REMOTE_SYS "\nRemote system type is "
# define LS_SEND "150\t Here comes the directory listing.\r\n"
# define LS_OK "226\t Directory send OK.\r\n"
# define CD_OK "250\t Directory successfully changed.\r\n"
# define CD_FAIL "550\t Failed to change directory.\r\n"
# define CD_USAGE "214\t usage: cd/cwd remote-directory\r\n"
# define CD_SECURITY "550\t Nope, you can't do that\r\n"
# define HELP_HELP "214\t help\t print local help information\r\n"
# define CD_HELP "214\t cd/cwd\t change remote working directory\r\n"
# define LS_HELP "214\t ls/list\t list contents of remote path\r\n"
# define PWD_HELP "214\t pwd\t print working directory on remote machine\r\n"
# define QUIT_HELP "214\t quit\t terminate ftp session and exit\r\n"

/*
** commands.c
*/
void	exec_cd(char *, int, char *);
void	exec_pwd(int);
void	exec_ls(int);
void	exec_quit(int, char *);
void	exec_help(int, char *);

/*
** exec_login.c
*/
void	exec_user(int);
void	exec_pass(int);

/*
** exec_utils.c
*/
int	get_ls_len();
void	try_to_cd(char *, int, char *);
void	exec_cdup(int, char *);
void	exec_prompt(int);
void	exec_not_found(int);

/*
** loop.c
*/
void	client_loop(int, char *);
void	server_loop(int, char *);
void	write_help(int);
void	write_cdup(int);

/*
** utils_server.c
*/
void	safe_write(int, char *);
void	exit_write(char *);
void	xclose(int);
void	xclose_exit_nwrite(int, char *);

/*
** server.c
*/
int	new_socket(int);
void	handle_client(int);
void	exec_command(char *, int, char *, char *);

#endif /* !_SERVER_H_ */
