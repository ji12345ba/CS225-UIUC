/**
 * @file hashes.h
 * Definition of a namespace containing a templatized hash function.
 *
 * @author Chase Geigle
 * @date Summer 2012
 *
 * @author Jordi Paris Ferrer
 * @date Fall 2019
 */

#pragma once

#include <string>

/**
 * hashes namespace: a collection of templated hash functions.
 *
 * @author Chase Geigle
 * @date Summer 2012
 *
 * @author Jordi Paris Ferrer
 * @data Fall 2019
 */
namespace hashes
{
    /**
     * Computes the hash code of a given key (templated), and returns it modulo
     * size for use in HashTable applications. This function **must** be
     * specialized in order for one of SCHashTable, LPHashTable, or DHHashTable
     * to contain keys of the specialized type.
     *
     * @param key The key to be hashed.
     * @param size What to modulo the hashcode by.
     * @return The hashcode, modulo size for use as a HashTable index.
     */
    template <class K>
    unsigned int hash(const K& key, int size);

    /**
     * Computes the secondary hash code of a given key (templated), and returns
     * it modulo size for use in HashTable applications. This function **must**
     * be specialized in order for DHHashTable to contain keys of the
     * specialized type.
     *
     * This function will never return 0
     *
     * @param key The key to be hashed.
     * @param size What to modulo the hashcode by.
     * @return The hashcode, modulo size for use as a HashTable index.
     */
    template <class K>
    unsigned int secondary_hash(const K& key, int size);
}
