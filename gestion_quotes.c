/*
** replace_quotes.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:00:24 2016
** Last update Wed Jun  8 09:36:04 2016 
*/

#include <stdlib.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

char	*move_over(char *str, int i)
{
  if (!(str = realloc(str, my_strlen(str))))
    return (NULL);
  while (str && str[i])
    {
      str[i] = str[i + 1];
      ++i;
    }
  return (str);
}

char	*destroy_quotes(char *str, char quote)
{
  int	i;

  i = 0;
  while (str && str[i])
    {
      if (str && str[i] && str[i] == quote && (i == 0 || str[i - 1] != '\\'))
	str = move_over(str, i--);
      ++i;
    }
  return (str);
}

void	replace_quotes(t_process *proc, int *i, t_mini *shell, int quote_mode)
{
  proc->cmd_argv[*i] = destroy_quotes(proc->cmd_argv[*i], quote_mode);
  if (quote_mode == '"')
    proc->cmd_argv[*i] = replace_var_in_str(proc->cmd_argv[*i], shell);
  ++(*i);
}
