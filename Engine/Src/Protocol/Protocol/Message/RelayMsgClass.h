﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : Generated
// 
// Description : Relay Message parser definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Protocol/SFProtocol.h"
#include "Net/SFMessage.h"
#include "Types/SFEngineTypedefs.h"
#include "Variable/SFVariableMapBuilder.h"



namespace SF
{
 	namespace Message
	{
 		namespace Relay
		{
 			// C2S: Event for Player Join request.
			class JoinRelayInstanceC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				uint32_t m_RelayInstanceID;
				PlayerID m_PlayerID;
				const char* m_PlayerIdentifier;
			public:
				JoinRelayInstanceC2SEvt()
				:m_PlayerIdentifier(nullptr)
					{}

				JoinRelayInstanceC2SEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
				,m_PlayerIdentifier(nullptr)
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };
				const char* GetPlayerIdentifier() const	{ return m_PlayerIdentifier; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID, const char* InPlayerIdentifier );

			}; // class JoinRelayInstanceC2SEvt : public MessageBase

			// S2C: Event for joined player
			class JoinRelayInstanceResS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return 0; }
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				Result m_Result;
				uint32_t m_RelayInstanceID;
				uint32_t m_MyEndpointID;
				ExternalBufferArray<RelayPlayerInfo> m_MemberInfos;
			public:
				JoinRelayInstanceResS2CEvt()
					{}

				JoinRelayInstanceResS2CEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const Result& GetResult() const	{ return m_Result; };
				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const uint32_t& GetMyEndpointID() const	{ return m_MyEndpointID; };
				const Array<RelayPlayerInfo>& GetMemberInfos() const	{ return m_MemberInfos; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const Result &InResult, const uint32_t &InRelayInstanceID, const uint32_t &InMyEndpointID, const Array<RelayPlayerInfo>& InMemberInfos );

			}; // class JoinRelayInstanceResS2CEvt : public MessageBase

			// C2S: Event for Player Join request.
			class LeaveRelayInstanceC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 1,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				uint32_t m_RelayInstanceID;
				PlayerID m_PlayerID;
			public:
				LeaveRelayInstanceC2SEvt()
					{}

				LeaveRelayInstanceC2SEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const PlayerID& GetPlayerID() const	{ return m_PlayerID; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InPlayerID );

			}; // class LeaveRelayInstanceC2SEvt : public MessageBase

			// S2C: Event for Player joined.
			class PlayerJoinS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return 0; }
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				uint32_t m_RelayInstanceID;
				RelayPlayerInfo m_JoinedPlayerInfo;
			public:
				PlayerJoinS2CEvt()
					{}

				PlayerJoinS2CEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const RelayPlayerInfo& GetJoinedPlayerInfo() const	{ return m_JoinedPlayerInfo; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const RelayPlayerInfo &InJoinedPlayerInfo );

			}; // class PlayerJoinS2CEvt : public MessageBase

			// S2C: Event for Player left.
			class PlayerLeftS2CEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return 0; }
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				uint32_t m_RelayInstanceID;
				PlayerID m_LeftPlayerID;
				uint32_t m_KickedReason;
			public:
				PlayerLeftS2CEvt()
					{}

				PlayerLeftS2CEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const PlayerID& GetLeftPlayerID() const	{ return m_LeftPlayerID; };
				const uint32_t& GetKickedReason() const	{ return m_KickedReason; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const PlayerID &InLeftPlayerID, const uint32_t &InKickedReason );

			}; // class PlayerLeftS2CEvt : public MessageBase

			// C2S: Relay packet
			class RelayPacketC2SEvt : public MessageBase
			{
 			public:
				static const MessageID MID;
				// Parameter type informations for template
				enum ParameterTypeInfo
				{
 					HasPlayerID = 0,
					HasTransactionID = 0,
					HasRouteContext = 0,
					HasRouteHopCount = 0,
					HasSender = 0,
				}; // enum ParameterTypeInfo
			public:
				uint64_t GetPlayerID() { return 0; }
				uint64_t GetTransactionID() { return 0; }
				RouteContext GetRouteContext() { return 0; }
				uint32_t GetRouteHopCount() { return 0; }
				uint64_t GetSender() { return 0; }
			private:
				uint32_t m_RelayInstanceID;
				uint32_t m_SenderEndpointID;
				uint32_t m_TargetEndpointMask;
				ExternalBufferArray<uint8_t> m_Payload;
			public:
				RelayPacketC2SEvt()
					{}

				RelayPacketC2SEvt( MessageDataPtr &&pMsg )
					: MessageBase(std::forward<MessageDataPtr>(pMsg))
					{}

					MessageUsage GetMessageUsage() { return MessageUsage_None; }

				const uint32_t& GetRelayInstanceID() const	{ return m_RelayInstanceID; };
				const uint32_t& GetSenderEndpointID() const	{ return m_SenderEndpointID; };
				const uint32_t& GetTargetEndpointMask() const	{ return m_TargetEndpointMask; };
				const Array<uint8_t>& GetPayload() const	{ return m_Payload; };

				static Result TraceOut(const char* prefix, const MessageDataPtr& pMsg);

				virtual Result ParseMessage( MessageData* pIMsg );
				static Result ParseMessageTo( MessageDataPtr& pIMsg, IVariableMapBuilder& variableBuilder );
				static Result ParseMessageToMessageBase( IHeap& memHeap, MessageDataPtr&& pIMsg, MessageBase* &pMsgBase );

				static MessageData* Create( IHeap& memHeap, const uint32_t &InRelayInstanceID, const uint32_t &InSenderEndpointID, const uint32_t &InTargetEndpointMask, const Array<uint8_t>& InPayload );

			}; // class RelayPacketC2SEvt : public MessageBase





		}; // namespace Relay
	}; // namespace Message
}; // namespace SF

