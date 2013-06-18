/*
 * $Id: ex.c,v 1.1 2013/06/18 14:11:14 urs Exp $
 */

#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

struct jblist {
	struct jblist *next;
	jmp_buf jb;
};

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

int exc_foo, exc_bar;

int bar(void)
{
	if (exc_bar)
		longjmp(jblist->jb, exc_bar);

	return 3;
}

int foo(void)
{
	if (exc_foo)
		longjmp(jblist->jb, exc_foo);
	bar();

	return 2;
}

int fun(void)
{
	int exc;

	if (exc = setjmp(jb_add()->jb)) {
		jb_del();
		// handle exception
		if (exc == 1 || exc == 2) {
			printf("fun: exception %d\n", exc);
			return 0;
		} else {
			longjmp(jblist->jb, exc);
		}
	}

	foo();

	jb_del();

	return 1;
}

int main(int argc, char **argv)
{
	int exc;

	if (argc > 1)
		exc_foo = atoi(argv[1]);
	if (argc > 2)
		exc_bar = atoi(argv[2]);

	if (exc = setjmp(jb_add()->jb)) {
		jb_del();
		printf("main: exception %d\n", exc);
		return 1;
	}

	fun();

	jb_del();

	return 0;
}
