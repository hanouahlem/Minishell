#include "minishell.h"


// int	ft_envsize(t_env *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst)
// 	{
// 		lst = lst->next;
// 		i++;
// 	}
// 	return (i);
// }

// void    env_in_tab(t_mini *data)
// {
//     t_env   *tmp;
//     int     i;

//     data->exec = NULL;
//     tmp = data->env;
//     data->exec->env_exec = malloc(987654);
//     i = 0;
//     printf("Iciiiii\n\n");
//     while (tmp)
//     {
//         data->exec->env_exec[i] = tmp->content;
//         printf("env_exec[i] -> %s\n", data->exec->env_exec[i]);
//         i++;
//         tmp = tmp->next;
//     }
// }

void env_in_tab(t_mini *data)
{
    t_env   *tmp;
    int     i;
    int     env_size;

    tmp = data->env;
    env_size = 0;
    i = 0;
    if (!data->exec)
    {
        data->exec = malloc(sizeof(t_exec));
        if (!data->exec)
        {
            perror("malloc failed for data->exec");
            return;
        }
    }
    data->exec->env_exec = NULL;
    while (tmp)
    {
        env_size++;
        tmp = tmp->next;
    }
    if (data->exec->env_exec)
        free(data->exec->env_exec);
    data->exec->env_exec = malloc(sizeof(char *) * (env_size + 1));
    if (!data->exec->env_exec)
    {
        perror("malloc failed for data->exec->env_exec");
        return;
    }
    tmp = data->env;
    while (tmp)
    {
        data->exec->env_exec[i] = tmp->content;
        // printf("env_exec[i] -> %s\n", data->exec->env_exec[i]);
        i++;
        tmp = tmp->next;
    }
    data->exec->env_exec[i] = NULL;
}

void    print_exec_env(t_exec *exec)
{
    int i = 0;
    while (exec->env_exec[i])
    {
        printf("env_exec --> %s\n", exec->env_exec[i]);
        i++;
    }
}

// void    child_process(t_mini *data, t_parse *tab)
// {
//     if (access())
// }

int    init_exec(t_mini *data, t_parse *tab, int i)
{
    // int i;
    int j = 0;

    // i = 0;
    printf("size_cmd : %d\n", tab->size_cmd);
    (void)data;
    while (tab[i].filename && tab[i].filename[j])
    {
        printf("{%i}", tab[i].typefile[j]);
        printf("{%s}\n", tab[i].filename[j]);
        if (!tab[i].filename[j + 1] && (tab[i].typefile[j] == 2 || tab[i].typefile[j] == 0))
        {
            printf("infile : {%s}\n", tab[i].filename[j]);
            // data->exec->infile = open(tab[i].filename[j], O_RDONLY, 0777);
            // if (data->exec->infile == -1)
            //     return (printf("Open Fail !\n"), 1);
        }
        else if (!tab[i].filename[j + 1] && (tab[i].typefile[j] == 1 || tab[i].typefile[j] == 3))
        {
            printf("outfile : {%s}\n", tab[i].filename[j]);
            // data->exec->outfile = open(tab[i].filename[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            // if (data->exec->outfile == -1)
            //     return (printf("Open Fail !\n"), 1);
            break ;
        }
        if (tab[i].filename[j + 1])
            j++;
        // j++;
    }
    return (0);
}

int    ft_exec(t_mini *data, t_parse *tab, char *line)
{
    int i;

    i = 0;
    env_in_tab(data);
    (void)line;
    while (i < tab->size_cmd)
    {
        init_exec(data, tab, i);
        // if (pipe(data->exec->fd) == -1)
        // {
        //     perror("Pipe Error !\n");
        //     exit(EXIT_FAILURE);
        // }
        // data->exec->pid[i] = fork();
        // if (data->exec->pid[i] < 0)
        //     return (printf("Failed fork !\n"), 1);
        // if (data->exec->pid[i] == 0)
        // {
        //     // child_process(data, tab);
        // }
        i++;
    }
    if (data->exec->env_exec)
        free(data->exec->env_exec);
    return (0);
}
    // if (tab->size_cmd == 1)
    // {
        // if (pipe(data->exec->fd) == -1)
        // {
        //     perror("Pipe Error !\n");
		//     exit(EXIT_FAILURE);
        // }
        // data->exec->pid[i] = fork();
        // if (data->exec->pid[i] < 0)
        //     return (printf("Failed fork !\n"), 1);
        // if (data->exec->pid[i] == 0)
    //     {
    //         find_path(data, tab, tab->args[0]);
    //         if (tab->cmd && ft_built_in_comp(data, tab, line) == 1)
    //         {
    //             printf("tab->cmd : %s\n", tab->cmd);
    //         }
    //     }
    // }

// whoami == $USER
// <<infile1 <infile2 <infile3 cmd >outfile1>>outfile2