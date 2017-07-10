# Charles-HashMap
Oh, GOD! I must use C++11, so game over. And my thoughts is that:  
the internal data structure is a tree, for each tree node, they have an array contain 16 leaves from `0-F`, node is defined like this:  
```c
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
```
