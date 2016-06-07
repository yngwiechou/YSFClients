/*
*   Copyright (C) 2016 by Jonathan Naylor G4KLX
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#if !defined(WIRESX_H)
#define	WIRESX_H

#include "Network.h"
#include "Timer.h"

#include <string>

enum WX_STATUS {
	WXS_NONE,
	WXS_CONNECT,
	WXS_DISCONNECT
};

enum WXSI_STATUS {
	WXSI_NONE,
	WXSI_DX,
	WXSI_CONNECT,
	WXSI_DISCONNECT,
	WXSI_ALL
};

class CWiresX {
public:
	CWiresX(CNetwork* network);
	~CWiresX();

	WX_STATUS process(const unsigned char* data, unsigned char fi, unsigned char dt, unsigned char fn);

	std::string getReflector() const;

	void clock(unsigned int ms);

private:
	CNetwork*      m_network;
	std::string    m_reflector;
	CTimer         m_timer;
	unsigned char  m_seqNo;
	unsigned char* m_csd1;
	WXSI_STATUS    m_status;

	void processConnect(const unsigned char* data);
	void processDisconnect();
	void processDX();
	void processAll();

	void sendDXReply();
	void sendConnectReply();
	void sendDisconnectReply();
	void sendAllReply();

	void createReply(const unsigned char* data, unsigned int length);
	unsigned char calculateFT(unsigned int length) const;
};

#endif
