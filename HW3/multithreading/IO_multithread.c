#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*Thread1-Parent, Thread2-Child, Thread3-Child*/
/*Thread 1-opens a file and writes data into it*/
/*Thread 2-Reads the file and counts number of words lines, characters in file*/
/*Thread 3-Prints statistics in human readable format*/
size_t file_size = 0;
/*struct report {
	size_t words;
	size_t line;
	size_t count;
};*/

void* to_file(void* arg)
{
	char* buff = malloc(1024*sizeof(char));
    memset(buff,0,sizeof(buff));
    FILE* fp = NULL;
	char** filename = (char**)arg;
	fp = fopen(filename,"w+");
    printf("Enter your text:");
    fgets(buff, 1024*sizeof(char),stdin);
    file_size = fwrite(buff,1,strlen(buff)*sizeof(char),fp);
    printf("Number of characters written into file:%d\n",file_size);
    fclose(fp);
    pthread_exit(NULL);

}

void* from_file(void* arg)
{
    FILE* fp = NULL;
    int words, line, count;
    words=line=count=0;
	char** filename = (char**)arg;
	fp = fopen(arg,"r+");
	char* buff = malloc(1024*sizeof(char));
    memset(buff,0,sizeof(buff));
    file_size = fread(buff,1,1024*sizeof(char),fp);
    printf("Number of characters read from file:%d\n",file_size);
    while(*buff!=NULL)
    {
    	count ++;
    	if(*buff == ' ' || *buff == '\n') words++;
    	if(*buff == '\n') line++;

    	buff++;

    }
    printf("Words:%d\nLines:%d\nCharacters:%d\n",words,line,(count-1));
    fclose(fp);
    pthread_exit(NULL);
}


int main(int argc, char** argv)
{
  
  pthread_t write_to_file;
  pthread_t read_from_file;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&write_to_file,&attr,&to_file,(void *)argv[1]);
  pthread_join(write_to_file,NULL);
  pthread_create(&read_from_file,&attr,&from_file,(void *)argv[1]);

  
  pthread_exit(0);

}
