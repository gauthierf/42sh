/*
** add_and_remove.c for  in /home/fernan_w/Téléchargements/backup/process
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 22:59:21 2016
** Last update Wed Jun  8 10:06:41 2016 
*/

#include <stdlib.h>
#include "jobs.h"
#include "my.h"

int	add_job(t_process *proc)
{
  int	i;

  i = 0;
  while (i < g_background.max_job_count)
    {
      if (!(g_background.active_jobs[i]))
	{
	  g_background.active_jobs_count++;
	  g_background.active_jobs[i] = proc;
	  return (i);
	}
      i++;
    }
  g_background.active_jobs_count++;
  g_background.max_job_count++;
  if (!(g_background.active_jobs = realloc(g_background.active_jobs,
					   sizeof(t_process *) *
				       (g_background.max_job_count + 1))))
    return (-1);
  g_background.active_jobs[i] = proc;
  return (i);
}

static int	get_biggest_job()
{
  int		i;
  int		max;

  i = 0;
  max = 0;
  while (g_background.active_jobs && i < g_background.max_job_count - 1)
    {
      if (g_background.active_jobs[i])
	max = i;
      i++;
    }
  return (max);
}

int	is_in_jobs_list(pid_t pid)
{
  int	i;

  i = 0;
  while (i < g_background.max_job_count)
    {
      if (g_background.active_jobs[i]
	  && g_background.active_jobs[i]->pid == pid)
	return (i);
      i++;
    }
  return (-1);
}

int	remove_job(pid_t pid)
{
  int	job_id;

  if ((job_id = is_in_jobs_list(pid)) == -1)
    return (-1);
  g_background.active_jobs[job_id] = NULL;
  g_background.active_jobs_count--;
  if (job_id == g_background.max_job_count - 1)
    {
      g_background.max_job_count = get_biggest_job();
      if (!(g_background.active_jobs =
	    realloc(g_background.active_jobs,
		    sizeof(t_process *) * (g_background.max_job_count + 1))))
	return (-1);
    }
  return (job_id);
}
