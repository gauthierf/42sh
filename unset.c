/*
** unset.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:55:13 2016
** Last update Wed Jun  8 10:02:03 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

static int	unset_in_shell(t_mini *shell, char *str)
{
  int		val;

  if (!(find_str_in_tab(str, shell->env)))
    return (FAILURE);
  unset_env(shell, str, &val, &val);
  return (SUCCESS);
}

static int	unset_in_secret_tab(t_mini *shell, char *str)
{
  t_mini	shell_temp;
  int		val;

  if (!(find_str_in_tab(str, shell->secret_env)))
    return (FAILURE);
  shell_temp.env = shell->secret_env;
  unset_env(&shell_temp, str, &val, &val);
  return (SUCCESS);
}

int	my_unset(t_mini *shell, t_process *proc)
{
  int	index;

  proc->status = 1;
  if (!proc->cmd_argv || !proc->cmd_argv[1])
    {
      my_print_error("unset: not enough arguments\n");
      return (SUCCESS);
    }
  index = 1;
  while (proc && proc->cmd_argv && proc->cmd_argv[index])
    {
      if ((unset_in_secret_tab(shell, proc->cmd_argv[index])) == FAILURE)
	if ((unset_in_shell(shell, proc->cmd_argv[index])) == FAILURE)
	  return (SUCCESS);
      index++;
    }
  proc->status = 0;
  return (SUCCESS);
}
