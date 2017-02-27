/* Copyright 2007-2015 QReal Research Group
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

#include "stm32Kit/blocks/stm32BlocksFactoryBase.h"

namespace stm32 {
namespace blocks {

/// Blocks factory for STM32 v6 case (with encoders marked as B1 - B4).
class Stm32V6BlocksFactory : public Stm32BlocksFactoryBase
{
public:
	qReal::interpretation::Block *produceBlock(const qReal::Id &element) override;
	qReal::IdList providedBlocks() const override;
};

}
}
