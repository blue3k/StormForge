﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) The Braves
// 
// Author : Generated
// 
// Description : Game Message debug definitions
// 
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Protocol/SFProtocol.h"
#include "Net/SFNetDef.h"



namespace SF
{
    class MessageEndpoint;
   class VariableTable;
   struct ActorMovement;


	class NetPolicyGame 
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetPolicyGame (const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// C2S: Client heartbeat
		Result HeartbeatC2SEvt(  );
		// Cmd: Player connected from a login server and moved to game server
		Result JoinGameServerCmd( const uint64_t &InTransactionID, const AccountID &InAccID, const AuthTicket &InTicket, const uint64_t &InLoginEntityUID );
		// Cmd: player complition statues
		Result GetComplitionStateCmd( const uint64_t &InTransactionID );
		// Cmd: Player complition state
		Result SetComplitionStateCmd( const uint64_t &InTransactionID, const char* InComplitionState );
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result RegisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID );
		// Cmd: Unregister Google notification service ID
		Result UnregisterGCMCmd( const uint64_t &InTransactionID, const char* InGCMRegisteredID );
		// Cmd: Invite friend
		Result InviteFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID );
		// Cmd: Accept friend request
		Result AcceptFriendRequestCmd( const uint64_t &InTransactionID, const AccountID &InInviterID, const FacebookUID &InInviterFacebookUID );
		// Cmd: Remove friden form the friend list
		Result RemoveFriendCmd( const uint64_t &InTransactionID, const AccountID &InFriendID );
		// Cmd: Get friend list
		Result GetFriendListCmd( const uint64_t &InTransactionID, const uint16_t &InStartIndex, const uint16_t &InCount );
		// Cmd: Query notification list
		Result GetNotificationListCmd( const uint64_t &InTransactionID );
		// Cmd: Delete notification
		Result DeleteNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: Set notification is read
		Result SetNotificationReadCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: Accept notification
		Result AcceptNotificationCmd( const uint64_t &InTransactionID, const uint32_t &InNotificationID );
		// Cmd: Query playerID list
		Result FindPlayerByEMailCmd( const uint64_t &InTransactionID, const char* InPlayerEMail );
		// Cmd: Query playerID list
		Result FindPlayerByPlayerIDCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID );
		// Cmd: *Request Player Status Update
		Result RequestPlayerStatusUpdateCmd( const uint64_t &InTransactionID, const Array<AccountID>& InTargetPlayerID );
		// Cmd: Get Ranking list
		Result GetRankingListCmd( const uint64_t &InTransactionID, const uint8_t &InRankingType, const uint8_t &InBaseRanking, const uint8_t &InCount );
		// Cmd: Game user game play information
		Result GetUserGamePlayerInfoCmd( const uint64_t &InTransactionID );
		// Cmd: Game game play information
		Result GetGamePlayerInfoCmd( const uint64_t &InTransactionID, const AccountID &InPlayerID );
		// Cmd: Change NickName
		Result SetNickNameCmd( const uint64_t &InTransactionID, const char* InNickName, const uint8_t &InIsCostFree );
		// Cmd: Create Party
		Result CreatePartyCmd( const uint64_t &InTransactionID );
		// Cmd: Join party
		Result JoinPartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InInviterID );
		// Cmd: Leave party command
		Result LeavePartyCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID );
		// Cmd: Kick player from the party
		Result PartyKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InPartyUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
		// Cmd: Invite a player to the party
		Result PartyInviteCmd( const uint64_t &InTransactionID, const AccountID &InInviteTargetID );
		// Cmd: Send Party quick chat message
		Result PartyQuickChatMessageCmd( const uint64_t &InTransactionID, const uint32_t &InQuickChatID );
		// Cmd: Party chatting
		Result PartyChatMessageCmd( const uint64_t &InTransactionID, const char* InChatMessage );
		// Cmd: Join to a game instance
		Result JoinGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID );
		// Cmd: Leave game instance
		Result LeaveGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InInsUID );
		// Cmd: Search game instance
		Result SearchGameInstanceCmd( const uint64_t &InTransactionID, const char* InSearchKeyword );
		// Cmd: Search game instance
		Result GetCharacterDataInGameInstanceCmd( const uint64_t &InTransactionID, const uint64_t &InGameInsUID, const PlayerID &InPlayerID );
		// Cmd: Request Game match
		Result RequestGameMatchCmd( const uint64_t &InTransactionID, const uint8_t &InNumPlayer, const uint8_t &InRequestRole );
		// Cmd: Cancel Game match
		Result CancelGameMatchCmd( const uint64_t &InTransactionID );
		// Cmd: Buy shop item prepare
		Result BuyShopItemPrepareCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID );
		// Cmd: Buy shop item
		Result BuyShopItemCmd( const uint64_t &InTransactionID, const uint32_t &InShopItemID, const char* InPlatform, const char* InPackageName, const char* InPurchaseTransactionID, const Array<uint8_t>& InPurchaseToken );
		// Cmd: Create or Join Chat channel
		Result CreateOrJoinChatChannelCmd( const uint64_t &InTransactionID, const char* InChannelName, const char* InPasscode );
		// Cmd: Join
		Result JoinChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InInviterID );
		// Cmd: Leave ChatChannel command
		Result LeaveChatChannelCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID );
		// Cmd: Kick player from the ChatChannel
		Result ChatChannelKickPlayerCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const AccountID &InPlayerID, const AccountID &InPlayerToKick );
		// Cmd: Party chatting
		Result ChatChannelChatMessageCmd( const uint64_t &InTransactionID, const uint64_t &InChatUID, const char* InChatMessage );
		// Cmd: Create character
		Result CreateCharacterCmd( const uint64_t &InTransactionID, const char* InCharacterName, const VariableTable &InVisualData, const VariableTable &InAttributes );
		// Cmd: Delete character
		Result DeleteCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID );
		// Cmd: Get character list
		Result GetCharacterListCmd( const uint64_t &InTransactionID );
		// Cmd: 
		Result GetCharacterDataCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID );
		// Cmd: Select character
		Result SelectCharacterCmd( const uint64_t &InTransactionID, const uint32_t &InCharacterID );
		// Cmd: To call general functionality
		Result CallFunctionCmd( const uint64_t &InTransactionID, const StringCrc32 &InFunctionName, const VariableTable &InParameters );

	}; // class NetPolicyGame 


	class NetSvrPolicyGame
	{
 		private:
			SharedPointerT<MessageEndpoint> m_Endpoint;
		public:
		// Constructor
		NetSvrPolicyGame ( const SharedPointerT<MessageEndpoint>& pEndpoint ) : m_Endpoint(pEndpoint)
		{}

		// Cmd: Player connected from a login server and moved to game server
		Result JoinGameServerRes( const uint64_t &InTransactionID, const Result &InResult, const char* InNickName, const uint64_t &InGameUID, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const MatchingQueueTicket &InMatchingTicket );
		// Cmd: player complition statues
		Result GetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult, const char* InComplitionState );
		// Cmd: Player complition state
		Result SetComplitionStateRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Register Google notification service ID, after this, the player will get notification from google. Only one notification ID can be active at a time
		Result RegisterGCMRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Unregister Google notification service ID
		Result UnregisterGCMRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Invite friend
		Result InviteFriendRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Accept friend request
		Result AcceptFriendRequestRes( const uint64_t &InTransactionID, const Result &InResult, const FriendInformation &InNewFriend );
		// S2C: Notification for friend request is accepted
		Result FriendRequestAcceptedS2CEvt( const FriendInformation &InAccepter );
		// Cmd: Remove friden form the friend list
		Result RemoveFriendRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InFriendID );
		// S2C: Friend removed
		Result FriendRemovedS2CEvt( const AccountID &InFriendID );
		// Cmd: Get friend list
		Result GetFriendListRes( const uint64_t &InTransactionID, const Result &InResult, const uint16_t &InMaxFriendSlot, const uint16_t &InTotalNumberOfFriends, const uint16_t &InStartIndex, const Array<FriendInformation>& InFriendList );
		// Cmd: Query notification list
		Result GetNotificationListRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Delete notification
		Result DeleteNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// Cmd: Set notification is read
		Result SetNotificationReadRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// Cmd: Accept notification
		Result AcceptNotificationRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InNotificationID );
		// S2C: Notify new notification
		Result NotifyS2CEvt( const uint32_t &InNotificationID, const uint32_t &InNotificationType, const uint64_t &InMessageParam0, const uint64_t &InMessageParam1, const char* InMessageText, const uint8_t &InIsRead, const uint64_t &InTimeStamp );
		// Cmd: Query playerID list
		Result FindPlayerByEMailRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
		// Cmd: Query playerID list
		Result FindPlayerByPlayerIDRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerInformation &InPlayer );
		// Cmd: *Request Player Status Update
		Result RequestPlayerStatusUpdateRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: *Notify Player Status Updated
		Result NotifyPlayerStatusUpdatedS2CEvt( const AccountID &InPlayerID, const uint32_t &InLatestActiveTime, const uint8_t &InIsInGame );
		// Cmd: Get Ranking list
		Result GetRankingListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<TotalRankingPlayerInformation>& InRanking );
		// Cmd: Game user game play information
		Result GetUserGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes );
		// Cmd: Game game play information
		Result GetGamePlayerInfoRes( const uint64_t &InTransactionID, const Result &InResult, const AccountID &InPlayerID, const VariableTable &InAttributes );
		// S2C: Player level up event
		Result LevelUpS2CEvt( const uint64_t &InCurrentTotalExp, const uint32_t &InCurrentLevel );
		// Cmd: Change NickName
		Result SetNickNameRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// Cmd: Create Party
		Result CreatePartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID );
		// Cmd: Join party
		Result JoinPartyRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID, const Array<uint8_t>& InChatHistoryData );
		// S2C: Player Joined event
		Result PartyPlayerJoinedS2CEvt( const uint64_t &InPartyUID, const PlayerInformation &InJoinedPlayer );
		// S2C: Party leader changed event
		Result PartyLeaderChangedS2CEvt( const uint64_t &InPartyUID, const AccountID &InNewLeaderID );
		// Cmd: Leave party command
		Result LeavePartyRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Party Player left event
		Result PartyPlayerLeftS2CEvt( const uint64_t &InPartyUID, const AccountID &InLeftPlayerID );
		// Cmd: Kick player from the party
		Result PartyKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Party Player kicked message
		Result PartyPlayerKickedS2CEvt( const uint64_t &InPartyUID, const AccountID &InKickedPlayerID );
		// Cmd: Invite a player to the party
		Result PartyInviteRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Party invite requested
		Result PartyInviteRequestedS2CEvt( const AccountID &InInviterID, const char* InInviterName, const uint64_t &InPartyToJoinUID );
		// Cmd: Send Party quick chat message
		Result PartyQuickChatMessageRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Party Chatting message event
		Result PartyQuickChatMessageS2CEvt( const AccountID &InSenderID, const uint32_t &InQuickChatID );
		// Cmd: Party chatting
		Result PartyChatMessageRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: Party Chatting message event
		Result PartyChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage );
		// Cmd: Join to a game instance
		Result JoinGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InInsUID, const NetAddress &InServerAddress4, const NetAddress &InServerAddress6 );
		// Cmd: Leave game instance
		Result LeaveGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Search game instance
		Result SearchGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InGameInstances );
		// Cmd: Search game instance
		Result GetCharacterDataInGameInstanceRes( const uint64_t &InTransactionID, const Result &InResult, const PlayerID &InPlayerID, const VariableTable &InGameInstances );
		// Cmd: Request Game match
		Result RequestGameMatchRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// S2C: Game matched
		Result GameMatchedS2CEvt( const uint64_t &InInsUID, const uint32_t &InTimeStamp, const uint8_t &InGameState, const uint8_t &InDay, const uint8_t &InMaxPlayer, const uint8_t &InPlayerIndex, const uint8_t &InPlayerCharacter, const uint8_t &InRole, const uint8_t &InDead, const Array<uint8_t>& InChatHistoryData, const Array<uint8_t>& InGameLogData, const uint32_t &InStamina, const uint64_t &InTotalGem, const uint64_t &InTotalGameMoney );
		// S2C: Game match failed
		Result GameMatchFailedS2CEvt( const Result &InFailedReason );
		// S2C: Game matching started
		Result GameMatchingStartedS2CEvt(  );
		// Cmd: Cancel Game match
		Result CancelGameMatchRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: game matching canceled
		Result GameMatchingCanceledS2CEvt(  );
		// Cmd: Buy shop item prepare
		Result BuyShopItemPrepareRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID, const char* InPurchaseID );
		// Cmd: Buy shop item
		Result BuyShopItemRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InShopItemID );
		// Cmd: Create or Join Chat channel
		Result CreateOrJoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InChatUID );
		// Cmd: Join
		Result JoinChatChannelRes( const uint64_t &InTransactionID, const Result &InResult, const uint64_t &InPartyUID, const AccountID &InPartyLeaderID );
		// S2C: Player Joined event
		Result ChatChannelPlayerJoinedS2CEvt( const uint64_t &InChatUID, const PlayerInformation &InJoinedPlayer );
		// S2C: ChatChannel leader changed event
		Result ChatChannelLeaderChangedS2CEvt( const uint64_t &InChatUID, const AccountID &InNewLeaderID );
		// Cmd: Leave ChatChannel command
		Result LeaveChatChannelRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Player left event
		Result ChatChannelPlayerLeftS2CEvt( const uint64_t &InChatUID, const AccountID &InLeftPlayerID );
		// Cmd: Kick player from the ChatChannel
		Result ChatChannelKickPlayerRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Player kicked message
		Result ChatChannelPlayerKickedS2CEvt( const uint64_t &InChatUID, const AccountID &InKickedPlayerID );
		// Cmd: Party chatting
		Result ChatChannelChatMessageRes( const uint64_t &InTransactionID, const Result &InResult );
		// S2C: ChatChannel Chatting message event
		Result ChatChannelChatMessageS2CEvt( const AccountID &InSenderID, const char* InSenderName, const char* InChatMessage );
		// Cmd: Create character
		Result CreateCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID );
		// Cmd: Delete character
		Result DeleteCharacterRes( const uint64_t &InTransactionID, const Result &InResult );
		// Cmd: Get character list
		Result GetCharacterListRes( const uint64_t &InTransactionID, const Result &InResult, const Array<VariableTable>& InCharacters );
		// Cmd: 
		Result GetCharacterDataRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InAttributes );
		// Cmd: Select character
		Result SelectCharacterRes( const uint64_t &InTransactionID, const Result &InResult, const uint32_t &InCharacterID, const VariableTable &InAttributes );
		// Cmd: To call general functionality
		Result CallFunctionRes( const uint64_t &InTransactionID, const Result &InResult, const VariableTable &InResults );

	}; // class NetSvrPolicyGame


}; // namespace SF


