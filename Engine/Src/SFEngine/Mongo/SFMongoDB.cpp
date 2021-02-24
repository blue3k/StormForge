////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c)  Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : MongoDB
//	
//
////////////////////////////////////////////////////////////////////////////////

#include "SFEnginePCH.h"

#include "Mongo/SFMongoDB.h"
#include "Util/SFStringFormat.h"


#ifdef USE_MONGODB


#include <bson/bson.h>
#include <mongoc/mongoc.h>



namespace SF
{

	void BsonDeleter::operator()(bson_t* _Ptr) const noexcept
	{
		if (_Ptr) bson_destroy(_Ptr);
	}

	void MongoCursorDeleter::operator()(mongoc_cursor_t* _Ptr) const noexcept
	{
		if (_Ptr) mongoc_cursor_destroy(_Ptr);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class MongoDBCursor
	//

	MongoDBCursor::MongoDBCursor(mongoc_cursor_t* _Ptr)
	{
		m_Cursor.reset(_Ptr);
	}

	MongoDBCursor::~MongoDBCursor()
	{

	}

	void MongoDBCursor::SetCursorRaw(mongoc_cursor_t* _Ptr)
	{
		m_Cursor.reset(_Ptr);
	}

	const bson_t* MongoDBCursor::Next()
	{
		if (m_Cursor == nullptr)
			return nullptr;

		const bson_t* pNext{};
		if (!mongoc_cursor_next(m_Cursor.get(), &pNext))
			return nullptr;

		return pNext;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//	class MongoDB
	//
	MongoDB::MongoDB(IHeap& heap)
		: m_Heap(heap)
	{
		m_AddOrUpdateOpt.reset(BCON_NEW("upsert", BCON_BOOL(true)));
	}

	MongoDB::~MongoDB()
	{
	}

	void MongoDB::Clear()
	{
		if (m_Database)
		{
			mongoc_database_destroy(m_Database);
			m_Database = nullptr;
		}

		if (m_Collection)
		{
			mongoc_collection_destroy(m_Collection);
			m_Collection = nullptr;
		}

		if (m_Uri)
		{
			mongoc_uri_destroy(m_Uri);
			m_Uri = nullptr;
		}

		if (m_Client)
		{
			mongoc_client_destroy(m_Client);
			m_Client = nullptr;
		}
	}

	void MongoDB::Dispose()
	{
		Clear();
		super::Dispose();
	}

	Result MongoDB::Initialize(const String& serverAddress)
	{
		bson_error_t error;

		Clear();

		mongoc_uri_t* uri = mongoc_uri_new_with_error(serverAddress, &error);
		if (!uri)
		{
			SFLog(Net, Error, "MongoDB: failed to parse URI:{0}, error:{1}", serverAddress, error.message);
			return ResultCode::IO_INVALID_ADDRESS;
		}

		m_Client = mongoc_client_new_from_uri(uri);
		if (!m_Client)
		{
			SFLog(Net, Error, "MongoDB: failed to create client:{0}", serverAddress);
			return ResultCode::OUT_OF_MEMORY;
		}

		mongoc_client_set_appname(m_Client, Util::GetModuleName());

		return ResultCode::SUCCESS;
	}


	Result MongoDB::SetDatabase(const char* database, const char* collection)
	{
		if (m_Database)
		{
			mongoc_database_destroy(m_Database);
			m_Database = nullptr;
		}

		if (m_Collection)
		{
			mongoc_collection_destroy(m_Collection);
			m_Collection = nullptr;
		}

		m_Database = mongoc_client_get_database(m_Client, database);
		m_Collection = mongoc_client_get_collection(m_Client, database, collection);

		return m_Database != nullptr && m_Collection != nullptr ? ResultCode::SUCCESS : ResultCode::FAIL;
	}

	Result MongoDB::Insert(const bson_t* row)
	{
		if (m_Collection == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (row == nullptr)
			return ResultCode::INVALID_ARG;

		// We don't want auto generated _id
		if (!bson_has_field(row, "_id"))
			return ResultCode::INVALID_FORMAT;

		bson_error_t error;
		auto ret = mongoc_collection_insert_one(m_Collection, row, nullptr, nullptr, &error);
		if (!ret)
		{
			SFLog(Net, Error, "MongoDB:Insert failed error:{0}", error.message);
		}

		return ResultCode::SUCCESS;
	}

	Result MongoDB::AddOrUpdate(uint64_t id, const bson_t* row)
	{
		if (m_Collection == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (row == nullptr)
			return ResultCode::INVALID_ARG;

		// We don't want auto generated _id
		if (!bson_has_field(row, "_id"))
			return ResultCode::INVALID_FORMAT;

		BsonUniquePtr selector(BCON_NEW("_id",BCON_INT64(id)));
		BsonUniquePtr update(BCON_NEW("$set", row));

		bson_error_t error;
		auto ret = mongoc_collection_update_one(m_Collection, selector.get(), update.get(), m_AddOrUpdateOpt.get(), nullptr, &error);
		if (!ret)
		{
			SFLog(Net, Error, "MongoDB:Insert failed error:{0}", error.message);
		}

		return ResultCode::SUCCESS;
	}

	Result MongoDB::Aggregate(const bson_t* aggregatePipeline, MongoDBCursor& outCursor)
	{
		if (m_Collection == nullptr)
			return ResultCode::NOT_INITIALIZED;

		if (aggregatePipeline == nullptr)
			return ResultCode::INVALID_ARG;

		BsonUniquePtr opt(BCON_NEW("batchSize", BCON_INT32(50)));

		mongoc_query_flags_t flags = (mongoc_query_flags_t)(MONGOC_QUERY_SLAVE_OK | MONGOC_QUERY_PARTIAL);
		const mongoc_read_prefs_t* read_prefs = nullptr;
		outCursor.SetCursorRaw(mongoc_collection_aggregate(m_Collection, flags, aggregatePipeline, opt.get(), read_prefs));

		return ResultCode::SUCCESS;
	}

}

#endif
