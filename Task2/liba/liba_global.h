#ifndef LIBA_GLOBAL_H
#define LIBA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBA_LIBRARY)
#  define LIBA_EXPORT Q_DECL_EXPORT
#else
#  define LIBA_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBA_GLOBAL_H
