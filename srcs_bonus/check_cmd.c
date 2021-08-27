#include "../inc/pipex.h"

void	check_file(char *infile, t_glb *glb)
{
	glb->cmd->fd_in = open(infile, O_RDONLY);
	if (glb->cmd->fd_in == -1)
	{
		perror("Erreur");
	}
}

void	check_outfile(char *outfile, t_glb *glb)
{
	glb->cmd->outfile = ft_strdup(glb, outfile);
	glb->cmd->fd_out = open(glb->cmd->outfile, O_CREAT | O_WRONLY, 0777);
	if (glb->cmd->fd_out == -1)
		perror("Erreur");
}

void	check_right_path(t_glb *glb, char ***cmd)
{
	int		i;
	char	*tmp;
	char	*cp;

	i = 0;
	while (glb->path_i == 0 && glb->path[i])
	{
		tmp = ft_strjoin(glb, "/", *cmd[0]);
		cp = ft_strjoin(glb, glb->path[i], tmp);
		if (access(cp, F_OK) == 0)
		{
			glb->path_i = 1;
			glb->check_path++;
			*cmd[0] = ft_strdup(glb, cp);
			break ;
		}
		i++;
	}
	glb->path_i = 0;
}

void	check_cmds_bonus(char **argv, t_glb *glb, char **env)
{
	int	i;

	i = 0;
	glb->cmd->cmds = malloc_list(glb, sizeof(int **) * (glb->cmd->nb_cmds + 1));
	while (i < glb->cmd->nb_cmds)
	{
		glb->cmd->cmds[i] = ft_split(glb, argv[2 + i], ' ');
		i++;
	}
	glb->cmd->cmds[i] = NULL;
	init_path(env, glb);
	i = 0;
	while (glb->cmd->cmds[i])
	{
		check_right_path(glb, &glb->cmd->cmds[i]);
		i++;
	}
}
