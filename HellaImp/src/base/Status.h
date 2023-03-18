#pragma once



/*
	@author:Haruluya.
	@function:core marcos.
*/

#define HELLA_MAXINT INT_MAX
#define HELLA_ARRAY_SIZE 99

#include <assert.h>

#define HELLA_ASSERT_MEMORY_MALLOC(cod)(assert(cod)) 
#define HELLA_MALLOC(n, type) ((type *) malloc((n)* sizeof(type)))
#define HELLA_REALLOC(base, size) realloc(base,(size)*sizeof(decltype(*base)))
#define HELLA_FREE(p) free(p); p = NULL;


#define HELLA_ASSERT_INDEX_INFEASIBLE(i,le,rt) \
			if (i < le || i > rt) { \
				HELLA_CORE_ERROR("INDEX_INFEASIBLE");\
				return Status::HELLA_INFEASIBLE; \
			}


namespace Hella {

	//status of function.
	enum class Status {
		HELLA_TRUE,
		HELLA_FALSE,
		HELLA_OK,
		HELLA_ERROR,
		HELLA_INFEASIBLE,
		HELLA_OVERFLOW,
		HELLA_NOT_FOUND,
	};





	//typedef int ElemType;
}