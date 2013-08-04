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
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR AS IS'' AND ANY EXPRESS OR
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

#ifndef RANGE_TRANSITION_H
#define RANGE_TRANSITION_H

#include <antlr/Definitions.h>
#include <antlr/atn/Transition.h>

namespace antlr4 {
namespace atn {

class ANTLR_API RangeTransition : public Transition
{
public:
    RangeTransition(ANTLR_NOTNULL ATNState* target, antlr_int32_t from, antlr_int32_t to);

    ANTLR_OVERRIDE
    antlr_int32_t getSerializationType() const;

    ANTLR_OVERRIDE
    ANTLR_NOTNULL
    antlr_auto_ptr<IntervalSet> label() const;

    ANTLR_OVERRIDE
    bool matches(antlr_int32_t symbol, antlr_int32_t minVocabSymbol, antlr_int32_t maxVocabSymbol) const;

    ANTLR_OVERRIDE
    std::string toString() const;
    
public:
    const antlr_int32_t from;
    const antlr_int32_t to;    
};


} /* namespace atn */
} /* namespace antlr4 */

#endif /* ifndef RANGE_TRANSITION_H */
