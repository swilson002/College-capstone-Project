#include <iostream>
#include <fstream>
using namespace std;

//#define DEBUG

int checkFile(char fileName[])
{
  ifstream fileIn(fileName);

  int count = 0;

  cout << fileName << ": ";
  if(fileIn.is_open())
  {

    count = 1;
    char test;

    do
    {
      test = fileIn.get();
   
      if(test == '\n')
      {
        count++;
      }
    }while(test != EOF);
#ifdef ___DONTDEFINE___   // this is to allow tabbing on emacs
  {
#endif

#ifdef DEBUG
  }
#endif
  
    cout << count << endl;
#ifndef DEBUG
  }
#endif
  else
  {
    cout << "File not found.\n";
  }
  return count;
}

main(int argc, char *argv[])
{
  bool classMode = false;
  bool extMode = false;

  char * suffix;

  int count = 1;

  int total = 0;

  bool suf = false;

  while(count < argc)
  {
  
    if(argv[count][0] == '-')
    {
      if(argv[count][1] == 'd')
      {
        classMode = false;
	extMode = false;
      }
      else if(argv[count][1] == 'c')
      {
        classMode = true;
	extMode = true;
        suf = true;
      }
      else if(argv[count][1] == 'e')
      {
	classMode = false;
	extMode = true;
	suf = true;
      }

      if(argv[count][2])
      {
        int rep = 2;
        while(argv[count][rep])
        {
          argv[count][rep - 2] = argv[count][rep];
          rep++;
        }

        argv[count][rep - 2] = '\0';
        count--;
      }
    }

    else if(suf)
    {
      suffix = argv[count];

      if(suffix[0] == '.')
      {
	int pos = 0;
	do
	{
	  pos++;
	  suffix[pos-1] = suffix[pos];

	}while(suffix[pos]);
      }

      suf = false;
    }
    else
    {
      if(!classMode)
      {
	total += checkFile(argv[count]);
      }
      if(classMode)
      {
	int length = 0;
	char file[255];

	while(argv[count][length])
	{
	  file[length] = argv[count][length];
	  length++;
	}

	file[length] = '.';
	file[length+1] = 'h';
	file[length+2] = '\0';

	total += checkFile(file);

      }
      if(extMode)
      {
	int length = 0;
	char file[255];

	while(argv[count][length])
	{
	  file[length] = argv[count][length];
	  length++;
	}

	file[length] = '.';

	int start = length + 1;
	int i = 0;

	while(suffix[i])
	{
	  file[start] = suffix[i];
	  start++;
	  i++;
	}

	file[start] = '\0';

	total += checkFile(file);
      }
    }

    count++;
  }

  cout << "Total: " << total << endl;
}
