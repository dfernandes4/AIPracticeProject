#include "AIState.h"

UAIState::UAIState()
{
	DisplayNameMap.Add(FName("Passive"));
	DisplayNameMap.Add(FName("Attacking"));
	DisplayNameMap.Add(FName("Frozen"));
	DisplayNameMap.Add(FName("Investigating"));
	DisplayNameMap.Add(FName("Dead"));
}
