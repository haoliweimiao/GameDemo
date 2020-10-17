#include <iostream>
#include <map>
#include <string.h>
#include <stdio.h>
#include "cache_file.h"

/**
 * 全局缓存变量
 */
std::map<std::string, std::string> gCacheMap;

/**
 * map操作方法实例
 */
void test_cache()
{
    const char *queryKey = "test";
    char *testValue = "testValue";
    cache_insert(queryKey, testValue);
    char query[1024];
    memset(query, '\0', 1);
    cache_query(queryKey, query);
    printf("query %s value %s in main \n", queryKey, query);
    cache_remove(queryKey);
    memset(query, '\0', 1);
    cache_query(queryKey, query);
    printf("query %s value %s in main \n", queryKey, query ? "NULL" : query);
}

CFG_API int cache_insert(const char *key, const char *value)
{
    using namespace std;
    // 第一种 用insert函數插入pair
    // gCacheMap.insert(pair<string, string>(key, value));

    // 第二种 用insert函数插入value_type数据
    pair<map<string, string>::iterator, bool> insertPair;
    insertPair = gCacheMap.insert(map<string, string>::value_type(key, value));
    // 我们通过pair的第二个变量来知道是否插入成功，它的第一个变量返回的是一个map的迭代器，
    // 如果插入成功的话insertPair.second应该是true的，否则为false。
    if (!insertPair.second)
    {
        printf("insert %s in cache, value:%s failed \n", key, value);
        return FUN_ERROR_CACHE_INSERT_FAILED;
    }

    // 第三种 用"array"方式插入
    // gCacheMap[111] = "insert_value";
    printf("insert %s in cache, value:%s success \n", key, value);
    return FUN_NORMAL;
}

/**
 * 从缓存中查询数据
 */
CFG_API int cache_query(const char *key, char *value)
{
    using namespace std;
    memset(value, '\0', 1);

    // find 返回迭代器指向当前查找元素的位置否则返回map::end()位置
    map<string, string>::iterator iter = gCacheMap.find(key);

    if (iter != gCacheMap.end())
    {
        strcat(value, iter->second.c_str());
        printf("query %s from cache, value:%s \n", key, value);
        return FUN_NORMAL;
    }
    else
    {
        printf("query %s from cache, error \n", key);
        return FUN_ERROR_CACHE_QUERY_FAILED;
    }
}

/**
* 从缓存中移除数据
*/
CFG_API int cache_remove(const char *key)
{
    // //迭代器刪除
    // iter = gCacheMap.find("123");
    // gCacheMap.erase(iter);

    // //用关键字刪除
    // int n = gCacheMap.erase("123"); //如果刪除了會返回1，否則返回0

    // //用迭代器范围刪除 : 把整个map清空
    // gCacheMap.erase(gCacheMap.begin(), gCacheMap.end());
    // //等同于gCacheMap.clear()

    int n = gCacheMap.erase(key);
    if (n == 1)
    {
        printf("remove %s from cache success", key);
        return FUN_NORMAL;
    }
    else
    {
        printf("remove %s from cache failed", key);
        return FUN_ERROR_CACHE_REMOVE_FAILED;
    }
}