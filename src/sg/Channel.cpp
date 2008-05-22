/**
 * \file		sg/Channel.cpp
 * \brief		The methods of the <b>Channel</b> class.
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
 * 
 */

using namespace std;

#include "Channel.h"

/**
 * \brief	Class constructor. Creates a new <b>Channel</b> element.
 * 
 * \fn		Channel::Channel()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	04/06/2004
 */
Channel::Channel()
{
	target = nextTarget++;
	writer = _CHANNEL_NONE;
	reader = _CHANNEL_NONE;
}

/**
 * \brief	Class constructor. Creates a new <b>Channel</b> element.
 * 
 * \fn		Channel::Channel(const char *lab)
 * \param	*lab: Label of the new channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	04/06/2004
 */
Channel::Channel(const char *lab)
{
	label = lab;
	target = nextTarget++;
	writer = _CHANNEL_NONE;
	reader = _CHANNEL_NONE;
}

/**
 * \brief	Class constructor. Creates a new <b>Channel</b> element.
 * 
 * \fn		Channel::Channel(const char *lab, int c, int s)
 * \param	*lab: Label of the new channel.
 * \param	c: Number of cells available in the channel.
 * \param	s: Number of slots available in each cell of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	07/09/2004
 */
Channel::Channel(const char *lab, int c, int s)
{
	label = lab;
	target = nextTarget++;
	cells = c;
	slots = s;
	writer = _CHANNEL_NONE;
	reader = _CHANNEL_NONE;
}

/**
 * \brief	Class destructor.
 * 
 * \fn		Channel::~Channel()
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
Channel::~Channel()
{}

/**
 * \brief	Gets the label of the channel.
 * 
 * \fn		string Channel::getLabel()
 * \return	A string with the label of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	04/06/2004
 */
string Channel::getLabel()
{
	return label;
}

/**
 * \brief	Gets the target of the channel.
 * 
 * \fn		int Channel::getTarget()
 * \return	An integer with the target of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
int Channel::getTarget()
{
	return target;
}

/**
 * \brief	Gets the number of cells available in the channel.
 * 
 * \fn		int Channel::getCells()
 * \return	An integer with the number of cells in the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	07/09/2004
 */
int Channel::getCells()
{
	return cells;
}

/**
 * \brief	Gets the number of slots available in each cell of the channel.
 * 
 * \fn		int Channel::getSlots()
 * \return	An integer with the number of slots in each cell of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
int Channel::getSlots()
{
	return slots;
}

/**
 * \brief	Gets the target of the writer process.
 * 
 * \fn		int Channel::getWriter()
 * \return	An integer with the target of the process that writes on the
 * 			channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
int Channel::getWriter()
{
	return writer;
}

/**
 * \brief	Gets the target of the reader process.
 * 
 * \fn		int Channel::getReader()
 * \return	An integer with the target of the process that reads from the
 * 			channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
int Channel::getReader()
{
	return reader;
}

/**
 * \brief	Gets the type of the channel.
 * 
 * \fn		int Channel::getType()
 * \return	An integer with the type of the communication mechanism implemented
 * 			by the channel as specifyied in the <code>type</code> attribute.
 * 
 * Gets the type of the channel. The type of the channel specifyies the kind of
 * of communication mechanism the channel should implements.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
int Channel::getType()
{
	return type;
}

/**
 * \brief	Sets the label of the channel.
 * 
 * \fn		void Channel::setLabel(const char *lab)
 * \param	*lab: a string with the label of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	04/06/2004
 */
void Channel::setLabel(const char *lab)
{
	label = lab;
}

/**
 * \brief	Sets the number of cells of the channel.
 * 
 * \fn		void Channel::setCells(int n)
 * \param	n: the number of cells of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	07/09/2004
 */
void Channel::setCells(int n)
{
	cells = n;
}

/**
 * \brief	Sets the number of slots of the channel.
 * 
 * \fn		void Channel::setSlots(int n)
 * \param	n: the number of slots in each cell of the channel.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	04/06/2004
 */
void Channel::setSlots(int n)
{
	slots = n;
}

/**
 * \brief	Sets the target of the writer process.
 * 
 * \fn		void Channel::setWriter(int trg)
 * \param	trg: the target of the writer process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	03/06/2004
 */
void Channel::setWriter(int trg)
{
	writer = trg;
}

/**
 * \brief	Sets the target of the reader process.
 * 
 * \fn		void Channel::setReader(int trg)
 * \param	trg: the target of the reader process.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
void Channel::setReader(int trg)
{
	reader = trg;
}

/**
 * \brief	Sets the type of the channel.
 * 
 * \fn		void Channel::setType(int t)
 * \param	t: the type of the channel. May be:
 * 			- <code>_CHANNEL_RRBB</code> if the channel implements a
 * 			  <b>message</b> (Re-Reading) policy.
 * 			- <code>_CHANNEL_OWBB</code> if the channel implements a
 * 			  <b>signal</b> (OverWriting) policy.
 * 			- <code>_CHANNEL_OWRRBB</code> if the channel implements a <b>pool</b>
 * 			  (OverWriting and Re-Reading) policy.
 * 
 * Sets the type of the channel. The type of the channel specifyies the kind of
 * of communication mechanism the channel should implements.
 * 
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	06/07/2004
 */
void Channel::setType(int t)
{
	type = t;
	
	/*
	 * TODO: This piece of code is a <i>gambearra</i> to avoid errors when
	 * reffering to the <code>slots</code> attribute. Should be fixed to fully
	 * support any arbitrary number of slots. Someday I will fixit.
	 */
	if (t == _CHANNEL_OWBB) {
		
		slots = 2;
	} else if (t == _CHANNEL_RRBB) {
		
		slots = 1;
	} else if (t == _CHANNEL_OWRRBB) {
		
		slots = 2;
	}
}
