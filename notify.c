#if 0
#!/bin/bash
src=$0
obj=${src%.*}
gcc -g -Wl,--no-as-needed `pkg-config --cflags --libs libnotify` -o $obj $src
$obj $@
exit
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libnotify/notify.h>

int
main(int argc, char *argv[])
{
  NotifyNotification *n = NULL;

  notify_init("notify");

  if (argc < 4) {
    printf("$ notify <summary> <body> <icon>\n");
    exit(0);
  }

  n = notify_notification_new(argv[1],argv[2],argv[3]);
  notify_notification_set_timeout(n,3000);
  notify_notification_show(n,NULL);

  return 0;
}
