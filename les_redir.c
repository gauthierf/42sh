/*
** get_redirections.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:57:03 2016
** Last update Wed Jun  8 10:15:33 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "readline.h"
#include "tools.h"
#include "my.h"

static char	*get_redi_file(char *str, int *is_double)
{
  char		*file;
  char		tmp;
  int		i;
  int		j;

  i = 0;
  if (str[0] == '>' || str[0] == '<')
    {
      i += 1;
      *is_double = 1;
    }
  while (str[i] && str[i] == ' ')
    i += 1;
  j = i;
  while (str[i] && str[i] != ' ' && str[i] != '|' && str[i] != '&'
	 && str[i] != ';')
    i += 1;
  tmp = str[i];
  str[i] = 0;
  if ((file = my_strdup(str + j)) == NULL)
    return (NULL);
  str[i] = tmp;
  return (file);
}

static int	search_redi_right(t_process *proc)
{
  char		*redi;
  int		is_double;
  int		i;

  i = 0;
  while (proc->cmd[i])
    {
      is_double = 0;
      pass_var(proc->cmd, &i);
      if (proc->cmd[i] == '>')
      {
	if ((redi = get_redi_file(proc->cmd + i + 1, &is_double)) == NULL)
	  return (-1);
	if ((push_output(&(proc->output), redi, is_double, 0)) == -1)
	  return (-1);
	i = (proc->cmd[i + 1] == '>') ? (i + 2) : (i);
      }
      if (proc->cmd[i])
	i += 1;
    }
  return (0);
}

static char	*get_double_left(char *redi, char **env, char ***files_comp)
{
  char		*tmp;
  char		*str;
  int		loop;

  str = NULL;
  loop = 0;
  tmp = "";
  while (tmp != NULL && is_same_strings(str, redi) == 0 && loop++ < 100)
    {
      if (is_bad_character(str))
	return (str);
      tmp = read_line(0, files_comp, env, "> ");
      if ((str = realloc_me_that(str, tmp)) == NULL)
	return (NULL);
      if (my_strcmp(str, redi) == 0)
	{
	  str[0] = 0;
	  break ;
	}
      if (isatty(0) != 1)
	loop = 100;
    }
  if (tmp)
    str = rm_good_string(str);
  return (str);
}

static int	search_redi_left(t_process *proc, char **env,
				 char ***files_comp, int is_double)
{
  char		*redi;
  int		i;
  char		*str;

  i = 0;
  while (proc->cmd[i])
    {
      is_double = 0;
      pass_var(proc->cmd, &i);
      if ((proc->cmd[i] == '<' && proc->cmd[i + 1] != '<') &&
	  (((redi = get_redi_file(proc->cmd + i + 1, &is_double)) == NULL)
	   || ((push_input(&(proc->input), redi, NULL, 0)) == -1)))
	return (-1);
      if ((proc->cmd[i] == '<' && proc->cmd[i + 1] == '<') &&
	  (((redi = get_redi_file(proc->cmd + ++i + 1, &is_double)) == NULL)
	   || ((str = get_double_left(redi, env, files_comp)) == NULL)
	   || ((push_input(&(proc->input), NULL, str, 0)) == -1)))
	return (-1);
      if (proc->cmd[i])
	i += 1;
    }
  return (0);
}

int	get_redirections(t_process *proc, char **env,
			 char ***files_completition)
{
  if ((search_redi_right(proc)) == -1)
    return (-1);
  if ((search_redi_left(proc, env, files_completition, 0)) == -1)
    return (-1);
  clean_redirections(proc->cmd);
  return (0);
}
