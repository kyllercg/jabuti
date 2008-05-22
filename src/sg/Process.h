/**
 * \file		sg/Process.h
 * \brief		The definition of the <b>Process</b> class.
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
 */

using namespace std;

#include "config.h"

#include "Arc.h"
#include "State.h"

#include <string>
#include <vector>

#ifndef PROCESS_H
#define PROCESS_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * DEFINES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** Internal code for an <b>Arc</b> element. */
#define _PROCESS_ARC_CODE					1

/** Internal code for a <b>State</b> element. */
#define _PROCESS_STATE_CODE					2
 
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * CODE ERRORS
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** Code error: indicates that a given element does not exist in the process. */
#define _PROCESS_ERROR_CODE_NOT_FOUND		-10

/** Code error: indicates that a given target is out of range. */
#define _PROCESS_ERROR_CODE_OUT_OF_RANGE	-20

/** Code error: indicates that a given element was not inserted. */
#define _PROCESS_ERROR_CODE_NOT_INSERTED	-30

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * ERRORS MESSAGE
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
 
/** Message error: informs that an element does not exist in the process. */
#define _PROCESS_ERROR_NOT_FOUND			"target not found"

/** Message error: informs that a target is out of range. */
#define _PROCESS_ERROR_OUT_OF_RANGE			"target out of range"

/**
 * \class	Process Process.h
 * \brief	The <b>Process</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	May, 2004
 * 
 * The <b>Process</b> class. An object of this type represents a process of the
 * system.
 */
class Process {
	
	public:
	
		/** States of the process. */
		vector<State *> States;
		
		/** Arcs linking states in the process. */
		vector<Arc *> Arcs;
	
		Process(const char *lab);						/* constructor */
		Process();										/* constructor */
		~Process();										/* destructor */
		
		int insertArc(int src, const char *lab, int dest);	/* insert arc */
		int insertArc(int src, const char *lab, int dest, int io, int ch);
		int insertArc(const char *lab);				/* insert arc */
		int insertState(const char *lab);			/* insert state */
		
		bool exists(const char *lab, int type);		/* exists state/arc? */
		
		int getNextTarget();						/* next available target */
		int getTarget();							/* process target */
		int getTarget(const char *lab);				/* state target */
		int getTarget(const char *src, const char *dest);	/* arc target */
		int getTarget(int src, int dest);			/* arc target */
		string getLabel();							/* process label */
		string getLabel(int trg);					/* state label */
		string getLabel(int src, int dest);			/* arc label */
		vector<int> getSuccessors(int trg);			/* vector of successors */
		vector<int> getPredecessors(int trg);		/* vector of predecessors */
	
	private:
	
		/** The label of the process. */
		string label;
		
		/** The target of the process. */
		int target;
		
		/** The target of the next <b>State</b> to be created inside the
		 *  process. */
		int nextStateTarget;
		
		/** The target of the next <b>Arc</b> to be created inside the
		 *  process. */
		int nextArcTarget;
		
		/** The target of the next process to be created. */
		static int nextTarget;
};
#endif /* PROCESS_H */
