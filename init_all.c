/*
** init_all.c for  in /home/fernan_w/Téléchargements/backup/start
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:03:04 2016
** Last update Wed Jun  8 09:36:58 2016 
*/

#include <unistd.h>
#include <stdlib.h>
#include "tools.h"
#include "shell.h"
#include "readline.h"
#include "my.h"

void	relaunch(int nb)
{
  (void)nb;
  tcsetpgrp(0, getpgrp());
}

char	**create_new_env(char **env)
{
  char	**tabs;
  int	index;
  int	count;

  index = 0;
  if (!(tabs = malloc(sizeof(char *) * (my_tablen(env) + 1))))
    return (NULL);
  while (env && env[index])
    {
      count = 0;
      if (!(tabs[index] = malloc(sizeof(char) * my_strlen(env[index]) + 1)))
	return (NULL);
      while (env[index][count])
	{
	  tabs[index][count] = env[index][count];
	  count++;
	}
      tabs[index++][count] = '\0';
    }
  tabs[index] = NULL;
  return (tabs);
}

static char	**create_default_env(void)
{
  char		**new;
  int		i;

  i = 0;
  if ((new = (char**)malloc(sizeof(char*) * 2)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  if (access("/usr/bin", X_OK) != -1 && access("/bin", X_OK) != -1)
    {
      if ((new[i] = my_strdup("PATH=/usr/bin:/bin")) == NULL)
	return (NULL);
      i += 1;
    }
  new[i] = NULL;
  return (new);
}

int	init_all(t_mini *elem, char **env)
{
  elem->is_env_exec = FAILURE;
  elem->secret_env = NULL;
  elem->need_exit = -1;
  if (env == NULL || env[0] == NULL)
    if ((env = create_default_env()) == NULL)
      return (FAILURE);
  if (!(elem->env = create_new_env(env)))
    return (FAILURE);
  elem->have_tty = isatty(0);
  elem->prompt = NULL;
  parse_rc_file(elem);
  return (SUCCESS);
}

void	reset_all(char **env, char **files_completition)
{
  restore_shell(files_completition);
  free_tab(env);
}
