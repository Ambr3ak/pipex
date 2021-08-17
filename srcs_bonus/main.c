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
    global->cmd->check = 0;
    global->path_i = 0;
    global->check_path = 0;
}


void ft_error(t_glb *global)
{
    if (global->check_path != global->cmd->nb_cmds)
        printf ("Error\ncommand not found.");
    else if (global->cmd->check != 0)
        printf ("Error\nPlease execute \n\"./pipex infile cmd1 cmd2 outfile\".");
    free_malloc_lst(global);
    free(global);

}

int main(int argc, char** argv, char **envp)
{
    t_glb *global;
    //int i = 0;

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
    ft_error(global);
}
