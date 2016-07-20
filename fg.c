/*
** fg.c for  in /home/fernan_w/Téléchargements/backup/builtins
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:53:26 2016
** Last update Wed Jun  8 09:25:14 2016 
*/

#include <unistd.h>
#include "builtins.h"
#include "jobs.h"
#include "my.h"

static int	my_print_error_fg(char *str, char *name, t_process *proc)
{
  proc->status = 1;
  if ((my_print_error(str, name)) == -1)
    return (FAILURE);
  return (SUCCESS);
}

static int	fg_solo()
{
  if (g_background.active_jobs_count > 0
      && g_background.active_jobs[g_background.active_jobs_count - 1])
    return (g_background.max_job_count - 1);
  else
    my_print_error("fg: please specify a job_id\n");
  return (-1);
}

static int	my_baby_fg(t_mini *shell, t_process *proc)
{
  int		job_id;

  job_id = -1;
  proc->status = 0;
  if (g_background.active_jobs_count == 0)
    return (my_print_error_fg("fg: no jobs to resume\n", NULL, proc));
  if (!(proc->cmd_argv[1]))
    job_id = fg_solo();
  else if (proc->cmd_argv[1] && ((job_id = my_getnbr(proc->cmd_argv[1])) < 0
				 || job_id >= g_background.max_job_count
				 || !(g_background.active_jobs[job_id])))
    return (my_print_error_fg("42sh: no such job [%s]\n",
			      proc->cmd_argv[1], proc));
  if (job_id > -1 && job_id < g_background.max_job_count)
    {
      if (put_to_foreground(g_background.active_jobs[job_id],
			    shell->env) == FAILURE)
	return (my_print_error_fg("fg: putting to foreground failed\n",
				  NULL, proc));
    }
  return (SUCCESS);
}

int	my_fg(t_mini *shell, t_process *proc)
{
  if (isatty(0) && isatty(1))
    return (my_baby_fg(shell, proc));
  else
    my_print_error("fg: no job control in this shell\n");
  proc->status = 1;
  return (SUCCESS);
}
