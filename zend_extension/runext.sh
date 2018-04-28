#!/bin/sh
exec php -d "zend_extension=`pwd`/modules/aflphp.so" $@
