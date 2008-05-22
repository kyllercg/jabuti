/**
 * \file		sg/Channel.h
 * \brief		The definition of the <b>Channel</b> class.
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

#include "config.h"

#include <string>

#ifndef CHANNEL_H
#define CHANNEL_H

/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * DEFINES
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

/** To denote nothing. Maybe no writer process or no IO operation! */
#define _CHANNEL_NONE                   -10

/** Defines the code for a <b>WRITE</b> operation. */
#define _CHANNEL_WRITE					-20

/** Defines the code for a <b>READ</b> operation. */
#define _CHANNEL_READ					-30

/** Defines the code for a <b>SIGNAL (OW)</b> communication mechanism. */
#define _CHANNEL_OWBB					100

/** Defines the code for a <b>MESSAGE (RR)</b> communication mechanism. */
#define _CHANNEL_RRBB					101

/** Defines the code for a <b>POOL (OW-RR)</b> communication mechanism. */
#define _CHANNEL_OWRRBB					102

/** Defines the minimum number of cells per channel that is allowed. */
#define _CHANNEL_MIN_CELLS				2

/**
 * \class	Channel Channel.h
 * \brief	The <b>Channel</b> class.
 * \author	Kyller Costa Gorgônio (kyller@lsi.upc.edu)
 * \date	July, 2004
 * 
 * The <b>Channel</b> class. An object of this type represents a channel on the
 * system.
 */
class Channel {
	
	public:

		Channel();
		Channel(const char *lab);
		Channel(const char *lab, int c, int s);
		~Channel();
		
		string getLabel();					/* channel label */
		int getTarget();					/* channel target */
		int getCells();						/* number of cells */
		int getSlots();						/* number of slots */
		int getWriter();					/* writer target */
		int getReader();					/* reader target */
		int getType();						/* communication mechanism type */
		
		void setLabel(const char *lab);		/* sets label */
		void setCells(int n);				/* sets number of cells */
		void setSlots(int n);				/* sets number of slots */
		void setWriter(int trg);			/* sets writer process */
		void setReader(int trg);			/* sets reader process */
		void setType(int t);				/* sets the type of the channel */
		
	private:
	
		/** The label of the channel. */
		string label;
		
		/** The targetof the channel. */
		int target;
		
		/** The number of cells of the channel. */
		int cells;
		
		/** The number of slots of the channel. */
		int slots;
		
		/** The target of the process that writes on the channel. */
		int writer;
		
		/** The target of the process that reads from the channel. */
		int reader;
		
		/** The communication mechanism implemented by the channel.
		 * <code>type</code> is equal to:
		 * - <code>_CHANNEL_RRBB</code> if the channel implements a
		 *   <b>message</b> (Re-Reading) policy.
		 * - <code>_CHANNEL_OWBB</code> if the channel implements a
		 *   <b>signal</b> (OverWriting) policy.
		 * - <code>_CHANNEL_OWRRBB</code> if the channel implements a
		 *   <b>pool</b> (OverWriting and Re-Reading) policy.
		 *  */
		int type;
		
		/** Target of the next channel that will be created. */
		static int nextTarget;
};
#endif /* CHANNEL_H */
