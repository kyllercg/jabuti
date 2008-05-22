/**
 * \file		sg/SGParser.cpp
 * \brief		The methods of the <b>Parser</b> class.
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

using namespace std;

#include "sg.h"
#include "sg_yacc.h"

#include "SGParser.h"

#include <iostream>

#include <stdlib.h>

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * EXTERNAL GLOBAL VARIABLES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** External variable to set the current line number of the input file. */
extern int lineNumber;

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * FUNCTIONS PROTOTYPES FROM LEX & YACC
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
//extern int yyparse(void);


/**
 * \brief	Class constructor. Creates a new <b>Parser</b> element.
 * 
 * \fn		SGParser::SGParser()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
SGParser::SGParser()
{
	errors = false;
}

/**
 * \brief	Class destructor.
 * 
 * \fn		SGParser::~SGParser()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	09/06/2004
 */
SGParser::~SGParser()
{}

/**
 * \brief	Call yacc functions to parse input file.
 * 
 * \fn		int SGParser::callSGParser(char *f)
 * \param	*f: name of the file containing the system description.
 * \return	An integer containing <b>_ERROR_NOT_EXISTS</b> if the input file
 * 			contains no parser errors. <b>_ERROR_EXISTS</b> if the file contains
 * 			paser errors. <b>_ERROR_CODE_FILE_OP</b> if it was not possible to
 * 			open the input file. <b>_SGPARSER_ERROR_CODE_FILE_CL</b> if there
 * 			was an error when closing the input file.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	26/10/2004
 */
int SGParser::callSGParser(char *f)
{
	FILE *srcfile;
	
	if ((srcfile = fopen(f, "rb")) == NULL) {
		
		return _SGPARSER_ERROR_CODE_FILE_OP;
	}
	
	yyin = srcfile;
	
	yyparse();
	
	if (fclose(srcfile) != 0) {
		
		return _SGPARSER_ERROR_CODE_FILE_CL;
	}
	
	if (hasErrors() == true) {
		
		return _SGPARSER_ERROR_EXISTS;
	}
	
	return _SGPARSER_ERROR_NOT_EXISTS;
}

