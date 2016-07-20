/*
** builtins.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:22:56 2016 
** Last update Wed Jun  8 08:52:16 2016 
*/

#ifndef BUILTINS_H_
# define BUILTINS_H_

# include "shell.h"

# define MAX_BUILT_FORK	8
# define MAX_BUILT	11

typedef struct	s_builtins
{
  char		*str;
  int		(*f_tab)(t_mini*, char *, int *, int *);
}		t_builtins;

typedef struct	s_echo
{
  char		exec_val;
  char		next_val;
}		t_echo;

int	builtins(t_mini *, t_process *);
int	check_builtins(t_process *);
int	built_no_fork(t_process *, t_mini *);
int	my_cd(t_mini *, t_process *);
int	my_disown(t_mini *, t_process *);
char	*my_strcat_spe(char *, char *);
int	char_only(char *, char );
void	fill_new_cd(char *, char *);
int	my_fg(t_mini *, t_process *);
int	my_jobs(t_mini *, t_process *);
int	my_bg(t_mini *, t_process *);
int	my_echo(t_mini *, t_process *);
char	*get_var(t_mini *, t_process *, int , int *);
char	*clean_var(char *);
int	my_env(t_mini *, t_process *);
int	my_print_env(char **, int );
int	my_egal_env(t_mini *, t_process *);
int	test_var(char *);
int	help_env(t_mini *, char *, int *, int *);
int	null_env(t_mini *, char *, int *, int *);
int	reset_env(t_mini *, char *, int *, int *);
int	unset_env(t_mini *, char *, int *, int *);
int	my_add_at_env(t_mini *, char *);
void	add_str_end_env(t_mini *, char *);
void	remplace_str_in_env(t_mini *, char *, char *);
void	get_new_cmd(char *, int , char **);
int	get_new_size(int , char **);
int	my_exit(t_mini *, t_process *);
int	my_export(t_mini *, t_process*);
int	my_unset(t_mini *, t_process*);
int	my_source(t_mini *, t_process *);

#endif /* !BUILTINS_H_ */
