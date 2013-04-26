/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include <memory>
#include <string>
#include <vector>
#include <cinamo/Logger.h>
#include <cinamo/ClassUtil.h>
#include <nekomata/classdefs.h>
#include <tinyxml2.h>

namespace nicomo {
namespace model {

/**
 * XML内のコメントを表現するクラス。
 * ！！　イミュータブル（変更不可）　！！
 */
class Comment{
	DEFINE_MEMBER(public, protected, unsigned long long, thread)
	DEFINE_MEMBER(public, protected, unsigned long long, no)
	DEFINE_MEMBER(public, protected, float, vpos)
	DEFINE_MEMBER(public, protected, unsigned long long, date)
	DEFINE_MEMBER(public, protected, unsigned long long, deleted)
	DEFINE_MEMBER(public, protected, long long, score)
	DEFINE_MEMBER(public, protected, std::string, user_id)
	DEFINE_MEMBER(public, protected, std::string, message)
	DEFINE_MEMBER(public, protected, std::string, mail)
	DEFINE_MEMBER(public, protected, bool, anonymity)
	DEFINE_MEMBER(public, protected, bool, leaf)
	DEFINE_MEMBER(public, protected, bool, premium)
	DEFINE_MEMBER(public, protected, bool, fork)
	DEFINE_MEMBER(public, protected, std::shared_ptr<const nekomata::tree::Node>, node)
public:
	bool haveScript() const;
protected:
	Comment();
public:
	Comment(cinamo::Logger& log, tinyxml2::XMLElement* const elem);
	virtual ~Comment() noexcept = default;
public:
	struct CompareLessByVpos
	{
		bool operator() (const Comment* a, const Comment* b)
		{
			return a->vpos() < b->vpos();
		}
		bool operator() (const float& a, const Comment* b)
		{
			return a < b->vpos();
		}
		bool operator() (const Comment* a, const float& b)
		{
			return a->vpos() < b;
		}
	};
};

}}