/**
 * \brief	Insert a new channel ID on table of symbols.
 *
 * \fn		int SGParser::insertChannel(const char *s)
 * \param	*s: string with the ID of the new Channel.
 * \return	An integer with the position of the identifier on the table of
 *          symbols. Or <code>_SGPARSER_ERROR_CODE_ID_DECLARATION</code> if the
 * 			ID was declared previously.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int SGParser::insertChannel(const char *s)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " insertChannel()" << endl;
	#endif
	
	int trg = _SGPARSER_ERROR_CODE_ID_DECLARATION;
		
	if (exists(s) == false) {
		
		Channel *ch = new Channel(s);
		Channels.insert(Channels.end(), ch);
		trg = (Channels.size() - 1);
	} else {
		
		pperrors(_SGPARSER_ERROR_ID_DECLARATION, s);
	}
			
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertChannel()" << endl;
	#endif
	
	return trg;
}

/**
 * \brief	Sets the policy implemented by a channel.
 *
 * \fn		void SGParser::setType(int t)
 * \param	t: the type of the channel. May be <b>SIGNAL</b> or <b>MESSAGE</b>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
void SGParser::setType(int t)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setType()" << endl;
	#endif
	
	switch (t) {
		
		case SIGNAL:
			
			Channels.back()->setType(_CHANNEL_OWBB);
			break;
		
		case MESSAGE:
			
			Channels.back()->setType(_CHANNEL_RRBB);
			break;
		
		case POOL:
		
			Channels.back()->setType(_CHANNEL_OWRRBB);
			break;
		
		default:
			
			break;
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setType()" << endl;
	#endif
}

/**
 * \brief	Insert a new process ID on table of symbols.
 *
 * \fn		int SGParser::insertProcess(const char *s)
 * \param	*s: string with the ID of the new process.
 * \return	An integer with the position of the identifier on the table of
 *          symbols. Or <code>_SGPARSER_ERROR_CODE_ID_DECLARATION</code> if the
 * 			ID was declared previously.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int SGParser::insertProcess(const char *s)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " insertProcess()" << endl;
	#endif
	
	int trg = _SGPARSER_ERROR_CODE_ID_DECLARATION;
	
	if (exists(s) == false) {
				
		Process *p = new Process(s);
		Processes.insert(Processes.end(), p);
		// p->~Process(); // fudeu tudo de novo
	} else {
				
		pperrors(_SGPARSER_ERROR_ID_DECLARATION, s);
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertProcess()" << endl;
	#endif
	
	return trg;
}

/**
 * \brief	Insert a new state ID on table of symbols.
 *
 * \fn		int SGParser::insertState(const char *id)
 * \param	*id: a string with the ID of the new State.
 * \return	- The target of the state if it was already declared or if it was 
 * 			  created correctly now. Or
 * 			- <code>_SGPARSER_DECLARED_GLOBAL</code> if ID was previously
 * 			  declared as global. Or 
 * 			- <code>_SGPARSER_DECLARED_OTHER_TYPE</code> if the ID was
 * 			  previously declared as local by another element.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int SGParser::insertState(const char *id)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " insertState()" << endl;
	#endif
	
	int trg = existsState(id);
			
	if (trg == _SGPARSER_N_DECLARED) {
			
		trg = Processes.back()->insertState(id);
	} else if (trg == _SGPARSER_DECLARED_GLOBAL) {
		
		pperrors(_SGPARSER_ERROR_ID_DECLARATION, id);
		pperrors(_SGPARSER_ERROR_ID_NOT_EXPECTED, id);
	} else if (trg == _SGPARSER_DECLARED_OTHER_TYPE) {
				
		pperrors(_SGPARSER_ERROR_ID_NOT_EXPECTED, id);
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertState()" << endl;
	#endif
	
	return trg;
}

/**
 * \brief	Insert a new arc ID on table of symbols.
 *
 * \fn		int SGParser::insertArc()
 * \return	- An integer with the position of the identifier on the table of
 *            states of its respective process.
 * 			- <code>_SGPARSER_REDECLARED</code> if ID was previously declared
 * 			  as local.
 * 			- <code>_SGPARSER_DECLARED_GLOBAL</code> if ID was previously
 * 			  declared as global.
 *          - <code>_SGPARSER_DECLARED_OTHER_TYPE</code> if the ID was
 * 			  previously declared as local by another element.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int SGParser::insertArc()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertArc()" << endl;
	#endif
	
	int trg = existsArc(tmp_src, tmp_arc.c_str(), tmp_dest);
			
	if (trg == _SGPARSER_N_DECLARED && tmp_ioarc == false) {
			
		trg = Processes.back()->insertArc(tmp_src, tmp_arc.c_str(), tmp_dest);
	} else if (trg == _SGPARSER_N_DECLARED && tmp_ioarc == true) {
		
		trg = Processes.back()->insertArc(tmp_src, \
			(const char *)tmp_arc.c_str(), tmp_dest, tmp_iotype, tmp_ioch);
	}else if (trg == _SGPARSER_DECLARED_GLOBAL) {
		
		pperrors(_SGPARSER_ERROR_ID_DECLARATION, (const char *)tmp_arc.c_str());
		pperrors(_SGPARSER_ERROR_ID_NOT_EXPECTED, (const char *)tmp_arc.c_str());
	} else if (trg == _SGPARSER_DECLARED_OTHER_TYPE) {
				
		pperrors(_SGPARSER_ERROR_ID_NOT_EXPECTED, (const char *)tmp_arc.c_str());
	} else if (trg == _SGPARSER_REDECLARED) {
		
		pperrors(_SGPARSER_ERROR_ID_DECLARATION, (const char *)tmp_arc.c_str());
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertArc()" << endl;
	#endif
	
	return trg;
}

/**
 * \brief	Checks if a global ID was previously declared.
 *
 * \fn		bool SGParser::exists(const char *id)
 * \param	*id: string of the identifier.
 * \return	<code><b>true</b></code> if <i>*id</i> is present on the table of
 * 			symbols. <code><b>false</b></code> otherwise.
 * 
 * This method checks if an ID was previously declared. It is used to verify if
 * there is a conflict between <i>*id</i> and some other name when <i>*id</i>
 * is a global name.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
bool SGParser::exists(const char *id)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " exists()" << endl;
	#endif
	
	int cont, cont2, size, size2;
	string aux = id;
	
	size = Channels.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Channels[cont]->getLabel() == aux) {
		
			return true;
		} 
	}
	
	size = Processes.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Processes[cont]->getLabel() == aux) {
		
			return true;
		}
		
		size2 = Processes[cont]->States.size();
		
		for (cont2 = 0; cont2 < size2; cont2++) {
			
			if (Processes[cont]->States[cont2]->getLabel() == aux) {
				
				return true;
			}
		}
		
		size2 = Processes[cont]->Arcs.size();
		
		for (cont2 = 0; cont2 < size2; cont2++) {
			
			if (Processes[cont]->Arcs[cont2]->getLabel() == aux) {
				
				return true;
			}
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /exists()" << endl;
	#endif
	
	return false;
}

/**
 * \brief	Checks if a channel ID was previously declared.
 *
 * \fn		int SGParser::existsChannel(const char *id)
 * \param	*id: label of the channel.
 * \return	The target of the channel if <i>*id</i> was previously declared.
 *          <code>_PARSE_N_DECLARED</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int SGParser::existsChannel(const char *id)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " existsChannel()" << endl;
	#endif
	
	int cont, size;
	string aux = id;
	
	size = Channels.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Channels[cont]->getLabel() == aux) {
		
			return cont;
		} 
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /existsChannel()" << endl;
	#endif
	
	return _SGPARSER_N_DECLARED;
}

/**
 * \brief	Check if a state> ID was previously declared..
 *
 * \fn		int SGParser::existsState(const char *id)
 * \param	*id: string of the identifier.
 * \return	- The target of the state if it was previously declared.
 * 			- <code>_SGPARSER_DECLARED_GLOBAL</code> if <i>*id</i> was
 * 			  previously declared as a global element (<b>Process</b> or
 * 			  <b>Channel</b>).
 * 			- <code>_SGPARSER_DECLARED_OTHER_TYPE</code> if <i>*id</i> was
 * 			  declared as an <b>Arc</b>.
 * 			- <code>_SGPARSER_N_DECLARED</code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int SGParser::existsState(const char *id)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " existsState()" << endl;
	#endif
	
	int cont, size;
	string aux = id;
	
	size = Processes.back()->States.size();
	for (cont = 0; cont < size; cont++) {
		
		if (Processes.back()->States[cont]->getLabel() == aux) {
			
			return cont;
		}
	}
	
	size = Processes.back()->Arcs.size();
	for (cont = 0; cont < size; cont++) {
		
		if (Processes.back()->Arcs[cont]->getLabel() == aux) {
	
			return _SGPARSER_DECLARED_OTHER_TYPE;
		}
	}
	
	size = Channels.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Channels[cont]->getLabel() == aux) {
		
			return _SGPARSER_DECLARED_GLOBAL;
		} 
	}
	
	size = Processes.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Processes[cont]->getLabel() == aux) {
		
			return _SGPARSER_DECLARED_GLOBAL;
		} 
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /existsState()" << endl;
	#endif
	
	return _SGPARSER_N_DECLARED;
}

/**
 * \brief	Check if a <b>Arc</b> ID was previously declared..
 *
 * \fn		int SGParser::existsArc(int src, const char *id, int dest)
 * \param	src: the target of the source state.
 * \param	*id: a string with the identifier.
 * \param	dest: the target of the destination state.
 * \return	- <code>_SGPARSER_N_DECLARED</code> if <i>*id</i> was not previously
 * 			  declared.
 * 			- <code>_SGPARSER_REDECLARED</code> if there is an arc with the same
 * 			  label, source and destination in the current process.
 * 			- <code>_SGPARSER_DECLARED_GLOBAL</code> if <i>*id</i> was
 * 			  previously declared as global (<b>State</b> or <b>Channel</b>).
 * 			- <code>_SGPARSER_DECLARED_OTHER_TYPE</code> if <i>*id</i> was
 * 			  declared as another type (<b>State</b>).
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int SGParser::existsArc(int src, const char *id, int dest)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " existsArc()" << endl;
	#endif
	
	int cont, size;
	string aux = id;

	size = Processes.back()->Arcs.size();
	for (cont = 0; cont < size; cont++) {
		
		if (Processes.back()->Arcs[cont]->getSrc() == src
			&& Processes.back()->Arcs[cont]->getDest() == dest) {
	
			return _SGPARSER_REDECLARED;
		}
	}	
	
	size = Processes.back()->States.size();
	for (cont = 0; cont < size; cont++) {
		
		if (Processes.back()->States[cont]->getLabel() == aux) {
			
			return _SGPARSER_DECLARED_OTHER_TYPE;
		}
	}
	

	
	size = Channels.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Channels[cont]->getLabel() == aux) {
		
			return _SGPARSER_DECLARED_GLOBAL;
		} 
	}
	
	size = Processes.size();
	for (cont = 0; cont < size; cont++) {
	
		if (Processes[cont]->getLabel() == aux) {
		
			return _SGPARSER_DECLARED_GLOBAL;
		} 
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /existsArc()" << endl;
	#endif
	
	return _SGPARSER_N_DECLARED;
}

/**
 * \brief	Sets the number of cells of the last inserted channel.
 *
 * \fn		void SGParser::setMem(int c)
 * \param	c: the number of cells available in the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	13/09/2004
 */
