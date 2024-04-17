/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:09:01 by dslaveev          #+#    #+#             */
/*   Updated: 2024/04/16 13:08:38 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(char **args, int *pfd, char **env);
void	child_process(char **args, int *pfd, char **env);

// int	main(int argc, char **argv, char **envp)
// {
// 	int		pfd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		status1;

// 	if (argc != 5)
// 		ft_error("Usage: ./pipex file1 cmd1 cmd2 file2", EXIT_FAILURE);
// 	if (pipe(pfd) == -1)
// 		ft_error("Failed to create pipe", EXIT_FAILURE);
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		ft_error("Failed to fork child process 1", EXIT_FAILURE);
// 	if (pid1 == 0)
// 		child_process(argv, pfd, envp);
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		ft_error("Failed to fork child process 2", EXIT_FAILURE);
// 	if (pid2 == 0)
// 		parent_process(argv, pfd, envp);
// 	ft_close_fd(pfd);
// 	waitpid(pid2, &status1, 0);
// 	if (WIFEXITED(status1))
// 		status1 = WEXITSTATUS(status1);
// 	return (status1);
// }

void	child_process(char **args, int *pfd, char **env)
{
	int		fdin;

	if (access(args[1], F_OK) == -1)
		ft_error("No such file", 1);
	fdin = open(args[1], O_RDONLY);
	if (fdin <= -1)
		ft_error("Error opening input file", EXIT_FAILURE);
	if (dup2(fdin, STDIN_FILENO) < 0)
	{
		perror("Dup2 failed");
		exit(EXIT_FAILURE);
	}
	if (dup2(pfd[1], STDOUT_FILENO) < 0)
	{
		perror("Dup2 failed");
		exit(EXIT_FAILURE);
	}
	close(fdin);
	ft_close_fd(pfd);
	ft_execute(args[2], env);
	exit(EXIT_FAILURE);
}

void	parent_process(char **args, int *pfd, char **env)
{
	int		fdout;

	fdout = open(args[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout <= -1)
	{
		perror("Error openning file descriptor");
		exit(EXIT_FAILURE);
	}
	if (dup2(fdout, STDOUT_FILENO) < 0)
	{
		perror("Dup2 failed");
		exit(127);
	}
	if (dup2(pfd[0], STDIN_FILENO) < 0)
	{
		perror("Dup2 failed");
		exit(127);
	}
	close(fdout);
	ft_close_fd(pfd);
	ft_execute(args[3], env);
	exit(EXIT_FAILURE);
}
