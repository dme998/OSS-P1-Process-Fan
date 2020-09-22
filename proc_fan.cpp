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
  cout << "Usage: proc_fan -n <number of processes>" << endl;
  exit(1);
}

void printError() {
  cout << "Generic error message." << endl;
}

//arc is argument count, argv is array that contains the specific args
int main(int argc, char *argv[]) {

  int option;       // user command line option
  int pr_count = 0; // number of current active children
  int pr_limit = 3; // max  children allowed to execute at a time (when one ends, launch another)
  
  while ( (option = getopt(argc, argv, "n:") ) != -1 ) {
    
    if (optind >= argc) {
      printUsage();
      exit(1);
    }

    switch(option) {
      case 'n': {
          int n = atoi(argv[(optind-1)]); //for parsing char array to int
          //for-loop encasing switch? doesnt getopt already loop through all args?
          /*
          cout << "argv[optind-1] as n: " <<  n << endl;
          cout << "argv[optind-1]     : " << (optind-1) << endl;
          cout << "argv[optind]       : " << argv[optind] << endl;
          cout << "optind             : " << (optind) << endl;
          
          // ARGV[OPTIND] IS THE FILENAME (PROCESS) THAT YOU CAN EXEC
          */
          
          /* Fork it. Should return >= 0 if successful, -1 if error */
          pid_t pid = fork();
          if(pid == -1) {
            perror("perror: fork failed."); 
          }
          else if(pid == 0) {
            //child
            cout << "I am a child, pid: " << pid << endl;
            
            //exec <argv[optind]>
            sleep(1); 
            char *args[2];
            string program = argv[optind]; //get filename param that we will exec
            args[0] = (char*)program.c_str(); //convert type for use in exec
            args[1] = NULL; //array must end in NULL to avoid seg fault
            if( execvp(args[0],args) == -1 ) {
              perror("perror: exec.");
            }
            
            cout << "Child now ending (if you see this message, exec didnt work)." << endl;
            exit(0);
          }
          else if(pid > 0) {
            //parent
            cout << "I am a parent, pid: " << pid << endl;
            wait(NULL);
            cout << "Parent done waiting" << endl;
          }
          
        }
        break;
      case '?': 
        perror("perror: case ?.");
        break;
      default:
        perror("perror: case default.");
        break;


    }
    
  }









/*  while ( (option = getopt(argc, argv, "N:n:") ) != -1 ) {
    for(int i = 3; i <= argc; i++) {
      switch(option) {
        case 'N':
        case 'n': {
          int n = atoi(argv[(i-1)]);  //for parsing char array to int
          //cout << "Fanning given process, " << argv[i] << ", " << n << " times :" << endl;
        for(int j = 0; j < n; j++) {
            pid_t pid = fork();
            if(pid == -1) // child should return >= 0 if successful fork, -1 if error
              {perror("error: fork failed.");}
            else if(pid == 0) {
              //cout << "I am a Child, PID: " << pid << endl;
              
              char *args[] = {"./fanwaitmsg","2", NULL};
              execv("./fanwaitmsg",args);
              
              exit(0);
            }
            else if(pid > 0) {
              //parent
              //cout << "I am Parent, PID: "<< pid << endl;
              wait(NULL);
              //cout << "I am done waiting." << endl;
            }
              
          }
          break;
        }     
        default:
          printUsage();
          break;
      }
      //cout << endl;
    }
  }
*/
  return 0;

}
