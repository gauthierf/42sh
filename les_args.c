/*
** get_args.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:56:29 2016
** Last update Wed Jun  8 10:03:42 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "shell.h"
#include "my.h"

static int	count_args(char *s, int size)
{
  int		i;
  int		is_string;
  int		n;

  n = 0;
  i = 0;
  while (s[i] && i < size)
    {
      is_string = 0;
      while (s[i] && (s[i] == ' ' || s[i] == '\t'))
	i += 1;
      if ((!(my_strncmp(s + i, "$(", 2)) || s[i] == '`' || s[i] == '\'') && ++n)
	pass_var(s, &i);
      else
	{
	  while (s[i] && ((s[i] != ' ' && s[i] != '\t' ) || is_string == 1))
	    is_string = ((s[i++] == '"') ? (is_string + 1) : (is_string));
	  if ((i > 0 && (s[i - 1] != ' ' && s[i - 1] != '\t'))
	      || (i == 0 && s[i] != ' ' && s[i] != '\t'))
	    n += 1;
	}
    }
  return (n);
}

static char	*get_this_arg(char *str, int *cur)
{
  char		*new;
  int		i;
  int		is_string;
  char		tmp;

  is_string = 0;
  i = 0;
  if (my_strncmp(str, "$(", 2) == 0 || str[i] == '`' || str[i] == '\'')
    pass_var(str, &i);
  else
    {
      while (str[i] && ((str[i] != ' ' && str[i] != '\t') || is_string == 1))
	{
	  if (str[i] == '"')
	    is_string += 1;
	  i += 1;
	}
    }
  tmp = str[i];
  str[i] = 0;
  if ((new = my_strdup(str)) == NULL)
    return (NULL);
  str[i] = tmp;
  *cur = *cur + i + 1;
  return (new);
}

static int	save_args(char **args, char *str, int nb_args)
{
  int		i;
  int		nb;
  int		size;

  i = 0;
  nb = 0;
  size = my_strlen(str);
  while (i < size && nb < nb_args)
    {
      while (str[i] && (str[i] == ' ' || str[i] == '\t') && str[i] != '"')
	i += 1;
      if ((args[nb] = get_this_arg(str + i, &i)) == NULL)
	return (-1);
      nb += 1;
    }
  args[nb] = NULL;
  return (0);
}

static char	**str_to_args(char *s)
{
  char		**args;
  int		nb_args;

  nb_args = count_args(s, my_strlen(s));
  if ((args = (char**)malloc(sizeof(char*) * (nb_args + 1))) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  if ((save_args(args, s, nb_args)) == -1)
    return (NULL);
  args[nb_args] = NULL;
  return (args);
}

int	get_args(t_process *proc, t_mini *shell, char ***files_completition)
{
  char	*to_rm;
  char	**tmp;

  tmp  = NULL;
  to_rm = proc->cmd;
  if ((tmp = str_to_args(proc->cmd)) == NULL)
    return (-1);
  proc->cmd_argv = tmp;
  if (my_strlen(tmp[0]) > 0 && (proc->cmd = my_strdup(tmp[0])) == NULL)
    return (-1);
  else if (my_strlen(tmp[0]) == 0)
    if ((proc->cmd = my_strdup("")) == NULL)
      return (-1);
  free(to_rm);
  if ((interprete_args(proc, shell, files_completition)) == -1)
    return (-1);
  return (0);
}
