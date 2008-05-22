/**
 * \file		sg/Process.cpp
 * \brief		The methods of the <b>Process</b> class.
 * \author		Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date		May, 2004
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
 * 
 */

using namespace std;

#include "Process.h"

#include <iostream>

#include <stdio.h>

/**
 * \brief	Class constructor. Creates a new <b>Process</b> element.
 * 
 * \fn		Process::Process(const char *lab)
 * \param	*lab: the label of the process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
Process::Process(const char *lab)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " Process()" << endl;
	#endif
	
	label = lab;
	target = nextTarget;
	nextTarget++;
	nextStateTarget = 0;
	nextArcTarget = 0;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /Process()" << endl;
	#endif
}

/**
 * \brief	Class constructor. Creates a new <b>Process</b> element.
 * 
 * \fn		Process::Process()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	17/06/2004
 */
Process::Process()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " Process()" << endl;
	#endif
	
	target = nextTarget;
	nextTarget++;
	nextStateTarget = 0;
	nextArcTarget = 0;
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /Process()" << endl;
	#endif
}

/**
 * \brief	Class destructor.
 * 
 * \fn		Process::~Process()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
Process::~Process()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
}

/**
 * \brief	Inserts a new <b>Arc</b> element in the process.
 * 
 * \fn		int Process::insertArc(int src, const char *lab, int dest)
 * \param	src: the target of the source state.
 * \param	*lab: the label of the new arc.
 * \param	dest: the target of the destination process.
 * \return	An integer with the target associated with the new <b>Arc</b> if it
 *          was created. <code>_PROCESS_ERROR_CODE_NOT_INSERTED</code>
 * 			otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::insertArc(int src, const char *lab, int dest)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	Arc *aux = new Arc(src, lab, dest, nextArcTarget);
	
	if (aux != NULL) {
		
		Arcs.insert(Arcs.end(), aux);
		// aux->~Arc(); // se destruir objeto vai ferrar a cópia no vetor
		nextArcTarget++;
		return(Arcs.back()->getTarget());
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return _PROCESS_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Inserts a new <b>Arc</b> element in the process.
 * 
 * \fn		int Process::insertArc(int src, const char *lab, int dest, int io, int ch)
 * \param	src: the target of the source state.
 * \param	*lab: the label of the new arc.
 * \param	dest: the target of the destination process.
 * \param	io: the type of the IO operation. May be:
 * 			- <code>_ARC_READ</code>. Or
 * 			- <code>_ARC_WRITE</code>.
 * \param	ch: the target of the channel in which the process is trying to
 * 			perform an IO operation.
 * \return	An integer with the target associated with the new <b>Arc</b> if it
 *          was created. <code>_PROCESS_ERROR_CODE_NOT_INSERTED</code>
 * 			otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::insertArc(int src, const char *lab, int dest, int io, int ch)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " insertArc()" << endl;
	#endif
	
	Arc *aux = new Arc(src, lab, dest, nextArcTarget);
	aux->setIO(io, ch);
	
	if (aux != NULL) {
		
		Arcs.insert(Arcs.end(), aux);
		// aux->~Arc(); // se destruir objeto vai ferrar a cópia no vetor
		nextArcTarget++;
		return(Arcs.back()->getTarget());
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << " /insertArc()" << endl;
	#endif
	
	return _PROCESS_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Inserts a new <b>Arc</b> element in the process.
 * 
 * \fn		int Process::insertArc(const char *lab)
 * \param	*lab: label of the new arc.
 * \return	An integer with the target associated with the new <b>Arc</b> if it
 *          was created. <code>_PROCESS_ERROR_CODE_NOT_INSERTED</code>
 * 			otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	11/06/2004
 */
