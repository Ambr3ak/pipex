#include "../inc/pipex.h"
#include "errno.h"

void check_file(char *infile, t_glb *glb, int *check)
{
    glb->cmd->fd_in = open(infile, O_RDONLY);
    if (glb->cmd->fd_in == -1)
        *check = -1;
    else
        glb->cmd->infile = ft_strdup(glb, infile);
}

void check_outfile(char *outfile, t_glb *glb)
{
	int err;
    glb->cmd->outfile = ft_strdup(glb, outfile);
	glb->cmd->fd_out = open(glb->cmd->outfile, O_CREAT | O_WRONLY, 0777);
	err = errno;
	printf("%d\n", err);
	if (glb->cmd->fd_out == -1)
		glb->cmd->check = -3;
}

void check_exec(char *exec, t_glb *glb, int *check)
{
    if (ft_strcmp(exec, "./pipex", 7))
        *check = -2;
    else
        glb->cmd->exec = ft_strdup(glb, exec);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n && str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i < n)
		return (str1[i] - str2[i]);
	else
		return (0);
}

void init_path(char **env, t_glb *glb)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			glb->path = ft_split(env[i] + 5, ':');
		}
		i++;
	}
}

void	check_right_path(t_glb *glb, char **cmd)
{
	int i;
	char *tmp;
	char *cp;

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
			break;
		}
		free (cp);
		i++;
	}
	glb->path_i = 0;
}

void check_cmds(char *cmd1, char *cmd2, t_glb *glb, char **env)
{
	int i = 0;

	glb->cmd->cmd1 = ft_split(cmd1, ' ');
	glb->cmd->cmd2 = ft_split(cmd2, ' ');
	init_path(env, glb);
	check_right_path(glb, &glb->cmd->cmd1[0]);
	check_right_path(glb, &glb->cmd->cmd2[0]);
	while (glb->path[i])
	{
		ft_putstr_fd(glb->path[i], 1);
		printf("\n");
		i++;
	}
}
