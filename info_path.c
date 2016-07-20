/*
** about_path.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:13:39 2016
** Last update Wed Jun  8 10:53:06 2016 
*/

#include <stdlib.h>
#include <dirent.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

int	is_double(char *file, t_completion *list)
{
  while (list)
    {
      if (my_strcmp(list->file, file) == 0)
	return (1);
      list = list->next;
    }
  return (0);
}

int		get_files(char **tab_c, t_completion **list, int *nb)
{
  struct dirent	*res;
  DIR		*dir;
  int		i;

  i = 0;
  while (tab_c[i])
    {
      dir = opendir(tab_c[i]);
      while (dir && (res = readdir(dir)))
	{
	  if (my_strcmp(res->d_name, ".") != 0
	      && is_double(res->d_name, *list) == 0)
	    {
	      if ((push_completition(list, res->d_name)) == -1)
		return (-1);
	      (*nb) += 1;
	    }
	}
      closedir(dir);
      i += 1;
    }
  return (0);
}

char	**list_to_tab(t_completion *list, int nb_files)
{
  char	**tab_c;
  int	i;
  int	j;

  if ((tab_c = (char**)malloc(sizeof(*tab_c) * (nb_files + 1))) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  i = 0;
  while (list)
    {
      j = 0;
      if ((tab_c[i] = (char*)malloc(my_strlen(list->file) + 1)) == NULL)
	return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
      while (list->file[j])
	{
	  tab_c[i][j] = list->file[j];
	  j += 1;
	}
      tab_c[i][j] = 0;
      i += 1;
      list = list->next;
    }
  tab_c[i] = NULL;
  return (tab_c);
}

void			free_list_completition(t_completion *list,
					       char **tab_c)
{
  t_completion		*to_rm;
  int			i;

  while (list)
    {
      to_rm = list;
      list = list->next;
      free(to_rm->file);
      free(to_rm);
    }
  i = 0;
  while (tab_c && tab_c[i])
    {
      free(tab_c[i]);
      i += 1;
    }
  free(tab_c[i]);
  free(tab_c);
}

char			**get_path(char *path)
{
  t_completion		*list;
  char			**tab_c;
  char			**files;
  int			nb_files;

  list = NULL;
  nb_files = 0;
  if ((tab_c = my_str_to_wordtab_dir(path)) == NULL)
    return (NULL);
  if ((get_files(tab_c, &list, &nb_files)) == -1)
    return (NULL);
  if ((files = list_to_tab(list, nb_files)) == NULL)
    return (NULL);
  free_list_completition(list, tab_c);
  return (files);
}
