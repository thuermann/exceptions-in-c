/*
 * $Id: example.c,v 1.2 2016/02/20 06:29:59 urs Exp $
 */

#include <stdlib.h>
#include <stdio.h>

#include "except.h"

static int exc_foo, exc_bar;

static int fun(void);
static int foo(void);
static int bar(void);

int main(int argc, char **argv)
{
	int exc;

	if (argc > 1)
		exc_foo = atoi(argv[1]);
	if (argc > 2)
		exc_bar = atoi(argv[2]);

	TRY {
		printf("calling fun()\n");
		printf("fun = %d\n", fun());
	} CATCH {
	default:
		// catch all
		printf("main: exception %d\n", exc);
		return 1;
	}
	return 0;
}

static int fun(void)
{
	int exc;

	TRY {
		printf("calling foo()\n");
		printf("foo = %d\n", foo());
	} CATCH {
	default:
		// re-throw exception
		THROW(exc);
	case 3:
	case 4:
	case 103:
	case 104:
		// handle exception
		printf("fun: exception %d\n", exc);
		break;
	}

	return 1;
}

static int foo(void)
{
	int exc;

	TRY {
		if (exc_foo)
			THROW(exc_foo);
		printf("calling bar()\n");
		printf("bar = %d\n", bar());
	} CATCH {
	default:
		// re-throw exception
		THROW(exc);
	case 1:
	case 2:
	case 101:
	case 102:
		// handle exception
		printf("foo: exception %d\n", exc);
		break;
	}

	return 2;
}

static int bar(void)
{
	if (exc_bar)
		THROW(exc_bar + 100);

	return 3;
}
