﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 StromForge
// 
// Author : Generated
// 
// Description : PlayInstance Network Adapter
// 
////////////////////////////////////////////////////////////////////////////////


using System;
using System.Diagnostics;
using System.Runtime.InteropServices;
using SF;



namespace SF.Net
{
 

	public class SendMessagePlayInstance
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessagePlayInstance( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessagePlayInstance( SF.SFConnection connection )

		// Cmd: Event for Player Join request.
		public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID,System.Text.Encoding.UTF8.GetBytes(InPlayerIdentifier + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.JoinGameInstanceCmd);
			return result;
		} // public int  JoinGameInstanceCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.String InPlayerIdentifier )

		// C2S: Play packet
		public int  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InSenderEndpointID, InTargetEndpointMask,(ushort)InPayload.Length, InPayload);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayPacketC2SEvt);
			return result;
		} // public int  PlayPacketC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.Byte[] InPayload )


		// C2S: Player Movement
		public int  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InMovement);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerMovementC2SEvt);
			return result;
		} // public int  PlayerMovementC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )


		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public int  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			int result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.ClientSyncReliableC2SEvt);
			return result;
		} // public int  ClientSyncReliableC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		public int  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )
		{
 			int result;
			var InSyncData_ = InSyncData.ToByteArray();
			using (var InSyncData_PinnedPtr_ = new PinnedByteBuffer(InSyncData_))
			{
			result = CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InSyncData_.Length, InSyncData_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.ClientSyncC2SEvt);
			return result;
		} // public int  ClientSyncC2SEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InSyncData )


		// Cmd: Occupy map object
		public int  OccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId, InUsageId);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.OccupyMapObjectCmd);
			return result;
		} // public int  OccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId )

		// Cmd: Unoccupy map object
		public int  UnoccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.UnoccupyMapObjectCmd);
			return result;
		} // public int  UnoccupyMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )

		// Cmd: Use map object
		public int  UseMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters )
		{
 			int result;
			var InUseParameters_ = InUseParameters.ToByteArray();
			using (var InUseParameters_PinnedPtr_ = new PinnedByteBuffer(InUseParameters_))
			{
			result = CSSFNetAdapter_PlayInstanceUseMapObjectCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InUseParameters_.Length, InUseParameters_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.UseMapObjectCmd);
			return result;
		} // public int  UseMapObjectCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InUseParameters )

		// Cmd: Havest area
		public int  HarvestAreaCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceHarvestAreaCmd(m_Connection.NativeHandle, InTransactionID, InPlayInstanceUID, InPlayerID, InAreaId);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.HarvestAreaCmd);
			return result;
		} // public int  HarvestAreaCmd( System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId )

		// Cmd: Create stream instance
		public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamCmd);
			return result;
		} // public int  CreateStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Open stream instance
		public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.FindStreamCmd);
			return result;
		} // public int  FindStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Delete stream instance
		public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamCmd(m_Connection.NativeHandle, InTransactionID, InTicket,System.Text.Encoding.UTF8.GetBytes(InStreamName + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamCmd);
			return result;
		} // public int  DeleteStreamCmd( System.UInt64 InTransactionID, System.UInt64 InTicket, System.String InStreamName )

		// Cmd: Get stream list
		public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListCmd(m_Connection.NativeHandle, InTransactionID, InTicket);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListCmd);
			return result;
		} // public int  GetStreamListCmd( System.UInt64 InTransactionID, System.UInt64 InTicket )

		// Cmd: To call general functionality
		public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters )
		{
 			int result;
			var InParameters_ = InParameters.ToByteArray();
			using (var InParameters_PinnedPtr_ = new PinnedByteBuffer(InParameters_))
			{
			result = CSSFNetAdapter_PlayInstanceCallFunctionCmd(m_Connection.NativeHandle, InTransactionID, InFunctionName,(ushort)InParameters_.Length, InParameters_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CallFunctionCmd);
			return result;
		} // public int  CallFunctionCmd( System.UInt64 InTransactionID, System.UInt32 InFunctionName, SF.VariableTable InParameters )

		#region Native Interfaces 
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinGameInstanceCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, [MarshalAs(UnmanagedType.LPArray)] byte[] InPlayerIdentifier );


		// C2S: Play packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayPacketC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayPacketC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt32 InSenderEndpointID, System.UInt32 InTargetEndpointMask, System.UInt16 _sizeOfInPayload,System.Byte[] InPayload );



		// C2S: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.ActorMovement InMovement );



		// C2S: Repliable player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncReliableC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// C2S: Player Sync packet. We shares packet for C2S and S2C, meaning other clients will receive same packet
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceClientSyncC2SEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceClientSyncC2SEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInSyncData,IntPtr InSyncData );



		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt32 InUsageId );


		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );


		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInUseParameters,IntPtr InUseParameters );


		// Cmd: Havest area
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceHarvestAreaCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceHarvestAreaCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId );


		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamName );


		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt64 InTicket );


		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionCmd", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionCmd(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.UInt32 InFunctionName, System.UInt16 _sizeOfInParameters,IntPtr InParameters );


		#endregion //Native Interfaces 
	}; // public class SendMessagePlayInstance
	public class SendMessageSvrPlayInstance
	{
 
		const string NativeDLLName = 
		#if UNITY_IOS
		    "__Internal";
		#else
		    "SFEngineDLL";
		#endif
		SF.SFConnection m_Connection;


		public  SendMessageSvrPlayInstance( SF.SFConnection connection )
		{
 			m_Connection = connection;
		} // public  SendMessageSvrPlayInstance( SF.SFConnection connection )

		// Cmd: Event for Player Join request.
		public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceJoinGameInstanceRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID,ref InMovement);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.JoinGameInstanceRes);
			return result;
		} // public int  JoinGameInstanceRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )


		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		public int  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InKickedPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerKickedS2CEvt);
			return result;
		} // public int  PlayerKickedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID )


		// S2C: New Player in get view
		public int  NewPlayerInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes, SF.ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )
		{
 			int result;
			var InAttributes_ = InAttributes.ToByteArray();
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InAttributes_PinnedPtr_ = new PinnedByteBuffer(InAttributes_))
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,(ushort)InAttributes_.Length, InAttributes_PinnedPtr_.Ptr,ref InMovement, InState,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.NewPlayerInViewS2CEvt);
			return result;
		} // public int  NewPlayerInViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.VariableTable InAttributes, SF.ActorMovement InMovement, System.UInt32 InState, SF.VariableTable InStateValues )


		// S2C: Remove player from view
		public int  RemovePlayerFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.RemovePlayerFromViewS2CEvt);
			return result;
		} // public int  RemovePlayerFromViewS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID )


		// S2C: Player Movement
		public int  PlayerMovementS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID,ref InMovement);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerMovementS2CEvt);
			return result;
		} // public int  PlayerMovementS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, SF.ActorMovement InMovement )


		// S2C: Player state change
		public int  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )
		{
 			int result;
			var InStateValues_ = InStateValues.ToByteArray();
			using (var InStateValues_PinnedPtr_ = new PinnedByteBuffer(InStateValues_))
			{
			result = CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(m_Connection.NativeHandle, InPlayInstanceUID, InPlayerID, InState, InMoveFrame,ref InPosition,(ushort)InStateValues_.Length, InStateValues_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.PlayerStateChangedS2CEvt);
			return result;
		} // public int  PlayerStateChangedS2CEvt( System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, SF.Vector4 InPosition, SF.VariableTable InStateValues )


		// Cmd: Occupy map object
		public int  OccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.OccupyMapObjectRes);
			return result;
		} // public int  OccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Unoccupy map object
		public int  UnoccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.UnoccupyMapObjectRes);
			return result;
		} // public int  UnoccupyMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId )


		// Cmd: Use map object
		public int  UseMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )
		{
 			int result;
			var InResultAttributes_ = InResultAttributes.ToByteArray();
			using (var InResultAttributes_PinnedPtr_ = new PinnedByteBuffer(InResultAttributes_))
			{
			result = CSSFNetAdapter_PlayInstanceUseMapObjectRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InMapObjectId,(ushort)InResultAttributes_.Length, InResultAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.UseMapObjectRes);
			return result;
		} // public int  UseMapObjectRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, SF.VariableTable InResultAttributes )


		// Cmd: Havest area
		public int  HarvestAreaRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId, SF.VariableTable InResultAttributes )
		{
 			int result;
			var InResultAttributes_ = InResultAttributes.ToByteArray();
			using (var InResultAttributes_PinnedPtr_ = new PinnedByteBuffer(InResultAttributes_))
			{
			result = CSSFNetAdapter_PlayInstanceHarvestAreaRes(m_Connection.NativeHandle, InTransactionID, InResult, InPlayInstanceUID, InPlayerID, InAreaId,(ushort)InResultAttributes_.Length, InResultAttributes_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.HarvestAreaRes);
			return result;
		} // public int  HarvestAreaRes( System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId, SF.VariableTable InResultAttributes )


		// Cmd: Create stream instance
		public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceCreateStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CreateStreamRes);
			return result;
		} // public int  CreateStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Open stream instance
		public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceFindStreamRes(m_Connection.NativeHandle, InTransactionID, InResult,ref InStreamServerAddr,ref InStreamServerAddrIPV4,System.Text.Encoding.UTF8.GetBytes(InStreamUID + "\0"));
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.FindStreamRes);
			return result;
		} // public int  FindStreamRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.NetAddress InStreamServerAddr, SF.NetAddress InStreamServerAddrIPV4, System.String InStreamUID )


		// Cmd: Delete stream instance
		public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )
		{
 			int result;
			{
			result = CSSFNetAdapter_PlayInstanceDeleteStreamRes(m_Connection.NativeHandle, InTransactionID, InResult);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.DeleteStreamRes);
			return result;
		} // public int  DeleteStreamRes( System.UInt64 InTransactionID, System.Int32 InResult )


		// Cmd: Get stream list
		public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )
		{
 			int result;
			using (var InStreamNamesArray = new ArrayObjectString(InStreamNames))
			{
			result = CSSFNetAdapter_PlayInstanceGetStreamListRes(m_Connection.NativeHandle, InTransactionID, InResult,InStreamNamesArray.NativeHandle);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.GetStreamListRes);
			return result;
		} // public int  GetStreamListRes( System.UInt64 InTransactionID, System.Int32 InResult, System.String[] InStreamNames )


		// Cmd: To call general functionality
		public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )
		{
 			int result;
			var InResults_ = InResults.ToByteArray();
			using (var InResults_PinnedPtr_ = new PinnedByteBuffer(InResults_))
			{
			result = CSSFNetAdapter_PlayInstanceCallFunctionRes(m_Connection.NativeHandle, InTransactionID, InResult,(ushort)InResults_.Length, InResults_PinnedPtr_.Ptr);
			}
			if (m_Connection != null && m_Connection.MessageRouter != null) m_Connection.MessageRouter.HandleSentMessage(result, MessageIDPlayInstance.CallFunctionRes);
			return result;
		} // public int  CallFunctionRes( System.UInt64 InTransactionID, System.Int32 InResult, SF.VariableTable InResults )


		#region Native Interfaces 
		// Cmd: Event for Player Join request.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceJoinGameInstanceRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceJoinGameInstanceRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.ActorMovement InMovement );



		// S2C: Player kicked event. this event will be broadcasted when a player kicked.
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerKickedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InKickedPlayerID );



		// S2C: New Player in get view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceNewPlayerInViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt16 _sizeOfInAttributes,IntPtr InAttributes, ref SF.ActorMovement InMovement, System.UInt32 InState, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// S2C: Remove player from view
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceRemovePlayerFromViewS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID );



		// S2C: Player Movement
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerMovementS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, ref SF.ActorMovement InMovement );



		// S2C: Player state change
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstancePlayerStateChangedS2CEvt(System.IntPtr InNativeConnectionHandle, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InState, System.UInt32 InMoveFrame, ref SF.Vector4 InPosition, System.UInt16 _sizeOfInStateValues,IntPtr InStateValues );



		// Cmd: Occupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceOccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceOccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Unoccupy map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUnoccupyMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId );



		// Cmd: Use map object
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceUseMapObjectRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceUseMapObjectRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InMapObjectId, System.UInt16 _sizeOfInResultAttributes,IntPtr InResultAttributes );



		// Cmd: Havest area
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceHarvestAreaRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceHarvestAreaRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt64 InPlayInstanceUID, System.UInt64 InPlayerID, System.UInt32 InAreaId, System.UInt16 _sizeOfInResultAttributes,IntPtr InResultAttributes );



		// Cmd: Create stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCreateStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCreateStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Open stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceFindStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceFindStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, ref SF.NetAddress InStreamServerAddr, ref SF.NetAddress InStreamServerAddrIPV4, [MarshalAs(UnmanagedType.LPArray)] byte[] InStreamUID );



		// Cmd: Delete stream instance
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceDeleteStreamRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceDeleteStreamRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult );



		// Cmd: Get stream list
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceGetStreamListRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceGetStreamListRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, IntPtr InStreamNames );



		// Cmd: To call general functionality
		[DllImport(NativeDLLName, EntryPoint = "CSSFNetAdapter_PlayInstanceCallFunctionRes", CharSet = CharSet.Ansi)]
		static extern int CSSFNetAdapter_PlayInstanceCallFunctionRes(System.IntPtr InNativeConnectionHandle, System.UInt64 InTransactionID, System.Int32 InResult, System.UInt16 _sizeOfInResults,IntPtr InResults );



		#endregion //Native Interfaces 
	}; // public class SendMessageSvrPlayInstance




} // namespace SF.Net


