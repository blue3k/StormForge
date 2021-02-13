﻿////////////////////////////////////////////////////////////////////////////////
// 
// CopyRight (c) 2016 Kyungkun Ko
// 
// Author : KyungKun Ko
//
// Description : Autogenerated header, SF
//
////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <stdint.h>



namespace SF {
	namespace ResultCode {



			// Invalid byte sequence. usually casued by invalid data stream 
			constexpr Result 			INVALID_BYTE_SEQUENCE                                              ((int32_t)0xE7010000L);

			// You can not register same name or type component 
			constexpr Result 			DUPLICATE_COMPONENT                                                ((int32_t)0xE7010001L);

			// Called without initialization. 
			constexpr Result 			NOT_INITIALIZED                                                    ((int32_t)0xE7010002L);

			// The version not available or miss match with system. 
			constexpr Result 			VERSION_NOT_AVAIL                                                  ((int32_t)0xE7010003L);

			// Invalid Cluster Master server 
			constexpr Result 			INVALID_CLUSTERMASTER                                              ((int32_t)0xE7010004L);

			// The version not available or miss match with system. 
			constexpr Result 			INVALID_STATE                                                      ((int32_t)0xE7010005L);

			// Invalid string format. 
			constexpr Result 			INVALID_STR_FORMAT                                                 ((int32_t)0xE7010006L);

			// ServerID is duplicated. 
			constexpr Result 			DUPLICATED_SERVERID                                                ((int32_t)0xE7010007L);

			// Invalid entity 
			constexpr Result 			INVALID_ENTITY                                                     ((int32_t)0xE7010008L);

			// Invalid duplicated entity 
			constexpr Result 			DUPLICATED_ENTITY                                                  ((int32_t)0xE7010009L);

			// Invalid duplicated entity 
			constexpr Result 			DUPLICATED_ENTITYID                                                ((int32_t)0xE701000AL);

			// Duplicated Account ID 
			constexpr Result 			DUPLICATED_ACCOUNTID                                               ((int32_t)0xE701000BL);

			// Duplicated Player ID 
			constexpr Result 			DUPLICATED_PLAYERID                                                ((int32_t)0xE701000CL);

			// Duplicated name 
			constexpr Result 			DUPLICATED_NAME                                                    ((int32_t)0xE701000DL);

			// Duplicated ID 
			constexpr Result 			DUPLICATED_ID                                                      ((int32_t)0xE701000EL);

			// Invalid duplicated entity 
			constexpr Result 			INVALID_ACCOUNTID                                                  ((int32_t)0xE701000FL);

			// Invalid ticket 
			constexpr Result 			INVALID_TICKET                                                     ((int32_t)0xE7010010L);

			// Invalid player ID 
			constexpr Result 			INVALID_PLAYERID                                                   ((int32_t)0xE7010011L);

			// Invalid value 
			constexpr Result 			INVALID_VALUE                                                      ((int32_t)0xE7010012L);

			// Invalid class value 
			constexpr Result 			INVALID_CLASS                                                      ((int32_t)0xE7010013L);

			// Invalid Difficulty 
			constexpr Result 			INVALID_DIFFICULTY                                                 ((int32_t)0xE7010014L);

			// Invalid registration to play 
			constexpr Result 			INVALID_REGISTRATION                                               ((int32_t)0xE7010015L);

			// Invalid Channel ID 
			constexpr Result 			INVALID_CHANNELID                                                  ((int32_t)0xE7010016L);

			// Invalid Zone instance ID 
			constexpr Result 			INVALID_INSTANCEID                                                 ((int32_t)0xE7010017L);

			// Duplicated component 
			constexpr Result 			DUPLICATED_COMPONENT                                               ((int32_t)0xE7010018L);

			// Maximum friend 
			constexpr Result 			MAX_FRIEND                                                         ((int32_t)0xE7010019L);

			// Invalid player count for service 
			constexpr Result 			INVALID_PLAYER_COUNT                                               ((int32_t)0xE701001AL);

			// Invalid player level 
			constexpr Result 			INVALID_PLAYER_LEVEL                                               ((int32_t)0xE701001BL);

