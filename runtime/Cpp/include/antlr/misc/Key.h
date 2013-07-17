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

#ifndef KEY_H
#define KEY_H

#include <antlr/Antlr4Definitions.h>
#include <cstring>      // size_t

namespace antlr4 {
namespace misc {


template <typename T>
class ANTLR_API Key
{
public:

    virtual ~Key();

    virtual antlr_int32_t hashCode() const = 0;
    
    virtual bool equals(const Key<T>& other) const;
    
    virtual bool operator==(const Key<T>& other) const;
    
    virtual T* clone() const = 0;

    operator size_t() const;
};

template <typename T>
Key<T>::~Key()
{
}

template <typename T>
bool Key<T>::equals(const Key<T>& other) const
{
    return this->operator==(other);
}

template <typename T>
bool Key<T>::operator==(const Key<T>& other) const
{
    return hashCode() == other.hashCode();
}

template <typename T>
Key<T>::operator size_t() const
{
    return static_cast<size_t>(hashCode());
}


} /* namespace misc */
} /* namespace antlr4 */

#endif /* ifndef KEY_H */