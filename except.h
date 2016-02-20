/*
 * $Id: except.h,v 1.2 2016/02/20 06:29:59 urs Exp $
 */

#ifndef EXCEPT_H
#define EXCEPT_H

#include <setjmp.h>

#define TRY      if ((exc = setjmp(jb_add()->jb)) == 0)
#define CATCH    jb_del(); if (exc) switch (exc)
#define THROW(e) longjmp(jblist->jb, (e))

struct jblist {
	struct jblist *next;
	jmp_buf jb;
};

extern struct jblist *jblist;

struct jblist *jb_add(void);
void jb_del(void);

#endif
