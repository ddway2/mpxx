#ifndef __MPXX_CONFIG_H__
#define __MPXX_CONFIG_H__

#if defined WINDOWS || defined __CYGWIN__
  #define MPXX_IMPORT_HELPER __declspec(dllimport)
  #define MPXX_EXPORT_HELPER __declspec(dllexport)
  #define MPXX_LOCAL_HELPER
#else
  #if __GNUC__ >= 4
    #define MPXX_IMPORT_HELPER __attribute__ ((visibility ("default")))
    #define MPXX_EXPORT_HELPER __attribute__ ((visibility ("default")))
    #define MPXX_LOCAL_HELPER  __attribute__ ((visibility ("hidden")))
  #else
    #define MPXX_IMPORT_HELPER
    #define MPXX_EXPORT_HELPER
    #define MPXX_LOCAL_HELPER
  #endif
#endif

#ifdef MPXX_EXPORTS /* defined when using */
  #define MPXX_API MPXX_EXPORT_HELPER
#else
  #define MPXX_API MPXX_IMPORT_HELPER
#endif

#define MPXX_LOCAL MPXX_LOCAL_HELPER

#endif  // __MPXX_CONFIG_H__