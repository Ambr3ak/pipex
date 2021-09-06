/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:54:55 by abourdar          #+#    #+#             */
/*   Updated: 2021/09/06 12:54:57 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	parse_cmd(char **str, char **env, t_glb *glb)
{
	check_file(str[1], glb);
	check_cmds(str[2], str[3], glb, env);
	check_outfile(str[4], glb);
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

void	ft_error(t_glb *global)
{
	if (global->check_path != 2)
		ft_putstr_fd("command not found\n", 1);
	else if (global->cmd->check != 0)
	{
		ft_putstr_fd("Error\nPlease execute \n", 1);
		ft_putstr_fd("./pipex infile cmd1 cmd2 outfile\n.", 1);
	}
	free_malloc_lst(global);
	free(global);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_glb	*global;

	global = malloc(sizeof(t_glb));
	global->ptrs = NULL;
	init_struct(global);
	if (argc == 5)
	{
		parse_cmd(argv, envp, global);
		if (global->cmd->check == 0)
			starting_2_process(global, envp);
	}
	ft_error(global);
}
