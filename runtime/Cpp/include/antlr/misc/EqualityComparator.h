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

#ifndef EQUALITY_COMPARATOR_H
#define EQUALITY_COMPARATOR_H

#include <antlr/Definitions.h>


namespace antlr4 {
namespace misc {

/**
 * This interface provides an abstract concept of object equality independent of
 * {@link Object#equals} (object equality) and the {@code ==} operator
 * (reference equality). It can be used to provide algorithm-specific unordered
 * comparisons without requiring changes to the object itself.
 *
 * @author Sam Harwell
 */
template <typename T>
class ANTLR_API EqualityComparator
{
public:
    
    virtual ~EqualityComparator();

    /**
     * This method returns a hash code for the specified object.
     *
     * @param obj The object.
     * @return The hash code for {@code obj}.
     */
    virtual antlr_int32_t hashCode(const T& obj) const = 0;

    /**
     * This method tests if two objects are equal.
     *
     * @param a The first object to compare.
     * @param b The second object to compare.
     * @return {@code true} if {@code a} equals {@code b}, otherwise {@code false}.
     */
    virtual bool equals(const T& a, const T& b) const = 0;
};


template<typename T>
EqualityComparator<T>::~EqualityComparator()
{
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef EQUALITY_COMPARATOR_H */
