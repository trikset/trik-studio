/* Copyright 2020 Iakov Kirilenko
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#pragma once
#include "parserRef.h"
namespace qrtext {
namespace core {

/// This helper class aims to fight against problem of
/// cyclic references. Recursive grammar structure produces
/// recursive references, and QSharedPointer cannot handle this
/// without hacks. Thus we manage a full list of shared pointers
/// to clean up manually in the dtor.
template<typename TokenTypes>
struct AutoreleaseRecursiveGrammarParser : ParserInterface<TokenTypes>
{
		AutoreleaseRecursiveGrammarParser(const ParserRef<TokenTypes> &main
										  , const QList<ParserRef<TokenTypes>> &other = {})
		{
				mParsers << main << other;
		}

		QSet<TokenTypes> first() const override
		{
				return mParsers[0]->first();
		}

		QSharedPointer<qrtext::core::ast::Node>
		parse(TokenStream<TokenTypes> &tokenStream, ParserContext<TokenTypes> &parserContext) const override
		{
				return mParsers[0]->parse(tokenStream, parserContext);
		}

		~AutoreleaseRecursiveGrammarParser() override
		{
				for (auto &&p: mParsers) {
						p.internalPointer()->clear();
				}
		}

private:
		QList<ParserRef<TokenTypes>> mParsers;
};
}
}
