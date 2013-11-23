#ifndef ROUTER_INFO_H__
#define ROUTER_INFO_H__

#include <inttypes.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <boost/asio.hpp>

namespace i2p
{
namespace data
{		
#pragma pack (1)

	struct RouterIdentity
	{
		uint8_t publicKey[256];
		uint8_t signingKey[128];
		uint8_t certificate[3];
	};
#pragma pack ()	
	
	
	class RouterInfo
	{
		public:

			enum TransportStyle
			{
				eTransportUnknown = 0,
				eTransportNTCP,
				eTransportSSU
			};

			struct Address
			{
				TransportStyle transportStyle;
				std::string host;
				int port;
				uint64_t date;
				uint8_t cost;
			};
			
			RouterInfo (const char * filename);
			RouterInfo () = default;
			RouterInfo (const RouterInfo& ) = default;
			RouterInfo (const uint8_t * buf, int len);
			
			const RouterIdentity& GetRouterIdentity () const { return m_RouterIdentity; };
			void SetRouterIdentity (const RouterIdentity& identity);
			const uint8_t * GetIdentHash () const { return m_IdentHash; };
			const char * GetIdentHashBase64 () const { return m_IdentHashBase64; };
			const std::vector<Address>& GetAddresses () const { return m_Addresses; };
			Address * GetNTCPAddress ();
			
			void AddNTCPAddress (const char * host, int port);
			void SetProperty (const char * key, const char * value);
			const char * GetProperty (const char * key) const;
			bool IsFloodfill () const;
			bool IsNTCP () const;
			
			void CreateBuffer ();
			const char * GetBuffer () const  { return m_Buffer; };
			int GetBufferLen () const { return m_BufferLen; };

			bool IsUpdated () const { return m_IsUpdated; };
			void SetUpdated (bool updated) { m_IsUpdated = updated; }; 
			
		private:

			void ReadFromFile (const char * filename);
			void ReadFromStream (std::istream& s);
			void ReadFromBuffer ();
			void WriteToStream (std::ostream& s);
			size_t ReadString (char * str, std::istream& s);
			void WriteString (const std::string& str, std::ostream& s);
			
		private:

			RouterIdentity m_RouterIdentity;
			uint8_t m_IdentHash[32];
			char m_IdentHashBase64[48];
			char m_Buffer[2048];
			int m_BufferLen;
			uint64_t m_Timestamp;
			std::vector<Address> m_Addresses;
			std::map<std::string, std::string> m_Properties;
			bool m_IsUpdated;
	};	
}	
}

#endif