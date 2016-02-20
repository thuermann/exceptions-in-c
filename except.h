/*
 * $Id: except.h,v 1.3 2016/02/20 06:31:01 urs Exp $
 */

#ifndef EXCEPT_H
#define EXCEPT_H

#include <setjmp.h>

#define TRY(exc)   if ((exc = setjmp(jb_add()->jb)) == 0)
#define CATCH(exc) jb_del(); if (exc) switch (exc)
#define THROW(exc) longjmp(jblist->jb, (exc))

struct jblist {
	struct jblist *next;
	jmp_buf jb;
};

extern struct jblist *jblist;

struct jblist *jb_add(void);
void jb_del(void);

#endif
