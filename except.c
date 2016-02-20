/*
 * $Id: except.c,v 1.1 2016/02/20 06:28:48 urs Exp $
 */

#include <stdlib.h>

#include "except.h"

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
