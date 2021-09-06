/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:55:01 by abourdar          #+#    #+#             */
/*   Updated: 2021/09/06 12:55:02 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	close_fds(t_glb *glb, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close (glb->cmd->fd_out);
	close (glb->cmd->fd_in);
}

int	child_1(t_glb *glb, char **envp, int *fd, int *id)
{
	*id = fork();
	if (*id < 0)
		return (1);
	if (*id == 0)
	{
		if (glb->cmd->fd_in == -1)
			ft_error(glb);
		dup2(glb->cmd->fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close_fds(glb, fd);
		execve(glb->cmd->cmd1[0], glb->cmd->cmd1, envp);
		perror(glb->cmd->cmd1[0]);
	}
	return (0);
}

int	child_2(t_glb *glb, char **envp, int *fd, int *id)
{
	*id = fork();
	if (*id < 0)
		return (2);
	if (*id == 0)
	{
		if (glb->cmd->fd_out == -1)
			ft_error(glb);
		dup2(fd[0], STDIN_FILENO);
		dup2(glb->cmd->fd_out, STDOUT_FILENO);
		close_fds(glb, fd);
		execve(glb->cmd->cmd2[0], glb->cmd->cmd2, envp);
		perror(glb->cmd->cmd2[0]);
	}
	return (0);
}

int	starting_2_process(t_glb *glb, char **envp)
{
	int	*fd;
	int	id_child_1;
	int	id_child_2;

	fd = malloc_list(glb, sizeof(int) * 2);
	if (pipe(fd) == -1)
		return (1);
	child_1(glb, envp, fd, &id_child_1);
	child_2(glb, envp, fd, &id_child_2);
	close_fds(glb, fd);
	waitpid(id_child_1, NULL, 0);
	waitpid(id_child_2, NULL, 0);
	return (0);
}
