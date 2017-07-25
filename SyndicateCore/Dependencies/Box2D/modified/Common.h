#ifdef SYNDICATE_DYNAMIC
#	define SYNDICATE_API		__declspec(dllexport)
#	define SYNDICATE_TEMPLATE
#else
#	define SYNDICATE_API		__declspec(dllimport)
#	define SYNDICATE_TEMPLATE   extern
#endif