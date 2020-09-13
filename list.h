#ifndef __LIST_H_INCLUDED__
#define __LIST_H_INCLUDED__
  #include <stdlib.h>
  #include <stdio.h>
  static struct item{
      void *data;
      struct item *prev;
      struct item *next;
  };
  extern void movetohead(struct item **mainlist, struct item *item);

  extern struct item *additem(struct item **mainlist);

  extern void delitem(struct item **mainlist, struct item *item);

  extern void freeitem(struct item **list, int *stored,struct item *item);

  extern void delallitems(struct item **list, int *stored);

  extern void listitems(struct item *mainlist);
#endif
