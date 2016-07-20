/*
** parser.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:20 2016 
** Last update Wed Jun  8 10:48:47 2016 
*/

#ifndef PARSER_H_
# define PARSER_H_

# include <sys/types.h>

typedef struct			s_input
{
  char				*file;
  char				*heredoc;
  int				is_pipe;
  struct s_input		*next;
}				t_input;

typedef struct			s_output
{
  char				*file;
  int				append_or_not;
  int				is_pipe;
  struct s_output		*next;
}				t_output;

typedef struct			s_mini
{
  char				**env;
  char				**env_exec;
  char				**secret_env;
  char				*prompt;
  char				**prompt_plugins;
  int				have_tty;
  int				need_exit;
  int				is_env_exec;
}				t_mini;

typedef struct			s_process
{
  char				*cmd;
  char				**cmd_argv;
  char				*path_cmd;
  pid_t				pid;
  pid_t				pgid;
  int				outfd;
  int				infd;
  int				mode;
  int				status;
  int				disowned;
  int				is_builtin;
  t_output			*output;
  t_input			*input;
  struct s_process		*next;
  struct s_process		*prev;
}				t_process;

# define IF_OK			(1)
# define IF_ERR			(2)
# define BACKGROUND		(3)

int		do_the_job_son(int[2], t_mini *, t_process *);
char		**remake_argv(t_process *, int, char *);
void		count_var(char *, int *);
void		count_quote(char *, int *);
void		pass_var(char *, int *);
int		check_str(char *);
void		rm_quotes(char *, int);
int		interprete_args(t_process *, t_mini *, char ***);
void		clean_redirections(char *);
void		clean_this_redirection(char *);
int		get_redirections(t_process *, char **, char ***);
char		*clean_str(char *);
int		is_bad_character(char *);
int		get_args(t_process *, t_mini *, char ***);
char		*get_this_cmd(char *, int *, char *);
int		get_mode(char *, char *);
int		go_to_end_cmd(char *, int);
int		parser(char *, t_process **, t_mini *, char ***);
int		push_proc(t_process **, char *, char *, t_process **);
int		push_output(t_output **, char *, int, int);
int		push_input(t_input **, char *, char *, int);
char		*realloc_me_that(char *, char *);
char		*rm_good_string(char *);
int		is_same_strings(char *, char *);
char		*complete_string(char *, char **, char ***);
t_process	*go_next(t_process *, int);
int		my_exit_in_main(t_process *, int);

#endif /* !PARSER_H_ */
