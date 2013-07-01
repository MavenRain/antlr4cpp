/*
 * [The "BSD license"]
 *  Copyright (c) 2012 Terence Parr
 *  Copyright (c) 2012 Sam Harwell
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Antlr 4 C++ Runtime
 * Gael Hatchue
 */

#ifndef ARRAY_2D_HASH_SET_H
#define ARRAY_2D_HASH_SET_H

#include <Antlr4Definitions.h>
#include <misc/AbstractEqualityComparator.h>
#include <misc/Key.h>
#include <misc/MurmurHash.h>
#include <misc/ObjectEqualityComparator.h>
#include <misc/Traits.h>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <sstream>

namespace antlr4 {
namespace misc {

template <typename T, typename K = T,
          bool K_isBaseOf_T = Traits::isSame<K, T>::value || Traits::isBaseOf<K, T>::value>
class ANTLR_API Array2DHashSet;

template <typename T, typename K>
class ANTLR_API Array2DHashSet<T, K, true> : Key< Array2DHashSet<T, K, true> >
{
public:

    class SetIterator
    {
    };

protected:
    
    struct TVal
    {
        TVal();
        TVal(const T& value);
        TVal(const TVal& other);
        bool hasValue;
        T value;
    };
    
public:

    ~Array2DHashSet();
    
    Array2DHashSet();
    
    Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator);
    
    Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator,
            antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);

    /**
     * Add {@code o} to set if not there; return existing value if already
     * there. This method performs the same operation as {@link #add} aside from
     * the return value.
     */
    const T* getOrAdd(const T& o);
        
    const T* get(const T& o) const;

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    ANTLR_OVERRIDE
    bool operator==(Array2DHashSet<T, K, true>& other) const;

    ANTLR_OVERRIDE
    bool add(const T& t);

    ANTLR_OVERRIDE
    antlr_uint32_t size() const;

    ANTLR_OVERRIDE
    bool isEmpty() const;

    ANTLR_OVERRIDE
    bool contains(const T& o) const;

    bool containsFast(ANTLR_NULLABLE const T* obj) const;

    ANTLR_OVERRIDE
    SetIterator iterator();

    ANTLR_OVERRIDE
    std::vector<T> toArray() const;

    //ANTLR_OVERRIDE
    template <typename U>
    std::vector<U>& toArray(std::vector<U>& a) const;

    ANTLR_OVERRIDE
    bool remove(const T& o);

    bool removeFast(ANTLR_NULLABLE const T* obj);

    ANTLR_OVERRIDE
    bool containsAll(Array2DHashSet<T, K, true>& other) const;

    //ANTLR_OVERRIDE
    //boolean addAll(Collection<? extends T> c);

    //ANTLR_OVERRIDE
    //boolean retainAll(Collection<?> c);

    //ANTLR_OVERRIDE
    //boolean removeAll(Collection<?> c);

    ANTLR_OVERRIDE
    void clear();

    ANTLR_OVERRIDE
    std::string toString();

    std::string toTableString();

protected:
    
    const T* getOrAdd(const T& o, bool& added);
    
    const T* getOrAddImpl(const T& o, bool& added);

    antlr_int32_t getBucket(const T& o) const;

    void expand();
    
    void initialize(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity);

    /**
     * Return an array of {@code T[]} with length {@code capacity}.
     *
     * @param capacity the length of the array to return
     * @return the newly constructed array
     */
    TVal** createBuckets(antlr_int32_t capacity, antlr_int32_t& numBuckets, antlr_int32_t*& sizes) const;

    /**
     * Return an array of {@code T} with length {@code capacity}.
     *
     * @param capacity the length of the array to return
     * @return the newly constructed array
     */
    TVal* createBucket(antlr_int32_t capacity, antlr_int32_t& bucketSize) const;
    
    /* De-allocate buckets */
    void cleanup();


public:
        
	static const antlr_int32_t INITAL_CAPACITY; // must be power of 2
	static const antlr_int32_t INITAL_BUCKET_CAPACITY;
	static const double LOAD_FACTOR;

protected:
    
    ANTLR_NOTNULL
    const AbstractEqualityComparator<K>* comparator;

    TVal** buckets;
    
    antlr_int32_t* bucketSizes;
    
    antlr_int32_t numBuckets;

    /** How many elements in set */
    antlr_uint32_t n;
    
    antlr_uint32_t threshold; // when to expand

    antlr_int32_t currentPrime; // jump by 4 primes each expand or whatever
    antlr_int32_t initialBucketCapacity;
};


