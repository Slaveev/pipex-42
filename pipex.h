/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 18:25:52 by dslaveev          #+#    #+#             */
/*   Updated: 2024/04/04 15:02:23 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

// process
void	parent_process(char **args, int *pfd, char **env);
void	child_process(char **args, int *pfd, char **env);

// error
void	ft_error(const char *msg, int status);

// free
void	free_str_array(char **array);

// exec path
char	*get_cmd_path(char *argv, char **env);
void	ft_execute(char *argv, char **envp);
char	*get_cmd_path(char *cmd, char **env);

// here doc
int		here_doc_check(char	*input);
void	here_doc_start(char **argv);
void	here_doc_exec(char *seach_word, int *fd);
void	not_here_doc_set(char **argv);

// bonu
// void	ft_wait_status(void);
void	ft_close_fd(int *pfd);

// Hello
// Hello
// < infile grep Hello | buzzFizz > outfile
// < infile fizzBuzz | wc -l > outfile
// < infile ls -l src/ | buzzFizz > outfile
// < infile fizzBuzz | ls -l > outfile
// < infile grep Hello | wc -l > outfile
// foo
// food

#endif
