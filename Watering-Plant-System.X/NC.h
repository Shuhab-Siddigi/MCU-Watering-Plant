#ifndef NC_H_
#define NC_H_

#include "NcApi\NeoParser.h"

#include <stdio.h>
#include <string.h>

NcApiErrorCodes SendUnacknowledged(uint16_t destNodeId, uint8_t port, uint8_t * payload, uint8_t payloadLen, uint8_t n);
NcApiErrorCodes SendAcknowledged(uint16_t destNodeId, uint8_t port, uint8_t * payload, uint8_t payloadLen, uint8_t n);
NcApiErrorCodes SendNodeInfoRequest(uint8_t n);
NcApiErrorCodes SendNeighborListRequest(uint8_t n);
NcApiErrorCodes SendNetCmd(uint16_t destNodeId, uint8_t cmd, uint8_t * payload, uint8_t payloadLength, uint8_t n);
NcApiErrorCodes SendWesCmd(NcApiWesCmdValues cmd, uint8_t n);
NcApiErrorCodes SendWesResponse(uint8_t uid[5], uint16_t nodeId, uint8_t appSettings[WES_APPSETTINGS_LENGTH], uint8_t n);
NcApiErrorCodes SendAltCmd(NcApiAltCmdValues cmd, uint8_t n);
NcApiErrorCodes SendRaw(uint16_t destNodeId, uint8_t destPort, uint8_t payloadLength, uint8_t * payload, uint8_t n);


void PassthroughNWU();
void NcApiSupportRxData();
void SetupNCApi();

#endif /* NC_H_ */