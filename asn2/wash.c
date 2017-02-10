//This is my code
//Jonathan Armstrong
//CS366

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <utime.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
  void quit    (void);
  void list    (char currentFile[]);
  void copy    (char currentFile[]);
  void giveName(char currentFile[]);
  void delete  (char currentFile[]);
  void zero    (char currentFile[]);
  void append  (char currentFile[]);
  void display (char currentFile[]);
  void chPermission (char currentFile[]);
  void chTime  (char currentFile[]);

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
      quit();
    }
    else if(strcmp(action,"c") == 0)
    {
      list(currentFile);
    }
    else if(strcmp(action,"d") == 0)
    {
      copy(currentFile);
    }
    else if(strcmp(action,"r") == 0)
    {
      giveName(currentFile);
    }
    else if(strcmp(action,"u") == 0)
    {
      delete(currentFile);
    }
    else if(strcmp(action,"t") == 0)
    {
      zero(currentFile);
    }
    else if(strcmp(action,"a") == 0)
    {
      append(currentFile);
    }
    else if(strcmp(action,"l") == 0)
    {
      display(currentFile);
    }
    else
    {
      continue;
    }
  }
  //FILE *fp = fopen(name, "ab+");

}

void list(char currentFile[])
{

}

void copy(char currentFile[])
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

void giveName(char currentFile[])
{
  char newName[30];
  printf("what is its new name?\n");
  scanf("%s", newName);

  rename(currentFile, newName);
}

void delete(char currentFile[])
{
  unlink(currentFile);
}

/*
* deletes the file, then creates a new file with the same name
*/
void zero(char currentFile[])
{
  char fileName[30];
  strcpy(fileName, currentFile);
  delete(currentFile);
  
  FILE *file = NULL;
  file = fopen(fileName, "a");
}

void append(char currentFile[])
{
  FILE *file1;
  FILE *file2;
  char buffer[100];

  char destination[30];
  printf("which file should be appended to?");
  scanf("%s", destination);

  file1 = fopen(currentFile, "r");
  file2 = fopen(destination, "a");
  if(file1 == NULL)
  {
    printf("There was an error with open");
  }
  else
  {
    while(fgets(buffer, sizeof(buffer), file1))
    {
      fprintf(file2, "%s", buffer);
    }
  }
  fclose(file2);
}

void display(char currentFile[])
{
  int fileDescriptor;
  int readByte;
  char buffer[101];

  if((fileDescriptor = open(currentFile, O_RDONLY)) < 0)
  {
    printf("There was an error with open");
  }

  lseek(fileDescriptor, -100L, SEEK_END);
  readByte = read(fileDescriptor, buffer, 100);
  buffer[readByte] = '\0';

  printf("%s\n", buffer);
}

void chPermission(char currentFile[])
{
  char mode[5];
  printf("What would you like to change the permission to?");
  scanf("%s", mode);

  //int chmod (const char *filename, mode_t mode);
  chmod(currentFile, S_IWGRP);
}

void chTime(char currentFile[])
{
  int retV;
  struct utimbuf utimeStruct;

  utimeStruct.actime = 0;

  if(utime(currentFile, &utimeStruct) != 0)
  {
    printf("There was an error with time");
  }
}

void n(void)
{

}

void quit(void)
{
  exit(0);
}








