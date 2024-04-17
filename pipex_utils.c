/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 12:37:32 by dslaveev          #+#    #+#             */
/*   Updated: 2024/04/04 14:29:08 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>

void	free_str_array(char **array);
void	ft_close_fd(int *pfd);

void	ft_error(const char *msg, int status)
{
	perror(msg);
	exit(status);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK | F_OK) == 0)
			return (free_str_array(paths), path);
		free(path);
		i++;
	}
	return (free_str_array(paths), NULL);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_execute(char *argv, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd_path = NULL;
	cmd = ft_split(argv, ' ');
	if (!cmd)
		ft_error("Command failed to split", EXIT_FAILURE);
	if (execve(cmd[0], cmd, envp) == -1)
	{
		cmd_path = get_cmd_path(cmd[0], envp);
		if (!cmd_path)
		{
			free_str_array(cmd);
			ft_error("Command not found", 127);
		}
		if (execve(cmd_path, cmd, envp) == -1)
		{
			free(cmd_path);
			free_str_array(cmd);
			ft_error("Command not executable", 126);
		}
		free(cmd_path);
	}
	free_str_array(cmd);
	exit(EXIT_FAILURE);
}

void	ft_close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}
