#include "NC.h"
#include "xc.h"

tNcApi g_ncApi[1];
uint8_t g_numberOfNcApis = 1;
tNcApiRxHandlers ncRx;

void NcApiSupportRxData()
{
    uint8_t byte = U1RXREG;
    if(byte != 0x00 || byte != 0x00)
    {
        byte++;
    }
    NcApiRxData(0, byte);
}

void NcApiSupportTxData(uint8_t n, uint8_t *finalMsg, uint8_t finalMsgLength)
{

}

void NcApiSupportMessageWritten(uint8_t n, void *callbackToken, uint8_t *finalMsg, uint8_t finalMsgLength)
{
    
}

void NcApiSupportMessageReceived(uint8_t n, void *callbackToken, uint8_t *msg, uint8_t msgLength)
{
    NcApiExecuteCallbacks(n, msg, msgLength);
    PassthroughNWU();
}


void PassthroughCTS()
{

}

void PassthroughNWU()
{
    NcApiCallbackNwuActive(0);
}

NcApiErrorCodes SendUnacknowledged(uint16_t destNodeId, uint8_t port, uint8_t * payload, uint8_t payloadLen, uint8_t n)
{
    tNcApiSendUnackParams args;
	NcApiErrorCodes apiStatus;
	args.msg.destNodeId = destNodeId;
	args.msg.destPort = port;
	args.msg.payload = payload;
	args.msg.payloadLength = payloadLen;
	args.callbackToken = &g_ncApi;
	apiStatus = NcApiSendUnacknowledged(n, &args);
    NcApiCtsActive(0);
	if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error sending queueing NACK!");
	}
    return apiStatus;
}

NcApiErrorCodes SendAcknowledged(uint16_t destNodeId, uint8_t port, uint8_t * payload, uint8_t payloadLen, uint8_t n)
{
	tNcApiSendAckParams args;
	NcApiErrorCodes apiStatus;
	args.msg.destNodeId = destNodeId;
	args.msg.destPort = port;
	args.msg.payload = payload;
	args.msg.payloadLength = payloadLen;
	args.callbackToken = &g_ncApi;
	apiStatus = NcApiSendAcknowledged(n, &args);
    NcApiCtsActive(0);
	if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:ACK!");
	}
    return apiStatus;
}

NcApiErrorCodes SendNodeInfoRequest(uint8_t n)
{
    tNcApiNodeInfoParams args;
	NcApiErrorCodes apiStatus;
    args.callbackToken = &g_ncApi;
	apiStatus = NcApiSendNodeInfoRequest(n, &args);
    NcApiCtsActive(0);
	if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:NodeInfo!");
	}
    return apiStatus;
}

NcApiErrorCodes SendNeighborListRequest(uint8_t n)
{
    NcApiErrorCodes apiStatus;
    apiStatus = NcApiSendNeighborListRequest(n, &g_ncApi);
    NcApiCtsActive(0);
	if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:NeighboListNode!");
	}
    return apiStatus;
}

NcApiErrorCodes SendNetCmd(uint16_t destNodeId, uint8_t cmd, uint8_t * payload, uint8_t payloadLength, uint8_t n)
{
    tNcApiNetCmdParams args;
    NcApiErrorCodes apiStatus;
    args.msg.destNodeId = destNodeId;
    args.msg.cmd = cmd;
    args.msg.payload = payload;
    args.msg.payloadLength = payloadLength;
    args.callbackToken = &g_ncApi;
    apiStatus = NcApiSendNetCmd(n, &args);
    NcApiCtsActive(0);
    if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:NetCmd!");
	}
    return apiStatus;
}

NcApiErrorCodes SendWesCmd(NcApiWesCmdValues cmd, uint8_t n)
{
	tNcApiWesCmdParams args;
    NcApiErrorCodes apiStatus;
	args.msg.cmd = cmd;
    args.callbackToken = &g_ncApi;
	apiStatus =  NcApiSendWesCmd(n, &args );
    NcApiCtsActive(0);
    if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:WesCmd!");
	}
    return apiStatus;
}

NcApiErrorCodes SendWesResponse(uint8_t uid[5], uint16_t nodeId, uint8_t appSettings[WES_APPSETTINGS_LENGTH], uint8_t n)
{

    tNcApiWesResponseParams args;
    memcpy(args.msg.uid, uid, sizeof(uid));
    args.msg.nodeId = nodeId;
    memcpy(args.msg.appSettings, appSettings, sizeof(appSettings));
    args.callbackToken = &g_ncApi;
    NcApiErrorCodes apiStatus;
    apiStatus = NcApiSendWesResponse(n, &args);
    NcApiCtsActive(0);
    if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:WesResponse!");
	}
    return apiStatus;
}

NcApiErrorCodes SendAltCmd(NcApiAltCmdValues cmd, uint8_t n)
{
    tNcApiAltCmdParams args;
    args.msg.cmd = cmd;
    args.callbackToken = &g_ncApi;
    NcApiErrorCodes apiStatus;
    apiStatus = NcApiSendAltCmd(n, &args);
    NcApiCtsActive(0);
    if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:AltCmd!");
	}
    return apiStatus;
}

NcApiErrorCodes SendRaw(uint16_t destNodeId, uint8_t destPort, uint8_t payloadLength, uint8_t * payload, uint8_t n)
{
    tNcApiSendAckParams args;
    args.msg.destNodeId = destNodeId;
    args.msg.destPort = destPort;
    args.msg.payloadLength = payloadLength;
    args.msg.payload = payload;
    args.callbackToken = &g_ncApi;
    NcApiErrorCodes apiStatus;
    apiStatus = NcApiSendRaw(n, &args);
    NcApiCtsActive(0);
    if (apiStatus != NCAPI_OK)
	{
		; // Application specific
        printf("Error: queueing Tx:Raw!");
	}
    return apiStatus;
}

void ReadCallback(uint8_t n, uint8_t * msg, uint8_t msgLength)
{
    uint16_t i = 0;
    i++;
	/*printf("Raw UART data received: ");
	for (i=0; i<msgLength; i++)
		printf( "%02x ", msg[i] );
	printf("\r\n");
    */
}

void SetupNCApi()
{
    tNcApiRxHandlers *rxHandlers = &ncRx;
    memset(rxHandlers, 0, sizeof(tNcApiRxHandlers));

    rxHandlers->pfnReadCallback = ReadCallback;

    NcApiInit();

    g_ncApi[0].NcApiRxHandlers = &ncRx;
}