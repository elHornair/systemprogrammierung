#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "optparse.h"

void printUsage() {
  printf("valid arguments: -w (width) -h (height)\n");
}

/* Retrieves height and width
 * Writes instructions when user arguments are inconsistent */
_Bool optparse(int argc, char *argv[]) {
  int index;
  int c;

  opterr = 0;

  if (argc == 1) {
    printUsage();
    return false;
  }

  while ((c = getopt(argc, argv, "h:w:")) != -1) {
    switch (c) {
      case 'h':
        height = atoi(optarg);
        break;
      case 'w':
        width = atoi(optarg);
        break;
      case '?':
        if ((optopt == 'h') || (optopt == 'w'))
          fprintf(stderr, "Option -%c requires an argument.\n", optopt);
        else if (isprint(optopt))
          fprintf(stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
        return false;
      default:
	    abort();
    }
  }

  for (index = optind; index < argc; index++)
    printf("Non-option argument %s\n", argv[index]);

  return true;
}
