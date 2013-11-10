#ifndef  MD5H
#define  MD5H

namespace  md5
{
	#ifndef uint8
	#define uint8   unsigned char
	#endif

	#ifndef uint32
	#define uint32  unsigned long int
	#endif

	class Get_md5
	{
	public:
		char *  operator () (char * buff,unsigned int len);
		char* 	ByteToCSTR	(const unsigned char * isx,unsigned int len);
	private:
		typedef struct
		{
		uint32 total[ 2 ];
		uint32 state[ 4 ];
		uint8 buffer[ 64 ];
		}
		md5_context;

		static uint8 md5_padding[64];

		void  md5_starts( md5_context *ctx );
		void  md5_process( md5_context *ctx, uint8 data[64 ] );

		void  md5_update( md5_context *ctx, uint8 *input, uint32 length );
		void  md5_finish( md5_context *ctx, uint8 digest[16 ] );

	};

uint8 Get_md5::md5_padding[64]={ 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

#endif  /* md5.h */
