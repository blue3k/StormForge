////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2017 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Server Config
//	
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "SFTypedefs.h"
#include "Types/SFEngineTypedefs.h"
#include "String/SFStringCrc32.h"
#include "String/SFString.h"


#include "Zookeeper/SFZookeeper.h"
#include "SFEnum.h"




namespace SF
{

	namespace ServerConfig
	{
		struct GameCluster;

		struct NetPrivate
		{
			String IP;
			uint Port = 0;

			NetPrivate(IHeap& heap)
				: IP(heap)
			{}
		};


		struct NetPublic
		{
			String Protocol; // UDP, TCP, MRUDP
			String IPV4;
			String IPV6;
			String ListenIP;
			uint Port = 0;
			uint MaxConnection = 1000000;

			NetPublic(IHeap& heap)
				: Protocol(heap)
				, IPV4(heap)
				, IPV6(heap)
				, ListenIP(heap)
			{}
		};


		struct DBInstance
		{
			String InstanceName;
			String ConnectionString;
			String UserID;
			String Password;

			DBInstance(IHeap& heap);
		};

		struct DBCluster
		{
			GameCluster* pGameCluster = nullptr; // Game Cluster pointer if it's under game cluster, deprecated
			String ClusterName;
			DBClusterType ClusterType;
			String DBInstanceName;
			String DBName;

			DBCluster(IHeap& heap)
				: ClusterName(heap)
				, ClusterType(DBClusterType::Normal)
				, DBInstanceName(heap)
				, DBName(heap)
			{}
		};

		struct ServerModule
		{
			String ModuleName;
			ServerModule(IHeap& heap)
				: ModuleName(heap)
			{}
			virtual ~ServerModule() {}
		};


		struct ServerModuleMatching_8 : public ServerModule
		{
			bool UseBot = false;

			ServerModuleMatching_8(IHeap& heap)
				: ServerModule(heap)
			{}
		};

		struct ServerModuleMatching_4 : public ServerModule
		{
			bool UseBot = false;

			ServerModuleMatching_4(IHeap& heap)
				: ServerModule(heap)
			{}
		};

		struct ServerModuleGooglePurchaseValidate : public ServerModule
		{
			String Account;
			String P12KeyFile;
			String AuthScopes;

			ServerModuleGooglePurchaseValidate(IHeap& heap)
				: ServerModule(heap)
				, Account(heap)
				, P12KeyFile(heap)
				, AuthScopes(heap)
			{}
		};

		struct ServerModuleIOSPurchaseValidate : public ServerModule
		{
			String URL;
			String AltURL;

			ServerModuleIOSPurchaseValidate(IHeap& heap)
				: ServerModule(heap)
				, URL(heap)
				, AltURL(heap)
			{}
		};

		struct ServerModulePublicService : public ServerModule
		{
			NetPublic PublicNet;

			ServerModulePublicService(IHeap& heap)
				: ServerModule(heap)
				, PublicNet(heap)
			{}
		};

		struct ServerModuleGameInstanceManager : public ServerModulePublicService
		{
			String Name;
			String DataTable;

			ServerModuleGameInstanceManager(IHeap& heap)
				: ServerModulePublicService(heap)
			{}
		};

		struct ServerModuleRelayService : public ServerModulePublicService
		{
			uint32_t MaximumRelayInstances = 1000;

			ServerModuleRelayService(IHeap& heap)
				: ServerModulePublicService(heap)
			{}
		};

		struct GenericServer
		{
			uint32_t UID = 0;
			String Name;
			String Executable;
			NetPrivate PrivateNet;
			uint WorkerThreadCount = 4;
			uint NetIOThreadCount = 4;
			DynamicArray<ServerModule*> Modules;

			GenericServer(IHeap& heap)
				: Name(heap)
				, Executable(heap)
				, PrivateNet(heap)
				, Modules(heap)
			{}
			virtual ~GenericServer()
			{
				for (auto itServer : Modules)
				{
					IHeap::Delete(itServer);
				}
				Modules.Clear();
			}

		};


		// deprecated use module
		struct ServerComponent
		{
			String ComponentName;

			ServerComponent(IHeap& heap)
				: ComponentName(heap)
			{}
			virtual ~ServerComponent() {}
		};

		// deprecated use module
		struct ServerComponentGoogle : public ServerComponent
		{
			String Account;
			String P12KeyFile;
			String AuthScopes;

			ServerComponentGoogle(IHeap& heap)
				: ServerComponent(heap)
				, Account(heap)
				, P12KeyFile(heap)
				, AuthScopes(heap)
			{}
			virtual ~ServerComponentGoogle() {}
		};

		// deprecated use module
		struct ServerComponentIOS : public ServerComponent
		{
			String URL;
			String AltURL;

			ServerComponentIOS(IHeap& heap)
				: ServerComponent(heap)
				, URL(heap)
				, AltURL(heap)
			{}
			virtual ~ServerComponentIOS() {}
		};


		struct ServerService : public GenericServer
		{
			GameID GameClusterID;
			String GameClusterName;
			String DataCenter;
			String LogFilePath;
			String LogServer;

			GenericServer* MonitoringServer{};
			DynamicArray<DBCluster*> DBClusters;
			DynamicArray<DBInstance*> DBInstances;

			ServerService()
				: GenericServer(GetSystemHeap())
				, DBClusters(GetSystemHeap())
				, DBInstances(GetSystemHeap())
			{}

			virtual ~ServerService()
			{
				for (auto& itServer : DBClusters)
				{
					IHeap::Delete(itServer);
				}
				DBClusters.Clear();
			}


			const DBCluster* FindDBCluster(const char* serverName) const;
			const DBInstance* FindDBInstance(const char* instanceName) const;
		};


	}
}

