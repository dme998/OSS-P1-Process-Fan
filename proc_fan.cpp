/* CS4760 Project 1: Unix System Calls and Library Functions
 * Author: Daniel Eggers
 * Instructor: Mark Hauschild
 * Date: September 22, 2020 
 */

#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

void printUsage() {
  cout << "Usage: proc_fan -n <pr_limit> <process or file name>" << endl;
  exit(1);
}

void printError() {
  cout << "Generic error message." << endl;
}  

//arc is argument count, argv is array that contains the specific args
int main(int argc, char *argv[]) {

  int pr_count = 0; // number of current active children
  int pr_limit = 3; // max  children allowed to execute at a time (when one ends, launch another)
  int option;       // user command line option
  
  while ( (option = getopt(argc, argv, "n:") ) != -1 ) {
    
    if (optind >= argc) {
      printUsage();
      exit(1);
    }

    switch(option) {
      case 'n': {
        
        int n = atoi(argv[(optind-1)]); //for parsing char array to int
        pr_limit = n;
        if(pr_limit > 20) {
          pr_limit = 20;
        }
        //cout << "pr_limit is " << pr_limit << endl;
       
        /* Fork it. Should return >= 0 if successful, -1 if error */
        for(; optind < argc; optind++) {

          if (pr_count == pr_limit) {
            //cout << "Hit pr_limit.  Waiting." << endl;
            wait(NULL);
            --pr_count;
            //cout << "pr_count is " << pr_count << endl;
          }
          
          pid_t pid = fork();
          
                  
          if(pid == -1) {
            perror("perror: fork failed"); 
          }
          else if (pid >= 0) {
            pr_count++; //fork successful
            // cout << "pr_count is " << pr_count << endl;
          }
          
          if(pid == 0) {
            /* child process */
            // cout << "I am a child, pid: " << pid << endl;
            
            //exec <argv[optind]>
            char *args[2];
            string program = argv[optind]; //get filename param that we will exec
            program = (string)"./" + program.c_str(); //adds dot slash prefix
            args[0] = (char*)program.c_str(); //convert type for use in exec
            args[1] = NULL; //array must end in NULL to avoid seg fault
            if( execvp(args[0],args) == -1 ) {
              perror("perror: execvp");
            }
            exit(0);
          }
          else if(pid > 0) {
            /* parent process */
            // cout < "I am the parent, pid: " << pid << endl;
          }
        }
        
      }//endof case
        break;
      case '?': 
        printUsage(); 
        break;
      default:
        perror("perror: case default.");
        break;
    }
    
    /* wait for any remaining child processes to finish */
    pid_t wpid;
    int status = 0;
    while ((wpid = wait(&status)) > 0); 
  }

  return 0;

}
