////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Network connection manager
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Multithread/SFThread.h"
#include "Multithread/SFSynchronization.h"
#include "Util/SFUniqueIDGenerator.h"
#include "Net/SFNetDef.h"
#include "Net/SFConnection.h"
#include "Net/SFConnectionTCP.h"
#include "Net/SFConnectionUDP.h"
#include "Net/SFNetSocket.h"
#include "Net/SFNetSvrDef.h"
#include "Task/SFAsyncTaskManager.h"
#include "SFEngine.h"
#include "Component/SFLibraryComponent.h"
#include "Service/SFEngineService.h"


namespace SF {
namespace Net {


	class ServerNet;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	// Connection manager
	//

	class ConnectionManager : public LibraryComponent, public ConnectionManagerService
	{
	public:
		static constexpr StringCrc64 TypeName = "ConnectionManager";

	private:

		Heap m_Heap;

		// Address map
		AddrMap		m_AddrMap;

		// Connection ID map
		CIDMap		m_CIDMap;

		// Peer ID map
		PeerIDMap	m_PeerIDMap;


		// CID generator
		UniqueIDGenerator	m_CIDGen;


	protected:

		// mapping Add/Remove
		Result RemoveMap(const ConnectionPtr& pConn );

		Result AddConnection_Internal(const ConnectionPtr& pConn);

		template<class ConnectionType,
			typename = std::enable_if_t<std::is_base_of<Connection, ConnectionType>::value>
		>
			Result NewUDPAddress_Internal(IHeap& memMgr, ServerNet* pNet, SF_SOCKET socket, const PeerInfo& local, const PeerInfo& remote)
		{
			Result hr;
			auto sockAddr = (sockaddr_storage)remote.PeerAddress;

			SharedPointerT<Connection> pFound;
			if (GetConnectionByAddr(sockAddr, pFound))
			{
				// already registered
				return hr;
			}

			SFLog(Net, Debug, "New UDP connection from {0}", remote.PeerAddress);

			auto pNewConnectionType = NewObject<ConnectionType>(memMgr, pNet->GetSocketIO());
			ConnectionPtr pNewConnection = pNewConnectionType.template StaticCast<Connection>();
			Assert(pNewConnection != nullptr);
			if (pNewConnection == nullptr)
				return hr;

			pNewConnection->SetCID(NewCID());
			netCheck(pNewConnection->InitConnection(local, remote));

			pNewConnection->SetTickGroup(EngineTaskTick::AsyncTick);

			if (pNet != nullptr)
				pNet->GetNewConnectionHandler()(pNewConnection);

			// add later so that new connection handler is kicked in first
			netCheck(AddConnection_Internal(pNewConnection));

			return hr;
		}

		void RemoveConnection_Internal(const ConnectionPtr& pConn);

		void AddressRemap_Internal(const ConnectionPtr& pConn, const sockaddr_storage &addressOrg, const sockaddr_storage &newAddress);
		void RemapPeerID_Internal(const ConnectionPtr& pConn, uint64_t ticket);

	public:
		// Constructor/Destructor
		// @param uiBucketSize : Hashmap bucket size
		ConnectionManager(uint uiBucketSize );
		virtual ~ConnectionManager();

		virtual const StringCrc64& GetTypeName() override { return TypeName; }

		virtual IHeap& GetHeap() override { return *m_Heap.get(); }


		// Initialize component
		virtual Result InitializeComponent() override;
		// Terminate component
		virtual void DeinitializeComponent() override;



		// CID generation
		virtual uint NewCID() override;
		virtual void FreeCID( uint uiCID ) override;


		// Active connection
		virtual CounterType GetNumActiveConnection() override;


		virtual void AddConnection(SharedPointerT<Connection>& pConn) override;

		// Free connection directly
		virtual EngineTaskPtr RemoveConnection(SharedPointerT<Connection>& pConn ) override;

		virtual void NewMUDPAddress(IHeap& memMgr, ServerNet* pNet, SF_SOCKET socket, const PeerInfo& local, const PeerInfo& remote) override;
		virtual void NewUDPAddress(IHeap& memMgr, ServerNet* pNet, SF_SOCKET socket, const PeerInfo& local, const PeerInfo& remote) override;

		virtual void AddressRemap(SharedPointerT<Connection>& pConn, const sockaddr_storage &addressOrg, const sockaddr_storage &newAddress) override;

		virtual void RemapPeerID(SharedPointerT<Connection>& pConn, uint64_t ticket) override;

		// Disconnect all connection
		virtual Result DisconnectAllConnection() override;


		// Remap PeerID

		// Find and return connection
		virtual Result GetConnectionByAddr(const sockaddr_storage& sockAddr, SharedPointerT<Connection> &pFound) override;
		virtual Result GetConnectionByCID( uint64_t uiCID, SharedPointerT<Connection> &pConn ) override;
		virtual Result GetConnectionByPeerID(uint64_t peerID, SharedPointerT<Connection> &pConn) override;
	};


#include "SFConnectionManager.inl"

} // namespace Net
} // namespace SF



