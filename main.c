/*
** main.c for  in /home/fernan_w/Téléchargements/.test/src
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Sun Jun  5 15:28:03 2016
** Last update Wed Jun  8 13:13:39 2016 
*/

#include <stdlib.h>
#include <unistd.h>
#include "tools.h"
#include "readline.h"
#include "builtins.h"
#include "my.h"

t_process      	*go_next(t_process *proc, int nb)
{
  int		status;

  (void)nb;
  status = proc->status;
  if ((proc->mode == IF_OK && status != 0)
       || (proc->mode == IF_ERR && status == 0))
    {
      while (proc && ((proc->mode == IF_OK && status != 0)
		      || (proc->mode == IF_ERR && status == 0)))
	proc = super_proc(proc);
      return (super_proc(proc));
    }
  else
    proc = super_proc(proc);
  return (proc);
}

int		my_exit_in_main(t_process *proc, int nb)
{
  t_process	*temp;

  while (proc)
    {
      temp = proc->next;
      free(proc);
      proc = temp;
    }
  return (nb);
}

int	my_loop_proc(int nb, t_process *proc, t_mini *shell)
{
  while (proc)
    {
      if (glob_and_replace(proc, shell) != SUCCESS)
	{
	  my_print_error("42sh: no matches found\n");
	  if (isatty(0))
	    return (-1);
	  return (0);
	}
      if ((nb = my_execute(proc, shell)) == FAILURE)
	if ((my_print_error("42sh : command not found: %s\n", proc->cmd)) == -1
	    || !(isatty(0)))
	  return (0);
      if (shell->need_exit >= 0)
	return (shell->need_exit);
      check_jobs(0);
      proc = go_next(proc, nb);
    }
  return (-1);
}

static int	my_loop(t_mini *shell, char ***files_comp, int nb, char *str)
{
  t_ps		*ps1;
  t_process	*proc;

  while (42)
    {
      nb = SUCCESS;
      proc = NULL;
      if (signal(SIGCHLD, &check_jobs) == SIG_ERR)
	return (FAILURE);
      my_printf("$>");
      if (!(ps1 = put_prompt(shell->prompt, shell))
	  || !(str = read_line(0, files_comp, shell->env, ps1->str))
	  || (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
	  || parser(str, &(proc), shell, files_comp) == -1)
	return (FAILURE);
      free(str);
      free(ps1->str);
      free(ps1);
      if ((nb = my_loop_proc(nb, proc, shell)) >= 0)
	return (nb);
      if (isatty(0) && tcsetpgrp(0, getpgrp()) == -1)
	return (my_print_error("42sh: tcsetgrp failed\n"));
    }
}

int		main(int ac, char **av, char **env)
{
  int		nb;
  t_mini	ft;
  static char	**files_completition;

  nb = 1;
  (void)av;
  (void)ac;
  if (isatty(0))
    {
      signal(SIGINT, SIG_IGN);
      signal(SIGQUIT, SIG_IGN);
      signal(SIGTSTP, SIG_IGN);
      signal(SIGTTIN, SIG_IGN);
      signal(SIGTTOU, SIG_IGN);
      signal(SIGCONT, &relaunch);
      if (tcsetpgrp(0, getpgrp()) == -1)
      	return (FAILURE);
    }
  if (init_all(&ft, env) == FAILURE)
    return (FAILURE);
  nb = my_loop(&ft, &files_completition, nb, "");
  reset_all(ft.env, files_completition);
  return (nb);
}
