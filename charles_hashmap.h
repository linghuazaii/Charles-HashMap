#ifndef _CHARLES_HASHMAP_H
#define _CHARLES_HASHMAP_H
/**
 * File: charles_hashmap.h
 * Description: hash map implementation
 * Author: Charles,Liu. 2017-7-10
 * Mailto: charlesliu.cn.bj@gmail.com
 */
#include <inttypes.h>
#include <typeinfo> 
#include <string>
using std::string;

/**
 * for conflicts, only the first one will be kept
 */

#define LEAVES 16

template<class T>
struct tree_node_t {
    /* for number 0, sdbm hash is 0, so use int64_t to store hash. -1 means it is not an end node */
    int64_t hash; 
    T value;
    /* ref_cnt is used to do delete */
    uint32_t ref_cnt;
    struct tree_node_t<T> *leaves[LEAVES];
    struct tree_node_t<T> *next;
};

template<class T>
struct is_pointer_struct { static const bool value = false; };

template<class T>
struct is_pointer_struct<T*> { static const bool value = true; };

template<class T>
struct is_pointer(T &var) {
    return is_pointer_struct<T>::value;
}

/**
 * after simple testing, sdbm hash is the best one
 * [Hash Function Test](https://github.com/linghuazaii/hash_function_and_testing)
 */
uint32_t sdbm_hash(const char *str, uint32_t length) {
    uint32_t hval = 0;
    for (int i = 0; i < length; ++i)
        hval = (int)str[i] + (hval << 6) + (hval << 16) - hval;
    return hval;
}

template<class T>
uint32_t hash(T &key) {
    return sdbm_hash((char *)&key, (uint32_t)sizeof(T));
}

template<>
uint32_t hash(string &key) {
    return sdbm_hash(key.c_str(), key.length());
}

template<class T>
tree_node_t<T> *alloc_node() {
    tree_node_t<T> *node = new tree_node_t<T>;
    node->hash = -1;
    T var; /* just for determine whether T is pointer type */
    if (is_pointer(var))
        node->value = NULL;
    else
        node->value = T();
    node->ref_cnt = 0;
    memset(node->leaves, 0, LEAVES);
    node->next = NULL;
    
    return node;
}

class CharlesMap {
public:
    CharlesMap() {
        //root = NULL;
    }
    ~CharlesMap() {
        /* pass */
    }
    template<class K, class V>
    int insert(K key, V v) {
    }
private:
    /* just a start, not store anything */
    tree_node_t<int> *root;
};

#endif
