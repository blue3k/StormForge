﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Connection interface
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
#if UNITY_IOS
using AOT;
#endif

namespace SF
{


    public class SFConnection : SFObject
    {

	    // Connection state
	    public enum ConnectionState
	    {
		    NONE,				// None just created
		    WAITING,			// Waiting accept
		    UDP_WAITING,		// UDP incoming Waiting
		    CONNECTING,		// Connecting sequence
		    CHECKVERSION,		// Checking protocol version
		    CONNECTED,		// Connected
		    DISCONNECTING,	// Disconnecting
		    DISCONNECTED,		// Disconnected
		    SLEEP,			// For Mobile connection
	    };


	    // Type of connection event
	    public enum EventTypes
	    {
		    EVT_NONE,
		    EVT_CONNECTION_RESULT,
		    EVT_DISCONNECTED,
		    EVT_STATE_CHANGE,
		    EVT_ADDRESS_REMAPPED,
            EVT_TIMESYNC_RESULT,
        };

        public enum ProtocolType
        {
            MRUDP,
            TCP
        };


        public struct Event
	    {
		    public EventTypes		EventType;

		    // connection result
		    public Result HResult;

		    // State changed
		    public ConnectionState State;


		    public Event(EventTypes eventType, ConnectionState state, int hr)
		    {
			    EventType = eventType;
			    State = state;
			    HResult.Code = hr;
		    }
	    };

        // message router instance
        readonly SFIMessageRouter m_MessageRouter;

        public SFIMessageRouter MessageRouter { get { return m_MessageRouter; } }


        public UInt64 LocalPeerID
        {
            get { return NativeGetLocalPeerID(NativeHandle); }
            set { NativeSetLocalPeerID(NativeHandle, value); }
        }


        // Local loopback message queue
        Queue<SFMessage> m_LoopBackQueue = new Queue<SFMessage>();

        public SFConnection(SFIMessageRouter messageRouter, ProtocolType protocolType = ProtocolType.MRUDP)
	    {
            // Don't use constructor of SFObject, it will increase reference count of the object
            if (protocolType == ProtocolType.MRUDP)
                NativeHandle = NativeCreateConnection();
            else
                NativeHandle = NativeCreateConnectionTCP();
            m_MessageRouter = messageRouter;
        }

        public SFConnection(SFConnectionGroup group, SFIMessageRouter messageRouter)
        {
            // Don't use constructor of SFObject, it will increase reference count of the object
            NativeHandle = NativeCreateConnectionWithGroup(group.NativeHandle);
            m_MessageRouter = messageRouter;
        }

        public SFConnection(IntPtr nativeHandle, SFIMessageRouter messageRouter = null)
        {
            // Don't use constructor of SFObject, it will increase reference count of the object
            NativeHandle = nativeHandle;
            m_MessageRouter = messageRouter;
        }

        virtual public int Connect(UInt64 authTicket, String address, int port)
	    {
            return NativeConnect(NativeHandle, authTicket, address, port);
	    }

        public UInt64 CID
        {
            get { return NativeGetCID(NativeHandle); }
        }

        virtual public ConnectionState State
        {
            get { return (ConnectionState)NativeGetState(NativeHandle); }
        }

        public bool IsConnected
        {
            get { return State == ConnectionState.CONNECTED; }
        }

        public override void Dispose()
        {
            Disconnect();
            // Connection uses deferred dispose
            NativeDispose(NativeHandle);
            NativeHandle = IntPtr.Zero;
            //base.Dispose();
        }

        public void Disconnect()
        {
            NativeDisconnect(NativeHandle);
        }

	    // Connection events
	    virtual public bool DequeueEvent(out Event conEvent)
	    {
            conEvent = new Event();

		    return NativeDequeueEvent(NativeHandle, out conEvent.EventType, out conEvent.HResult.Code, out conEvent.State);
        }
        

