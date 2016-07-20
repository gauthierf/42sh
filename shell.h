/*
** shell.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:29 2016 
** Last update Wed Jun  8 10:10:56 2016 
*/

#ifndef SHELL_H_
# define SHELL_H_

# include <signal.h>
# include "parser.h"

# define NOAPPEND	(O_RDWR | O_TRUNC | O_CREAT | O_CLOEXEC)
# define APPEND		(O_RDWR | O_APPEND | O_CREAT | O_CLOEXEC)
# define RIGHTS		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
# define OP_MODE(x)	((x) == 1) ? (APPEND) : (NOAPPEND)

# ifdef WCOREDUMP
#  define SHCOREDUMP(x)	(WCOREDUMP(x)) ? ("(core dumped)") : (" ")
# else
#  define SHCOREDUMP(x) (x) ? (" ") : (" ")
# endif /* !WCOREDUMP */

# define MYDIR		"."

typedef struct	s_dentifrice
{
  int		signal_num;
  char		*msg;
}		t_dentifrice;

typedef struct	s_opec
{
  char		*str;
  int		(*funct)(t_mini *, t_process *);
}		t_opec;

int		put_to_background(t_process *, int);
int		put_to_foreground(t_process *, char **);
void		report_signal(t_process *, int, int, int);
void		update_process_info(int, int);
int		close_all(t_process *);
void		check_jobs(int);
int		put_glob(t_process *, int *);
int		glob_and_replace(t_process *, t_mini *);
void		replace_quotes(t_process *, int *, t_mini *, int);
int		add_job(t_process *);
int		is_in_jobs_list(pid_t);
int		remove_job(pid_t);
void		report_stop(pid_t, int);
void		report_continuation(pid_t, int);
void		report_termination(pid_t, int);
int		pgid_alive(pid_t, pid_t);
void		print_sig_msg(t_process *, int, int);
int		inpath_execute(t_process *, t_mini *);
int		direct_execute(t_process *);
int		my_execute(t_process *, t_mini *);
void		set_all_signals(int);
int		my_loop_proc(int, t_process *, t_mini *);
int		set_redirections(t_process *);
char		*replace_var_in_str(char *, t_mini *);
void		free_proc(t_process *);
t_process	*proc_copy(t_process *);
t_process	*super_proc(t_process *);
char		**process_path(char **);
int		put_redirections(t_process *);
char		**create_new_env(char **);
int		init_all(t_mini *, char **);
void		reset_all(char **, char **);
void		relaunch(int);
char		*readline(int, char ***, char **);

#endif /* !SHELL_H_ */
