// Contents of DLLDefines.h
#ifndef _LibEditorModel_DLLDEFINES_H_
#define _LibEditorModel_DLLDEFINES_H_

/* Cmake will define LibEditorModel_EXPORTS on Windows when it
configures to build a shared library. If you are going to use
another build system on windows or create the visual studio
projects by hand you need to define LibEditorModel_EXPORTS when
building a DLL on windows.
*/
// We are using the Visual Studio Compiler and building Shared libraries

#if defined (_WIN32)
#if defined(LibEditorModel_EXPORTS)
#define  EXPORT __declspec(dllexport)
#else
#define  EXPORT __declspec(dllimport)
#endif /* LibEditorModel_EXPORTS */
#else /* defined (_WIN32) */
#define EXPORT
#endif

#endif /* _LibEditorModel_DLLDEFINES_H_ */