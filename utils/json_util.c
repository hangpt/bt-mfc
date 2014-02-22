/*
 * json_util.c
 *
 *  Created on: Nov 22, 2013
 *      Author: nvthanh
 */


#include "json_util.h"

#include <stdio.h>

#if (PLATFORM_USED == PLATFORM_LINUX)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#endif

#ifndef USE_JANSSON

json_t *json_load_file(const char * file,size_t flag, json_error_t *error)
{
	if(!file) return NULL;
	json_t * out=NULL;
#if (PLATFORM_USED == PLATFORM_LINUX)
	off_t fz=0;
	int fd = open(file,O_RDWR);
	if(fd>0){
		fz = lseek(fd,0,SEEK_END);
		lseek(fd,0,SEEK_SET);
		char * str = (char *)malloc((size_t ) fz);
		if(!str) {
			perror("Out of memory");
			close(fd);
			return NULL;
		}
//		printf("file size %d\n",fz);
		if(read(fd,(void*)str,(size_t ) fz) < 0){
			perror("read file error\n");
			close(fd);
			free(str);
			return NULL;
		}
		printf("string: <%s>\n",str);
		close(fd);
		out= json_loads(str,0,NULL);
		free(str);
	}else{
		perror("Open file failed\n");
	}
#elif (PLATFORM_USED == PLATFORM_WINDOWS)

#else

#endif
	return  out;
}

int 	json_dump_file(const json_t *json, const char *path, size_t flags)
{
	if(!path || !json) return 1;
#if (PLATFORM_USED == PLATFORM_LINUX)
	char cmd[1024];
	sprintf(cmd,"rm -f \"%s\"",path);
	system(cmd);
	int fd = open(path,O_RDWR | O_CREAT);
	if(fd>0){
		char * str = json_dumps((json_t*)json,0);
		if(str){
			write(fd,str,strlen((const char*)str));
		}
		write(fd,"\n",1);
		close(fd);
	}else{
		perror("Open file failed\n");
		return 1;
	}
#elif (PLATFORM_USED == PLATFORM_WINDOWS)

#else

#endif
	return 0;
}

inline char* json_dumps(json_t * root,size_t flags){
	return	(char*)json_object_to_json_string(( json_t *)root) ;
}

int json_array_remove(json_t *array, size_t index)
{
	if(json_array_size(array) <= index)return -1;
	void *t;
	array->o.c_array->length--;
	array->o.c_array->size--;
	if(array->o.c_array->array[index]) array->o.c_array->free_fn(array->o.c_array->array[index]);
	t=malloc(array->o.c_array->size* sizeof(void*));
	if(index>0){
		memcpy(t,array->o.c_array->array , (index)* sizeof(void*));
	}
	if(index < array->o.c_array->length){
		memcpy(t,& array->o.c_array->array[index+1], (array->o.c_array->length - index)* sizeof(void*) );
	}
	free(array->o.c_array->array);
	array->o.c_array->array=(void **)t;
	return 0;
}
#endif
