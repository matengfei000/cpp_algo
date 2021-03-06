#include "dynamic_array.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct Test
{
	int a;
	int b;
	int c;
}Test;


void travel(void* data)
{
//	Test *test = (Test*)data;

//	printf("a=%d,b=%d,c=%d\n",test->a,*test->b,test->c);
}


void destroy_test(void* data)
{
	Test *test = (Test*)data;
	if(test)
	{
//		free(test->b);
//		test->b = NULL;
	}
}

int find_test(const void *source,const void *find)
{
	Test *test_source  = (Test*)source;
	Test *test_find  = (Test*)find;
	if(test_source->a == test_find->a && test_source->b == test_find->b && test_source->c == test_find->c)
		return 1;
	return -1;
}














int dynamic_array_init(dynamic_array * dynamic_array,const unsigned int unit_size,const unsigned int init_count)
{


	if(dynamic_array == NULL)
	{
		return -1;
	}

	dynamic_array->data = (void*)calloc(unit_size,init_count);

	if(dynamic_array->data == NULL)
	{
		return -1;
	}

	dynamic_array->cur_index = 0;
	dynamic_array->unit_size = unit_size;
	dynamic_array->last_index = init_count;

	

	return 0;
}
int dynamic_array_push(dynamic_array * dynamic_array,void *data)
{
	if(!dynamic_array)
	{
		return -1;
	}
	
	if(dynamic_array->cur_index == dynamic_array->last_index)
	{
		dynamic_array->data = (void*)realloc(dynamic_array->data,dynamic_array->cur_index*2*dynamic_array->unit_size);
		dynamic_array->last_index *= 2;
	}

	memcpy(dynamic_array->data+dynamic_array->cur_index*dynamic_array->unit_size,data, dynamic_array->unit_size);
	dynamic_array->cur_index++;


	return 0;
}

void dynamic_array_travel(dynamic_array * dynamic_array,const dynamic_array_travel_fun fun)
{
	int index = 0;
	if(dynamic_array && dynamic_array->cur_index)
	{
		for(index = 0; index < dynamic_array->cur_index;index++)
		{
			fun(dynamic_array->data+index*dynamic_array->unit_size);
		}
	}
}

void dynamic_array_destroy(dynamic_array * dynamic_array,const  dynamic_array_travel_fun fun)
{
	if(dynamic_array && dynamic_array->data)
	{

		if(fun)
		{
			dynamic_array_travel(dynamic_array,fun);
		}

		free(dynamic_array->data);
		dynamic_array->data = NULL;
	}
}
int   dynamic_array_find(dynamic_array * dynamic_array,const  dynamic_array_find_fun fun,const void* find)
{
	int index = 0;
	int ret = -1;
	if(dynamic_array && dynamic_array->cur_index)
	{
		for(index = 0; index < dynamic_array->cur_index;index++)
		{
			ret = fun(dynamic_array->data+index*dynamic_array->unit_size,find);
			if(ret == 1)
			{
				return index;
			}
		}
	}

	return -1;

}
void * dynamic_array_getByIndex(dynamic_array * dynamic_array,const int index)
{
	if(!dynamic_array_empty(dynamic_array) && index > dynamic_array_size(dynamic_array))
	{
		return NULL;
	}

	return NULL;
}
int dynamic_array_empty(dynamic_array * dynamic_array)
{
	return dynamic_array->cur_index == 0 ? 1:0;

}
int dynamic_array_size(dynamic_array * dynamic_array)
{
	return dynamic_array->cur_index;
}
int dynamic_array_maxsize(dynamic_array * dynamic_array)
{
	return dynamic_array->last_index;
}
void test()
{
	dynamic_array dynamic_array = {};
	dynamic_array_init(&dynamic_array,sizeof(Test),10);

	int i = 0;
	for(i = 0 ; i < 10000; i++)
	{
		Test test;
		test.a = i;
		test.b = i;
		test.c = i;
		dynamic_array_push(&dynamic_array,&test);
	}
	dynamic_array_travel(&dynamic_array,travel);

	
	Test test={0,0,0};
	printf("%d\n",dynamic_array_find(&dynamic_array,find_test,&test));


	dynamic_array_destroy(&dynamic_array,NULL);
}


int main()
{
	test();
	return 0;
}

