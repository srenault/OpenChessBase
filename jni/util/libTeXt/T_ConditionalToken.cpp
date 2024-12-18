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

#include "T_ConditionalToken.h"

using namespace TeXt;


ConditionalToken::ConditionalToken()
{
	// no action
}


bool
ConditionalToken::isConditional() const
{
	return true;
}

// vi:set ts=3 sw=3:
