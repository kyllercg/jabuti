/**
 * \file		sg/Arc.cpp
 * \brief		The methods of the <b>Arc</b> class.
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
 * .
 */

using namespace std;

#include "Arc.h"

/**
 * \brief	Class constructor. Creates a new <b>Arc</b> element.
 * 
 * \fn		Arc::Arc(int src, const char *lab, int dest, int trg)
 * \param	src: target of the source state.
 * \param	*lab: label of the arc.
 * \param	dest: target of the destination state.
 * \param	trg: target of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
Arc::Arc(int src, const char *lab, int dest, int trg)
{
	source = src;
	label = lab;
	destination = dest;
	//aTarget = nextTarget++;
	target = trg;
	IOArc = false;
	IOType = _ARC_NONE;
	IOChannel = _ARC_NONE;
	IOSlot = _ARC_NONE;
	IOCell = _ARC_NONE;
}

/**
 * \brief	Class constructor. Creates a new <b>Arc</b> element.
 * 
 * \fn		Arc::Arc(const char *lab, int trg)
 * \param	*lab: label of the arc.
 * \param	trg: target of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	14/06/2004
 */
Arc::Arc(const char *lab, int trg)
{
	label = lab;
	//aTarget = nextTarget++;
	target = trg;
	IOArc = false;
	IOType = _ARC_NONE;
	IOChannel = _ARC_NONE;
	IOSlot = _ARC_NONE;
}
/**
 * \brief	Class destructor.
 * 
 * \fn		Arc::~Arc()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
Arc::~Arc()
{}

/**
 * \brief	Gets the target of the source state.
 * 
 * \fn		int Arc::getSrc()
 * \return	An integer with the target of the source state of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
int Arc::getSrc()
{
	return source;
}

/**
 * \brief	Gets the target of the destination state.
 * 
 * \fn		int Arc::getDest()
 * \return	An integer with the target of the destination state of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
int Arc::getDest()
{
	return destination;
}

/**
 * \brief	Gets the label of the arc.
 * 
 * \fn		string Arc::getLabel()
 * \return	A string with the label of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
string Arc::getLabel()
{
	return label;
}

/**
 * \brief	Gets the target of the arc.
 * 
 * \fn		int Arc::getTarget()
 * \return	An integer with the target of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	02/06/2004
 */
int Arc::getTarget()
{
	return target;
}

/**
 * \brief	Gets the type of  IO operation (_ARC_READ? or _ARC_WRITE?).
 * 
 * \fn		int Arc::getIOType()
 * \return	An integer with the IO type. May be:
 * 			- <code>_ARC_READ</code> if the arc is a read operation.
 * 			- <code>_ARC_WRITE</code> if the arc is a write operation.
 * 			- <code>_ARC_NONE</code> if the arc is an internal action of the
 * 			  process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	16/06/2004
 */
int Arc::getIOType()
{
	return IOType;
}

/**
 * \brief	Gets the target of the channel to perform IO..
 * 
 * \fn		int Arc::getChannel()
 * \return	An integer with the target of the channel in which the arc will
 * 			write or read.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	16/06/2004
 */
int Arc::getChannel()
{
	return IOChannel;
}

/**
 * \brief	Gets the number of the cell to perform an IO operation.
 * 
 * \fn		int Arc::getOnCell()
 * \return	An integer with the cell number in which the arc will write or read.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	20/09/2004
 */
int Arc::getOnCell()
{
	return IOCell;
}

/**
 * \brief	Gets the number of the slot to perform an IO operation.
 * 
 * \fn		int Arc::getOnSlot()
 * \return	An integer with the slot number  in which the arc will write or
 * 			read.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	16/06/2004
 */
int Arc::getOnSlot()
{
	return IOSlot;
}

/**
 * \brief	Sets the target of the source state.
 * 
 * \fn		void Arc::setSrc(int trg)
 * \param	trg: the target of the source state of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
void Arc::setSrc(int trg)
{
	source = trg;
}

/**
 * \brief	Sets the label of the arc.
 * 
 * \fn		void Arc::setLabel(const char *lab)
 * \param	*lab: the label of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
void Arc::setLabel(const char *lab)
{
	string aux = lab;
	label.swap(aux);
}

/**
 * \brief	Sets the target of the destination state.
 * 
 * \fn		void Arc::setDest(int trg)
 * \param	trg: the target of the destination state of the arc.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	31/05/2004
 */
void Arc::setDest(int trg)
{
	destination = trg;
}

/**
 * \brief	Sets IO information about an arc.
 * 
 * \fn		void Arc::setIO(int type, int trg)
 * \param	type: the type of the operation. May be:
 * 			- <code>_ARC_READ</code> if the arc is a read operation.
 * 			- <code>_ARC_WRITE</code> if the arc is a write operation.
 * \param	trg: the target of the channel.
 * 
 * Sets IO information about an arc. This method is used to inform if the arc
 * performs a write or a read in a channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	15/06/2004
 */
void Arc::setIO(int type, int trg)
{
	IOArc = true;
	IOType = type;
	IOChannel = trg;
}

/**
 * \brief	Sets the number of the cell to perform an IO operation.
 * 
 * \fn		void Arc::setOnCell(int c)
 * \param	c: number of the cell.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	16/06/2004
 */
void Arc::setOnCell(int c)
{
	IOCell = c;
}

/**
 * \brief	Sets the number of the slot to perform an IO operation.
 * 
 * \fn		void Arc::setOnSlot(int s)
 * \param	s: number of the slot.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	20/09/2004
 */
void Arc::setOnSlot(int s)
{
	IOSlot = s;
}

/**
 * \brief	Checks if the arc performs an IO operation.
 * 
 * \fn		bool Arc::isIO()
 * \return	- true: if the arc writes (or reads) on (from) a channel.
 * 			- false: otherwise.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	15/06/2004
 */
bool Arc::isIO()
{
	return IOArc;
}
