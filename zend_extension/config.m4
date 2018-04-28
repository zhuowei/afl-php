PHP_ARG_ENABLE(AFLPHP, whether to enable afl-php support, 
[ --enable-aflphp   Enable afl-php support])

if test "$PHP_AFLPHP" = "yes"; then
   AC_DEFINE(HAVE_AFLPHP, 1, [Whether you have afl-php])
   PHP_NEW_EXTENSION(aflphp, aflphp.c, $ext_shared)
fi
