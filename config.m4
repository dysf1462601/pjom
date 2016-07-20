dnl $Id$
dnl config.m4 for extension pjom

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(pjom, for pjom support,
dnl Make sure that the comment is aligned:
dnl [  --with-pjom             Include pjom support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(pjom, whether to enable pjom support,
 Make sure that the comment is aligned:
 [  --enable-pjom           Enable pjom support])

if test "$PHP_PJOM" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-pjom -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/pjom.h"  # you most likely want to change this
  dnl if test -r $PHP_PJOM/$SEARCH_FOR; then # path given as parameter
  dnl   PJOM_DIR=$PHP_PJOM
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for pjom files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PJOM_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PJOM_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the pjom distribution])
  dnl fi

  dnl # --with-pjom -> add include path
  dnl PHP_ADD_INCLUDE($PJOM_DIR/include)

  dnl # --with-pjom -> check for lib and symbol presence
  dnl LIBNAME=pjom # you may want to change this
  dnl LIBSYMBOL=pjom # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PJOM_DIR/$PHP_LIBDIR, PJOM_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PJOMLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong pjom lib version or lib not found])
  dnl ],[
  dnl   -L$PJOM_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PJOM_SHARED_LIBADD)

  PHP_NEW_EXTENSION(pjom, pjom.c, $ext_shared)
fi
