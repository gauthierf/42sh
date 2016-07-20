/*
** get_historic.c for  in /home/fernan_w/Téléchargements/backup/readline
**
** Made by
** Login   <fernan_w@epitech.net>
**
** Started on  Thu Jun  2 23:13:49 2016
** Last update Wed Jun  8 10:44:19 2016 
*/

#include <stdlib.h>
#include "readline.h"
#include "tools.h"
#include "my.h"

char		*little_list_to_str(t_rd *list_read)
{
  t_rd		*tmp;
  char		*str;
  int		i;

  i = 0;
  tmp = list_read;
  if ((str = (char*)malloc(get_size_list(list_read) + 1)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  while (tmp)
    {
      str[i] = tmp->c;
      i += 1;
      tmp = tmp->next;
    }
  str[i] = 0;
  return (str);
}

int	is_cmd(char *str, int cur)
{
  int	i;

  if (cur > 0 && str[cur - 1] != ' ' && str[cur - 1] != '&'
      && str[cur - 1] != '|' && str[cur - 1] != ';')
    return (0);
  i = cur - 1;
  while (i > 0 && (str[i] == ' ' || str[i] == '\t'))
    i -= 1;
  if (i <= 0 || str[i] == '|' || str[i] == ';' || str[i] == '&')
    return (1);
  return (0);
}

char		*get_name_cmd(char *str)
{
  char		*this;
  int		i;
  char		tmp;

  i = 0;
  while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '|'
	 && str[i] != '&' && str[i] != ';')
    i += 1;
  tmp = str[i];
  str[i] = 0;
  if ((this = my_strdup(str)) == NULL)
    return (NULL);
  str[i] = tmp;
  return (this);
}

char	*search_last_cmd(char *str, t_histo *historic)
{
  char	*this_cmd;
  char	*here;
  char	*tmp;

  if ((this_cmd = get_name_cmd(str)) == NULL)
    return (NULL);
  if (historic)
    historic = historic->next;
  while (historic)
    {
      if (historic->list_read && (tmp = little_list_to_str(historic->list_read))
	  == NULL)
	return (NULL);
      if ((here = my_strstr(tmp, this_cmd))
	  && ((here != tmp && *(here - 1) != '!') || here == tmp))
	{
	  free(this_cmd);
	  return (here);
	}
      free(tmp);
      historic = historic->next;
    }
  free(this_cmd);
  return (str);
}

char	*replace_it(char *str, int cur, char *last_cmd)
{
  char	*new;
  int	i;
  int	j;

  if ((new = (char*)malloc(my_strlen(str) + my_strlen(last_cmd) + 3)) == NULL)
    return ((void*)(unsigned long)my_putstr("error: could not alloc\n", 1));
  i = 0;
  while (i < cur)
    {
      new[i] = str[i];
      i += 1;
    }
  j = 0;
  while (last_cmd[j])
    new[i++] = last_cmd[j++];
  j = cur;
  while (str[j] && str[j] != ' ' && str[j] != ';' && str[j] != '|'
	 && str[j] != '&' && str[j] != '\t')
    j += 1;
  while (str[j])
    new[i++] = str[j++];
  new[i] = 0;
  return (new);
}
