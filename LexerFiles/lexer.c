/************************************************************************
University of Leeds
School of Computing
COMP2932- Compiler Design and Construction
Lexer Module

I confirm that the following code has been developed and written by me and it is entirely the result of my own work.
I also confirm that I have not copied any parts of this program from another person or any other source or facilitated someone to copy this program from me.
I confirm that I will not publish the program online or share it with anyone without permission of the module leader.

Student Name: Muhammad Shahrulnizam
Student ID: 201599713
Email: sc22mibs@leeds.ac.uk
Date Work Commenced: 08/02/2024
*************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

#define NUMBERKEYWORDS 21
#define NUMBERSYMBOLS 19
// YOU CAN ADD YOUR OWN FUNCTIONS, DECLARATIONS AND VARIABLES HERE
FILE *file;
int LineCounter;
const char* keywords[NUMBERKEYWORDS] = { "class", "method", "function", "construtor", "int", "boolean", "char", "void", "var"
					 , "static", "field", "let", "do", "if", "else", "while", "return", "true"
					 , "false", "null", "this" };
const char* symbols[NUMBERSYMBOLS] = { "{", "}", "(", ")", "[", "]", ".", ",", ";", "+"
				       , "-", "*", "/", "&", "|", "<", ">", "=", "~" };
Token t;

// IMPLEMENT THE FOLLOWING functions
//***********************************

// Initialise the lexer to read from source file
// file_name is the name of the source file
// This requires opening the file and making any necessary initialisations of the lexer
// If an error occurs, the function should return 0
// if everything goes well the function should return 1
int InitLexer (char* file_name)
{
  if (file = fopen(file_name, "r")) {
    LineCounter = 1;
    strcpy(t.fl, file_name);
    return 1;
  }
  return 0;
}
                        

// Get the next token from the source file
Token GetNextToken ()
{
  int c = getc(file);

  if( c==EOF )
    {
      t.ln = LineCounter;
      t.tp = EOFile;
    }

  char temp[128];
  int i = 0;
  if(isspace(c))
    {
      while(c != EOF && isspace(c))
	{
	  if((char) c == '\n') LineCounter++;
	  c = getc(file);
	}
    }

  // check for comments
  else if (c == '/')
    {
      c = getc(file);
      if (c == '/')
	{
	  while( c!=EOF && c!='\n' )
	    {
	      c = getc(file);
	      if ((char) c == '\n') LineCounter++;
	    }
	}
      else if ( c=='*' )
	{
	  while( c!=EOF && c!='/' )
	    {
	      c= getc(file);
	      if ((char) c == '\n' || (char) c == '/' ) LineCounter++;
	    }
	}
    }

  // check alphabetic character
  else if(isalpha(c))
    {
      while(c != EOF && isalpha(c))
	{
	  temp[i++] = c;
	  c = getc(file);
	}
      
      temp[i] = '\0';
      ungetc(c, file);
      
      strcpy(t.lx, temp);
      for (int j = 0; j < NUMBERKEYWORDS; j++)
	{
	  if (!strcmp(keywords[j], temp)) {
	    t.tp = RESWORD;
	    break;
	  }
	  else t.tp = ID;
	}
      t.ln = LineCounter;
      return t;
    }
  
  
  // check numeric character
  else if(isdigit(c))
    {
      while(c != EOF && isdigit(c))
	{
	  temp[i++];
	  c = getc(file);
	}
      
      temp[i] = '\0';
      ungetc(c, file);
      
      strcpy(t.lx, temp);
      t.ln = LineCounter;
      t.tp = INT;
      
      return t;
    }
  else if(c == '"')
    {
      c = getc(file);
      while( c!=EOF && c!='"' )
	{
	  temp[i++] = c;
	  c = getc(file);
	}
      
      temp[i] = '\0';
      // c = ungetc(file);

      strcpy(t.lx, temp);
      t.ln = LineCounter;
      t.tp = STRING;
    }
	
  //t.tp = ERR;
  return t;
}

// peek (look) at the next token in the source file without removing it from the stream
Token PeekNextToken ()
{
  t.tp = ERR;
  return t;
}

// clean out at end, e.g. close files, free memory, ... etc
int StopLexer ()
{
	return 0;
}

// do not remove the next line
#ifndef TEST
int main ()
{
  if (InitLexer("List.jack")) {
    t = GetNextToken();
    while (t == NULL) {
      printf ("<%s, %i, %s, %s>\n", t.fl, t.ln , t.lx, TokenTypeString (t.tp));
      t = GetNextToken();
    }
  }
  else
    exit(1);
	// implement your main function here
  // NOTE: the autograder will not use your main function

  
  return 0;
}
// do not remove the next line
#endif
