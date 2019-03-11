////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2013 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Time Utility library
//	
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "SFTypedefs.h"
#include "Object/SFLibraryComponent.h"
#include "Thread/SFThread.h"
#include "Service/SFService.h"

namespace SF {
	namespace Util {




		////////////////////////////////////////////////////////////////////////////////
		//
		//	Win32 timer class
		//

		class Time_Chrono
		{
		public:
			const int UTC_REFERENCE_YEAR = 2014;

		private:

			std::chrono::time_point<ClockType> m_TickStamp;

			// Time stamp
			std::atomic<uint64_t>			m_ullTimeStamp;

			ClockType::duration				m_ullTimeStampPrevious;
			std::atomic<TimeStampMS>		m_ulTimeStampMs;
			std::atomic<TimeStampSec>		m_ullTimeStampUTC;

			// Default UTC offset
			uint64_t					m_ullUTCOffset;

			// Time correction over network
			uint64_t					m_UTCPeerOffset = 0;
			uint64_t					m_UTCPeerTickOffset = 0;

		protected:
			// Update Time stamp
			void		UpdateTimer();

			friend class LibraryComponentTime;

		public:
			Time_Chrono();
			~Time_Chrono();


			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// Time query
			//

			// Get time stamp in ms
			TimeStampMS		GetTimeMs();

			// Get UTC time stamp
			TimeStampSec	GetTimeUTCSec();



			/////////////////////////////////////////////////////////////////////////////////////////////////////
			//
			// Global Time query
			//

			// Get time tick in ms
			TimeStampMS		GetRawTimeMs();

			// Get current UTC sec
			TimeStampSec	GetRawUTCSec();

			DurationSec		GetUTCSecOffset() { return DurationSec(m_ullUTCOffset); }
			uint64_t		GetUTCSecPeerOffset() { return m_UTCPeerOffset; }

			uint64_t		GetUTCTickPeerOffset() { return m_UTCPeerTickOffset; }

			

			void			UpdateUTCPeerOffset(TimeStampSec expectedTime);
			void            UpdateUTCPeerTickOffset(TimeStampSec expectedTime);

		};


		// Global main timer
		extern Time_Chrono Time;


		////////////////////////////////////////////////////////////////////////////////
		//
		//	Timer
		//

		class TimeStampTimer
		{
		public:
			const static TimeStampMS	InvalidTime;

		private:
			TimeStampMS	m_ulTimeToExpire;
			TimeStampMS	m_ulTimeToExpirePrev;

			// Timer expire caller
			std::function<void()> m_delOnExpired;

		public:
			inline TimeStampTimer();
			inline ~TimeStampTimer();


			// Set timer delegate
			inline  void	SetTimerFunc(std::function<void()> funcOnExpired);

			// set timer
			Result	SetTimer(DurationMS TimerDuration);

			// clear timer
			inline void	ClearTimer();

			TimeStampMS	GetTimerExpireTime() { return m_ulTimeToExpire; }

			// check about timer is working
			inline bool	IsTimerWorking() const;

			// Timer check update
			bool	CheckTimer();
		};


		////////////////////////////////////////////////////////////////////////////////
		//
		//	Module
		//

		class LibraryComponentTime : public LibraryComponent
		{
		public:
			static constexpr FixedString TypeName = "LibraryComponentTime";

		private:

			FunctorThread m_Thread;

		public:

			LibraryComponentTime();
			~LibraryComponentTime();

			virtual const FixedString& GetTypeName() override { return TypeName; }

			// Initialize server component
			virtual Result InitializeComponent() override;
			// Terminate server component
			virtual void DeinitializeComponent() override;

		};




		////////////////////////////////////////////////////////////////////////////////
		//
		//	Utility
		//



		DurationMS TimeMinNonZero(DurationMS timeMs, DurationMS timeMs2);
		TimeStampMS TimeMinNonZero(TimeStampMS timeMs, TimeStampMS timeMs2);


		inline DurationMS TimeSinceRaw(TimeStampMS timeMs) { auto timeCur = Time.GetRawTimeMs(); return (timeCur > timeMs) ? (timeCur - timeMs) : DurationMS(0); }
		inline DurationMS TimeSince(TimeStampMS timeMs) { auto timeCur = Time.GetTimeMs(); return (timeCur > timeMs) ? (timeCur - timeMs) : DurationMS(0); }
		inline DurationSec TimeSinceUTC(TimeStampSec timeUTC) { auto timeCur = Time.GetTimeUTCSec(); return (timeCur > timeUTC) ? (timeCur - timeUTC) : DurationSec(0); }



	} // namespace Util
} // namespace SF

#include "SFTimeUtil.inl"

