//IpDll.h
//header file for IpDll class
#include "pdll.h"

// Fedorov I.L.14.11.07
#ifndef ANY_SIZE

#define ANY_SIZE 1

#endif
//end 

typedef struct _MIB_IPFORWARDROW{
  DWORD   dwForwardDest;       // IP addr of destination
  DWORD   dwForwardMask;       // subnetwork mask of destination
  DWORD   dwForwardPolicy;     // conditions for multi-path route
  DWORD   dwForwardNextHop;    // IP address of next hop
  DWORD   dwForwardIfIndex;    // index of interface
  DWORD   dwForwardType;       // route type
  DWORD   dwForwardProto;      // protocol that generated route
  DWORD   dwForwardAge;        // age of route
  DWORD   dwForwardNextHopAS;  // autonomous system number 
                               // of next hop
  DWORD   dwForwardMetric1;    // protocol-specific metric 
  DWORD   dwForwardMetric2;    // protocol-specific metric 
  DWORD   dwForwardMetric3;    // protocol-specific metric 
  DWORD   dwForwardMetric4;    // protocol-specific metric 
  DWORD   dwForwardMetric5;    // protocol-specific metric 
} MIB_IPFORWARDROW, *PMIB_IPFORWARDROW;

// Fedorov I.L.14.11.07
typedef struct _MIB_IPFORWARDTABLE {
  DWORD               dwNumEntries;    // number of entries in the table 
  MIB_IPFORWARDROW    table[ANY_SIZE]; // array of route entries 
} MIB_IPFORWARDTABLE, *PMIB_IPFORWARDTABLE;
//end
class IpDLL : public PDLL
{
   DECLARE_CLASS(IpDLL)
//we call macros according to how many parameters the function 
//takes, we pass to the macros the following parameters
//return type, function name, parameters
   DECLARE_FUNCTION1(DWORD, CreateIpForwardEntry, PMIB_IPFORWARDROW)
   DECLARE_FUNCTION1(DWORD, DeleteIpForwardEntry, PMIB_IPFORWARDROW)
   // Fedorov I.L.14.11.07
   DECLARE_FUNCTION2(DWORD, GetIpForwardTable, PMIB_IPFORWARDTABLE, PULONG, BOOL)
   //end
};

