#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
    int     i = 0;
    int     rd;
    char    c;
    char    *line = malloc(100000);
    
    if (BUFFER_SIZE <= 0)
    {
        free(line);
        return (NULL);
    }

    rd = read(fd, &c, BUFFER_SIZE - BUFFER_SIZE + 1);
    
    while (rd > 0)
    {
        line[i] = c;
        i++;
        if (c == '\n')
            break ;
        rd = read(fd, &c, BUFFER_SIZE - BUFFER_SIZE + 1);
    }
    
    line[i] =  '\0';
    
    if (rd == -1 || i == 0 || (!line[i - 1] && !rd))
    {
        free(line);
        return (NULL);
    }
    return(line);
}
