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

using namespace std;

void printUsage() {
  cout << "Usage: proc_fan -n <number of processes>" << endl;
  exit(1);
}

//arc is argument count, argv is array that contains the specific args
int main(int argc, char *argv[]) {
  /*
  // parse command line options
  if(argc==1)
    cout << "Usage: ./program_name arg1" << endl;
  else {
    for(int i=1;i<argc; i++) {
      cout << argv[i] << endl;
    }
  }
  */
  
  if (argc < 3) {
    printUsage();
  }

  int option;
  while ( (option = getopt(argc, argv, "n:") ) != -1) {
    switch(option) {
      case 'n':
        cout << argv[2] << endl;
        break;
      default:
        printUsage();
        break;
    }
  }

  return 0;

}
