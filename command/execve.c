#include "ft_minishell.h"
/*t_list_pid	*ft_create_elem(pid_t *data,int size)
{
	t_list_pid	 *elem;

	elem = (t_list_pid *)malloc(sizeof(t_list_pid));
	elem->pid = data;
	elem->size=size;
	elem->next = 0;
	return (elem);
}

void	ft_list_clear_wait(t_list_pid *begin_list)
{
	t_list_pid	*elem;
	int	status;
	while (begin_list)
	{
		while(begin_list->size>=0)
			waitpid(begin_list->pid[begin_list->size--],&status,0);
		elem = begin_list->next;
		free(begin_list->pid);
		free(begin_list);
		begin_list = elem;
	}
}
void	ft_list_push_front(t_list_pid *begin_list, pid_t *data,int size)
{
	t_list_pid *elem;

	if (begin_list != 0)
	{
		elem = ft_create_elem(data,size);
		elem->next = begin_list;
		begin_list = elem;
	}
	else
		begin_list = ft_create_elem(data,size);
}*/
t_command_and_flag	*ft_create_elem(t_command_and_flag *data)
{
	t_command_and_flag	 *elem;
	int i;

	i = 0;
	elem = (t_command_and_flag *)malloc(sizeof(t_command_and_flag));
	elem->pape=data->pape;
	elem->f_error=data->f_error;
	elem->command = ft_strdup(data->command);
	while(data->array_flags[i])
		i++;
	elem->array_flags=malloc(sizeof(char*)*(i+1));
	i=-1;
	while(data->array_flags[++i])
		elem->array_flags[i]=ft_strdup(data->array_flags[i]);
	elem->array_flags[i]=NULL;
	elem->next = 0;
	return (elem);
}
void	ft_list_push_front(t_command_and_flag **begin_list, t_command_and_flag *data)
{
	t_command_and_flag *elem;

	if (begin_list != 0)
	{
		elem = ft_create_elem(data);
		elem->next = *begin_list;
		*begin_list = elem;
	}
	else
		*begin_list = ft_create_elem(data);
}

