/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_pjom.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream> 

#include <assert.h>

using  namespace std;
/* If you declare any globals in php_pjom.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(pjom)
*/

/* True global resources - no need for thread safety here */
static int le_pjom;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("pjom.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_pjom_globals, pjom_globals)
    STD_PHP_INI_ENTRY("pjom.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_pjom_globals, pjom_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_pjom_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_pjom_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "pjom", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string pom_pjom(string params, string p1, string p2)
    */

#define DEBUG 

#ifdef DEBUG

#include <jni.h>

JNIEnv *env = NULL;
JavaVM *jvm = NULL;


jstring stoJstring(JNIEnv* env, const char* pat);
char* jstringTostring(JNIEnv* env, jstring jstr);
int callJava( char *src_str, int src_len , char* out_str,char *classpath,int classpath_len, char* classname);

#endif

PHP_FUNCTION(pom_pjom)
{
	char *params = NULL;
	char *p1 = NULL;
	char *p2 = NULL;
	int argc = ZEND_NUM_ARGS();
	int params_len;
	int p1_len;
	int p2_len;

	if (zend_parse_parameters(argc TSRMLS_CC, "sss", &params, &params_len, &p1, &p1_len, &p2, &p2_len) == FAILURE) 
		return;

	char* outSrc ;
	int   callRet ;

	outSrc  = (char *) emalloc( 4*1024 );

#ifdef DEBUG
	callRet = callJava( params , params_len , outSrc,p1,p1_len ,p2);
	RETURN_STRINGL(outSrc, callRet, 0);
#else
	RETURN_STRINGL(outSrc, strlen(outSrc), 0);
#endif

	efree(outSrc);



}
/* }}} */

#ifdef DEBUG

int callJava( char *src_str, int src_len , char* out_str,char *classpath,int classpath_len, char* classname)
{
	char* classPathStr =  (char *) emalloc(classpath_len+50); //[classpath_len+50] = {0};
	memset(classPathStr, 0, sizeof(classPathStr));

	strcat(classPathStr,"-Djava.class.path=.:");
	strcat(classPathStr,classpath);

	// JNIEnv *env = NULL;
	// JavaVM *jvm = NULL;
	
	JavaVMOption options[2];
    JavaVMInitArgs vm_args;
    long status = 0;
    jclass cls;
    jmethodID mid;
    jint square;
    jboolean jnot;
    jobject jobj;
    
    if(NULL == jvm ) {
	    options[0].optionString = "-Djava.compiler=NONE";
	    options[1].optionString = classPathStr;//"-Djava.class.path=.:./tests/pjb.jar";
	    //options[2].optionString = "-verbose:jni"; //用于跟踪运行时的信息
	    vm_args.version = JNI_VERSION_1_4;          // JDK版本号
	    vm_args.nOptions = 2;
	    vm_args.options = options;
	    vm_args.ignoreUnrecognized = JNI_TRUE;
	    status = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);

	    // printf("classpath: %s, classname: %s \n", options[1].optionString,classname);
	}


	if(status != JNI_ERR){
		// printf("classpath: %s, classname: %s \n", options[1].optionString,classname);

		cls = env->FindClass(classname);//"com/test/MyTest");  // 在这里查找java类
        if(cls !=0){
	        mid = env->GetMethodID(cls,"<init>","()V");
	        if(mid !=0){
	        	jobj = env->NewObject(cls,mid);
	        }else{
	        	// jvm->DestroyJavaVM();
	        	if(classPathStr)efree(classPathStr);
	        	return 0;
	        }

	        mid = env->GetMethodID(cls, "pom_pjom","(Ljava/lang/String;)Ljava/lang/String;"); 
	        if(mid !=0){ 
			    jstring arg = stoJstring(env, src_str);  
			    jstring msg = (jstring) env->CallObjectMethod(jobj, mid, arg); 
			    char*   tmp = jstringTostring(env, msg);
			    int     len = strlen(tmp); 
			    memcpy(out_str, tmp, len);
			    free(tmp);
			    // jvm->DestroyJavaVM();
			    if(classPathStr)efree(classPathStr);
			    return len;
			}
        }
        // jvm->DestroyJavaVM();
	}
	if(classPathStr)efree(classPathStr);
	return 0;
}




jstring stoJstring(JNIEnv* env, const char* pat)
{
	jclass strClass = env->FindClass("java/lang/String");
	jmethodID ctorID = env->GetMethodID(strClass, "<init>", "([BLjava/lang/String;)V");
	jbyteArray bytes = env->NewByteArray(strlen(pat));
	env->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*)pat);
	jstring encoding = env->NewStringUTF("utf-8");
	return (jstring)env->NewObject(strClass, ctorID, bytes, encoding);
}


char* jstringTostring(JNIEnv* env, jstring jstr)
{
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr,JNI_FALSE);
	if(alen > 0){
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}

#endif


/* {{{ php_pjom_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_pjom_init_globals(zend_pjom_globals *pjom_globals)
{
	pjom_globals->global_value = 0;
	pjom_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(pjom)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(pjom)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(pjom)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(pjom)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pjom)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "pjom support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ pjom_functions[]
 *
 * Every user visible function must have an entry in pjom_functions[].
 */
const zend_function_entry pjom_functions[] = {
	PHP_FE(confirm_pjom_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(pom_pjom,	NULL)
	PHP_FE_END	/* Must be the last line in pjom_functions[] */
};
/* }}} */

/* {{{ pjom_module_entry
 */
zend_module_entry pjom_module_entry = {
	STANDARD_MODULE_HEADER,
	"pjom",
	pjom_functions,
	PHP_MINIT(pjom),
	PHP_MSHUTDOWN(pjom),
	PHP_RINIT(pjom),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(pjom),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(pjom),
	PHP_PJOM_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_PJOM
ZEND_GET_MODULE(pjom)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