int Process::insertArc(const char *lab)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	Arc *aux = new Arc(lab, nextArcTarget);
	
	if (aux != NULL) {
		
		Arcs.insert(Arcs.end(), aux);
		// aux->~Arc(); // se destruir objeto vai ferrar a cópia no vetor
		nextArcTarget++;
		return(Arcs.back()->getTarget());
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return _PROCESS_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Inserts a new <b>State</b> element in the process.
 * 
 * \fn		int Process::insertState(const char *lab)
 * \param	*lab: the label of the new state
 * \return	An integer with the target associated with the new <b>State</b> if
 *          it was created. <code>_PROCESS_ERROR_CODE_NOT_INSERTED</code>
 * 			otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
int Process::insertState(const char *lab)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	State *aux = new State(lab, nextStateTarget);
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	if (aux != NULL) {
		
		States.insert(States.end(), aux);
		// aux->~State(); // se destruir objeto vai ferrar a cópia no vetor
		nextStateTarget++;
		return(States.back()->getTarget());
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return _PROCESS_ERROR_CODE_NOT_INSERTED;
}

/**
 * \brief	Checks if a state or an arc with a given label exists.
 * 
 * \fn		bool Process::exists(const char *lab, int type)
 * \param	*lab: the label of the state/arc to find
 * \param	type: specifyies the type of the element to verify. May be:
 * 			- <code>_STATE_CODE</code> if <i>*lab</i> is a label of a state.
 *          - <code>_ARC_CODE</code> if <i>*lab</i> is a label of an arc.
 * \return	- <code><b>true</b></code> if an element with label <i>*lab</i>
 * 			  exists.
 * 			- <code><b>false</b></code> otherwise
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
bool Process::exists(const char *lab, int type)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int size;
	string aux = lab;
	
	switch (type) {
		
		case _PROCESS_STATE_CODE:
		
			size = States.size();
	
			for (cont = 0; cont < size; cont++) {
		
				if (States[cont]->getLabel() == aux) {
			
					return true;
				}
			}
			break;
		
		case _PROCESS_ARC_CODE:
		
			size = Arcs.size();
	
			for (cont = 0; cont < size; cont++) {
		
				if (Arcs[cont]->getLabel() == aux) {
			
					return true;
				}
			}
			break;
			
		default:
		
			return false;
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
		
	return false;
}

/**
 * \brief	Gets the next free target.
 * 
 * \fn		int Process::getNextTarget()
 * \return	An integer with the target that will be associated to the next
 *          process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::getNextTarget()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return nextTarget;
}

/**
 * \brief	Gets the target of the process.
 * 
 * \fn		int Process::getTarget()
 * \return	An integer with the target of the process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::getTarget()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return target;
}

/**
 * \brief	Gets the target of a state.
 * 
 * \fn		int Process::getTarget(const char *lab)
 * \param	*lab: the label of the state to find the target.
 * \return	An integer with the target of the state with label <i>*lab</i>. Or
 *          <code>_PROCESS_ERROR_CODE_NOT_FOUND</code> if <i>*lab</i> does not
 * 			exists.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::getTarget(const char *lab)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int nStates = States.size();
	string aux = lab;
	
	for (cont = 0; cont < nStates; cont++) {
		
		if (States[cont]->getLabel() == aux) {
			
			return cont;
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
		
	return _PROCESS_ERROR_CODE_NOT_FOUND;
}

/**
 * \brief	Gets the target of an arc that links two states.
 * 
 * \fn		int Process::getTarget(const char *src, const char *dest)
 * \param	*src: the label of the source state.
 * \param	*dest: the label of the destination state.
 * \return	An integer with the target of the arc linking the states with label
 *          <i>src</i> and <i>dest</i>. Or
 * 			<code>_PROCESS_ERROR_CODE_NOT_FOUND</code> if such arc does not
 * 			exists.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::getTarget(const char *src, const char *dest)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int srct = getTarget(src);
	int destt = getTarget(dest);
	int nArcs = Arcs.size();
	
	if (srct == _PROCESS_ERROR_CODE_NOT_FOUND 
		|| destt == _PROCESS_ERROR_CODE_NOT_FOUND) {
		
		return _PROCESS_ERROR_CODE_NOT_FOUND;
	}
	
	for (cont = 0; cont < nArcs; cont++) {
		
		if (Arcs[cont]->getSrc() == srct 
		    && Arcs[cont]->getDest() == destt) {
			
			return Arcs[cont]->getTarget();
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
			
	return _PROCESS_ERROR_CODE_NOT_FOUND;
}

/**
 * \brief	Gets the target of an arc.
 * 
 * \fn		int Process::getTarget(int src, int dest)
 * \param	src: the target of the source state.
 * \param	dest: the target of the destination state.
 * \return	An integer with the target of the arc linking the states with
 * 			targets <i>src</i> and <i>dest</i>. Or
 * 			<code>_PROCESS_ERROR_CODE_NOT_FOUND</code> if such arc does not
 * 			exists. Or <code>_PROCESS_ERROR_CODE_OUT_OF_RANGE</code> if there
 * 			was no process with target <i>src</i> or <i>dest</i>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
int Process::getTarget(int src, int dest)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int nStates = States.size();
	int nArcs = Arcs.size();
	
	if (src < 0 || src >= nStates || dest < 0 || dest >= nStates) {
		
		return _PROCESS_ERROR_CODE_OUT_OF_RANGE;
	}
	
	for (cont = 0; cont < nArcs; cont++) {
		
		if (Arcs[cont]->getSrc() == src
		    && Arcs[cont]->getDest() == dest) {
			
			return Arcs[cont]->getTarget();
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return _PROCESS_ERROR_CODE_NOT_FOUND;
}

/**
 * \brief	Gets the label of the process.
 * 
 * \fn		string Process::getLabel()
 * \return	A string with the label of the process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
string Process::getLabel()
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return label;
}

/**
 * \brief	Gets the label of a state or arc.
 * 
 * \fn		string Process::getLabel(int trg)
 * \param	trg: the target of the state.
 * \return	A string with the label of the state if the state exists.
 *          <code>_PROCESS_ERROR_OUT_OF_RANGE</code> if <i>trg</i> is out of
 * 			range.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
string Process::getLabel(int trg)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	if (trg >= States.size() || trg < 0) {
				
		return _PROCESS_ERROR_OUT_OF_RANGE;
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return States[trg]->getLabel();
}

/**
 * \brief	Gets the label of an arc.
 * 
 * \fn		string Process::getLabel(int src, int dest)
 * \param	src: the target of the source state.
 * \param	dest: the target of the destination state.
 * \return	A string with the label of the arc if the arc exists. 
 *          <code>_PROCESS_ERROR_OUT_OF_RANGE</code> if <i>src</i> or
 * 			<i>dest</i> are out of range. <code>_PROCESS_ERROR_NOT_FOUND</code>
 * 			if arc was not found.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
string Process::getLabel(int src, int dest)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int nStates = States.size();
	int nArcs = Arcs.size();
	
	if (src < 0 || src >= nStates || dest < 0 || dest >= nStates) {
		
		return _PROCESS_ERROR_OUT_OF_RANGE;
	}
	
	for (cont = 0; cont < nArcs; cont++) {
		
		if (Arcs[cont]->getSrc() == src
		    && Arcs[cont]->getDest() == dest) {
			
			return Arcs[cont]->getLabel();
		}
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return _PROCESS_ERROR_NOT_FOUND;
}

/**
 * \brief	Returns a vector with the targets of the successors of a state.
 * 
 * \fn		vector<int> Process::getSuccessors(int trg)
 * \param	trg: the target of the state to calculate successors.
 * \return	A vector with the targets of all successors states of the state with
 *          target <i>trg</i>.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	10/06/2004
 */
vector<int> Process::getSuccessors(int trg)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int nArcs = Arcs.size();
	vector<int> succ;
	
	for (cont = 0; cont < nArcs; cont++) {
	
		if (Arcs[cont]->getSrc() == trg) {
		
			succ.insert(succ.end(), Arcs[cont]->getDest());
		}	
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return succ;
}

/**
 * \brief	Returns a vector with the targets of the predecessors of a state.
 * 
 * \fn		vector<int> Process::getPredecessors(int trg)
 * \param	trg: the target of the state to calculate predecessors.
 * \return	A vector with the targets of all predecessors states of the state
 * 			with target <i>trg</i>.
 * 
 * \author Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date   10/06/2004
 */
vector<int> Process::getPredecessors(int trg)
{
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	int cont;
	int nArcs = Arcs.size();
	vector<int> pred;
	
	for (cont = 0; cont < nArcs; cont++) {
	
		if (Arcs[cont]->getDest() == trg) {
		
			pred.insert(pred.end(), Arcs[cont]->getSrc());
		}	
	}
	
	#ifdef _JABUTI_SG_DEBBUGING
		cerr << __FILE__ << ": " << __LINE__ << endl;
	#endif
	
	return pred;
}
