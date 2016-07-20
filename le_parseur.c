/*
** parser.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:57:53 2016
** Last update Wed Jun  8 09:37:44 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "readline.h"
#include "my.h"

int	go_to_end_cmd(char *str, int end)
{
  int	is_string;

  is_string = 0;
  while (str[end] && ((str[end] != ';' && str[end] != '|'
		       && str[end] != '&') || is_string == 1))
    {
      if (my_strncmp(str + end, "$(", 2) == 0 || str[end] == '`'
	  || str[end] == '\'')
	pass_var(str, &end);
      else
	{
	  if ((end > 0 && str[end] == '"' && str[end - 1] != '\\')
	      || (end == 0 && str[end] == '"'))
	    is_string += 1;
	  end += 1;
	}
    }
  return (end);
}

int	get_mode(char *str, char *mode)
{
  int	size;

  size = 1;
  mode[1] = 0;
  mode[2] = 0;
  mode[0] = str[0];
  if (str[0] && str[1] && (str[1] == '&' || str[1] == '|'))
    {
      mode[1] = str[1];
      size = 2;
    }
  return (size);
}

char	*get_this_cmd(char *str, int *i, char *mode)
{
  char	*cmd;
  char	tmp;
  int	end;

  end = 0;
  end = go_to_end_cmd(str, *i);
  tmp = str[end];
  str[end] = 0;
  if ((cmd = my_strdup(str + *i)) == NULL)
    return (NULL);
  str[end] = tmp;
  end += get_mode(str + end, mode);
  *i = end;
  return (cmd);
}

int		get_each_cmd(t_process **proc, char *str,  t_mini *shell,
			     char ***files_completition)
{
  t_process	*tmp_proc;
  char		mode[3];
  char		*tmp;
  int		i;
  int		size;

  i = 0;
  size = my_strlen(str) - 1;
  buf_zero(mode, 3);
  while (i <= size)
    {
      if ((tmp = get_this_cmd(str, &i, mode)) == NULL)
	return (-1);
      if ((push_proc(proc, tmp, mode, &tmp_proc)) == -1)
	return (-1);
      if ((get_redirections(tmp_proc, shell->env, files_completition)) == -1)
	return (-1);
      if ((get_args(tmp_proc, shell, files_completition)) == -1)
	return (-1);
    }
  return (0);
}

int	parser(char *str, t_process **proc, t_mini *shell,
	       char ***files_completition)
{
  int	check;

  if (is_bad_character(str))
    {
      my_putstr("bad caracters: ", 2);
      my_putstr(str, 2);
      return (my_putstr("\n", 2));
    }
  if (isatty(0) == 1)
    if ((str = complete_string(str, shell->env, files_completition)) == NULL)
      return (-1);
  if ((check = check_str(str)) == -1)
    return (-1);
  else if (check == 0)
    {
      if (isatty(0))
	return (0);
      return (-1);
    }
  if ((get_each_cmd(proc, str, shell, files_completition)) == -1)
    return (-1);
  return (0);
}
