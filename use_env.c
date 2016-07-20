/*
** egal_env.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:53:03 2016
** Last update Wed Jun  8 10:02:38 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

int	test_var(char *str)
{
  int	index;
  int	egal;

  index = 0;
  egal = 0;
  while (str && str[index])
    {
      if (str[index] == '=')
	++egal;
      ++index;
    }
  if (egal != 1)
    {
      if (my_print_error("Error : invalid value\n") == FAILURE)
	return (FAILURE);
      return (FAILURE);
    }
  return (SUCCESS);
}

static void	while_env(char *temp, t_process *proc, int index)
{
  int		cursor;

  cursor = 0;
  while (cursor < index)
    {
      temp[cursor] = proc->cmd[cursor];
      cursor++;
    }
  temp[cursor] = '\0';
}

int		my_egal_env(t_mini *shell, t_process *proc)
{
  int		index;
  char		*temp;
  t_mini	shell_temp;

  index = 0;
  proc->status = 1;
  shell_temp.env = shell->secret_env;
  if (test_var(proc->cmd) == FAILURE)
    return (SUCCESS);
  while (proc->cmd && proc->cmd[index] && proc->cmd[index] != '=')
    index++;
  if (!(temp = malloc(sizeof(char) * (index + 1))))
    return (SUCCESS);
  while_env(temp, proc, index);
  if (find_str_in_tab(temp, shell->env))
    remplace_str_in_env(shell, proc->cmd, temp);
  else if (find_str_in_tab(temp, shell->secret_env))
    remplace_str_in_env(&shell_temp, proc->cmd, temp);
  else
    add_str_end_env(&shell_temp, proc->cmd);
  shell->secret_env = shell_temp.env;
  proc->status = 0;
  return (SUCCESS);
}
