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

#ifndef INTSET_H
#define INTSET_H

#include <Antlr4Definitions.h>
#include <misc/Key.h>
#include <list>
#include <memory>
#include <string>

namespace antlr4 {
namespace misc {

/** A generic set of ints.
 *
 *  @see IntervalSet
 */
class ANTLR_API IntSet : public virtual Key<IntSet>
{
public:
    
    virtual ~IntSet();

    /** Add an element to the set */
    virtual void add(antlr_int32_t el) = 0;

    /** Add all elements from incoming set to this set.  Can limit
     *  to set of its own type. Return "this" so we can chain calls.
     */
    virtual IntSet* addAll(const IntSet* set) = 0;

    /** Return the intersection of this set with the argument, creating
     *  a new set.
     */
    virtual IntSet* and_(const IntSet* a) const = 0;

    virtual IntSet* complement(const IntSet* elements) const = 0;

    virtual IntSet* or_(const IntSet* a) const = 0;

    virtual IntSet* subtract(const IntSet* a) const = 0;

    /** Return the size of this set (not the underlying implementation's
     *  allocated memory size, for example).
     */
    virtual antlr_uint32_t size() const = 0;

    virtual bool isNil() const = 0;
    
    virtual bool operator==(const IntSet& other) const = 0;

    virtual antlr_int32_t getSingleElement() const = 0;

    virtual bool contains(antlr_int32_t el) const = 0;

    /** remove this element from this set */
    virtual void remove(antlr_int32_t el) = 0;

    virtual antlr_auto_ptr< std::list<antlr_int32_t> > toList() const = 0;
    
    virtual std::string toString() const = 0;
};

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef INTSET_H */
