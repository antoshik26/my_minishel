#include"function.h"
/*int find_slash_dot(char **line)
{
	int i;

	i = -1;
	while(line[++i])
	{
		if(line[i]==47)//47-ascii "\"
			return(1);
		else if(line[i]=='.')
			return(1);
	}
	return(0);
}*/
void free_array_of_strings(char **array)
{
	int i;

	i = -1;
	while(array[++i])
		free(array[i]);
	free(array);
}
int find_path(t_pars *all,char **array,int *pipe_1,int *pipe_2)
{
	char **PATH;
	int i;
	char *tmp;
	struct stat buff;
	i = -1;
	tmp = getenv("PATH");
	PATH = ft_split(tmp,':');
	if(pipe_2!=0)
		pipe(pipe_2);
	while(PATH[++i])
	{
		tmp = ft_strjoin(PATH[i],all->filename);
		printf("%s\n",tmp);
		if(!stat(tmp,&buff))
		{
			if(!fork())
			{
				if(pipe_1!=0)
				{
					dup2(pipe_1[1],1);
					close(pipe_1[1]);
					close(pipe_1[0]);
				}
				if(pipe_2!=0)
				{
					dup2(pipe_2[0],0);
					close(pipe_2[1]);
					close(pipe_2[0]);
				}
				execve(tmp,array,all->env);
			
			}
			//free_array_of_strings(PATH);
			//free(tmp);
			//return(0);
			if(pipe_1!=0)
			{
				close(pipe_1[1]);
				close(pipe_1[0]);
			}
		}
		free(tmp);
	}
	free_array_of_strings(PATH);
	return(-1);
}

/*int check_function(t_pars *all)
{
	if(!strncmp(all->filename,"pwd\0",4))
	{	
		if(ft_pwd(all))
			printf("error\n");
	}
	else if(!strncmp(all->filename,"env\0",4))	
	{
		if(ft_env(all))
			printf("error\n");
	}
	else if(!strncmp(all->filename,"cd\0",3))
	{
		if(ft_cd(all))
			printf("error\n");
	}
	if(find_slash_dot(all->filename))
	{	
		if(execve(all->filename,all->array,all->env)==-1)
			ft_putchar("error");
	}
	else
	{	
		if(find_path(all)==-1)
			ft_putchar("error");
	}
}*/
int main(int argc,char **argv,char **env)
{
	t_pars *all[3];
	char *a[3];
	char *b[3];
	char *c[2];
	int **pipe;
	//array
	a[0]=argv[0];
	a[1]="hello";
	a[2]=NULL;
	b[0]=argv[0];
	b[1]="third";
	b[2]=NULL;
	c[0]=argv[0];
	c[1]=NULL;
	//array
	//filename
	/*all[0]->filename="/cat";
	all[1]->filename="/grep";
	all[2]->filename="/wc";*/
	//pipe
	
	pipe=malloc(sizeof(int*)*4);
	pipe[0]=NULL;
	pipe[1]=malloc(sizeof(int)*2);
	pipe[2]=malloc(sizeof(int)*2);
	pipe[3]=NULL;
	int i;
	i = -1;
	while(all[++i])
	{

		all[i]->env= env;
		//find_path(all[i],pipe[i],pipe[i+1]);
	}
	//int pipe_1[2];
	//int pipe_2[2];
	find_path(all[2],c,0,pipe[1]);
	find_path(all[1],b,pipe[1],pipe[2]);
	find_path(all[0],a,pipe[2],0);
	wait(0);
	wait(0);
	wait(0);
	//find_path(all,pipe_2,0);
	//find_path(all,pipe_1,1);
	//execve("/bin/cat ",wc, all[0]->env);
	/*pipe(pipe_1);
	if(!fork())
	{
		dup2(pipe_1[0],0);
        close(pipe_1[1]);
        close(pipe_1[0]);
        execve("/usr/bin/wc",wc, all[0]->env);
	}
	pipe(pipe_2);

	if(!fork())
	{
		dup2(pipe_2[0],0);
        close(pipe_2[1]);
        close(pipe_2[0]);
		dup2(pipe_1[1],1);
		close(pipe_1[1]);
		close(pipe_1[0]);
        execve("/usr/bin/grep",all[1]->array, all[0]->env);
	}
	
	if (!fork())
	{
		dup2(pipe_2[1],1);
		close(pipe_2[1]);
		close(pipe_2[0]);
		execve("/bin/cat",all[0]->array, all[1]->env);
	}
	close(pipe_1[1]);
    close(pipe_1[0]);
	close(pipe_2[1]);
    close(pipe_2[0]);
	wait(0);
	wait(0);
		wait(0);*/
}