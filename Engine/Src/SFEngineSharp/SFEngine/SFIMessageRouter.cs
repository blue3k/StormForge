﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : network message router
//	
//
////////////////////////////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace SF
{


    public abstract class SFIMessageRouter
    {
        /// <summary>
        /// Message event argument
        /// </summary>
        public delegate void delMessageIDEventHandler(int sendResult, int messageID);
        public delegate void delMessageEventHandler(SFMessage message);


        /// <summary>
        /// When a message data is sent
        /// </summary>
        public delMessageIDEventHandler OnMessageSent = null;

        /// <summary>
        /// When a message data is dequeued for processing
        /// </summary>
        public delMessageEventHandler OnMessageProcessing = null;


        /// <summary>
        /// Register message handler
        /// </summary>
        /// <param name="messageID"></param>
        /// <param name="priority"></param>
        /// <param name="handler"></param>
        public virtual void RegisterMessageHandler(int messageID, int priority, Action<SFMessage> handler) { }
        public virtual void RegisterMessageHandler(int messageID, Action<SFMessage> handler) { RegisterMessageHandler(messageID, 0, handler); }

        /// <summary>
        /// Unregister whole message handlers of the messageID and priority. This method will clear whole message handlers with same priority
        /// </summary>
        /// <param name="messageID">Message ID</param>
        /// <param name="priority">Priority</param>
        public virtual void UnregisterMessageHandler(int messageID, int priority) { }

        /// <summary>
        /// Unregister message handler. 
        /// </summary>
        /// <param name="messageID">Message ID</param>
        /// <param name="priority">Priority</param>
        public virtual void UnregisterMessageHandler(int messageID, Action<SFMessage> handler) { }

        /// <summary>
        /// Callback called when a message is sent
        /// </summary>
        /// <param name="result">Send result</param>
        /// <param name="messageID">Message ID</param>
        public virtual void HandleSentMessage(int result, int messageID) { }


        /// <summary>
        /// Handle received message
        /// </summary>
        /// <param name="message">message to handle</param>
        public virtual void HandleRecvMessage(SFMessage message) { }
    }
}