//void SGParser::setMem(int c, int s)
void SGParser::setMem(int c)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setMem()" << endl;
	#endif
	
	if (c < _CHANNEL_MIN_CELLS) {
		
		pperrors(_SGPARSER_ERROR_FEW_CELLS, (const char *)\
			Channels.back()->getLabel().c_str());
	}
	
	Channels.back()->setCells(c);
	// Channels.back()->setSlots(s);
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setMem()" << endl;
	#endif
}

/**
 * \brief	Sets an internal attribute with the source state of an arc.
 *
 * \fn		void SGParser::setSrc(int n)
 * \param	n: the target of the source state.
 * 
 * This method is needed because we need to put some information on some
 * temporaly variables to insert the arc later.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
void SGParser::setSrc(int n)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setSrc()" << endl;
	#endif
	
	tmp_src = n;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setSrc()" << endl;
	#endif
}

/**
 * \brief	Sets an internal attribute with the destination state of an arc.
 *
 * \fn		void SGParser::setDest(int n)
 * \param	n: the target of the destination state.
 * 
 * This method is needed because we need to put some information on some
 * temporaly variables to insert the arc later.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
void SGParser::setDest(int n)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setDest()" << endl;
	#endif
	
	tmp_dest = n;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setDest()" << endl;
	#endif
}

/**
 * \brief	Sets an internal attribute with the ID of an arc.
 *
 * \fn		void SGParser::setArc(const char *id)
 * \param	*id: the label of the new arc.
 * 
 * This method is needed because we need to put some information on some
 * temporaly variables to insert the arc later.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
void SGParser::setArc(const char *id)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setArc()" << endl;
	#endif
	
	tmp_arc = id;
	tmp_ioarc = false;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setArc()" << endl;
	#endif
}

/**
 * \brief	Sets an internal attribute with the ID of an arc and the IO stuffs.
 *
 * \fn		bool SGParser::setArc(const char *ch, int type)
 * \param	*ch: the label of the channel of READ/WRITE operation.
 * \param	type: the type of IO operation. Should be <b>READ</b> or
 * 			<b>WRITE</b>.
 * \return	<code><b>true</b></code> if <i>*ch</i> was correctly inserted on
 * 			the table of arcs. <code><b>false</b></code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
bool SGParser::setArc(const char *ch, int type)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setArc()" << endl;
	#endif
	
	string aux = ch;
	int trg = existsChannel(ch);
	
	if (trg == _SGPARSER_N_DECLARED) {
		
		pperrors(_SGPARSER_ERROR_ID_NOT_DECLARED, ch);
		return false;
	} else if (type == WRITE) {
	
		// TODO
		/** \todo It is necessary to change the names of the arcs. There will
		 *  be some confusion for channels with more than 9 cells or slots. 
		 *  This is related with the number of digits required to represent the
		 *  control variables in tha label of the arc. */
		//tmp_arc = "WRITE(";
		tmp_arc = "WRITE_";
		tmp_arc.append(ch);
		//tmp_arc.append(")");
		tmp_ioarc = true;
		tmp_iotype = _ARC_WRITE;
		tmp_ioch = trg;
		
		if (setWriter(ch) == false){
		
			pperrors(_SGPARSER_ERROR_WRITER_CHANNEL, ch);
			return false;
		}
	} else if (type == READ) {
		
		//tmp_arc = "READ(";
		tmp_arc = "READ_";
		tmp_arc.append(ch);
		//tmp_arc.append(")");
		tmp_ioarc = true;
		tmp_iotype = _ARC_READ;
		tmp_ioch = trg;
		
		if (setReader(ch) == false){
		
			pperrors(_SGPARSER_ERROR_READER_CHANNEL, ch);
			return false;
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setArc()" << endl;
	#endif
	
	return true;
}

/**
 * \brief	Sets the writer process of a channel.
 *
 * \fn		bool SGParser::setWriter(const char *ch)
 * \param	*ch: the label of the channel.
 * \return	<code><b>true</b></code> if the writter was properly setted.
 * 			<code><b>false</b></code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
bool SGParser::setWriter(const char *ch)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setWriter()" << endl;
	#endif
	
	int trg = existsChannel(ch);
	int size;
	string aux = ch;
	
	if (trg == _SGPARSER_N_DECLARED) {
		
		return false;
	}
	
	if (Channels[trg]->getWriter() != _CHANNEL_NONE
		&& Channels[trg]->getWriter() != Processes.back()->getTarget()) {
		
		return false;
	}

	Channels[trg]->setWriter(Processes.back()->getTarget());
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setWriter()" << endl;
	#endif
	
	return true;
}

/**
 * \brief	Sets the writer process of a channel.
 *
 * \fn		bool SGParser::setReader(const char *ch)
 * \param	*ch: the label of the channel.
 * \return	<code><b>true</b></code> if the reader was properly setted.
 * 			<code><b>false</b></code> otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
bool SGParser::setReader(const char *ch)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " setReader()" << endl;
	#endif
	
	int trg = existsChannel(ch);
	int size;
	string aux = ch;
	
	if (trg == _SGPARSER_N_DECLARED) {
		
		return false;
	}
	
	if (Channels[trg]->getReader() != _CHANNEL_NONE
		&& Channels[trg]->getReader() != Processes.back()->getTarget()) {
		
		return false;
	}

	Channels[trg]->setReader(Processes.back()->getTarget());
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /setReader()" << endl;
	#endif
	
	return true;
}

/**
 * \brief	Prints an error message.
 * 
 * \fn		void SGParser::pperrors(const char *m)
 * \param	*m: the error message.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
void SGParser::pperrors(const char *m)
{
	cerr << "line " << lineNumber << ": " << m << endl;
	errors = true;
}

/**
 * \brief	Prints an error message.
 * 
 * \fn		void SGParser::pperrors(const char *m, const char *f)
 * \param	*m: the error message.
 * \param	*f: the identifier related to the error.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
void SGParser::pperrors(const char *m, const char *f)
{
	cerr << "line " << lineNumber << ": " << f << " - " << m << endl;
	errors = true;
}

/**
 * \brief	Sets the value of the <code>SGParser::errors</code> attribute.
 * 
 * \fn		void SGParser::hasErrors(bool e)
 * \param	e: The new value of <code>SGParser::errors</code>. Should be
 * 			<b><code>true</code></b> or <b><code>false</code></b>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/10/2004
 */
void SGParser::hasErrors(bool e)
{
	errors = e;
}

/**
 * \brief	Verifyies if there is any parser error.
 * 
 * \fn		bool SGParser::hasErrors()
 * \return	The value of the attribute <code>SGParser::errors</code>. That
 * 			indicates if some parser error has accurred or not.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/10/2004
 */
bool SGParser::hasErrors()
{
	return errors;
}
