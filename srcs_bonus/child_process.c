#include "../inc/pipex.h"

int	first_child(t_glb *glb, char **envp, t_rec *r)
{
	r->i = 0;
	r->id[r->i] = fork();
	if (r->id[r->i] < 0)
		return (2);
	if (r->id[r->i] == 0)
	{
		if (glb->cmd->fd_in == -1)
			ft_error(glb);
		dup2(glb->cmd->fd_in, STDIN_FILENO);
		dup2(r->fd[r->i][1], STDOUT_FILENO);
		close_fds_bonus(glb, r->fd);
		execve(glb->cmd->cmds[r->i][0], glb->cmd->cmds[r->i], envp);
		perror(glb->cmd->cmds[r->i][0]);
	}
	r->i++;
	return (0);
}

int	middle_child(t_glb *glb, char **envp, t_rec *r)
{
	r->id[r->i] = fork();
	if (r->id[r->i] < 0)
		return (2);
	if (r->id[r->i] == 0)
	{
		dup2(r->fd[r->i - 1][0], STDIN_FILENO);
		dup2(r->fd[r->i][1], STDOUT_FILENO);
		close_fds_bonus(glb, r->fd);
		execve(glb->cmd->cmds[r->i][0], glb->cmd->cmds[r->i], envp);
		perror(glb->cmd->cmds[r->i][0]);
	}
	return (0);
}

int	last_child(t_glb *glb, char **envp, t_rec *r)
{
	r->id[r->i] = fork();
	if (r->id[r->i] < 0)
		return (2);
	if (r->id[r->i] == 0)
	{
		if (glb->cmd->fd_out == -1)
			ft_error(glb);
		dup2(r->fd[r->i - 1][0], STDIN_FILENO);
		dup2(glb->cmd->fd_out, STDOUT_FILENO);
		close_fds_bonus(glb, r->fd);
		execve(glb->cmd->cmds[r->i][0], glb->cmd->cmds[r->i], envp);
		perror(glb->cmd->cmds[r->i][0]);
	}
	return (0);
}

void	wait_pid(t_rec *recup, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (i < cmd->nb_cmds)
	{
		waitpid(recup->id[i], NULL, 0);
		i++;
	}
}