template <typename T, typename K>
const antlr_int32_t Array2DHashSet<T, K, true>::INITAL_CAPACITY = 16; // must be power of 2

template <typename T, typename K>
const antlr_int32_t Array2DHashSet<T, K, true>::INITAL_BUCKET_CAPACITY = 8;

template <typename T, typename K>
const double Array2DHashSet<T, K, true>::LOAD_FACTOR = 0.75;


template <typename T, typename K>
Array2DHashSet<T, K, true>::TVal::TVal()
    :   hasValue(false)
{
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::TVal::TVal(const T& value)
    :   hasValue(true),
        value(value)
{
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::TVal::TVal(const TVal& other)
    :   hasValue(other.hasValue),
        value(other.value)
{
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::~Array2DHashSet()
{
    cleanup();
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet()
    :   comparator(NULL),
        buckets(NULL),
        bucketSizes(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(NULL, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator)
    :   comparator(NULL),
        buckets(NULL),
        bucketSizes(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(comparator, INITAL_CAPACITY, INITAL_BUCKET_CAPACITY);
}

template <typename T, typename K>
Array2DHashSet<T, K, true>::Array2DHashSet(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
    :   comparator(NULL),
        buckets(NULL),
        bucketSizes(NULL),
        numBuckets(0),
        n(0),
        threshold((antlr_uint32_t)(INITAL_CAPACITY * LOAD_FACTOR)),
        currentPrime(1),
        initialBucketCapacity(INITAL_BUCKET_CAPACITY)
{
    initialize(comparator, initialCapacity, initialBucketCapacity);
}

template <typename T, typename K>
void Array2DHashSet<T, K, true>::initialize(ANTLR_NULLABLE const AbstractEqualityComparator<K>* comparator,
        antlr_int32_t initialCapacity, antlr_int32_t initialBucketCapacity)
{
    if (comparator == NULL) {
        comparator = &ObjectEqualityComparator<T>::INSTANCE;
    }

    this->comparator = comparator;
    this->buckets = createBuckets(initialCapacity, this->numBuckets, this->bucketSizes);
    this->initialBucketCapacity = initialBucketCapacity;
}

/**
 * Add {@code o} to set if not there; return existing value if already
 * there. This method performs the same operation as {@link #add} aside from
 * the return value.
 */
template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::getOrAdd(const T& o)
{
    bool added = false;
    return getOrAdd(o, added);
}

template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::getOrAdd(const T& o, bool& added)
{
    if ( n > threshold ) expand();
    return getOrAddImpl(o, added);
}

template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::get(const T& o) const
{
    antlr_int32_t b = getBucket(o);
    TVal* bucket = buckets[b];
    if ( bucket==NULL ) return NULL; // no bucket
    for (antlr_int32_t i = 0; i < bucketSizes[b]; i++) {
        const TVal& e = bucket[i];
        if ( !e.hasValue ) return NULL; // empty slot; not there
        if ( comparator->equals(e.value, o) ) return &e.value;
    }
    return NULL;
}

template <typename T, typename K>
antlr_int32_t Array2DHashSet<T, K, true>::hashCode() const
{
    antlr_int32_t hash = MurmurHash::initialize();
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const TVal* bucket = buckets[i];
        if ( bucket==NULL ) continue;
        for (antlr_int32_t j = 0; j < bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) break;
            hash = MurmurHash::update(hash, comparator->hashCode(o.value));
        }
    }
 
    hash = MurmurHash::finish(hash, size());
    return hash;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::operator==(Array2DHashSet<T, K, true>& other) const
{
    if ( other.size() != size() ) return false;
    bool same = this->containsAll(other);
    return same;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::add(const T& t)
{
    bool added = false;
    getOrAdd(t, added);
    return added;
}

template <typename T, typename K>
antlr_uint32_t Array2DHashSet<T, K, true>::size() const
{
    return n;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::isEmpty() const
{
    return n==0;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::contains(const T& o) const
{
    return containsFast(&o);
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::containsFast(ANTLR_NULLABLE const T* obj) const
{
    if (obj == NULL) {
        return false;
    }

    return get(*obj) != NULL;
}

template <typename T, typename K>
typename Array2DHashSet<T, K, true>::SetIterator Array2DHashSet<T, K, true>::iterator()
{
    return typename Array2DHashSet<T, K, true>::SetIterator();
}

template <typename T, typename K>
std::vector<T> Array2DHashSet<T, K, true>::toArray() const
{
    std::vector<T> a;
    a.reserve(size());
    
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const TVal* bucket = buckets[i];
        if ( bucket==NULL ) {
            continue;
        }
        
        for (antlr_int32_t j = 0; j < bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) {
                break;
            }
            
            a.push_back(o.value);
        }
    }
    
    return a;
}

template <typename T, typename K>
template <typename U>
std::vector<U>& Array2DHashSet<T, K, true>::toArray(std::vector<U>& a) const
{
    a.reserve(size());
    
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const TVal* bucket = buckets[i];
        if ( bucket==NULL ) {
            continue;
        }
        
        for (antlr_int32_t j = 0; j < bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) {
                break;
            }
            
            a.push_back(static_cast<U>(o.value));
        }
    }

    return a;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::remove(const T& o)
{
    return removeFast(&o);
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::removeFast(ANTLR_NULLABLE const T* obj)
{
    if (obj == NULL) {
        return false;
    }

    antlr_int32_t b = getBucket(*obj);
    TVal* bucket = buckets[b];
    if ( bucket==NULL ) {
        // no bucket
        return false;
    }

    antlr_int32_t bucketLength = bucketSizes[b];
    for (antlr_int32_t i=0; i<bucketLength; i++) {
        const TVal& e = bucket[i];
        if ( !e.hasValue ) {
            // empty slot; not there
            return false;
        }

        if ( comparator->equals(e.value, *obj) ) {          // found it
            // shift all elements to the right down one
            std::rotate(bucket + i, bucket + i+1, bucket + bucketLength);
            bucket[bucketLength - 1].hasValue = false;
            n--;
            return true;
        }
    }

    return false;
}

template <typename T, typename K>
bool Array2DHashSet<T, K, true>::containsAll(Array2DHashSet<T, K, true>& other) const
{
    for (antlr_int32_t i = 0; i < other.numBuckets; i++) {
        const TVal* bucket = other.buckets[i];
        if ( bucket==NULL ) continue;
        for (antlr_int32_t j = 0; j < other.bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) break;
            if ( !this->containsFast(&o.value) ) return false;
        }
    }
    return true;
}

template <typename T, typename K>
void Array2DHashSet<T, K, true>::clear()
{
    cleanup();
    buckets = createBuckets(INITAL_CAPACITY, this->numBuckets, this->bucketSizes);
    n = 0;
    
}

template <typename T, typename K>
std::string Array2DHashSet<T, K, true>::toString()
{
    if ( size()==0 ) return "{}";

    std::stringstream buf;
    buf << "{";
    bool first = true;
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const TVal* bucket = buckets[i];
        if ( bucket==NULL ) continue;
        for (antlr_int32_t j = 0; j < bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) break;
            if ( first ) first=false;
            else buf << ", ";
            buf << o.value;
        }
    }
    buf << "}";
    return buf.str();    
}

template <typename T, typename K>
std::string Array2DHashSet<T, K, true>::toTableString()
{
    std::stringstream buf;
    bool first = true;
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        const TVal* bucket = buckets[i];
        if ( bucket==NULL ) {
            buf << "null\n";
            continue;
        }
        buf << "[";
        for (antlr_int32_t j = 0; j < bucketSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( first ) first=false;
            else buf << " ";
            if ( !o.hasValue ) buf << "_";
            else buf << o.value;
        }
        buf << "]\n";
    }
    return buf.str();
}

template <typename T, typename K>
const T* Array2DHashSet<T, K, true>::getOrAddImpl(const T& o, bool& added)
{
    antlr_int32_t b = getBucket(o);
    TVal* bucket = buckets[b];
    added = false;

    // NEW BUCKET
    if ( bucket==NULL ) {
        added = true;
        bucket = createBucket(initialBucketCapacity, bucketSizes[b]);
        bucket[0].hasValue = true;
        bucket[0].value = o;
        buckets[b] = bucket;
        n++;
        return &bucket[0].value;
    }

    // LOOK FOR IT IN BUCKET
    antlr_int32_t bucketLength = bucketSizes[b];
    for (antlr_int32_t i=0; i<bucketLength; i++) {
        TVal& existing = bucket[i];
        if ( !existing.hasValue ) { // empty slot; not there, add.
            added = true;
            existing.hasValue = true;
            existing.value = o;
            n++;
            return &existing.value;
        }
        if ( comparator->equals(existing.value, o) ) return &existing.value; // found existing, quit
    }

    // FULL BUCKET, expand and add to end
    TVal* oldBucket = bucket;    
    bucket = new TVal[bucketLength * 2];
    memcpy(bucket, oldBucket, sizeof(TVal) * bucketLength);
    memset(bucket + bucketLength, 0, sizeof(TVal) * bucketLength);
    delete[] oldBucket;

    buckets[b] = bucket;
    bucketSizes[b] = bucketLength * 2;
    
    // add to end
    added = true;
    bucket[bucketLength].hasValue = true;
    bucket[bucketLength].value = o;
    n++;
    return &bucket[bucketLength].value;
}

template <typename T, typename K>
antlr_int32_t Array2DHashSet<T, K, true>::getBucket(const T& o) const
{
    antlr_int32_t hash = comparator->hashCode(o);
    antlr_int32_t b = hash & (numBuckets-1); // assumes len is power of 2
    return b;
}

template <typename T, typename K>
void Array2DHashSet<T, K, true>::expand()
{
    TVal** old = buckets;
    antlr_int32_t oldNumBuckets = numBuckets;
    antlr_int32_t* oldSizes = bucketSizes;
    
    currentPrime += 4;
    antlr_int32_t newCapacity = numBuckets * 2;
    TVal** newTable = createBuckets(newCapacity, numBuckets, bucketSizes);
    antlr_int32_t* newBucketLengths = new antlr_int32_t[numBuckets];
    memset(newBucketLengths, 0, sizeof(antlr_int32_t) * numBuckets);
    buckets = newTable;
    threshold = (antlr_uint32_t)(newCapacity * LOAD_FACTOR);
    // System.out.println("new size="+newCapacity+", thres="+threshold);
    
    // rehash all existing entries
    antlr_uint32_t oldSize = size();
    for (antlr_int32_t i = 0; i < oldNumBuckets; i++) {
        const TVal* bucket = old[i];
        if ( bucket==NULL ) {
            continue;
        }

        for (antlr_int32_t j = 0; j < oldSizes[i]; j++) {
            const TVal& o = bucket[j];
            if ( !o.hasValue ) {
                break;
            }

            antlr_int32_t b = getBucket(o.value);
            antlr_int32_t bucketLength = newBucketLengths[b];
            TVal* newBucket = NULL;
            if (bucketLength == 0) {
                // new bucket
                newBucket = createBucket(initialBucketCapacity, bucketSizes[b]);
                newTable[b] = newBucket;
            }
            else {
                newBucket = newTable[b];
                if (bucketLength == bucketSizes[b]) {
                    // expand
                    TVal* oldBucket = newBucket;    
                    newBucket = new TVal[bucketLength * 2];
                    memcpy(newBucket, oldBucket, sizeof(TVal) * bucketLength);
                    memset(newBucket + bucketLength, 0, sizeof(TVal) * bucketLength);
                    delete[] oldBucket;
                    
                    newTable[b] = newBucket;
                    bucketSizes[b] = bucketLength * 2;                    
                }
            }

            newBucket[bucketLength] = o;
            newBucketLengths[b]++;
        }
        
        // cleanup old bucket
        delete[] bucket;
    }
    
    // cleanup old table
    delete[] old;
    delete[] oldSizes;
    delete[] newBucketLengths;

    assert(n == oldSize);
}

/**
 * Return an array of {@code T[]} with length {@code capacity}.
 *
 * @param capacity the length of the array to return
 * @return the newly constructed array
 */
template <typename T, typename K>
typename Array2DHashSet<T, K, true>::TVal** Array2DHashSet<T, K, true>::createBuckets(antlr_int32_t capacity, antlr_int32_t& numBuckets, antlr_int32_t*& sizes) const
{
    TVal** table = new TVal*[capacity];
    memset(table, 0, sizeof(TVal*) * capacity);
    numBuckets = capacity;
    sizes = new antlr_int32_t[capacity];
    memset(sizes, 0, sizeof(antlr_int32_t) * capacity);
    return table;
}

/**
 * Return an array of {@code T} with length {@code capacity}.
 *
 * @param capacity the length of the array to return
 * @return the newly constructed array
 */
template <typename T, typename K>
typename Array2DHashSet<T, K, true>::TVal* Array2DHashSet<T, K, true>::createBucket(antlr_int32_t capacity, antlr_int32_t& bucketSize) const
{
    TVal* bucket = new TVal[capacity];
    memset(bucket, 0, sizeof(TVal) * capacity);
    bucketSize = capacity;
    return bucket;
}

/* De-allocate buckets */
template <typename T, typename K>
void Array2DHashSet<T, K, true>::cleanup()
{
    for (antlr_int32_t i = 0; i < numBuckets; i++) {
        delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketSizes;
    buckets = NULL;
    bucketSizes = NULL;
    n = 0;
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef ARRAY_2D_HASH_SET_H */
