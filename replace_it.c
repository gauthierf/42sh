/*
** do_replacements.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:01:27 2016
** Last update Wed Jun  8 09:59:32 2016 
*/

#include <stdlib.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

static int	get_quote_mode(char *str)
{
  int		i;

  i = 0;
  while (str && str[i])
    {
      if ((str[i] == '"' || str[i] == '\'') && (i == 0 || str[i - 1] != '\\'))
	return (str[i]);
      i++;
    }
  return (-1);
}

static int	is_glob_str(char *str)
{
  int		i;
  int		j;
  const char	*glob_char;

  i = 0;
  glob_char = "*~?[]";
  while (str && str[i])
    {
      j = 0;
      while (glob_char[j] && str[i] != glob_char[j])
	j++;
      if (str[i] == glob_char[j])
	return (i);
      i++;
    }
  return (-1);
}

int	glob_and_replace(t_process *proc, t_mini *shell)
{
  int		i;
  int		quote_mode;

  i = 0;
  while (proc->cmd_argv && proc->cmd_argv[i])
    {
      if ((quote_mode = get_quote_mode(proc->cmd_argv[i])) != -1)
	replace_quotes(proc, &i, shell, quote_mode);
      else if (is_glob_str(proc->cmd_argv[i]) >= 0)
	{
	  if (put_glob(proc, &i) == FAILURE)
	    return (FAILURE);
	}
      else
	{
	  proc->cmd_argv[i] = replace_var_in_str(proc->cmd_argv[i], shell);
	  ++i;
	}
    }
  proc->cmd = replace_var_in_str(proc->cmd, shell);
  return (SUCCESS);
}
