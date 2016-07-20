/*
** get_next_line.h for  in /home/fernan_w/Téléchargements/42sh/includes
** 
** Made by 
** Login   <fernan_w@epitech.net>
** 
** Started on  Thu Jun  2 23:23:38 2016 
** Last update Wed Jun  8 10:56:54 2016 
*/

#ifndef GET_NEXT_LINE_H_
# define GET_NEXT_LINE_H_

# define BUFFSIZE 42

typedef struct	s_fd
{
  char		*str;
  int		fd;
  struct s_fd	*next;
}		t_fd;

char	*get_next_line(const int);
char	*my_memset(char *, int);

#endif /* !GET_NEXT_LINE_H_ */
