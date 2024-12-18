// ======================================================================
// Author : $Author$
// Version: $Revision$
// Date   : $Date$
// Url    : $URL$
// ======================================================================

// ======================================================================
// Copyright: (C) 2012-2013 Gregor Cramer
// ======================================================================

// ======================================================================
// libhyphenate: A TeX-like hyphenation algorithm.
// Copyright (C) 2007 Steve Wolter
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// If you have any questions, feel free to contact me:
// http://swolter.sdf1.org
// ======================================================================

#include "Language.h"

#include "m_assert.h"

#include <ctype.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

using namespace rfc_3066;


Language::Language(mstl::string const& rfc_3066)
{
	char const* c = rfc_3066.c_str();

	m_components.push_back();

	do
	{
		if (::isdigit(*c))
		{
			if (m_components.size() == 1)
				M_RAISE("libhyphenate: RFC 3066 allows digits only in subtags.");

			m_components.back().push_back(*c);
		}
		else if (::isalpha(*c))
		{
			m_components.back().push_back(::tolower(*c));
		}
		else if (*c == '-')
		{
			m_components.push_back();
		}
		else
		{
			M_RAISE("libhyphenate: RFC 3066 tags must contain only letters, spaces, and dashes.");
		}
	}
	while (*++c);
}


bool
Language::operator==(Language const& lang) const
{
	mstl::list<mstl::string>::const_iterator me	= m_components.begin();
	mstl::list<mstl::string>::const_iterator you	= lang.m_components.begin();

	while (true)
	{
		if (me == m_components.end() || you == lang.m_components.end())
			return true;

		if (*me != *you)
			return false;

		++me;
		++you;
	}
}


bool
Language::operator<(Language const& lang) const
{
	mstl::list<mstl::string>::const_iterator me	= m_components.begin();
	mstl::list<mstl::string>::const_iterator you	= lang.m_components.begin();

	while (true)
	{
		if (me == m_components.end() || you == lang.m_components.end())
			return false;

		if (*me < *you)
			return true;

		if (*me > *you)
			return false;

		++me;
		++you;
	}
}


Language::operator mstl::string() const
{
	return concat(m_components.size());
}


mstl::string
Language::concat(int depth, mstl::string const& sep) const
{
	mstl::string accum;

	for (mstl::list<mstl::string>::const_iterator i = m_components.begin(); i != m_components.end(); ++i)
	{
		accum += ((i == m_components.begin()) ? "" : sep) + *i;
		if (--depth <= 0)
			break;
	}

	return accum;
}


mstl::string
Language::find_suitable_file(mstl::string const& dir) const 
{
	struct ::stat buf;

	for (int i = m_components.size(); i > 0; --i)
	{
		mstl::string path = dir + concat(i);

		if (::stat(path.c_str(), &buf) != -1)
			return path;
	}

	return mstl::string::empty_string;
}


bool
Language::is_german() const
{
	return !m_components.empty() && ::strncmp(m_components.front().c_str(), "de", 2) == 0;
}

// vi:set ts=3 sw=3:
