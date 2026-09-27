
// -*- C++ -*-
// Definition for Win32 Export directives.
// This file is generated automatically by generate_export_file.pl uatm
// ------------------------------
#ifndef UATM_EXPORT_H
#define UATM_EXPORT_H

#include "ace/config-all.h"

#if defined (ACE_AS_STATIC_LIBS) && !defined (UATM_HAS_DLL)
#  define UATM_HAS_DLL 0
#endif /* ACE_AS_STATIC_LIBS && UATM_HAS_DLL */

#if !defined (UATM_HAS_DLL)
#  define UATM_HAS_DLL 1
#endif /* ! UATM_HAS_DLL */

#if defined (UATM_HAS_DLL) && (UATM_HAS_DLL == 1)
#  if defined (UATM_BUILD_DLL)
#    define uatm_Export ACE_Proper_Export_Flag
#    define UATM_SINGLETON_DECLARATION(T) ACE_EXPORT_SINGLETON_DECLARATION (T)
#    define UATM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_EXPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  else /* UATM_BUILD_DLL */
#    define uatm_Export ACE_Proper_Import_Flag
#    define UATM_SINGLETON_DECLARATION(T) ACE_IMPORT_SINGLETON_DECLARATION (T)
#    define UATM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK) ACE_IMPORT_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#  endif /* UATM_BUILD_DLL */
#else /* UATM_HAS_DLL == 1 */
#  define uatm_Export
#  define UATM_SINGLETON_DECLARATION(T)
#  define UATM_SINGLETON_DECLARE(SINGLETON_TYPE, CLASS, LOCK)
#endif /* UATM_HAS_DLL == 1 */

// Set UATM_NTRACE = 0 to turn on library specific tracing even if
// tracing is turned off for ACE.
#if !defined (UATM_NTRACE)
#  if (ACE_NTRACE == 1)
#    define UATM_NTRACE 1
#  else /* (ACE_NTRACE == 1) */
#    define UATM_NTRACE 0
#  endif /* (ACE_NTRACE == 1) */
#endif /* !UATM_NTRACE */

#if (UATM_NTRACE == 1)
#  define UATM_TRACE(X)
#else /* (UATM_NTRACE == 1) */
#  if !defined (ACE_HAS_TRACE)
#    define ACE_HAS_TRACE
#  endif /* ACE_HAS_TRACE */
#  define UATM_TRACE(X) ACE_TRACE_IMPL(X)
#  include "ace/Trace.h"
#endif /* (UATM_NTRACE == 1) */

#endif /* UATM_EXPORT_H */

// End of auto generated file.
