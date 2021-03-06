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

#ifndef ORDERED_HASH_SET_H
#define ORDERED_HASH_SET_H

#include <antlr/Definitions.h>
#include <antlr/misc/HashKeyHelper.h>
#include <antlr/misc/HashSet.h>
#include <antlr/misc/Key.h>
#include <antlr/misc/Utils.h>
#include <memory>
#include <stdexcept>
#include <vector>

namespace antlr4 {
namespace misc {

/** A HashSet that remembers the order that the elements were added.
 *  You can alter the ith element with set(i,value) too :)  Unique list.
 *  I need the replace/set-element-i functionality so I'm subclassing
 *  LinkedHashSet.
 */
template <typename T>
class ANTLR_API OrderedHashSet : public HashSet<T>,
                                 public virtual Key<OrderedHashSet<T> >
{
public:

    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;

    OrderedHashSet();

    OrderedHashSet(const OrderedHashSet& other);

    const T* get(antlr_uint32_t i) const;

    /** Replace an existing value with a new value; updates the element
     *  list and the hash table, but not the key as that has not changed.
     *  Returns a pointer to the new value unlike the Java counterpart
     */
    const T* set(antlr_uint32_t i, const T& value);

    bool remove(antlr_uint32_t i);

    /** Add a value to list; keep in hashtable for consistency also;
     *  Key is object itself.  Good for say asking if a certain string is in
     *  a list of strings.
     */
    ANTLR_OVERRIDE
    bool add(const T& value);

    ANTLR_OVERRIDE
    bool remove(const T& value);

    ANTLR_OVERRIDE
    void clear();

    ANTLR_OVERRIDE
    antlr_int32_t hashCode() const;

    ANTLR_OVERRIDE
    bool equals(const Key< OrderedHashSet<T> >* o) const;

    ANTLR_OVERRIDE
    const_iterator begin() const;

    ANTLR_OVERRIDE
    const_iterator end() const;

    /** Return the List holding list of table elements.  Note that you are
     *  NOT getting a copy so don't write to the list.
     */
    const std::vector<T>& elements() const;

    ANTLR_OVERRIDE
    OrderedHashSet<T>* clone() const;

    ANTLR_OVERRIDE
    antlr_auto_ptr< std::vector<const T*> > toPtrArray() const;

    ANTLR_OVERRIDE
    antlr_auto_ptr< std::vector<T> > toArray() const;

    ANTLR_OVERRIDE
    std::string toString() const;

private:

    std::vector<T> _elements;
};


template<typename T>
OrderedHashSet<T>::OrderedHashSet()
{
}

template<typename T>
OrderedHashSet<T>::OrderedHashSet(const OrderedHashSet& other)
    :   Key<OrderedHashSet<T> >(),
        HashSet<T>(other),
        _elements(other._elements)
{
}

template<typename T>
const T* OrderedHashSet<T>::get(antlr_uint32_t i) const
{
    if (i >= _elements.size()) {
        throw std::out_of_range("OrderedHashSet<T>::get index out of range");
    }    
    return &_elements[i];
}

/** Replace an existing value with a new value; updates the element
    *  list and the hash table, but not the key as that has not changed.
    *  Returns a pointer to the new value unlike the Java counterpart
    */
template<typename T>
const T* OrderedHashSet<T>::set(antlr_uint32_t i, const T& value)
{
    if (i >= _elements.size()) {
        throw std::out_of_range("OrderedHashSet<T>::set index out of range");
    }    
    HashSet<T>::remove(_elements[i]); // update the set: remove/add
    HashSet<T>::add(value);
    _elements[i] = value; // update list
    return &_elements[i];
}

template<typename T>
bool OrderedHashSet<T>::remove(antlr_uint32_t i)
{
    if (i >= _elements.size()) {
        throw std::out_of_range("OrderedHashSet<T>::remove index out of range");
    }    
    bool result = HashSet<T>::remove(_elements[i]);
    _elements.erase(_elements.begin() + i);
    return result;
}

/** Add a value to list; keep in hashtable for consistency also;
    *  Key is object itself.  Good for say asking if a certain string is in
    *  a list of strings.
    */
template<typename T>
bool OrderedHashSet<T>::add(const T& value)
{
    bool result = HashSet<T>::add(value);
    if ( result ) {  // only track if new element not in set
        _elements.push_back(value);
    }
    return result;
}

template<typename T>
bool OrderedHashSet<T>::remove(const T&)
{
    throw std::logic_error("OrderedHashSet<T>::remove not supported");
}

template<typename T>
void OrderedHashSet<T>::clear()
{
    _elements.clear();
    HashSet<T>::clear();
}

template<typename T>
antlr_int32_t OrderedHashSet<T>::hashCode() const
{
    HashKeyHelper<T> hash;
    antlr_int32_t hashCode = 1;
    for (typename OrderedHashSet<T>::const_iterator it = _elements.begin(); it != _elements.end(); it++) {
        hashCode = 31*hashCode + hash(*it);
    }
    return hashCode;
}

template<typename T>
bool OrderedHashSet<T>::equals(const Key< OrderedHashSet<T> >* o) const
{
    const OrderedHashSet<T>* other = dynamic_cast<const OrderedHashSet<T>*>(o);
    if (other == NULL) {
        return false;
    }
    return _elements == other->_elements;
}

template<typename T>
typename OrderedHashSet<T>::const_iterator OrderedHashSet<T>::begin() const
{
    return _elements.begin();
}

template<typename T>
typename OrderedHashSet<T>::const_iterator OrderedHashSet<T>::end() const
{
    return _elements.end();
}

/** Return the List holding list of table elements.  Note that you are
    *  NOT getting a copy so don't write to the list.
    */
template<typename T>
const std::vector<T>& OrderedHashSet<T>::elements() const
{
    return _elements;
}

template<typename T>
OrderedHashSet<T>* OrderedHashSet<T>::clone() const
{
    return new OrderedHashSet<T>(*this);
}

template<typename T>
antlr_auto_ptr< std::vector<const T*> > OrderedHashSet<T>::toPtrArray() const
{
    antlr_auto_ptr< std::vector<const T*> > a(new std::vector<const T*>());
    for (typename std::vector<T>::const_iterator it = _elements.begin(); it != _elements.end(); it++)
        a->push_back(&(*it));
    return a;
}

template<typename T>
antlr_auto_ptr< std::vector<T> > OrderedHashSet<T>::toArray() const
{
    return antlr_auto_ptr< std::vector<T> >(new std::vector<T>(_elements));
}

template<typename T>
std::string OrderedHashSet<T>::toString() const
{
    return Utils::stringValueOf(_elements);
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef ORDERED_HASH_SET_H */