void ft_list_clear(t_command_and_flag *command)
{
    int i;
    t_command_and_flag *tmp;

    while(command)
    {
		if(!command->f_error)
        free(command->command);
        i = 1;
       	while(command->array_flags[i])
        {
            free(command->array_flags[i]);
            i++;
        }
        free(command->array_flags);
        tmp = command->next;
        free(command);
        command = tmp;
    }
}
pid_t test(t_command_and_flag *all,int *pipe_1,int *pipe_2,int fd, char **env)
{
	
	if(pipe_2!=0)
		pipe(pipe_2);
	pid_t pid=fork();
	if(!pid)
	{
		if(pipe_1!=0)
		{
			dup2(pipe_1[1],1);
			close(pipe_1[1]);
			close(pipe_1[0]);//add function close_fd -5 lines
		}
		if(pipe_2!=0)
		{
			dup2(pipe_2[0],0);
			close(pipe_2[1]);
			close(pipe_2[0]);
		}
		if(fd)
		{	
			dup2(fd,1);
			close(fd);
		}
		execve(all->command,all->array_flags,env);
	}
	if(pipe_1!=0)
	{
		close(pipe_1[1]);
		close(pipe_1[0]);
	}
	return(pid);
}
t_command_and_flag *number_of_pipes(int *size,t_command_and_flag **head1,t_command_and_flag **new_head)
{
	//1 | 2 > 3 >> 4 < 5; 6 eof
	t_command_and_flag *head;

	head=*head1;
	*size=0;
	if(head->pape==2)
		*size=-1;
	ft_list_push_front(new_head,head);
	if(!head->f_error)
		head=head->next;
	else
	{
		*size=-1;
		return head->next;
	}
	while(head)
	{
		if(head->f_error)
			return(head);
		if(head->pape==2 || head->pape==3 ||head->pape==4 || head->pape==5)
			return head;
		ft_list_push_front(new_head,head);
		*size+=1;
		head = head->next;
	}
	return head;
}
int **make_pipe(int size)
{
	int **pipe;
	int i;

	i = 0;
	if(size < 0)
		return(0);
	pipe = malloc(sizeof(int*) * (size + 2));
	pipe[i++] = NULL;
	while(i <= size)
		pipe[i++] = malloc(sizeof(int) * 2);
	pipe[size+1]=NULL;
	return(pipe);
	
}
void find_function(int size,char **env,t_command_and_flag *head)
{
	int **pipe;
	int i;
	int fd;
	pid_t *pid;
	i = -1;
	fd = 0;
	pipe = make_pipe(size);
	pid=malloc(sizeof(pid)*(size+1));
	while(++i<=size)
	{
		if(head->pape==4 ||head->pape==2)//add function check pipe to chosw correct options for open
		{
			fd=open(head->command,O_WRONLY);
			head=head->next;
		}
		pid[i]=test(head,pipe[i],pipe[i+1],fd,env);
		fd = 0;
		head=head->next;
	}
	while(size>=0)
		waitpid(pid[size--],&fd,0);
	if(i>0)
	{
		i = 0;
		free(pipe[i++]);
		while(pipe[i])
			free(pipe[i++]);
		free(pipe[i]);
		free(pipe);
	}
}
void functions_launch(t_command_and_flag **head,char **env)
{
	t_command_and_flag *current_head;
	t_command_and_flag *tmp;
	int size;
	pid_t pid;
	tmp=0;
	current_head=*head;

	while(current_head)
	{
		tmp=0;
		current_head=number_of_pipes(&size,&current_head,&tmp);
		//printf("%d %s\n",size,current_head->command);
		if(size==-1 && tmp->f_error)
			printf("zsh: command not found:\n"/*,tmp->command*/);//waiting for wrong command name abort with wrong command
		else if(size>0 || (size==0 && tmp->pape==2))
			find_function(size,env,tmp);
		else if(size==0)
		{	
			pid = test(tmp,0,0,0,env);
			waitpid(pid,&size,0);
		}
		ft_list_clear(tmp);
			//printf("%s\n",tmp->command);
			//printf("%p\n",tmp->next);
	}
}

/*int main(int argc,char **argv,char **env)
{
	//function_lounch test
	//t_minishell *all;
	argc=0;
	printf("%s\n\n",argv[0]);
	//free(argv[0]);
	//char *a[2];
	//a[1] = argv[0];
	//a[2]=NULL;
	t_command_and_flag *head1;
	t_command_and_flag *head2;
	t_command_and_flag *head3;
	t_command_and_flag *head4;
	//all=malloc(sizeof(t_minishell));
	head1 = malloc(sizeof(t_command_and_flag));
	head2 = malloc(sizeof(t_command_and_flag));
	head3 = malloc(sizeof(t_command_and_flag));
	head4 = malloc(sizeof(t_command_and_flag));
	head1->command=ftstrdup("/usr/bin/wc");
	head1->next=0;
	head1->pape=1;
	head1->f_error=0;
	head2->command=ftstrdup("/bin/ls");
	head2->next=0;
	head2->pape=5;
	head2->f_error=0;
	head3->command=ftstrdup("/bin/ls");
	head3->next=0;
	head3->pape=1;
	head3->f_error=0;
	head4->command=NULL;
	//char a[3];
	head4->array_flags=malloc(sizeof(3));
	head4->array_flags[0]=argv[0];
	head4->array_flags[1]="k";
	head4->array_flags[2]=0;
	head4->next=0;
	head4->pape=4;
	head4->f_error=0;
	head1->next=head3;
	head1->array_flags=argv;
	head2->array_flags=argv;
	head3->array_flags=argv;
	//head3->next=head4;
	functions_launch(&head1,env);

}*/