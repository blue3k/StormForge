////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Message Definitions
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "SFAssert.h"
#include "Protocol/SFProtocol.h"


namespace SF {
namespace Message {
	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message ID definition
	//

	//
	//  Bit assignment of messageID
	//    2  1 1 1      7                 9                  11
	//   1 0 9 8 7  6 5 4 3 2 1 0  9 8 7 6 5 4 3 2 1  0 9 8 7 6 5 4 3 2 1 0
	//  +---+-+-+-+---------------+--------------------+----------------------+
	//  | T |G|M|E|   Policy      |       MsgCode      |        Seq           |
	//  +---+-+-+-+---------------+--------------------+----------------------+
	//
	//  where
	//
	//      T - Packet type
	//          00 - Net Control
	//          01 - Event
	//          10 - Command
	//          11 - Result
	//
	//      G - Reliability control bit - Only enabled when using TCP or connection based UDP
	//          0 - Not Guaranteed
	//          1 - Reliable message.
	//
	//      Encrypted
	//      Mobile - Mobility
	//      Policy - Protocol Policy ID
	//      MsgCode - Message ID, 0 is not used
	//      Seq - Sequence of the message
	//

#define NET_SEQUENCE_BITS		11
#define NET_SEQUENCE_MASK		((1<<NET_SEQUENCE_BITS)-1)
#define NET_SEQUENCE_MAX_DIFF	(NET_SEQUENCE_MASK >> 1)

#if !defined(SWIG)
	// Because we pass net class in sequence id, NetClass::Max must be fit in the bits
	static_assert((uint)NetClass::Max <= NET_SEQUENCE_MASK, "Too big net class value");
#endif

	union MessageID
	{
		struct {
			uint32_t Sequence : NET_SEQUENCE_BITS;
			uint32_t MsgCode		: 9;
			uint32_t Policy			: 7;
			uint32_t Encrypted		: 1;
			uint32_t Mobile			: 1;
			uint32_t Reliability	: 1;
			uint32_t Type			: 2;
			uint32_t				: 0;
		} IDs;
		struct {
			uint32_t Sequence : NET_SEQUENCE_BITS;
			uint32_t MsgID	    : 21;
		} IDSeq;
		uint32_t ID;

		MessageID() : ID(0) {}
		//inline tag_MessageID( const tag_MessageID& src );
		MessageID( uint32_t uiID ) : ID(uiID) {}
		MessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode );

		uint32_t SetMessageID( uint uiType, uint uiReliability, uint uiMobility, uint uiPolicy, uint uiCode );

		void SetSequence(uint sequence) { IDSeq.Sequence = sequence; }

		// Only MsgID part, no sequence or length. result will be shifted
		uint GetMsgID() const { return IDSeq.MsgID; }

		uint GetMsgIDOnly() const { return static_cast<uint32_t>(IDSeq.MsgID) << NET_SEQUENCE_BITS; }
#ifndef SWIG
		operator uint32_t() const { return ID; }
#endif
	} ;



	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Constants
	//
	enum
	{
		MAX_MESSAGE_SIZE = (1 << 14) - 1,
		MAX_SUBFRAME_SIZE = 1024 - 64,

		MSGTYPE_NONE			= 0,	

		// Packet type
		MSGTYPE_NETCONTROL		= 0,	// Net Control
		MSGTYPE_EVENT			= 1,	// Event
		MSGTYPE_COMMAND			= 2,	// Command
		MSGTYPE_RESULT			= 3,	// Result

		MSGTYPE_RELIABLE		= 1,	// Reliable messages

		MSGTYPE_MOBILE			= 1,	// Mobile protocol
	};


	////////////////////////////////////////////////////////////////////////////////
	//
	// Message Usage Constants
	//
	enum MessageUsage
	{
		MessageUsage_None,
		MessageUsage_ClusterDataRead,
		MessageUsage_ClusterDataWrite,
		MessageUsage_ClusterStatusRead,
		MessageUsage_ClusterStatusWrite,
	};

	
	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Message Interface
	//

#pragma pack(push, 4)


	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message base Header
	//
	struct MessageHeader
	{
		// Message ID
		MessageID	msgID;

		// Data length
		uint32_t		Length	: 16;

		// lower 16 bit of crc32 or sub frame sequence
		uint32_t		Crc32		: 16;

		// bit field termination
		uint32_t					: 0;

		void SetIDNLen(uint id, uint msgLen);
	};

	static INT SequenceDifference(uint seq1, uint seq2);

	////////////////////////////////////////////////////////////////////////////////
	//
	//	Network Packet Message base Header
	//

	struct MobileMessageHeader : public MessageHeader
	{
		// Mobile peer ID
		uint64_t		PeerID;
	};


#pragma pack(pop)


#include "SFMessage.inl"

} // Message
} // SF




