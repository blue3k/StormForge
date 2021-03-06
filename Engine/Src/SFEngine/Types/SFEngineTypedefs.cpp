////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Engine type defines
//	
//
////////////////////////////////////////////////////////////////////////////////


#include "SFEnginePCH.h"
#include "SFAssert.h"
#include "Util/SFStrUtil.h"
#include "ResultCode/SFResultCodeSystem.h"





namespace SF {


#define __CLUSTERID_NAMES__ \
	"None",\
	"ClusterManager",\
	"Monitoring",\
	"PlayerManager",\
	"Login",\
	"Game",\
	"GameStaticInstanceManager",\
	"GameInstanceManager",\
	"GamePartyManager",\
	"Ranking",\
	"ChatChannelManager",\
	"CharacterData",\
	"LoginPlayer",\
	"GamePlayer",\
	"GameInstance",\
	"PurchaseValidateGoogle",\
	"PurchaseValidateIOS",\
	"Matching_Game_4",\
	"Matching_Game_8",\
	"MatchingQueue_Game_4x1",\
	"MatchingQueue_Game_4x2",\
	"MatchingQueue_Game_4x3",\
	"MatchingQueue_Game_4x1S",\
	"MatchingQueue_Game_4x1W",\
	"MatchingQueue_Game_8x1",\
	"MatchingQueue_Game_8x2",\
	"MatchingQueue_Game_8x3",\
	"MatchingQueue_Game_8x4",\
	"MatchingQueue_Game_8x5",\
	"MatchingQueue_Game_8x6",\
	"MatchingQueue_Game_8x7",\
	"MatchingQueue_Game_8x1S",\
	"MatchingQueue_Game_8x1W",\
	"Relay",\
	"Max",\



	static constexpr const char* __ClusterID_NameList[] =
	{
		__CLUSTERID_NAMES__
	};

	static constexpr StringCrc64 __ClusterID_NameCrcList[] =
	{
		__CLUSTERID_NAMES__
	};

	const char* ToString(ClusterID clusterId)
	{
		return __ClusterID_NameList[(int)clusterId];
	}

	StringCrc64 ToStringCrc64(ClusterID clusterId)
	{
		return __ClusterID_NameCrcList[(int)clusterId];
	}

	/////////////////////////////////////////////////////////////////////
	//
	//	Type utility
	//

	//GameInstanceInfo::GameInstanceInfo(const GameInstanceInfo& src)
	//	: GameInstanceUID(src.GameInstanceUID)
	//	, TypeName(src.TypeName)
	//	, ZoneTableID(src.ZoneTableID)
	//{
	//}

	//GameInstanceInfo::GameInstanceInfo(GameInsUID InGameInstanceUID, StringCrc32 InTypeName, uint32_t InZoneTableID)
	//	: GameInstanceUID(InGameInstanceUID)
	//	, TypeName(InTypeName)
	//	, ZoneTableID(InZoneTableID)
	//{
	//}

	//GameInstanceInfo& GameInstanceInfo::operator = (const GameInstanceInfo& src)
	//{
	//	GameInstanceUID = src.GameInstanceUID;
	//	TypeName = src.TypeName;
	//	ZoneTableID = src.ZoneTableID;

	//	return *this;
	//}

	//bool GameInstanceInfo::operator == (const GameInstanceInfo& src) const
	//{
	//	return GameInstanceUID == src.GameInstanceUID
	//		&& TypeName == src.TypeName
	//		&& ZoneTableID == src.ZoneTableID;
	//}



	////////////////////////////////////////////////////////////////////////////////////
	//
	//	Player informations
	//

	PlayerInformation::PlayerInformation(const PlayerInformation& src)
	{
		(*this) = src;
	}

	PlayerInformation& PlayerInformation::operator = (const PlayerInformation& src)
	{
		this->PlayerID = src.PlayerID;
		this->FBUID = src.FBUID;
		Level = src.Level;
		IsPlayingGame = src.IsPlayingGame;
		LastActiveTime = src.LastActiveTime;

		StrUtil::StringCopy(NickName, src.NickName);

		return *this;
	}

