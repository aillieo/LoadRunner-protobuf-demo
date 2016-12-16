/* protobuf config.h for MSVC.  On other platforms, this is generated
 * automatically by autoheader / autoconf / configure. */

/* the location of <hash_map> */
#define HASH_MAP_H <hash_map>

/* the namespace of hash_map/hash_set */
// Apparently Microsoft decided to move hash_map *back* to the std namespace
// in MSVC 2010:
//   http://blogs.msdn.com/vcblog/archive/2009/05/25/stl-breaking-changes-in-visual-studio-2010-beta-1.aspx
// TODO(kenton):  Use unordered_map instead, which is available in MSVC 2010.
#ifdef _WIN32
#if _MSC_VER < 1310 || _MSC_VER >= 1600
#define HASH_NAMESPACE std
#else
#define HASH_NAMESPACE stdext
#endif

/* define if the compiler has hash_map */
#define HAVE_HASH_MAP 1

/* define if the compiler has hash_set */
#define HAVE_HASH_SET 1

/* the location of <hash_set> */
#define HASH_SET_H <hash_set>

#else

#define HASH_SET_H <ext/hash_set>
#define HASH_NAMESPACE stdext
#define HAVE_PTHREAD

#endif