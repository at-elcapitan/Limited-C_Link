AC_INIT([AT_C/LINK], [0.0.4], [at-elcapitan])
AC_CONFIG_HEADERS([src/ac_config.h])

AC_PROG_CC

AC_COPYRIGHT([
AT_C/LINK (c) by Vladislav 'ElCapitan' Nazarov

AT_C/LINK is licensed under a
Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International
License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
])

AC_CHECK_HEADER([jansson.h], [], 
[
  AC_MSG_ERROR([jansson.h not found, please install the jansson library])
])

AC_CHECK_HEADER([concord/discord.h], [], 
[
  AC_MSG_ERROR([concord/discord.h not found, please install the concord library])
])

AC_CHECK_SIZEOF([unsigned long long], [8])

if test "$ac_cv_sizeof_unsigned_long_long" = "8"; then
    AC_DEFINE([__ULL_OK], [1], [2])
fi

AC_CHECK_SIZEOF([int], [4])

if test "$ac_cv_sizeof_int" = "4"; then
    AC_DEFINE([__INT_OK], [1], [int is 4 bytes])
fi

AC_OUTPUT