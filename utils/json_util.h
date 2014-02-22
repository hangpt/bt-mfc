/*!
 * @file json_util.h
 *  Created on: Nov 22, 2013
 * @brief Utility for JSON, with is wrapped between JSON_C0.9 and JANNSON
 * @authors Thanh Nguyen, thanhnv@centic.vn or thanh_bk05@yahoo.com
 * @copyright CENTIC (http://www.centic.vn) & ICDREC (http://www.icdrec.edu.vn)
 */

#ifndef JSON_UTIL_H_
#define JSON_UTIL_H_


#include <configs.h>
#if (ALLOC_MEM == DYNAMIC_ALLOC_MEM)
#ifdef __cplusplus
extern "C" {
#endif

#ifdef USE_JANSSON
#include <jansson.h>
#else

#include <json/json.h>
#include <stdio.h>
#include <stdlib.h>
/**
 *@brief Support some macros to map from jansson library to json library
 *
 **/

typedef struct json_object 			json_t;
typedef void 						json_error_t;

json_t*	json_load_file		(const char * file,size_t flag, json_error_t *error);
int 	json_dump_file		(const json_t *json, const char *path, size_t flags);
char* 	json_dumps			(json_t * root,size_t flags);
int 	json_array_remove	(json_t *array, size_t index);


#define json_loads(x,y,z) 						(x != NULL) ? json_tokener_parse((x)) : NULL
#define json_object_get(jobject,key) 			json_object_object_get((jobject),key)
#define json_string_value(jstring) 				((const char*)((jstring)->o.c_string))
#define json_integer_value(jint) 				((jint)->o.c_int)
#define json_bool_value(jbool) 					((jbool)->o.c_boolean)
#define json_real_value(jreal) 					((jreal)->o.c_double)
#define json_is_array(jarray) 					((jarray)->o_type == json_type_array)
#define json_is_int(jint) 						((jint)->o_type == json_type_int)
#define json_is_object(jobject) 				((jobject)->o_type == json_type_object)
#define json_is_real(jreal) 					((jreal)->o_type == json_type_double)
#define json_is_bool(jbool) 					((jbool)->o_type == json_type_boolean)

#define json_integer_set(jint,value) 			(jint)->o.c_int = value
#define json_real_set(jreal,value)				(jreal)->o.c_double = value
#define json_bool_set(jbool,value)				(jbool)->o.c_boolean = value
#define json_string_set(jstring,value)			{if((jstring)->o.c_string ) free((jstring)->o.c_string );  (jstring)->o.c_string = strdup((char*)(value));}

#define json_object_set_new(object,key,value) 	json_object_object_add(object,key,value)
#define json_object_del(object,key)				json_object_object_del(object,key)

#define json_is_string(jstring) 				((jstring)->o_type == json_type_string)
#define json_array_size(x) 						json_object_array_length(x)
//#define json_array_get(x,idx) 				(json_t*)((x)->.c_array->array[idx])
#define json_array_append_new(jarray,value)		json_object_array_add(jarray,value)
#define json_array_insert(jarray,index,value)	json_object_array_put_idx(jarray,index,value)
#define json_array_get(jarray,index)			json_object_array_get_idx(jarray,index)

#define json_string(string) 					json_object_new_string((char*)(string))
#define json_real(jreal) 						json_object_new_double(jreal)
#define json_interger(jint) 					json_object_new_int(jint)
#define json_bool(boolvalue)					json_object_new_boolean(boolvalue)
#define json_true()								json_object_new_boolean(true)
#define json_false()							json_object_new_boolean(false)
#define json_array()							json_object_new_array()
#define json_object()							json_object_new_object()

#define json_is_true(jbool) 					((jbool)->o.c_boolean == TRUE)
#define json_delete(x) 							json_object_put(x)

#endif

#ifdef __cplusplus
}//extern "C" {
#endif

#endif // ALLOC_MEM

#endif /* JSON_UTIL_H_ */