			// Invalid player nick 
			constexpr Result 			INVALID_PLAYER_NICK                                                ((int32_t)0xE701001CL);

			// Invalid Notification ID 
			constexpr Result 			INVALID_NOTIFICATIONID                                             ((int32_t)0xE701001DL);

			// Invalid Ranking range 
			constexpr Result 			INVALID_RANKING_RANGE                                              ((int32_t)0xE701001EL);

			// Target Maximum friend 
			constexpr Result 			TARGET_MAX_FRIEND                                                  ((int32_t)0xE701001FL);

			// Invalid string data. 
			constexpr Result 			INVALID_STR_DATA                                                   ((int32_t)0xE7010020L);

			// Not authorized 
			constexpr Result 			NOT_AUTORIZED                                                      ((int32_t)0xE7010021L);

			// No permition 
			constexpr Result 			NO_PERMITION                                                       ((int32_t)0xE7010022L);

			// No file or directory 
			constexpr Result 			NO_FILE_OR_DIR                                                     ((int32_t)0xE7010023L);

			// No such process 
			constexpr Result 			NO_SUCH_PROCESS                                                    ((int32_t)0xE7010024L);

			// Interrupted system call 
			constexpr Result 			INTERRUPTED_SYSCALL                                                ((int32_t)0xE7010025L);

			// I/O error 
			constexpr Result 			IO_ERROR                                                           ((int32_t)0xE7010026L);

			// No such device or address 
			constexpr Result 			NOT_DEVICE                                                         ((int32_t)0xE7010027L);

			// Arg list too long 
			constexpr Result 			TOO_MANY_ARGLIST                                                   ((int32_t)0xE7010028L);

			// Exec format error 
			constexpr Result 			INVALID_EXEC_FROMAT                                                ((int32_t)0xE7010029L);

			// Bad file number 
			constexpr Result 			INVALID_FILE_HANDLE                                                ((int32_t)0xE701002AL);

			// No child process 
			constexpr Result 			NO_CHILD_PROCESS                                                   ((int32_t)0xE701002BL);

			// Block device required 
			constexpr Result 			NOT_BLOCK                                                          ((int32_t)0xE701002CL);

			// Not exist 
			constexpr Result 			NOT_EXIST                                                          ((int32_t)0xE701002DL);

			// Busy 
			constexpr Result 			BUSY                                                               ((int32_t)0xE701002EL);

			// File exists 
			constexpr Result 			FILE_EXISTS                                                        ((int32_t)0xE701002FL);

			// Cross-device link 
			constexpr Result 			CROSS_LINK                                                         ((int32_t)0xE7010030L);

			// No such device 
			constexpr Result 			INVALID_DEVICE                                                     ((int32_t)0xE7010031L);

			// Not a directory 
			constexpr Result 			INVALID_DIRECTORY                                                  ((int32_t)0xE7010032L);

			// Is a directory 
			constexpr Result 			DIRECTORY                                                          ((int32_t)0xE7010033L);

			// File table overflow 
			constexpr Result 			NOT_ENOUGH_FILE_TABLE                                              ((int32_t)0xE7010034L);

			// Too many open files 
			constexpr Result 			TOO_MANY_OPENED_FILE                                               ((int32_t)0xE7010035L);

			// Not a typewriter 
			constexpr Result 			INVALID_TYPEWRITER                                                 ((int32_t)0xE7010036L);

			// Text file busy 
			constexpr Result 			BUSY_FILE                                                          ((int32_t)0xE7010037L);

			// File too large 
			constexpr Result 			TOO_BIG_FILE                                                       ((int32_t)0xE7010038L);

			// No space left on device 
			constexpr Result 			NOT_ENOUGH_SPACE                                                   ((int32_t)0xE7010039L);

			// Illegal seek 
			constexpr Result 			INVALID_SEEK                                                       ((int32_t)0xE701003AL);

			// Read-only file system 
			constexpr Result 			READ_ONLY                                                          ((int32_t)0xE701003BL);

			// Too many links 
			constexpr Result 			TOO_MANY_LINK                                                      ((int32_t)0xE701003CL);

