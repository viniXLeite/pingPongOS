// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.4 -- Janeiro de 2022

// Demonstração das funções POSIX de troca de contexto (ucontext.h).

// operating system check
#if defined(_WIN32) || (!defined(__unix__) && !defined(__unix) && (!defined(__APPLE__) || !defined(__MACH__)))
#warning Este codigo foi planejado para ambientes UNIX (LInux, *BSD, MacOS). A compilacao e execucao em outros ambientes e responsabilidade do usuario.
#endif

#define _XOPEN_SOURCE 600	/* para compilar no MacOS */

#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>

#define STACKSIZE 64*1024	/* tamanho de pilha das threads */

/*
ContextPing, ContextPong: Contextos das tarefas de ping e pong
ContextMain: Contexto da função main
*/
ucontext_t ContextPing, ContextPong, ContextMain ;

/*****************************************************/
// Tarefas ping e pong que se intercalam através da troca de contexto

void BodyPing (void * arg)
{
   int i ;

   printf ("%s: inicio\n", (char *) arg) ;

   for (i=0; i<4; i++)
   {
      printf ("%s: %d\n", (char *) arg, i) ;
      // Troca o contexto de ping com o de pong
      swapcontext (&ContextPing, &ContextPong); // Salva o contexto de ping e restaura o de pong
   }
   printf ("%s: fim\n", (char *) arg) ;

   swapcontext (&ContextPing, &ContextMain) ;
}

/*****************************************************/

void BodyPong (void * arg)
{
   int i ;

   printf ("%s: inicio\n", (char *) arg) ;

   for (i=0; i<4; i++)
   {
      printf ("%s: %d\n", (char *) arg, i) ;
      // Troca o contexto de pong com o de ping
      swapcontext (&ContextPong, &ContextPing) ; // Salva o contexto de pong e restaura o de ping
   }
   printf ("%s: fim\n", (char *) arg) ;

   swapcontext (&ContextPong, &ContextMain) ;
}

/*****************************************************/

int main (int argc, char *argv[])
{
   char *stack ;

   printf ("main: inicio\n") ;

   // Salva o contexto atual em contextping
   getcontext (&ContextPing);

   stack = malloc (STACKSIZE); // Aloca o espaço da pilha

   // Cria a pilha
   if (stack) {
      ContextPing.uc_stack.ss_sp = stack; // Define a pilha
      ContextPing.uc_stack.ss_size = STACKSIZE; 
      ContextPing.uc_stack.ss_flags = 0;
      ContextPing.uc_link = 0;
   }
   else {
      perror ("Erro na criação da pilha: ") ;
      exit (1) ;
   }

   // Associa contextPing à tarefa bodyping
   makecontext (&ContextPing, (void*)(*BodyPing), 1, "    Ping") ;


   // Salva o contexto atual em pong
   getcontext (&ContextPong) ;

   stack = malloc (STACKSIZE) ;
   if (stack)
   {
      ContextPong.uc_stack.ss_sp = stack ;
      ContextPong.uc_stack.ss_size = STACKSIZE ;
      ContextPong.uc_stack.ss_flags = 0;
      ContextPong.uc_link = 0 ;
   }
   else
   {
      perror ("Erro na criação da pilha: ") ;
      exit (1) ;
   }

   // Associa contextPong à tarefa pong
   makecontext (&ContextPong, (void*)(*BodyPong), 1, "        Pong") ;

   // Inicia a execução alternada
   swapcontext (&ContextMain, &ContextPing) ;
   swapcontext (&ContextMain, &ContextPong) ;

   printf ("main: fim\n") ;

   exit (0) ;
}
