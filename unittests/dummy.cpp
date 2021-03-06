//
// $Id$
//
// Copyright (C) 2007 Turner Technolgoies Inc. http://www.turner.ca
//
// Permission is hereby granted, free of charge, to any person 
// obtaining a copy of this software and associated documentation 
// files (the "Software"), to deal in the Software without 
// restriction, including without limitation the rights to use, 
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the 
// Software is furnished to do so, subject to the following 
// conditions:
//      
// The above copyright notice and this permission notice shall be 
// included in all copies or substantial portions of the Software. 
//      
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
// OTHER DEALINGS IN THE SOFTWARE.

#include <assert.h>
#include <cstdio>
#include "dummy.hpp"


// Event Interface -------------------

DummyDb::DummyDb() :
  numInits(0),
  numChanges(0)
{
}


void DummyDb::changePoint(   DnpAddr_t      addr,
                             DnpIndex_t     index,
                             PointType_t    pointType,
                             int            value,
                             DnpTime_t      timestamp)
{
    assert(addr != 0);
    numChanges++;
}

void  DummyDb::registerName( DnpAddr_t      addr,
                             DnpIndex_t     index,
                             PointType_t    pointType,
                             char*          name,
                             int            initialValue )
{

}

// Transmit Interface -----------------

DummyTx::DummyTx(int* debugLevel_p, char name1, char name2) :
numTxs(0), debug_p(debugLevel_p)
{
    n[0] = name1;
    n[1] = name2;
    n[2] = 0;
}

Uptime_t DummyTx::transmit( const Lpdu& lpdu)
{
    char buf[Lpdu::MAX_LEN*3+1];
    assert(lpdu.ab.size() >= 10);
    lastTxBytes = lpdu.ab;
    if (*debug_p > 0)
        printf( "%s Tx %s\n", n, hex_repr( lpdu.ab, buf,sizeof(buf)));
    numTxs++;
    return 0;
}

// Timer Interface --------------------

DummyTimer::DummyTimer() : 
  timerActive(TimerInterface::NUM_TIMERS, false)
{
}

void DummyTimer::activate( TimerId timerId)
{
    timerActive[timerId] = true;
}

void DummyTimer::cancel( TimerId timerId)
{
    timerActive[timerId] = false;
}

bool DummyTimer::isActive( TimerId timerId)
{
    return timerActive[timerId];
}
