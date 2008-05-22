/**
 * \file		sg/sg.h
 * \brief		The definitions to be used by the <b>sg_test</b> program.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		June, 2004
 * \version		$Id$
 * 
 * Copyright (C) 2004, 2008 - Kyller Costa Gorgônio
 * Copyright (C) 2004, 2008 - Universitat Politècnica de Catalunya
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef SG_H
#define SG_H

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * INTERNAL FUNCTIONS PROTOTYPES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/**
 * \brief	Prints an error message.
 *
 * \fn		void yyerror(char *mesg)
 * \param	*mesg: the error message.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/05/2004
 */
void yyerror(char *mesg);

/**
 * \brief	Prints an error message.
 *
 * \fn		void yyerror2(char *mesg, char *v)
 * \param	*mesg: the error message.
 * \param	*v: the identifier related to the error.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	25/05/2004
 */
void yyerror2(char *mesg, char *v);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FUNCTIONS PROTOTYPES FROM LEX & YACC
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** for calling LEX. */
extern int yylex();

/** For calling YACC (BISON). */
extern int yyparse(void);

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * ERRORS MESSAGE
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Message error: sintaxe error when using the <b>sg-test</b> program */
#define _SG_ERROR_USAGE						"usage: sg_test"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CODE ERRORS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Error code: wrong syntax when calling the <b>sg-test</b> program. */
#define _SG_ERROR_CODE_SYNTAX				-10

#endif /* SG_H */
 
