#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>

char * getWord(char * str,int * ptr)
{
    while(str[*ptr]==' '&&str[*ptr]!='\0'&&str[*ptr]!='\n')
    {
        (*ptr)++;
    }
    int leftptr=*ptr;
    while(str[*ptr]!=' '&&str[*ptr]!='\0'&&str[*ptr]!='\n')
    {
        (*ptr)++;
    }
    int rightptr=*ptr;
    char * ret;
    ret=(char *)malloc((rightptr-leftptr+1)*sizeof(char));
    for(int i=leftptr;i<rightptr;i++)
    {
        ret[i-leftptr]=str[i];
    }
    ret[rightptr-leftptr]='\0';
    return ret;
}

void writeToFile(char * path,char * content,int rdlen)
{
    int dst_file=open(path,O_WRONLY|O_CREAT,S_IRWXU);
    int wd=write(dst_file,content,rdlen);
}

char * deleteCharacter(char * src,char c)
{
    int len=strlen(src);
    char * ret=malloc(len*sizeof(char));

    int ptr=0,sptr=0;
    while(src[ptr]!='\0')
    {
        if(src[ptr]!='|')
        {
            ret[sptr]=src[ptr];
            sptr++;
        }
        ptr++;
    }
    ret[sptr]='\0';
    return ret;
}
void split(char * source,char **dest)
{
	char * p;
	p=strsep(&source,"|");
	int i=0;
	for(int i=0;p[i]!='\0';i++)
	{
		dest[0][i]=p[i];
	}
	dest[0][i]='\0';
	int j=1;
	while(p)
	{
		p=strsep(&source,"|");
		if(p)
		{
			for(int i=0;p[i]!='\0';i++)
			{
				dest[j][i]=p[i];
			}
			dest[j][i]='\0';
			j++;
		}
	}
}
int splitString(char * src,char * ins,char *args[],int * nums)
{
    int sptr=0;
    int ispipe=0;

    while(src[sptr]!='\0'&&src[sptr]!='\n')
    {
        if(src[sptr]=='|')
        {
            ispipe=1;
            break;
        }
    sptr++;
    }

    if(ispipe)
    {
        ins==NULL;
        int ptr=0;
        int leftptr=ptr;
        int nNum=0;
        int argnums=0;
        while(src[ptr]!='\0')
        {
            if(src[ptr]=='|'||src[ptr]=='\n')
            {
                strncpy(args[argnums],src+leftptr,nNum);
                nNum=0;
                ptr++;
                leftptr=ptr;
		argnums++;
            }
            ptr++;
            nNum++;
        }
        args[argnums]="";
	(*nums)=argnums;
	//split(src, args);
	int iii=0;
    }else
    {
        int ptr=0;

        strcpy(ins,getWord(src,&ptr));

        int argnums=1;
        strcpy(args[0],ins);
        while(src[ptr]!='\0'&&src[ptr]!='\n')
        {
            char * single=getWord(src,&ptr);
            strcpy(args[argnums],single);
            argnums++;
              
        }
        args[argnums]=(char *)0;
    }
    
    return ispipe;
}

int buildin_command(char * ins,char * argv[])
{

    if(strcmp(ins,"exit")==0)
    {
        exit(0);
    }
    if(strcmp(ins,"cd")==0)
    {
        if(chdir(argv[1]))
        {
            printf("error:cd:%s:no such directory\n",argv[0] );
        }
        return 1;
    }
    if(strcmp(ins,"pwd")==0)
    {
        char buf[1024];
        printf("%s\n",getcwd(buf,sizeof(buf)) );
        return 1;
    }
    return 0;
}

void listFiles(char * dir)
{
    DIR * dp;
    struct dirent * dirp;
    dp=opendir(dir);
    while((dirp=readdir(dp))!=NULL)
    {
        printf("%s\n",dirp->d_name);
    }
    closedir(dp);
}

void mysys(char * ins)
{
    int ptr=0;
    char * word=getWord(ins,&ptr);
    if(strcmp(word,"echo")==0)
    {
        ptr++;
        while(ins[ptr]!='\0')
        {
            printf("%c",ins[ptr]);
            ptr++;
        }
    }else if(strcmp(word,"ls")==0)
    {
        char * dir;
        dir=(char *)malloc(100*sizeof(char));
        ptr++;
        int cur=ptr;
        int sptr=0;
        while(ins[ptr]!='\0')
        {
            if(ins[ptr]!='\n')
            {
                dir[sptr]=ins[ptr];  
                sptr++;
            }
            ptr++;
        }
        dir[sptr]='\0';
        listFiles(dir);
    }
}

void eval(char ins[1024])
{
    mysys(ins);
}