        public void UpdateMessageQueue()
        {
            var message = DequeueMessage();
            while (message != null)
            {
                m_MessageRouter.HandleRecvMessage(message);
                message = DequeueMessage();
            }

            while (m_LoopBackQueue.Count > 0)
            {
                lock (m_LoopBackQueue)
                {
                    if (m_LoopBackQueue.Count == 0)
                        break;
                    message = m_LoopBackQueue.Dequeue();
                }
                m_MessageRouter.HandleRecvMessage(message);
           }
        }


        public void AddLoopBackMessage(SFMessage msg)
        {
            if (msg == null)
                return;

            lock(m_LoopBackQueue)
            {
                m_LoopBackQueue.Enqueue(msg);
            }
        }

        // Request time sync
        public bool TimeSync()
        {
            if (NativeHandle == IntPtr.Zero)
                return false;

            return NativeTimeSync(NativeHandle);
        }
        

        #region Message Parsing

        // Message
        public SFMessage DequeueMessage()
	    {
            lock(SFMessageParsingUtil.stm_ParsingLock)
            {
                System.Diagnostics.Debug.Assert(SFMessageParsingUtil.stm_ParsingMessage == null);

                NativeDequeueMessage(NativeHandle,
                    SFMessageParsingUtil.MessageParseCreateCallback,
                    SFMessageParsingUtil.MessageParseSetValue,
                    SFMessageParsingUtil.MessageParseSetArray
                    );

                var message = SFMessageParsingUtil.stm_ParsingMessage;
                SFMessageParsingUtil.stm_ParsingMessage = null;
                return message;
            }
        }

        #endregion // Message parsing

        ////////////////////////////////////////////////////////////////////////////////
        //
        //	Native interfaces
        //

#region Native interfaces

        const string NativeDllName =
#if UNITY_IOS
            "__Internal";
#else
            "SFEngineDLL";
#endif

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_MESSAGE_FUNCTION(UInt32 messageID);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, IntPtr Value);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SET_ARRAY_FUNCTION([MarshalAs(UnmanagedType.LPStr)] string stringHash, [MarshalAs(UnmanagedType.LPStr)] string typeNameHash, int arrayCount, IntPtr Value);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeCreateConnection", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConnection();

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeCreateConnectionWithGroup", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConnectionWithGroup(IntPtr groupNativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeCreateConnectionTCP", CharSet = CharSet.Auto)]
        static extern IntPtr NativeCreateConnectionTCP();

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeDispose", CharSet = CharSet.Auto)]
        static extern int NativeDispose(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeConnect", CharSet = CharSet.Auto)]
        static extern int NativeConnect(IntPtr nativeHandle, UInt64 authTicket, [MarshalAs(UnmanagedType.LPStr)] string address, int port);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeDisconnect", CharSet = CharSet.Auto)]
        static extern void NativeDisconnect(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeGetCID", CharSet = CharSet.Auto)]
        static extern UInt64 NativeGetCID(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeGetLocalPeerID", CharSet = CharSet.Auto)]
        static extern UInt64 NativeGetLocalPeerID(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeSetLocalPeerID", CharSet = CharSet.Auto)]
        static extern void NativeSetLocalPeerID(IntPtr nativeHandle, UInt64 peerID);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeGetState", CharSet = CharSet.Auto)]
        static extern int NativeGetState(IntPtr nativeHandle);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeDequeueEvent", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeDequeueEvent(IntPtr nativeHandle, out EventTypes eventType, out Int32 result, out ConnectionState state );

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeDequeueMessage", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeDequeueMessage(IntPtr nativeHandle, SET_MESSAGE_FUNCTION setMessageFunc, SET_FUNCTION setValueFunc, SET_ARRAY_FUNCTION setArrayValueFunc);

        [DllImport(NativeDllName, EntryPoint = "SFConnection_NativeTimeSync", CharSet = CharSet.Auto)]
        [return: MarshalAs(UnmanagedType.I1)]
        static extern bool NativeTimeSync(IntPtr nativeHandle);

        #endregion
    }
}

