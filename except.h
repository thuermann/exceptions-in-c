/*
 * $Id: except.h,v 1.1 2016/02/20 06:28:48 urs Exp $
 */

#ifndef EXCEPT_H
#define EXCEPT_H

#include <setjmp.h>

struct jblist {
	struct jblist *next;
	jmp_buf jb;
};

extern struct jblist *jblist;

struct jblist *jb_add(void);
void jb_del(void);

#endif