	PlayerInformation::PlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime)
	{
		InitPlayerInformation(playerID, fbUID, nickName, level, isPlayingGame, lastActiveTime);
	}

	Result PlayerInformation::InitPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint8_t isPlayingGame, uint64_t lastActiveTime)
	{
		if (nickName == nullptr)
			return ResultCode::INVALID_ARG;

		this->PlayerID = playerID;
		this->FBUID = fbUID;
		Level = level;
		IsPlayingGame = isPlayingGame;
		LastActiveTime = lastActiveTime;

		return StrUtil::StringCopy(NickName, nickName);
	}


	bool PlayerInformation::operator == (const PlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}




	RankingPlayerInformation::RankingPlayerInformation()
		:WeeklyWin(0)
		, WeeklyLose(0)
	{
	}

	RankingPlayerInformation::RankingPlayerInformation(const RankingPlayerInformation& src)
		: PlayerInformation(src)
	{
		WeeklyWin = src.WeeklyWin;
		WeeklyLose = src.WeeklyLose;
	}

	RankingPlayerInformation::RankingPlayerInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime)
		:PlayerInformation(playerID, fbUID, nickName, level, isPlayingGame, lastActiveTime)
	{
		WeeklyWin = weeklyWin;
		WeeklyLose = weeklyLose;
	}

	RankingPlayerInformation& RankingPlayerInformation::operator = (const RankingPlayerInformation& src)
	{
		*(PlayerInformation*)this = src;
		//InitPlayerInformation(src.PlayerID, src.FBUID, src.NickName, src.Level, src.IsPlayingGame, src.LastActiveTime);
		WeeklyWin = src.WeeklyWin;
		WeeklyLose = src.WeeklyLose;
		return *this;
	}

	bool RankingPlayerInformation::operator == (const RankingPlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}




	FriendInformation::FriendInformation()
		:LastStaminaSent(0)
	{
	}

	FriendInformation::FriendInformation(const FriendInformation& src)
		: RankingPlayerInformation(src)
	{
		LastStaminaSent = src.LastStaminaSent;
	}

	FriendInformation::FriendInformation(AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint weeklyWin, uint weeklyLose, uint8_t isPlayingGame, uint64_t lastActiveTime, uint64_t lastStaminaSent)
		: RankingPlayerInformation(playerID, fbUID, nickName, level, weeklyWin, weeklyLose, isPlayingGame, lastActiveTime)
	{
		LastStaminaSent = lastStaminaSent;
	}

	FriendInformation& FriendInformation::operator = (const FriendInformation& src)
	{
		//InitPlayerInformation(src.PlayerID, src.FBUID, src.NickName, src.Level, src.weeklyWin, src.weeklyLose, src.IsPlayingGame, src.LastActiveTime);
		*(RankingPlayerInformation*)this = src;
		LastStaminaSent = src.LastStaminaSent;
		return *this;
	}

	bool FriendInformation::operator == (const FriendInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}





	TotalRankingPlayerInformation::TotalRankingPlayerInformation()
	{
		memset(this, 0, sizeof(TotalRankingPlayerInformation));
	}

	TotalRankingPlayerInformation::TotalRankingPlayerInformation(const TotalRankingPlayerInformation& src)
	{
		(*this) = src;
	}

	TotalRankingPlayerInformation& TotalRankingPlayerInformation::operator = (const TotalRankingPlayerInformation& src)
	{
		RankingID = src.RankingID;
		Ranking = src.Ranking;
		this->PlayerID = src.PlayerID;
		this->FBUID = src.FBUID;
		Level = src.Level;
		ScoreLow = src.ScoreLow;
		ScoreHigh = src.ScoreHigh;

		StrUtil::StringCopy(NickName, src.NickName);

		return *this;
	}

	TotalRankingPlayerInformation::TotalRankingPlayerInformation(uint32_t rankingID, uint32_t ranking, AccountID playerID, FacebookUID fbUID, const char* nickName, uint level, uint scoreLow, uint scoreHigh)
	{
		//if( nickName == nullptr ) 
		//	return ResultCode::INVALID_ARG;

		RankingID = rankingID;
		Ranking = ranking;
		this->PlayerID = playerID;
		this->FBUID = fbUID;
		Level = level;
		ScoreLow = scoreLow;
		ScoreHigh = scoreHigh;

		StrUtil::StringCopy(NickName, nickName);
	}

	bool TotalRankingPlayerInformation::operator == (const TotalRankingPlayerInformation& src) const
	{
		if (PlayerID == src.PlayerID)
		{
			Assert(FBUID == src.FBUID);
			return true;
		}
		return false;
	}





} // namespace SF