			// Broken pipe 
			constexpr Result 			INVALID_PIPE                                                       ((int32_t)0xE701003DL);

			// Math argument out of domain of func 
			constexpr Result 			INVALID_MATH_DOMAIN                                                ((int32_t)0xE701003EL);

			// Math result not representable 
			constexpr Result 			INVALID_NUMERIC                                                    ((int32_t)0xE701003FL);

			// Invalid password 
			constexpr Result 			INVALID_PASSWORD                                                   ((int32_t)0xE7010040L);

			// Target already in friends list 
			constexpr Result 			ALREADY_IN_FRIEND                                                  ((int32_t)0xE7010041L);

			// Thread is wrong, running on wrong thread? 
			constexpr Result 			INVALID_THREAD                                                     ((int32_t)0xE7010042L);

			// Requested object already exist 
			constexpr Result 			ALREADY_EXIST                                                      ((int32_t)0xE7010043L);

			// Network sequence already processed 
			constexpr Result 			SUCCESS_IO_PROCESSED_SEQUENCE                                      ((int32_t)0x27010044L);

			// The version not available or miss match with system. 
			constexpr Result 			IO_PROTOCOL_VERSION_MISMATCH                                       ((int32_t)0xE7010045L);

			// Network is not initialized 
			constexpr Result 			IO_NOTINITIALIZED                                                  ((int32_t)0xE7010046L);

			// The version not available or miss match with system. 
			constexpr Result 			IO_INVALID_NETCLASS                                                ((int32_t)0xE7010047L);

			// Not enough space in sliding window 
			constexpr Result 			IO_NOT_ENOUGH_WINDOWSPACE                                          ((int32_t)0xE7010048L);

			// Network IO aborted 
			constexpr Result 			IO_IO_ABORTED                                                      ((int32_t)0xE7010049L);

			// Network IO send failed 
			constexpr Result 			IO_IO_SEND_FAIL                                                    ((int32_t)0xE701004AL);

			// Network IO recv failed 
			constexpr Result 			IO_IO_RECV_FAIL                                                    ((int32_t)0xE701004BL);

			// Network send failed 
			constexpr Result 			IO_SEND_FAIL                                                       ((int32_t)0xE701004CL);

			// Network recv failed 
			constexpr Result 			IO_RECV_FAIL                                                       ((int32_t)0xE701004DL);

			// Network Message sequence is invalid 
			constexpr Result 			IO_INVALID_SEQUENCE                                                ((int32_t)0xE701004EL);

			// Network Message not expected bad packet size 
			constexpr Result 			IO_BADPACKET_SIZE                                                  ((int32_t)0xE701004FL);

			// Network connection closed 
			constexpr Result 			IO_CONNECTION_CLOSED                                               ((int32_t)0xE7010050L);

			// Network connection is never made 
			constexpr Result 			IO_NOT_CONNECTED                                                   ((int32_t)0xE7010051L);

			// Network connection ID is invalid 
			constexpr Result 			IO_INVALID_CID                                                     ((int32_t)0xE7010052L);

			// Network Connection timeout 
			constexpr Result 			IO_CONNECTION_TIMEOUT                                              ((int32_t)0xE7010053L);

			// Network connection is failed 
			constexpr Result 			IO_CONNECTION_FAIL                                                 ((int32_t)0xE7010054L);

			// Too big packet data 
			constexpr Result 			IO_BADPACKET_TOOBIG                                                ((int32_t)0xE7010055L);

			// Network Message not expected bad packet 
			constexpr Result 			IO_BADPACKET_NOTEXPECTED                                           ((int32_t)0xE7010056L);

			// Checksum value of the message is invalid 
			constexpr Result 			IO_INVALID_MESSAGE_CHECKSUM                                        ((int32_t)0xE7010057L);

			// Message encryption is invalid 
			constexpr Result 			IO_INVALID_MESSAGE_ENCRYPTION                                      ((int32_t)0xE7010058L);

			// Invalid connection state 
			constexpr Result 			IO_INVALID_CONNECTION_STATE                                        ((int32_t)0xE7010059L);

			// Too big sequence id 
			constexpr Result 			IO_SEQUENCE_OVERFLOW                                               ((int32_t)0xE701005AL);

