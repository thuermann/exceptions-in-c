/*
 * $Id: except.c,v 1.2 2016/02/20 06:31:11 urs Exp $
 */

#include <stdlib.h>

#include "except.h"

/* We store a linked list of setjmp buffers representing the nested
 * TRY blocks.  Each TRY inserts a new jump buffer at the list's head
 * that THROW() uses to jump to the CATCH block of the first TRY on
 * the list.  Following the TRY block, either after executing the
 * block or after catching an exception, the CATCH macro removes the
 * head from the jump buffer list.
 */

struct jblist *jblist;

struct jblist *jb_add(void)
{
	struct jblist *jb = malloc(sizeof(struct jblist));
	jb->next = jblist;
	jblist = jb;

	return jb;
}

void jb_del(void)
{
	struct jblist *jb = jblist;
	jblist = jb->next;
	free(jb);
}
