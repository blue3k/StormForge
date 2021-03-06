////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Net connection action. 
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Net/SFNetDef.h"
#include "Net/SFNetCtrl.h"
#include "Net/SFNetUtil.h"
#include "Net/SFConnectionAction.h"
#include "ResultCode/SFResultCodeEngine.h"



namespace SF {
namespace Net {


	class Connection;


	////////////////////////////////////////////////////////////////////////////////
	//
	//	net control connection Action
	//



	class ConnectionMessageAction_UDPHandleAck : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_HandleAck : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_UDPHandleNack : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_HandleNack : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_HandleHeartbeat : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_HandleTimeSync : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_HandleTimeSyncRtn : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_MUDPHandleSyncReliableServer : public ConnectionMessageActionMUDP
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_MUDPHandleSyncReliableClient : public ConnectionMessageActionMUDP
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};



	class ConnectionMessageAction_UDPHandleConnect : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};

	class ConnectionMessageAction_HandleConnect : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};


	class ConnectionMessageAction_HandleDisconnect : public ConnectionMessageAction
	{
	public:
		virtual Result Run(const Message::MessageHeader* netCtrlMsg) override;
	};



	////////////////////////////////////////////////////////////////////////////////
	//
	//	connection state Action
	//

	class ConnectionStateAction_DisposeOnExpire : public ConnectionAction
	{
	private:
		TimeStampMS m_Start;

	public:

		void Start() { m_Start = Util::Time.GetTimeMs(); }

		virtual Result Run() override;
	};

	class ConnectionStateAction_TimeoutConnecting : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendConnect : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};


	class ConnectionStateAction_TimeoutHeartbeat : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendHeartbeat : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_StateTimeout : public ConnectionAction
	{
	private:

		TimeStampMS m_StartTimeStamp = TimeStampMS(DurationMS(0));
		DurationMS m_Timeout = DurationMS(60 * 1000); // default 60s timeout

	public:

		void SetTimeout(DurationMS timeout) { m_Timeout = timeout; }

	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_TimeoutDisconnecting : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendDisconnect : public ConnectionAction
	{
	public:
		virtual Result Run() override;
	};


	class ConnectionStateAction_SendSync : public ConnectionActionMUDP
	{
	private:

		TimeStampMS m_ReliableSyncTime = TimeStampMS(DurationMS_Zero);

	public:
		virtual Result Run() override;
	};


	class ConnectionStateAction_SendSyncSvr : public ConnectionActionMUDP
	{
	private:

		TimeStampMS m_ReliableSyncTime = TimeStampMS(DurationMS_Zero);

	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendReliableQueue : public ConnectionActionUDP
	{
	public:
		virtual Result Run() override;
	};

	class ConnectionStateAction_SendReliableRetry : public ConnectionActionUDP
	{
	public:
		virtual Result Run() override;
	};
/*
	class ConnectionStateAction_UpdateRecvReliable : public ConnectionActionMUDP
	{
	public:
		virtual Result Run() override;
	};
*/

}  // namespace Net
} // namespace SF



