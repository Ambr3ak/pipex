/* **************************************************************************
 * */
/*                                                                            */
/*                                                        :::      ::::::::
 *                                                        */
/*   pipex.h                                            :+:      :+:    :+:
 *   */
/*                                                    +:+ +:+         +:+
 *                                                    */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+
 *   */
/*                                                +#+#+#+#+#+   +#+
 *                                                */
/*   Created: 2021/09/06 13:28:18 by abourdar          #+#    #+#
 *   */
/*   Updated: 2021/09/06 13:28:18 by abourdar         ###   ########.fr
 *   */
/*                                                                            */
/* **************************************************************************
 * */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_cmd
{
	char	*exec;
	char	*infile;
	int		fd_in;
	int		fd_out;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	***cmds;
	int		nb_cmds;
	int		check;
}				t_cmd;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_rec
{
	int	i;
	int	**fd;
	int	*id;
}				t_rec;

typedef struct s_glb
{
	t_list	*ptrs;
	t_cmd	*cmd;
	t_rec	*recup;

	char	**env;
	char	**path;
	char	*limiter;
	int		path_i;
	int		check_path;
	int		err;
}				t_glb;

void	*lst_add(t_glb *glb, void *ptr);
void	*malloc_list(t_glb *glb, int size);
void	*free_malloc_lst(t_glb *glb);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(t_glb *glb, const char *s1);
char	*ft_strjoin(t_glb *glb, char *s1, char *s2);
int		ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(t_glb *glb, char *s, unsigned int start, size_t len);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
int		ft_strcmp(const char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split( t_glb *glb, char const *s, char c);
void	check_file(char *infile, t_glb *glb);
void	check_outfile(char *outfile, t_glb *glb);
void	check_exec(char *exec, t_glb *glb, int *check);
void	check_cmds(char *cmd1, char *cmd2, t_glb *glb, char **env);
void	check_cmds_bonus(char **argv, t_glb *glb, char **env);
int		starting_process(t_glb *glb, char **envp, t_cmd *cmd);
int		starting_2_process(t_glb *glb, char **envp);
int		first_child(t_glb *glb, char **envp, t_rec *r);
int		middle_child(t_glb *glb, char **envp, t_rec *r);
int		last_child(t_glb *glb, char **envp, t_rec *r);
void	wait_pid(t_rec *recup, t_cmd *cmd);
void	close_fds_bonus(t_glb *glb, int **fd);
void	init_struct(t_glb *global);
void	init_path(char **env, t_glb *glb);
void	ft_error(t_glb *global);
#endif
