/**
 * cache save file
 */
#ifndef cache_file_h
#define cache_file_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <module_base/cfg_base.h>

    /**
    * 添加数据到缓存
    */
    CFG_API int cache_insert(const char *key, const char *value);
    /**
    * 从缓存中查询数据
    */
    CFG_API int cache_query(const char *key, char *value);
    /**
    * 从缓存中移除数据
    */
    CFG_API int cache_remove(const char *key);

#ifdef __cplusplus
}
#endif

#endif /* cache_file_h */
