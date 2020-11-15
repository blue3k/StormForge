﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromFOrge
// 
// Author : Generated
// 
// Description : Relay Message debug implementations
// 
////////////////////////////////////////////////////////////////////////////////


#include "SFProtocolPCH.h"
#include "SFTypedefs.h"
#include "Net/SFNetDef.h"
#include "Net/SFMessage.h"
#include "Net/SFConnection.h"
#include "Protocol/Policy/RelayNetPolicy.h"
#include "Protocol/Message/RelayMsgClass.h"



namespace SF
{
 	namespace Policy
	{
 		// C2S: Event for Player Join request.
		Result NetPolicyRelay::JoinRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID, InPlayerIdentifier);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::JoinRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier )
		// C2S: Event for Player Join request.
		Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::LeaveRelayInstanceC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InPlayerID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::LeaveRelayInstanceC2SEvt( const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID )
		// C2S: Relay packet
		Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::RelayPacketC2SEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InSenderEndpointID, InTargetEndpointMask, InPayload);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::RelayPacketC2SEvt( const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload )
		// Cmd: Create stream instance
		Result NetPolicyRelay::CreateStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::CreateStreamingCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::CreateStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Open stream instance
		Result NetPolicyRelay::OpenStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::OpenStreamingCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamName);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::OpenStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamName )
		// Cmd: Delete stream instance
		Result NetPolicyRelay::DeleteStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::DeleteStreamingCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::DeleteStreamingCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket, const char* InStreamUID )
		// Cmd: Create stream instance
		Result NetPolicyRelay::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::GetStreamListCmd::Create(m_pConnection->GetIOHeap(), InTransactionID, InTicket);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetPolicyRelay::GetStreamListCmd( const uint64_t &InTransactionID, const AuthTicket &InTicket )


		// S2C: Event for joined player
		Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::JoinRelayInstanceResS2CEvt::Create(m_pConnection->GetIOHeap(), InResult, InRelayInstanceID, InMyEndpointID, InMemberInfos);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::JoinRelayInstanceResS2CEvt( const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos )
		// S2C: Event for Player joined.
		Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerJoinS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InJoinedPlayerInfo);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerJoinS2CEvt( const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo )
		// S2C: Event for Player left.
		Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::PlayerLeftS2CEvt::Create(m_pConnection->GetIOHeap(), InRelayInstanceID, InLeftPlayerID, InKickedReason);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::PlayerLeftS2CEvt( const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason )
		// Cmd: Create stream instance
		Result NetSvrPolicyRelay::CreateStreamingRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::CreateStreamingRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::CreateStreamingRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Open stream instance
		Result NetSvrPolicyRelay::OpenStreamingRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::OpenStreamingRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamServerAddr, InStreamServerAddrIPV4, InStreamUID);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::OpenStreamingRes( const uint64_t &InTransactionID, const Result &InResult, const NetAddress &InStreamServerAddr, const NetAddress &InStreamServerAddrIPV4, const char* InStreamUID )
		// Cmd: Delete stream instance
		Result NetSvrPolicyRelay::DeleteStreamingRes( const uint64_t &InTransactionID, const Result &InResult )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::DeleteStreamingRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::DeleteStreamingRes( const uint64_t &InTransactionID, const Result &InResult )
		// Cmd: Create stream instance
		Result NetSvrPolicyRelay::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamNames )
		{
 			FunctionContext hr;

			 MessageDataPtr pMessage;
			 protocolCheckPtr(m_pConnection);

			 pMessage = SF::Message::Relay::GetStreamListRes::Create(m_pConnection->GetIOHeap(), InTransactionID, InResult, InStreamNames);
			 protocolCheckPtr(*pMessage);

			 return m_pConnection->Send( pMessage );

			return hr;

		}; // Result NetSvrPolicyRelay::GetStreamListRes( const uint64_t &InTransactionID, const Result &InResult, const char* InStreamNames )


	}; // namespace Policy
}; // namespace SF


