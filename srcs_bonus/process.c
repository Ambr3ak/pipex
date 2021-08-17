#include "../inc/pipex.h"

void	close_fds(t_glb *glb, int **fd)
{
	int i = 0;
	while (i < glb->cmd->nb_cmds - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	close (glb->cmd->fd_out);
	close (glb->cmd->fd_in);
}

int starting_process(t_glb *glb, char **envp, t_cmd *cmd)
{
	int **fd;
	int *id;

	int i = 0;

	fd = malloc_list(glb, sizeof(int *) * (cmd->nb_cmds - 1));
	id = malloc_list(glb, sizeof(int) * cmd->nb_cmds);
	while (i < cmd->nb_cmds - 1)
	{
		fd[i] = malloc_list(glb, sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
			return 1;
		i++;
	}
	i = 0;
	id[i] = fork();
	if (id[i] < 0)
		return 2;
	if (id[i] == 0)
	{
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(fd[i][1], STDOUT_FILENO);
		close_fds(glb, fd);
		execve(cmd->cmds[i][0], cmd->cmds[i],envp);
	}
	i++;
	while (i < cmd->nb_cmds - 1)
	{
		id[i] = fork();
		if (id[i] < 0)
			return 2;
		if (id[i] == 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
			close_fds(glb, fd);
			execve(cmd->cmds[i][0], cmd->cmds[i], envp);
		}
		i++;
	}
	id[i] = fork();
	if (id[i] < 0)
		return 2;
	if (id[i] == 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close_fds(glb, fd);
		execve(cmd->cmds[i][0], cmd->cmds[i], envp);
	}
	close_fds(glb, fd);
	
	i = 0;
	while (i < cmd->nb_cmds)
	{
		waitpid(id[i], NULL, 0);
		i++;
	}
	return 0;
}
