#ifndef SSAS_H
#define SSAS_H

#include <QtCore>

#if defined(SSAS_COMPILE_LIBRARY)
#  define SSAS_LIB_DECL Q_DECL_EXPORT
#elif defined(QTEP_USE_LIBRARY)
#  define SSAS_LIB_DECL Q_DECL_IMPORT
#else
#  define SSAS_LIB_DECL
#endif
#endif // SSAS_H
