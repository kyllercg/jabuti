/**
 * \file		sg/Arc.h
 * \brief		The definition of the <b>Arc</b> class.
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

#include <string>

#ifndef ARC_H
#define ARC_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * DEFINES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** Code for an arc that is an internal action of a process. */
#define _ARC_NONE   	                -10

/** Code for an arc that writes on a channel. */
#define _ARC_WRITE						-20

/** Code for an arc that reads from a channel. */
#define _ARC_READ						-30

/** Code for an arc that updates a control variable. */
#define _ARC_CONTROL					-40

/**
 * \class	Arc Arc.h
 * \brief	The <b>Arc</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	May, 2004
 * 
 * The <b>Arc</b> class. An object of this type represents an arc between two
 * states in a process.
 */
class Arc {
		
	public:
	
		Arc(int src, const char *lab, int dest, int trg);	/* constructor */
		Arc(const char *lab, int trg);						/* constructor */
		~Arc();												/* destructor */
		
		int getSrc();					/* gets target of source state */
		int getDest();					/* gets target of destination state */
		string getLabel();				/* gets label of arc */
		int getTarget();				/* gets target of arc */
		int getIOType();				/* gets io type */
		int getChannel();				/* gets channel target */
		int getOnCell();				/* gets slot number to IO */
		int getOnSlot();				/* gets slot number to IO */
		
		void setSrc(int trg);			/* sets target of source state */
		void setLabel(const char *lab);	/* sets label of arc */
		void setDest(int trg);			/* sets target of destination state */
		void setIO(int type, int trg);	/* sets Arc as IO */
		void setOnCell(int c);			/* sets cell number to IO */
		void setOnSlot(int s);			/* sets slot number to IO */
		
		bool isIO();
		
	private:
	
		/** The label of the arc. */
		string label;
		
		/** The target of the arc. */
		int target;
		
		/** The target of the source state of the arc. */
		int source;
		
		/** The target of the destination state of the arc. */
		int destination;
		
		/** If the object models an IO operation, then <code>IOArc</code> is
		 * equal to <code><b>true</b></code>. Otherwise it is equal to
		 * <code><b>false</b></code>. */
		bool IOArc;
		
		/** If <code>IOArc</code> is equal to <code><b>true</b></code>, then
		 * <code>IOType</code> contains:
		 * - <code>_ARC_WRITE</code> if the the arc writes on a channel.
		 * - <code>_ARC_READ</code> if the arc reads from a channel.
		 * If <code>IOArc</code> is equal to <code><b>false</b></code>, then
		 * <code>IOType</code> will be equal to <code>_ARC_NONE</code>. */
		int IOType;
		
		/** If <code>IOArc</code> is equal to <code><b>true</b></code>, then
		 * <code>IOChannel</code> contains the target of the channel in which
		 * the arc performs the IO operation. */
		int IOChannel;
		
		/** If <code>IOArc</code> is equal to <code><b>true</b></code>, then
		 * <code>IOCell</code> is equal to the number of the cell in which the
		 * IO operation is performed. */
		int IOCell;
		
		/** If <code>IOArc</code> is equal to <code><b>true</b></code>, then
		 * <code>IOSlot</code> is equal to the number of the slot in which the
		 * IO operation is performed. */
		int IOSlot;
};
#endif /* ARC_H */
