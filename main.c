#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "includes/util.h"
#include "zlog.h"

int		main(int argc, char *argv[]) {

  int rc;
  zlog_category_t *c;

  UNUSED(argc);
  UNUSED(argv);

  rc = zlog_init("./zlog.conf");
  if (rc) {
    printf("init failed\n");
    return -1;
  }

  c = zlog_get_category("my_cat");
  if (!c) {
    printf("get cat fail\n");
    zlog_fini();
    return -2;
  }

  zlog_info(c, "hello, zlog");

  zlog_fini();

  printf("coucou\n");
  return (0);
}
