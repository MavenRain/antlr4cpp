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

#ifndef OBJECT_EQUALITY_COMPARATOR_H
#define OBJECT_EQUALITY_COMPARATOR_H

#include <Antlr4Definitions.h>
#include <misc/AbstractEqualityComparator.h>
#include <misc/Key.h>

namespace antlr4 {
namespace misc {

/**
 * This default implementation of {@link EqualityComparator} uses object equality
 * for comparisons by calling {@link Object#hashCode} and {@link Object#equals}.
 *
 * @author Sam Harwell
 */
template <typename T>
class ANTLR_API ObjectEqualityComparator : public virtual AbstractEqualityComparator< Key<T> >
{
public:

    /**
     * {@inheritDoc}
     * <p/>
     * This implementation returns
     * {@code obj.}{@link Object#hashCode hashCode()}.
     */
    ANTLR_OVERRIDE
    antlr_int32_t hashCode(const Key<T>& obj) const;

    /**
     * {@inheritDoc}
     * <p/>
     * This implementation relies on object equality. If both objects are
     * {@code null}, this method returns {@code true}. Otherwise if only
     * {@code a} is {@code null}, this method returns {@code false}. Otherwise,
     * this method returns the result of
     * {@code a.}{@link Object#equals equals}{@code (b)}.
     */
    ANTLR_OVERRIDE
    bool equals(const Key<T>& a, const Key<T>& b) const;

};

/**
 * {@inheritDoc}
 * <p/>
 * This implementation returns
 * {@code obj.}{@link Object#hashCode hashCode()}.
 */
template <typename T>
antlr_int32_t ObjectEqualityComparator<T>::hashCode(const Key<T>& obj) const
{
    return obj.hashCode();
}

/**
 * {@inheritDoc}
 * <p/>
 * This implementation relies on object equality. If both objects are
 * {@code null}, this method returns {@code true}. Otherwise if only
 * {@code a} is {@code null}, this method returns {@code false}. Otherwise,
 * this method returns the result of
 * {@code a.}{@link Object#equals equals}{@code (b)}.
 */
template <typename T>
bool ObjectEqualityComparator<T>::equals(const Key<T>& a, const Key<T>& b) const
{
    return a.equals(b);
}

} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef OBJECT_EQUALITY_COMPARATOR_H */
