// ======================================================================
// Author : $Author$
// Version: $Revision$
// Date   : $Date$
// Url    : $URL$
// ======================================================================

// ======================================================================
// Copyright: (C) 2009-2013 Gregor Cramer
// ======================================================================

// ======================================================================
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// ======================================================================

#ifndef _TeXt_InvalidToken_included
#define _TeXt_InvalidToken_included

#include "T_ExpandableToken.h"

namespace TeXt {


class InvalidToken : public ExpandableToken
{
public:

	InvalidToken(unsigned char c);

	Type type() const override;
	mstl::string name() const override;
	mstl::string meaning() const override;
	Value value() const override;

	void perform(Environment& env) override;

private:

	unsigned char m_value;
};

} // namespace TeXt

#endif // _TeXt_InvalidToken_included

// vi:set ts=3 sw=3:
