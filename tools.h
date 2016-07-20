/*
** tools.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:24:05 2016 
** Last update Wed Jun  8 08:49:42 2016 
*/

#ifndef TOOLS_H_
# define TOOLS_H_

# define SUCCESS	1
# define FAILURE	0

# ifdef GLOB_TILDE
#  define MYGLOBFLAG	(GLOB_TILDE)
# else
#  define MYGLOBFLAG	(0)
# endif /* !GLOB_TILDE */

# define ABS(x) ((x) < 0) ? -(x) : (x)

# define RC_FILELOC	".42shrc"

#include "shell.h"

typedef struct	s_ps
{
  char		*str;
  int		len;
}		t_ps;

typedef struct	s_prcode
{
  char		code;
  char		*var;
  char		*(*funct)(char *, t_mini *);
}		t_prcode;

char	*alias(char *, int);
int	check_alias(char *);
int	access_test_exe(char *);
int	append_file_to_fd(char *, int);
char	*find_str_in_tab(char *, char **);
char	**my_tab_copy(char **);
void	free_tab(char **);
int	is_in_str(char *, char );
char	*my_append(char *, char *);
int	append_one_char(t_ps *, char, int *);
int	my_getnbr(char *);
int	count_prints();
int	my_count_putchar(char, int);
int	my_count_putstr(char *, int);
int	my_count_putnbr_base(unsigned int, char *, int);
int	chop_chop_count(unsigned int, int, char *, int);
int	my_count_put_nbr(int, int);
int	my_print_error(const char *, ...);
int	my_printf(const char *, ...);
int	my_put_hex(unsigned int, char, int);
int	my_put_ptr(unsigned int, int);
int	my_putstr_weird(char *, int);
int	my_put_unsigned_nbr(unsigned int, int);
int	print_modified_count(char, int);
char	*str_cat(char *, char *);
int	my_strcmp(char *, char *);
char	*my_strdup(const char *);
int	my_strlen(char *);
int	my_strncmp(char *, char *, int);
char	*my_strstr(char *, char *);
char	**my_str_to_wordtab_dir(char *);
char	**my_str_to_wordtab(char *);
void	my_swap_str(char **, char **);
int	my_tablen(char **);
char	*my_str_copy(char *, int);
int	have_var(char *);
char	*prompt_script(char *, t_mini *);
t_ps	*put_prompt(char *, t_mini *);
char	*get_username(char *, t_mini *);
char	*get_hostname(char *, t_mini *);
char	*prompt_get_wd(char *, t_mini *);
char	*prompt_kw_char(char *, t_mini *);
char	*get_homedir();
int	parse_rc_file(t_mini *);
char	*prompt_mini_wd(char *, t_mini *);

#endif /* !TOOLS_H_ */
