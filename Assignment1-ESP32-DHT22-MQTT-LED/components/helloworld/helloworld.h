#pragma once
 
#ifndef HELLOWORLD_H_INCLIDE
#define HELLOWORLD_H_INCLIDE

typedef struct HELLOWORLD_ARGS
{
  int number;
  char *text;
} xHelloWorldArgs;



void print_hello_world();
void print_hello_world_param(void * args);
 
#endif