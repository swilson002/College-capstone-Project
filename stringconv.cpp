#include "stringconv.h"

//#define DEBUG

#ifdef DEBUG
#include<iostream>
using namespace std;
#endif

string conv::convToString(int convert)
{
  #ifdef DEBUG
  cerr << convert << endl;
  #endif

  string result;
  if(!convert)
  {
    result = "0";
  }
  else
  {
    if(convert < 0)
    {
      result = '-';
      convert *= -1;
    }

    int digit[32];
    int numDigits = 0;

    while(convert)
    {
      digit[numDigits] = convert % 10;
      numDigits++;
      convert /= 10;
    }

    for(int i = numDigits - 1; i >= 0; i--)
    {
      char dig = '0' + digit[i];
      result += dig;
    }
  }
  #ifdef DEBUG
  cerr << result << endl;
  #endif
  return result;
}
