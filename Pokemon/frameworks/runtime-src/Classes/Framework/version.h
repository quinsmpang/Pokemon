#ifndef __VERSION_H__
#define __VERSION_H__

#include <iostream>

static const char *VERSION = "v1.00";

void printVersion()
{
	printf("\n/**************************************************/\npsframework current version: %s\n/**************************************************/\n\n", VERSION);
}

#endif