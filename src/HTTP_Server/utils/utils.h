#pragma once

#include <stdio.h>

#define eprintf(mesg, ...)  fprintf(stderr, "%s: "mesg, __func__, ##__VA_ARGS__)

