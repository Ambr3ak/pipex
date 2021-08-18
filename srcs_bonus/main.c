#include "../inc/pipex.h"

void parse_cmd(char **str, char **env, t_glb *glb, t_cmd *cmd)
{
    check_file(str[1], glb, &cmd->check);
    check_cmds_bonus(str, glb, env);
    if (cmd->check == 0)
        check_outfile(str[cmd->nb_cmds + 2], glb);
}

int	ft_strlen2(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
			x++;
		x = 0;
		y++;
	}
	return (y);
}

void init_struct(t_glb *global)
{
    global->cmd = malloc_list(global, sizeof(t_cmd));
    global->recup = malloc_list(global, sizeof(t_rec));
    global->cmd->check = 0;
    global->path_i = 0;
    global->check_path = 0;
}


void ft_error(t_glb *global)
{
    if (global->cmd->check != 0)
        ft_putstr_fd("Error\nPlease execute \n\"./pipex infile cmd1 cmd2 cmd3 ... cmdn outfile\".", 1);
    else if (global->check_path != global->cmd->nb_cmds)
        ft_putstr_fd("Error\ncommand not found.", 1);
    free_malloc_lst(global);
    free(global);

}

int main(int argc, char** argv, char **envp)
{
    t_glb *global;

    global = malloc(sizeof(t_glb));
    global->ptrs = NULL;
    init_struct(global);
    if (argc > 4)
    {
        global->cmd->nb_cmds = argc - 3;
        parse_cmd(argv, envp, global, global->cmd);
        if (global->cmd->check == 0 && global->check_path == global->cmd->nb_cmds)
            starting_process(global, envp, global->cmd);
    }
    else
        global->cmd->check++;
    ft_error(global);
}
