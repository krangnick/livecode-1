/* Copyright (C) 2003-2013 Runtime Revolution Ltd.

This file is part of LiveCode.

LiveCode is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License v3 as published by the Free
Software Foundation.

LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef __COMMANDS_ASK_H
#define __COMMANDS_ASK_H

#ifndef __EXECUTION_POINT_H
#include "execpt.h"
#endif

#ifndef __VARIABLE_H
#include "variable.h"
#endif

#ifndef __EXPRESSION_H
#include "express.h"
#endif

#ifndef __STATEMENT_H
#include "statemnt.h"
#endif

class MCAsk : public MCStatement
{
	Ask_type mode;
	MCVarref *it;
	MCExpression *title;
	Boolean sheet;

	union
	{
		struct
		{
			MCExpression *prompt;
			MCExpression *answer;
			bool hint : 1;
		} question;
		struct
		{
			MCExpression *prompt;
			MCExpression *answer;
			bool hint : 1;
		} password;
		struct
		{
			MCExpression *prompt;
			MCExpression *initial;
			MCExpression *filter;
			MCExpression **types;
			uint4 type_count;
		} file;
	};

public:
	MCAsk(void)
	{
		title = NULL;
		file . prompt = file . initial = file . filter = NULL;
		file . types = NULL;
		file . type_count = 0;
		mode = AT_UNDEFINED;
		it = NULL;
		sheet = False;
	}
	virtual ~MCAsk(void);

	virtual Parse_stat parse(MCScriptPoint &);
	virtual Exec_stat exec(MCExecPoint &);

private:
	Parse_errors parse_question(MCScriptPoint& sp);
	Parse_errors parse_password(MCScriptPoint& sp);
	Parse_errors parse_file(MCScriptPoint& sp);

	Exec_errors exec_question(MCExecPoint& ep, const char *p_title);
	Exec_errors exec_password(MCExecPoint& ep, const char *p_title);
	Exec_errors exec_file(MCExecPoint& ep, const char *p_title);

	Exec_errors exec_custom(MCExecPoint& sp, bool& p_cancelled, const MCString& p_name, const char *p_type, unsigned int t_count, ...);
};

#endif
