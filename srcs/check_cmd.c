#include "../inc/pipex.h"

void	check_file(char *infile, t_glb *glb)
{
	glb->cmd->fd_in = open(infile, O_RDONLY);
	if (glb->cmd->fd_in == -1)
		perror("Erreur");
}

void	check_outfile(char *outfile, t_glb *glb)
{
	glb->cmd->outfile = ft_strdup(glb, outfile);
	glb->cmd->fd_out = open(glb->cmd->outfile, O_CREAT | O_WRONLY, 0777);
	if (glb->cmd->fd_out == -1)
		glb->cmd->check = -3;
}

void	check_right_path(t_glb *glb, char **cmd)
{
	int		i;
	char	*tmp;
	char	*cp;

	i = 0;
	while (glb->path_i == 0 && glb->path[i])
	{
		tmp = ft_strjoin(glb, "/", *cmd);
		cp = ft_strjoin(glb, glb->path[i], tmp);
		if (access(cp, F_OK) == 0)
		{
			glb->path_i = 1;
			glb->check_path++;
			*cmd = ft_strdup(glb, cp);
			break ;
		}
		i++;
	}
	glb->path_i = 0;
}

void	check_cmds(char *cmd1, char *cmd2, t_glb *glb, char **env)
{
	glb->cmd->cmd1 = ft_split(glb, cmd1, ' ');
	glb->cmd->cmd2 = ft_split(glb, cmd2, ' ');
	init_path(env, glb);
	check_right_path(glb, &glb->cmd->cmd1[0]);
	check_right_path(glb, &glb->cmd->cmd2[0]);
}
