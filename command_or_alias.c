/*
** get_real_command.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:00:52 2016
** Last update Wed Jun  8 09:31:50 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "tools.h"
#include "my.h"

int	direct_execute(t_process *proc)
{
  if (access_test_exe(proc->cmd) == FAILURE)
    return (FAILURE);
  proc->path_cmd = my_strdup(proc->cmd);
  return (SUCCESS);
}

int	inpath_execute(t_process *proc, t_mini *shell)
{
  int	i;
  char	*tmp;
  char	**tmp_path;

  i = 0;
  proc->path_cmd = NULL;
  if (!(tmp_path = process_path(shell->env)))
    return (FAILURE);
  while (tmp_path[i] && proc->cmd && !(proc->path_cmd))
    {
      if (access((tmp = my_append(tmp_path[i], proc->cmd)), X_OK) == 0)
        proc->path_cmd = tmp;
      else if (access(tmp, F_OK) == 0)
	return (my_print_error("%s: permission denied\n", proc->cmd));
      else
	free(tmp);
      i++;
    }
  free_tab(tmp_path);
  return (SUCCESS);
}