			// A non-blocking socket operation could not be completed immediately. 
			constexpr Result 			IO_WOULDBLOCK                                                      ((int32_t)0xE701005BL);

			// A blocking operation is currently executing. 
			constexpr Result 			IO_INPROGRESS                                                      ((int32_t)0xE701005CL);

			// An operation was attempted on a non-blocking socket that already had an operation in progress. 
			constexpr Result 			IO_ALREADY                                                         ((int32_t)0xE701005DL);

			// An operation was attempted on something that is not a socket. 
			constexpr Result 			IO_NOTSOCK                                                         ((int32_t)0xE701005EL);

			// A required address was omitted from an operation on a socket. 
			constexpr Result 			IO_DESTADDRREQ                                                     ((int32_t)0xE701005FL);

			// A socket operation encountered a dead network. 
			constexpr Result 			IO_NETDOWN                                                         ((int32_t)0xE7010060L);

			// A socket operation was attempted to an unreachable network. 
			constexpr Result 			IO_NETUNREACH                                                      ((int32_t)0xE7010061L);

			// The connection has been broken due to keep-alive activity detecting a failure while the operation was in progress. 
			constexpr Result 			IO_NETRESET                                                        ((int32_t)0xE7010062L);

			// An established connection was aborted by the software in your host machine. 
			constexpr Result 			IO_CONNABORTED                                                     ((int32_t)0xE7010063L);

			// An existing connection was forcibly closed by the remote host. 
			constexpr Result 			IO_CONNRESET                                                       ((int32_t)0xE7010064L);

			// An operation on a socket could not be performed because the system lacked sufficient buffer space or because a queue was full. 
			constexpr Result 			IO_NOBUFS                                                          ((int32_t)0xE7010065L);

			// A connect request was made on an already connected socket. 
			constexpr Result 			IO_ISCONN                                                          ((int32_t)0xE7010066L);

			// A request to send or receive data was disallowed because the socket is not connected and (when sending on a datagram socket using a sendto call) no address was supplied. 
			constexpr Result 			IO_NOTCONN                                                         ((int32_t)0xE7010067L);

			// A request to send or receive data was disallowed because the socket had already been shut down in that direction with a previous shutdown call. 
			constexpr Result 			IO_SHUTDOWN                                                        ((int32_t)0xE7010068L);

			// Too many references to some kernel object. 
			constexpr Result 			IO_TOOMANYREFS                                                     ((int32_t)0xE7010069L);

			// A connection attempt failed because the connected party did not properly respond after a period of time, or established connection failed because connected host has failed to respond. 
			constexpr Result 			IO_TIMEDOUT                                                        ((int32_t)0xE701006AL);

			// No connection could be made because the target machine actively refused it. 
			constexpr Result 			IO_CONNECTION_REFUSSED                                             ((int32_t)0xE701006BL);

			// Cannot translate name. 
			constexpr Result 			IO_LOOP                                                            ((int32_t)0xE701006CL);

			// Name component or name was too long. 
			constexpr Result 			IO_NAMETOOLONG                                                     ((int32_t)0xE701006DL);

			// A socket operation failed because the destination host was down. 
			constexpr Result 			IO_HOSTDOWN                                                        ((int32_t)0xE701006EL);

			// A socket operation was attempted to an unreachable host. 
			constexpr Result 			IO_HOSTUNREACH                                                     ((int32_t)0xE701006FL);

			// Cannot remove a directory that is not empty. 
			constexpr Result 			IO_NOTEMPTY                                                        ((int32_t)0xE7010070L);

			// A Windows Sockets implementation may have a limit on the number of applications that may use it simultaneously. 
			constexpr Result 			IO_PROCLIM                                                         ((int32_t)0xE7010071L);

			// WSAStartup cannot function at this time because the underlying system it uses to provide network services is currently unavailable. 
			constexpr Result 			IO_SYSNOTREADY                                                     ((int32_t)0xE7010072L);

			// The Windows Sockets version requested is not supported. 
			constexpr Result 			IO_VERNOTSUPPORTED                                                 ((int32_t)0xE7010073L);

