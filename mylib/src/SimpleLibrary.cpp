#ifdef SIMPLELIBRARY_EXPORTS
#define SIMPLELIBRARY_API __declspec(dllexport)
#else
#define SIMPLELIBRARY_API __declspec(dllimport)
#endif

extern SIMPLELIBRARY_API int nSimpleLibrary;

SIMPLELIBRARY_API int Add(int a, int b);