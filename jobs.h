/*
** jobs.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:07 2016 
** Last update Wed Jun  8 10:14:44 2016 
*/

#ifndef JOBS_H_
# define JOBS_H_

# include "shell.h"
# include "tools.h"

# define STOPPED	(10)
# define RUNNING	(11)

# define OUT_IS_PIPE(p)	((p) && (p->output) && (p->output->is_pipe == SUCCESS))

typedef struct		s_background
{
  t_process		*frontjob;
  t_process		**active_jobs;
  int			active_jobs_count;
  int			max_job_count;
}			t_background;

t_background		g_background;

#endif /* !JOBS_H_ */