			// Either the application has not called WSAStartup, or WSAStartup failed. 
			constexpr Result 			IO_NOTINITIALISED                                                  ((int32_t)0xE7010074L);

			// Returned by WSARecv or WSARecvFrom to indicate the remote party has initiated a graceful shutdown sequence. 
			constexpr Result 			IO_DISCON                                                          ((int32_t)0xE7010075L);

			// A system call has failed. 
			constexpr Result 			IO_SYSCALLFAILURE                                                  ((int32_t)0xE7010076L);

			// Host not found. 
			constexpr Result 			IO_HOST_NOT_FOUND                                                  ((int32_t)0xE7010077L);

			// Try again 
			constexpr Result 			IO_TRY_AGAIN                                                       ((int32_t)0xE7010078L);

			// IOPending 
			constexpr Result 			IO_IO_PENDING                                                      ((int32_t)0xE7010079L);

			// No such host is known securely. 
			constexpr Result 			IO_SECURE_HOST_NOT_FOUND                                           ((int32_t)0xE701007AL);

			// Protocol error 
			constexpr Result 			IO_PROTO                                                           ((int32_t)0xE701007BL);

			// Protocol wrong type for socket. 
			constexpr Result 			IO_PROTOTYPE                                                       ((int32_t)0xE701007CL);

			// Protocol not available 
			constexpr Result 			IO_NOPROTOOPT                                                      ((int32_t)0xE701007DL);

			// Machine is not on the network 
			constexpr Result 			IO_NONET                                                           ((int32_t)0xE701007EL);

			// Operation not supported on socket 
			constexpr Result 			IO_OPNOTSUPP                                                       ((int32_t)0xE701007FL);

			// An invalid value was provided for the ai_flags member of the pHints parameter. 
			constexpr Result 			IO_BADFLAGS                                                        ((int32_t)0xE7010080L);

			// Bad network family 
			constexpr Result 			IO_FAMILY                                                          ((int32_t)0xE7010081L);

			// The pServiceName parameter is not supported for the specified ai_socktype member of the pHints parameter. 
			constexpr Result 			IO_INVALID_SERVICE                                                 ((int32_t)0xE7010082L);

			// Invalid network address 
			constexpr Result 			IO_INVALID_ADDRESS                                                 ((int32_t)0xE7010083L);

			// Address in use 
			constexpr Result 			IO_ADDRINUSE                                                       ((int32_t)0xE7010084L);

			// Network Message not expected packet data 
			constexpr Result 			IO_BADPACKET                                                       ((int32_t)0xE7010085L);

			// Disconnected 
			constexpr Result 			IO_DISCONNECTED                                                    ((int32_t)0xE7010086L);

			// Canceled 
			constexpr Result 			IO_CANCELED                                                        ((int32_t)0xE7010087L);

			// Zookeeper System and server-side errors. 
			constexpr Result 			ZK_SYSTEM                                                          ((int32_t)0xE7010088L);

			// Zookeeper  A runtime inconsistency was found 
			constexpr Result 			ZK_ZRUNTIMEINCONSISTENCY                                           ((int32_t)0xE7010089L);

			// Zookeeper A data inconsistency was found 
			constexpr Result 			ZK_ZDATAINCONSISTENCY                                              ((int32_t)0xE701008AL);

			// Zookeeper Connection to the server has been lost 
			constexpr Result 			ZK_ZCONNECTIONLOSS                                                 ((int32_t)0xE701008BL);

			// Zookeeper Error while marshalling or unmarshalling data 
			constexpr Result 			ZK_ZMARSHALLINGERROR                                               ((int32_t)0xE701008CL);

			// Zookeeper Operation is unimplemented 
			constexpr Result 			ZK_ZUNIMPLEMENTED                                                  ((int32_t)0xE701008DL);

			// Zookeeper Operation timeout 
			constexpr Result 			ZK_ZOPERATIONTIMEOUT                                               ((int32_t)0xE701008EL);

			// Zookeeper Invalid arguments 
			constexpr Result 			ZK_ZBADARGUMENTS                                                   ((int32_t)0xE701008FL);