void dealEcho(char * str)
{
    int ptr=0;
    int is=0;
    while(str[ptr]!='\0'&&str[ptr]!='\n')
    {
        if(str[ptr]=='>')
        {
            is=1;
            break;
        }
        ptr++;
    }
    if(is)
    {
        int sptr=5;
        char * content=malloc(1024*sizeof(char));
        int cptr=0;
        while(str[sptr]!='>')
        {
            content[cptr]=str[sptr];
            sptr++;
            cptr++;
        }
        content[cptr]='\0';cptr++;
        sptr++;
        int pptr=0;
        char * path=malloc(512*sizeof(char));
        while(str[sptr]!='\0'&&str[sptr]!='\n')
        {
            path[pptr]=str[sptr];
            sptr++;
            pptr++;
        }
        path[pptr]='\0';pptr++;

        writeToFile(path,content,cptr);
    }else
    {
        int sptr=5;
        while(str[sptr]!='\0'&&str[sptr]!='\n')
        {
            printf("%c", str[sptr]);
            sptr++;
        }
    }
}

void errorShow()
{
    if(errno==EACCES)
    {
        printf("EACCES\n");
    }else if(errno==EPERM)
    {
        printf("EPERM\n");
    }else if(errno==E2BIG)
    {
        printf("参数数组过大\n");
    }else if(errno==ENOEXEC)
    {
        printf("无法判断欲执行文件的执行文件格式，有可能是格式错误或无法在此平台执行。\n");
    }else if(errno==EFAULT)
    {
        printf("参数filename所指的字符串地址超出可存取空间范围\n");
    }else if(errno==ENAMETOOLONG)
    {
        printf("参数filename所指的字符串太长\n");
    }else if(errno==ENOENT)
    {
        printf("参数filename字符串所指定的文件不存在\n");
    }
    else if(errno==ENOMEM)
    {
        printf("核心内存不足\n");
    }
    else if(errno==ENOTDIR)
    {
        printf("参数filename字符串所包含的目录路径并非有效目录\n");
    }
    else if(errno==EACCES)
    {
        printf("参数filename字符串所包含的目录路径无法存取，权限不足\n");
    }
    else if(errno==ELOOP)
    {
        printf("过多的符号连接\n");
    }
    else if(errno==EIO)
    {
        printf("I/O 存取错误\n");
    }
    else if(errno==ENFILE)
    {
        printf("已达到系统所允许的打开文件总数\n");
    }
    else if(errno==EINVAL)
    {
        printf("欲执行文件的ELF执行格式不只一个PT_INTERP节区\n");
    }else if(errno==EISDIR)
    {
        printf("ELF翻译器为一目录\n");
    }
    else if(errno==ELIBBAD)
    {
        printf("ELF翻译器有问题\n");
    }
}

char * mergetwoString(char * s1,char * s2)
{
    int len=strlen(s1)+strlen(s2);
    char * ret=malloc(len*sizeof(char));
    int ptr=0,ptr1=0,ptr2=0;
    while(s1[ptr1]!='\0')
    {
        ret[ptr]=s1[ptr1];
        ptr++;ptr1++;
    }
    ret[ptr++]=' ';
    while(s2[ptr2]!='\0')
    {
        ret[ptr]=s2[ptr2];
        ptr++;
        ptr2++;
    }
    ret[ptr]='\0';
    return ret;
}
int main()
{
    int n;
    pid_t pid;
    int status;
    char * instr;
    char * argv[100];
    int paranum=0;
    while(1)
    {
        instr=malloc(64*sizeof(char));
        for(int i=0;i<100;i++)
        {
            argv[i]=malloc(64*sizeof(char));
        }
        char  buf[1024];

        printf("myshell* %s> $",getcwd(buf,sizeof(buf)));

        fflush(stdout);

        char instruction[1024];
        fgets(instruction,1000,stdin);
        

        int ispipe=splitString(instruction,instr,argv,&paranum);

        if(ispipe)
        {
            int fd[2];
            if(pipe(fd))
	    {
		printf("create pipe failed\n");
	    }
            int j=0;
            for(j=0;j<paranum-1;j++)
            {
                pid=fork();
		if(pid==-1)
		{
			printf("create fork fail\n");
		}
                if(pid==0)
		{
			dup2(fd[1],1);
			close(fd[0]);
			//execlp("cat","cat","tmp.txt",NULL);
			system(argv[j]);
			exit(0);
			
		}else
		{
			dup2(fd[0],0);
			close(fd[1]);
			//execlp("sort","sort",NULL);
			system(argv[j+1]);
			exit(0);
		}
		wait(&status);
            }
        }else
        {
            if(buildin_command(instr,argv))
            {
                if(strcmp(instr,"exit")==0)
                   break;
                continue;
            }

            pid=fork();
            if(pid==0)
            {
                if(strcmp(argv[0],"echo")==0)
                {
                    dealEcho(instruction);  
                }else
                {
                    if(execvp(argv[0],argv)<0)
                    {
                        errorShow();
                    }
                }    
            }
            else
            {
                wait(&status);
            }  
        }
        
    }
    return 0;
}
