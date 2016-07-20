/*
** readline.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:56 2016 
** Last update Wed Jun  8 09:02:12 2016 
*/

#ifndef READLINE_H_
# define READLINE_H_

# define TERM_BUF_SIZE	(4096)
# define SIZE_BUF	(10)
# define HISTORIC_SIZE	(15)

# include <term.h>

typedef struct		s_rd
{
  char			c;
  unsigned int		is_current;
  struct s_rd		*prev;
  struct s_rd		*next;
}			t_rd;

typedef struct		s_rdd
{
  struct s_histo	*historic;
  struct termios	term_attr;
  struct termios	term_attr_save;
  t_rd			*list_read;
  t_rd			*clipboard;
  char			**path;
  char			**env;
  char			*prompt;
  int			size_prompt;
  int			size_read;
  int			current;
  int			is_rm;
  int			is_completition;
  int			fd;
  char			*dir_cur;
}			t_rdd;

typedef struct		s_histo
{
  t_rd			*list_read;
  int			is_cur;
  struct s_histo	*prev;
  struct s_histo	*next;
}			t_histo;

typedef struct		s_completion
{
  char			*file;
  struct s_completion	*prev;
  struct s_completion	*next;
}			t_completion;

typedef struct		s_fct
{  char			str[7];
  int			(*function)(t_rdd *reader);
}			t_fct;

char		*replace_alias(char *, int, char *);
char		*replace_it(char *, int, char *);
char		*search_last_cmd(char *, t_histo *);
int		is_cmd(char *, int);
int		disp_possible_comp(t_rdd *, t_completion *);
int		disp_historic(t_histo *);
int		manage_signal(int, t_rdd *);
void		get_sigint(int);
int		init_termcaps(char **, struct termios *,  struct termios *);
char		*get_prompt(char **, char *, int *);
char		**get_path(char *);
char		**list_to_tab(t_completion *, int);
int		is_double(char *, t_completion *);
int		get_files(char **, t_completion **, int *);
void		buf_zero(char *, int);
int		clean_screen(t_rdd *);
int		completition(t_rdd *);
char		*cut_after_dir(char *);
char		*cut_before_dir(char *);
char		*cut_dir_cur(char *);
char		**cut_executable(char **);
char		*cut_word(char *);
int		past_clipboard(t_rdd *);
int		rm_after(t_rdd *);
int		rm_before(t_rdd *);
int		is_good_with_list(t_completion *, int);
void		rm_bad_name(t_completion **, char *);
t_completion	**rm_not_executable(char *, char *, t_completion **);
char		*check_if_slash(char *);
int		move_down_hist(t_rdd *);
int		move_up_hist(t_rdd *);
int		push_historic(t_histo **, t_rd *);
int		get_len_max(t_completion *);
int		get_size_completition(t_completion *);
void		free_completition(t_completion *);
char		*list_to_str(t_rd *, t_histo **);
int		get_size_list(t_rd *);
t_rd		*rm_in_list(t_rdd *, int);
t_rd		*create_read(char);
int		disp_list_read(t_rd *, int);
char		*read_line(int, char ***, char **, char *);
int		get_key(t_rdd *, char *);
int		init_shell(char **, struct termios *, struct termios *);
void		restore_shell(char **);
int		go_end(t_rdd *);
int		go_next_word(t_rdd *);
int		go_prev_word(t_rdd *);
int		go_start(t_rdd *);
int		get_char(t_rdd *, char *);
int		go_left(t_rdd *);
int		go_right(t_rdd *);
int		rm_cur(t_rdd *);
int		rm_left(t_rdd *);
int		my_putstr(char *, int);
int		my_putchar(char);
int		my_putnbr(int);
int		my_tputs(char *, int);
char		*get_complete_path(char *, char *);
char		*get_true_path(char *, char *, char **);
int		mod_directory(char *, t_completion *);
char		*list_to_word(t_rd *);
int		is_same_list(t_rd *, t_rd *);
int		push_at_place(t_rd *, char, int);
int		push_read(t_rd **, char, int);
void		reverse_str(char *);
char		*search_in_env(char **, char *);
int		push_completition(t_completion **, char *);
int		search_var_env(char **, t_completion **, char *);
int		complete_history(t_rdd *, char *, char *);
char		*get_word_current(t_rdd *);
int		disp_possible_comp(t_rdd *, t_completion *);
int		is_char_completition(char);
int		is_not_first_word(t_rdd *);
int		rm_or_quit(t_rdd *);
int		is_multiline(t_rdd *);
int		rm_left_without_change_line(t_rdd *);
int		line_up(void);
int		line_down(int);

#endif /* !READLINE_H_ */
