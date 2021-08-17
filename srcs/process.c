#include "../inc/pipex.h"

void	close_fds(t_glb *glb, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close (glb->cmd->fd_out);
	close (glb->cmd->fd_in);
}

int starting_process(t_glb *glb, char **envp, t_cmd *cmd)
{
	int *fd;
	int id_child_1;
	int id_child_2;

	fd = malloc_list(glb, sizeof(int) * 2);
	if (pipe(fd) == -1)
		return 1;
	id_child_1 = fork();
	if (id_child_1 < 0)
		return 1;
	if (id_child_1 == 0)
	{
		dup2(glb->cmd->fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close_fds(glb, fd);
		execve(cmd->cmd1[0], cmd->cmd1,envp);
	}
	id_child_2 = fork();
	if (id_child_2 < 0)
		return 2;
	if (id_child_2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(glb->cmd->fd_out, STDOUT_FILENO);
		close_fds(glb, fd);
		execve(cmd->cmd2[0], cmd->cmd2, envp);
	}
	close_fds(glb, fd);
	
	waitpid(id_child_1, NULL, 0);
	waitpid(id_child_2, NULL, 0);
	return 0;
}