			// Zookeeper Invliad zhandle state 
			constexpr Result 			ZK_ZINVALIDSTATE                                                   ((int32_t)0xE7010090L);

			// Zookeeper API errors. 
			constexpr Result 			ZK_ZAPIERROR                                                       ((int32_t)0xE7010091L);

			// Zookeeper Node does not exist 
			constexpr Result 			ZK_ZNONODE                                                         ((int32_t)0xE7010092L);

			// Zookeeper Not authenticated 
			constexpr Result 			ZK_ZNOAUTH                                                         ((int32_t)0xE7010093L);

			// Zookeeper Version conflict 
			constexpr Result 			ZK_ZBADVERSION                                                     ((int32_t)0xE7010094L);

			// Zookeeper Ephemeral nodes may not have children 
			constexpr Result 			ZK_ZNOCHILDRENFOREPHEMERALS                                        ((int32_t)0xE7010095L);

			// Zookeeper The node already exists 
			constexpr Result 			ZK_ZNODEEXISTS                                                     ((int32_t)0xE7010096L);

			// Zookeeper The node has children 
			constexpr Result 			ZK_ZNOTEMPTY                                                       ((int32_t)0xE7010097L);

			// Zookeeper The session has been expired by the server 
			constexpr Result 			ZK_ZSESSIONEXPIRED                                                 ((int32_t)0xE7010098L);

			// Zookeeper Invalid callback specified 
			constexpr Result 			ZK_ZINVALIDCALLBACK                                                ((int32_t)0xE7010099L);

			// Zookeeper Invalid ACL specified 
			constexpr Result 			ZK_ZINVALIDACL                                                     ((int32_t)0xE701009AL);

			// Zookeeper Client authentication failed 
			constexpr Result 			ZK_ZAUTHFAILED                                                     ((int32_t)0xE701009BL);

			// Zookeeper Zookeeper is closing 
			constexpr Result 			ZK_ZCLOSING                                                        ((int32_t)0xE701009CL);

			// Zookeeper (not error) no server responses to process 
			constexpr Result 			ZK_ZNOTHING                                                        ((int32_t)0xE701009DL);

			// Zookeeper session moved to another server, so operation is ignored 
			constexpr Result 			ZK_ZSESSIONMOVED                                                   ((int32_t)0xE701009EL);

			// End of stream 
			constexpr Result 			END_OF_STREAM                                                      ((int32_t)0xE701009FL);

			// End of file 
			constexpr Result 			END_OF_FILE                                                        ((int32_t)0xE70100A0L);

			// Out of reserved memory 
			constexpr Result 			OUT_OF_RESERVED_MEMORY                                             ((int32_t)0xE70100A1L);

			// The object not initialized or opened 
			constexpr Result 			NOT_OPENED                                                         ((int32_t)0xE70100A2L);

			// Operation is canceled 
			constexpr Result 			SUCCESS_CANCELED                                                   ((int32_t)0x270100A3L);

			// Operation is not supported 
			constexpr Result 			NOT_SUPPORTED                                                      ((int32_t)0xE70100A4L);

			// Format is not supported 
			constexpr Result 			NOT_SUPPORTED_FORMAT                                               ((int32_t)0xE70100A5L);

			// Format is not valid 
			constexpr Result 			INVALID_FORMAT                                                     ((int32_t)0xE70100A6L);

			// Failed to open file 
			constexpr Result 			INVALID_FILE                                                       ((int32_t)0xE70100A7L);

			// Specific variable not found 
			constexpr Result 			VARIABLE_NOT_FOUND                                                 ((int32_t)0xE70100A8L);

			// Specific function not found 
			constexpr Result 			FUNCTION_NOT_FOUND                                                 ((int32_t)0xE70100A9L);

			// Specific object not found 
			constexpr Result 			OBJECT_NOT_FOUND                                                   ((int32_t)0xE70100AAL);

			// Invalid stream ID 
			constexpr Result 			INVALID_STREAMID                                                   ((int32_t)0xE70100ABL);

			// Generic DB failure 
			constexpr Result 			DB_FAILURE                                                         ((int32_t)0xE70100ACL);

	}//namespace ResultCode 
}//namespace SF 





