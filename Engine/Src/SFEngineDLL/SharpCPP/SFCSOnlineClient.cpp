////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEngineDLLPCH.h"

#include "SFAssert.h"
#include "Util/SFUtility.h"

#include "Util/SFLog.h"
#include "Object/SFObject.h"
#include "Service/SFEngineService.h"
#include "Net/SFConnection.h"
#include "Net/SFMessage.h"
#include "Protocol/SFProtocol.h"
#include "Online/SFOnlineClient.h"
#include "Actor/Movement/SFActorMovement.h"
#include "Actor/Movement/SFActorMovementManager.h"
#include "SFCSUtil.h"


namespace SF
{
	typedef void(*ONLINE_STATECHANGED_CALLBACK)(OnlineClient::OnlineState prevState, OnlineClient::OnlineState newState);

}

using namespace SF;





//////////////////////////////////////////////////////////////////////////////////////
//
//	Connection interface
//

SFDLL_EXPORT intptr_t SFOnlineClient_NativeCreateOnlineClient()
{
	auto pOnlineClient = NewObject<OnlineClient>(GetEngineHeap());
	Service::EngineObjectManager->AddToDetainedRelease(pOnlineClient.StaticCast<SharedObject>());

	return NativeObjectToIntptr(pOnlineClient.get());
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeStartConnection(intptr_t nativeHandle, uint64_t transactionId, const char* gameId, const char* loginAddress, const char* userId, const char* password)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (int32_t)pOnlineClient->StartConnection(transactionId, gameId, loginAddress, userId, password);
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeJoinGameInstance(intptr_t nativeHandle, uint64_t transactionId, uint64_t gameInstanceUID)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (int32_t)pOnlineClient->JoinGameInstance(transactionId, gameInstanceUID);
}

SFDLL_EXPORT void SFOnlineClient_NativeDisconnectAll(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	pOnlineClient->DisconnectAll();
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeGetOnlineState(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return int32_t(pOnlineClient->GetOnlineState());
}

SFDLL_EXPORT uint64_t SFOnlineClient_NativeGetPlayerId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetPlayerID();
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetCharacterId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetCharacterId();
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetGameId(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return (uint32_t)(pOnlineClient->GetGameId());
}

SFDLL_EXPORT uint64_t SFOnlineClient_NativeGetGameInstanceUID(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return uint64_t(pOnlineClient->GetGameInstanceUID());
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeUpdateGameTick(intptr_t nativeHandle, 
	ONLINE_STATECHANGED_CALLBACK stateChangedCallback, 
	SET_EVENT_FUNCTION setEventFunc, 
	SET_MESSAGE_FUNCTION setMessageFunc, VariableMapBuilderCS::SET_FUNCTION setValueFunc, VariableMapBuilderCS::SET_ARRAY_FUNCTION setArrayValueFunc, ON_READY_FUNCTION onMessageReady, 
	OnlineClient::ONLINE_TASK_FINISHED_CALLBACK onTaskFinished)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;


	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);


	auto eventHandler = [setEventFunc](Net::Connection* pConn, const Net::ConnectionEvent& evt)
	{
		setEventFunc(evt.Components.EventType, evt.Components.hr, evt.Components.State);
	};

	auto messageHandler = [setMessageFunc, setValueFunc, setArrayValueFunc, onMessageReady](Net::Connection* pConn, const SharedPointerT<Message::MessageData>& pMsgData)
	{
		setMessageFunc(pMsgData->GetMessageHeader()->msgID.IDSeq.MsgID);

		VariableMapBuilderCS builder(setValueFunc, setArrayValueFunc);
		SF::Protocol::ParseMessage(pMsgData, builder);

		onMessageReady();
	};


	if (pOnlineClient->GetConnectionLogin() != nullptr)
	{
		pOnlineClient->GetConnectionLogin()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionLogin()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

	if (pOnlineClient->GetConnectionGame() != nullptr)
	{
		pOnlineClient->GetConnectionGame()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionGame()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

	if (pOnlineClient->GetConnectionGameInstance() != nullptr)
	{
		pOnlineClient->GetConnectionGameInstance()->GetConnectionEventDelegates().AddDelegateUnique(1, eventHandler);
		pOnlineClient->GetConnectionGameInstance()->GetRecvMessageDelegates().AddDelegateUnique(1, messageHandler);
	}

	pOnlineClient->SetStateChangeCallback(stateChangedCallback);
	pOnlineClient->SetTaskFinishedCallback(onTaskFinished);

	pOnlineClient->UpdateGameTick();


	if (pOnlineClient->GetConnectionLogin() != nullptr)
	{
		pOnlineClient->GetConnectionLogin()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionLogin()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

	if (pOnlineClient->GetConnectionGame() != nullptr)
	{
		pOnlineClient->GetConnectionGame()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionGame()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

	if (pOnlineClient->GetConnectionGameInstance() != nullptr)
	{
		pOnlineClient->GetConnectionGameInstance()->GetConnectionEventDelegates().RemoveDelegateAll(1);
		pOnlineClient->GetConnectionGameInstance()->GetRecvMessageDelegates().RemoveDelegateAll(1);
	}

	pOnlineClient->SetStateChangeCallback(nullptr);
	pOnlineClient->SetTaskFinishedCallback(nullptr);

	return ResultCode::SUCCESS;

}

SFDLL_EXPORT int32_t SFOnlineClient_NativeUpdateMovement(intptr_t nativeHandle, uint32_t& outDeltaFrames)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	outDeltaFrames = pOnlineClient->UpdateMovement();

	return ResultCode::SUCCESS;
}

SFDLL_EXPORT uint64_t SFOnlineClient_NativeGetConnection(intptr_t nativeHandle, int32_t connectionIndex)
{
	if (nativeHandle == 0)
		return 0;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	switch (connectionIndex)
	{
	case 0:
		return NativeObjectToIntptr(pOnlineClient->GetConnectionLogin().get());
		break;
	case 1:
		return NativeObjectToIntptr(pOnlineClient->GetConnectionGame().get());
		break;
	case 2:
		return NativeObjectToIntptr(pOnlineClient->GetConnectionGameInstance().get());
		break;
	default:
		break;
	}

	return 0;
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeGetMovementForPlayer(intptr_t nativeHandle, uint64_t playerId, SF::ActorMovement& actorMovement)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return int32_t(pOnlineClient->GetMovementForPlayer(playerId, actorMovement));
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeGetMovementForPlayerAll(intptr_t nativeHandle, uint64_t playerId, SF::ActorMovement& actorMovement, SF::ActorMovement& actorReceivedMovement, SF::ActorMovement& actorExpectedMovement)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return int32_t(pOnlineClient->GetMovementForPlayerAll(playerId, actorMovement, actorReceivedMovement, actorExpectedMovement));
}

SFDLL_EXPORT uint32_t SFOnlineClient_NativeGetCurrentMoveFrame(intptr_t nativeHandle)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	return pOnlineClient->GetCurrentMovementFrame();
}

SFDLL_EXPORT int32_t SFOnlineClient_NativeSendMovement(intptr_t nativeHandle, const ActorMovement& newMove)
{
	if (nativeHandle == 0)
		return ResultCode::NOT_INITIALIZED;

	auto pOnlineClient = NativeToObject<OnlineClient>(nativeHandle);

	if (pOnlineClient->GetSendMovementManager() == nullptr)
		return ResultCode::INVALID_STATE;

	// ActorMovement requires special memory alignment, copy incoming data to local storage
	ActorMovement tempMove = newMove;

	return int32_t(pOnlineClient->SendMovement(tempMove));
}

