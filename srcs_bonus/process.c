#include "../inc/pipex.h"

void	close_fds_bonus(t_glb *glb, int **fd)
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


t_rec *init_process(t_glb *glb, t_cmd *cmd, t_rec *r)
{
	r = malloc_list(glb, sizeof(t_rec));
	r->fd = malloc_list(glb, sizeof(int *) * (cmd->nb_cmds - 1));
	r->id = malloc_list(glb, sizeof(int) * cmd->nb_cmds);
	return (r);
}

int starting_process(t_glb *glb, char **envp, t_cmd *cmd)
{
	t_rec *recup;
	int i;
	
	i = 0;
	recup = NULL;
	recup = init_process(glb, cmd, recup);
	while (i < cmd->nb_cmds - 1)
	{
		recup->fd[i] = malloc_list(glb, sizeof(int) * 2);
		if (pipe(recup->fd[i]) == -1)
			return 1;
		i++;
	}
	first_child(glb, envp, recup);
	while (recup->i < cmd->nb_cmds - 1)
	{
		middle_child(glb, envp, recup);
		recup->i++;
	}
	last_child(glb, envp, recup);
	close_fds_bonus(glb, recup->fd);
	wait_pid(recup, cmd);
	return 0;
}
