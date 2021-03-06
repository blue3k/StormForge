////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2018 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Asset Importer
//
////////////////////////////////////////////////////////////////////////////////


#pragma once

#include "Resource/SFResource.h"
#include "Container/SFArray.h"
#include "Asset/Importer/SFAssetImportContext.h"

namespace SF
{
	

	////////////////////////////////////////////////////////////////////
	//
	//	AssetImporter
	//
	class AssetImporter
	{
	private:

		// Name of importer
		StringCrc64 m_Name;

		// heap for importer
		IHeap& m_Heap;

		// Supporting asset types
		//Array<StringCrc64>& m_AssetTypes;
		StaticArray<StringCrc64, 4> m_AssetTypes;


	public:
		AssetImporter(IHeap& heap, const StringCrc64& name);
		virtual ~AssetImporter();

		StringCrc64 GetName() const { return m_Name; }

		IHeap& GetHeap() { return m_Heap; }

		// Add Asset type 
		void AddAssetType(const char* pAssetType);

		// Asset type list
		const Array<StringCrc64>& GetAssetTypes() const { return m_AssetTypes; }


		// Import
		// @resources: imported resources will be added
		virtual Result Import(AssetImportContext& context, Array<ResourcePtr>& resources) = 0;
	};


	//extern template class SharedPointerT<AssetImporter>;
	//extern template class WeakPointerT<AssetImporter>;
	//typedef SharedPointerT<AssetImporter> AssetImporterPtr;

}

