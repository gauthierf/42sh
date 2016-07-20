/*
** job_son_underground.c for  in /home/fernan_w/Téléchargements/backup/parser
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:58:20 2016
** Last update Wed Jun  8 09:36:29 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "tools.h"
#include "builtins.h"
#include "shell.h"
#include "readline.h"
#include "shell.h"
#include "my.h"

static int	loop_underground(t_process *proc, t_mini *shell)
{
  int		nb;

  nb = SUCCESS;
  while (proc && nb == SUCCESS)
    {
      if ((nb = my_execute(proc, shell)) == FAILURE)
	my_print_error("42sh : command not found: %s\n", proc->cmd);
      proc = go_next(proc, nb);
    }
  return (0);
}

int	do_the_job_son(int pipefd[2], t_mini *shell, t_process *proc)
{
  if ((close(pipefd[0])) == -1)
    return (my_putstr("error: close pipe\n", 2));
  if ((dup2(pipefd[1], 1)) == -1)
    return (my_putstr("error: dup2\n", 2));
  loop_underground(proc, shell);
  if ((write(1, "\0", 1)) == -1)
    return (-1);
  if ((close(pipefd[1])) == -1)
    return (my_putstr("error: close pipe\n", 2));
  return (-1);
}
