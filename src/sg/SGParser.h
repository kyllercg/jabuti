/**
 * \file		sg/SGParser.h
 * \brief		The definition of the <b>Parser</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		June, 2004
 * \version		$Id$
 * 
 * Header file for Parse class. Contains definitions for the parser for the
 * files describing the process of a system.
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

using namespace std;

#include "config.h"

#include "Channel.h"
#include "Process.h"

#include <string>
#include <vector>

#include <stdio.h>
 
#ifndef SGPARSER_H
#define SGPARSER_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * DEFINES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */ 

/** ID was <b>NOT</b> declared before. */
#define _SGPARSER_N_DECLARED					-100

/** ID was declared before as local. */
#define _SGPARSER_DECLARED_LOCAL				-200

/** ID was declared before as global. */
#define _SGPARSER_DECLARED_GLOBAL				-300

/** ID was declared before with other type. */
#define _SGPARSER_DECLARED_OTHER_TYPE			-400

/** Arc was declared before. With same source and destination states. */
#define _SGPARSER_REDECLARED					-450

/** Scope for global variables. */
#define _SGPARSER_GLOBAL						-500

/** unknown status. */
#define _SGPARSER_NONE						-600

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * ERRORS MESSAGE
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** Message error: error when closing an open file. */
#define _SGPARSER_ERROR_FILE_CL				"error when closing file"

/** Message error: error when opening a file. */
#define _SGPARSER_ERROR_FILE_OP				"error when opening file"

/** Message error: ID was declared before. */
#define _SGPARSER_ERROR_ID_DECLARATION		"declared previously"

/** Message error: ID size is too big. */
#define _SGPARSER_ERROR_ID_SIZE				"bigger than _MAX_ID_SIZE"

/** Message error: ID was not declared before. */
#define _SGPARSER_ERROR_ID_NOT_DECLARED		"not declared"

/** Message error: symbol is not expected at this point. */
#define _SGPARSER_ERROR_ID_NOT_EXPECTED		"not expected here"

/** Message error: error of memory allocation. */
#define _SGPARSER_ERROR_MEM_ALLOC			"memory allocation error"

/** Message error: errors found when parsing input file. */
#define _SGPARSER_ERROR_MSG					"errors were found"

/** Message error: more symbols than permited. */
#define _SGPARSER_ERROR_NUMBER_SYMBOLS		"too many symbols"

/** Message error: sintaxe error when using the parse program. */
#define _SGPARSER_ERROR_USAGE				"usage: parser <filename>"

/** Message error: more than one process is writing on the same channel. */
#define _SGPARSER_ERROR_WRITER_CHANNEL		"too many process writers"

/** Message error: more than one process is reading from the same channel. */
#define _SGPARSER_ERROR_READER_CHANNEL		"too many process readers"

/** Message error: channels with less than two cells are not allowed. */
#define _SGPARSER_ERROR_FEW_CELLS			"few cells in the channel"

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CODE ERRORS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** No errors were found when parsing input file. */
#define _SGPARSER_ERROR_EXISTS				-100

/** Errors were found when parsing input file. */
#define _SGPARSER_ERROR_NOT_EXISTS			-110

/** Error code: unable to open input file. */
#define _SGPARSER_ERROR_CODE_FILE_OP		-120

/** Error code: unable to open input file. */
#define _SGPARSER_ERROR_CODE_FILE_CL		-130

/** Error code: memory allocation error. */
#define _SGPARSER_ERROR_CODE_MEM_ALLOC		-140

/** Error code: too many symbols. */
#define _SGPARSER_ERROR_CODE_NUMBER_SYMBOLS	-150

/** Error code: wrong syntax when calling the parser program. */
#define _SGPARSER_ERROR_CODE_SYNTAX			-160

/** Error code: ID previously declared. */
#define _SGPARSER_ERROR_CODE_ID_DECLARATION	-170

/** Error code: policy for less than two cells not implemented. */
#define _SGPARSER_ERROR_CODE_FEW_CELLS		-180

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * GLOBAL VARIABLES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Used to set the input file name for LeX & Yacc. */
extern FILE *yyin;

/**
 * \class	SGParser SGParser.h
 * \brief	The <b>SGParser</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	June, 2004
 * 
 * The <b>SGParser</b> class. An object of this type implements a parser for the
 * files containing the description of the system.
 * 
 * It is very important to oberve that any application that will use the parser
 * defined here <b>SHOULD</b> declare an object of type <b>SGParser</b> named
 * <b>sgparser</b> as a global variable. If <b>sgparser</b> was not declared the
 * parser will not works correctly.
 */
class SGParser {

	public:
	
		/** Vector containing stored communication channels. */
		vector<Channel *> Channels;
		
		/** Vector containing stored processes. */
		vector<Process *> Processes;
		
		/* Class constructors/destructors */
		SGParser();								/* class constructor */
		~SGParser();							/* class destructor */
		
		int callSGParser(char *f);
		
		/* Public methods */
		int insertChannel(const char *s);		/* insert channel */
		int insertProcess(const char *s);		/* insert process */
		int insertState(const char *id);		/* insert state */
		int insertArc();						/* insert arc */
		
		bool exists(const char *id);
		int existsChannel(const char *id);
		int existsState(const char *id);
		int existsArc(int src, const char *id, int dest);
		
		void setMem(int c);						/* sets channel memory info */
		void setSrc(int n);						/* sets source */
		void setDest(int n);					/* sets destination */
		void setArc(const char *id);			/* sets arc */
		bool setArc(const char *ch, int type);	/* sets arc */
		bool setWriter(const char *ch);			/* sets writer of a channel */
		bool setReader(const char *ch);			/* sets reader of a channel */
		void setType(int t);					/* sets  type of channel */
		
		void pperrors(const char *m);					/* prints error message */
		void pperrors(const char *m, const char *f);	/* prints error message */
		
		void hasErrors(bool e);			/* sets errors */
		bool hasErrors();				/* to verify if there is any error */
		
	private:
		
		/** To indicate if errors occured when parsing. */
		bool errors;
		
		/* Para armazenar informações temporariamente (isso é culpa do yacc) */
		int tmp_src;		/**< source state target. (for bison) */
		int tmp_dest;		/**< destination state target. (for bison) */
		string tmp_arc;		/**< arc label. (for bison) */
		bool tmp_ioarc;		/**< IO arc? (for bison) */
		int tmp_iotype;		/**< IO is READ os WRITE. (for bison) */
		int tmp_ioch;		/**< IO channel. (for bison) */
};
#endif /* SGPARSER_H */
