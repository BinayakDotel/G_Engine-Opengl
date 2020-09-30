#pragma once
#include<GL/glew.h>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCALL(x) clearError();\
    x;\
    ASSERT(glLogCall(#x, __FILE__, __LINE__));

void clearError();
bool glLogCall(const char* function, const char* file, int line);
