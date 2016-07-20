/*
** export.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:51:50 2016
** Last update Wed Jun  8 09:34:43 2016 
*/

#include <stdlib.h>
#include "builtins.h"
#include "tools.h"
#include "my.h"

static void	find_my_var(t_mini *shell, char *str, int *val, int *index)
{
  int		count;
  char		*temp;
  int		cursor;

  while (shell->secret_env && shell->secret_env[*index] && *val == 0)
    {
      count = 0;
      while (shell->secret_env[*index][count]
	     && shell->secret_env[*index][count] != '=')
	count++;
      if (!(temp = malloc(sizeof(char) * (count + 1))))
	return ;
      cursor = 0;
      while (cursor < count)
	{
	  temp[cursor] = shell->secret_env[*index][cursor];
	  cursor++;
	}
      temp[cursor] = '\0';
      if (my_strcmp(temp, str) == 0)
	*val += 1;
      else
	*index += 1;
      free(temp);
    }
}

static void	export_one_in_env(t_mini *shell, char *str)
{
  int		index;
  int		val;
  t_mini	shell_temp;

  val = 0;
  index = 0;
  find_my_var(shell, str, &val, &index);
  if (val == 1)
    {
      add_str_end_env(shell, shell->secret_env[index]);
      shell_temp.env = shell->secret_env;
      unset_env(&shell_temp, str, &val, &val);
      shell->secret_env = shell_temp.env;
    }
}

static void	export_all_in_env(t_mini *shell)
{
  int		index;

  index = 0;
  while (shell->secret_env && shell->secret_env[index])
    add_str_end_env(shell, shell->secret_env[index++]);
  free_tab(shell->secret_env);
  shell->secret_env = NULL;
}

int	my_export(t_mini *shell, t_process *proc)
{
  int	index;

  if (!proc || !proc->cmd_argv || !proc->cmd_argv[1])
    {
      export_all_in_env(shell);
      my_print_env(shell->env, SUCCESS);
      return (SUCCESS);
    }
  index = 1;
  while (proc && proc->cmd_argv && proc->cmd_argv[index])
    {
      if (is_in_str(proc->cmd_argv[index], '=') == SUCCESS)
	{
	  if (my_add_at_env(shell, proc->cmd_argv[index]) == FAILURE)
	    return (SUCCESS);
	}
      else
	export_one_in_env(shell, proc->cmd_argv[index]);
      index++;
    }
  return (SUCCESS);
}
