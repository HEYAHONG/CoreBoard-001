#ifndef VERSION_H_INCLUDED
#define VERSION_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#ifndef VERSION
#define VERSION    testing_version
#endif // VERSION

#define VERSION_TO_STRING1(x) #x
#define VERSION_TO_STRING(x) VERSION_TO_STRING1(x)

#define VERSION_STRING VERSION_TO_STRING(VERSION)

#ifdef PACKAGE_VERSION
#define PACKAGE_VERSION_STRING VERSION_TO_STRING(PACKAGE_VERSION)
#define FULL_VERSION_STRING PACKAGE_VERSION_STRING
#else
#define FULL_VERSION_STRING VERSION_STRING
#endif // PACKAGE_VERSION

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // VERSION_H_INCLUDED
