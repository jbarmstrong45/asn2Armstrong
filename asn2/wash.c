//This is my code
//Jonathan Armstrong
//CS366

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
  void q(void);
  void d(char currentFile[]);
  void r(char currentFile[]);
  void u(char currentFile[]);

  char arg1[30];
  char arg2[30];
  char arg3[30];
  char currentFile[30];
  char args[3][30];

  if(argc == 1)
  {
    strcpy(arg1, argv[0]);
  }
  else if(argc == 2)
  {
    strcpy(arg1, argv[0]);
    strcpy(arg2, argv[1]);
    strcpy(currentFile, arg2);
    strcpy(args[0], currentFile);
  }
  else if(argc == 3)
  {
    strcpy(arg1, argv[0]);
    strcpy(arg2, argv[1]);
    strcpy(arg3, argv[2]);
    strcpy(currentFile, arg2);
  }
  else
  {
    printf("That's too many args!\n");
  }

  printf("Welcome to asn2!\n");
  printf("Your command line arg was %s and %s and %s\n", arg1, arg2, arg3);
  char action[30] ;
  while(1)
  {
    printf("What would you like to do in %s?\n", currentFile);
    scanf("%s", action);
    if(strcmp(action,"q") == 0)
    {
      q();
    }
    else if(strcmp(action,"d") == 0)
    {
      d(currentFile);
    }
    else if(strcmp(action,"r") == 0)
    {
      r(currentFile);
    }
    else if(strcmp(action,"u") == 0)
    {
      u(currentFile);
    }
    else
    {
      continue;
    }
  }
  //FILE *fp = fopen(name, "ab+");

}

void c(void)
{

}

void d(char currentFile[])
{
  int readDescriptor;
  int writeDescriptor;
  char buffer[BUFFER_SIZE];
  char *pointer;
  int readChars;
  int writtenChars;

  char destination[30];
  printf("Where do you want the file to be copied?\n");
  scanf("%s", destination);

  if((readDescriptor = open(currentFile, O_RDONLY, 0)) < 0)
  {
    printf("%d", readDescriptor);
    printf("There was an error with open\n");
  }
  
  if((writeDescriptor = open(destination, O_WRONLY | O_CREAT | O_TRUNC,
                             S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
  {
    printf("%d", writeDescriptor);
    printf("There was an error with open\n");
  }

  while(1)
  {
    if((readChars = read(readDescriptor, buffer, BUFFER_SIZE)) > 0)
    {
      pointer = buffer;

      while(readChars > 0)
      {
        if((writtenChars = write(writeDescriptor, pointer, readChars)) < 0)
	{
	  printf("There was an error with write");
	}

	readChars -= writtenChars;
	pointer += writtenChars;
      }
    }
    else if(readChars == 0)
    {
      break;
    }
    else
    {
      printf("There was an error with read");
    }
  }
}

void r(char currentFile[])
{
  char newName[30];
  printf("what is its new name?\n");
  scanf("%s", newName);

  rename(currentFile, newName);
}

void u(char currentFile[])
{
  unlink(currentFile);
}

void t(void)
{

}

void a(void)
{

}

void l(void)
{

}

void m(void)
{

}

void x(void)
{

}

void n(void)
{

}

void q(void)
{
  exit(0);
}








