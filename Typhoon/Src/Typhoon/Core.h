#pragma once

#define uint8 unsigned char
#define uint16 unsigned short
#define uint32 unsigned int
#define uint64 unsigned int64_t

#define int8 char
#define int16 short
#define int32 int
#define int64 int64_t

#define uchar unsigned char
#define ushort unsigned short

#define BIT(x) (1 << x)

#ifdef TE_ASSERTS
	#define TE_ASSERT( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
	#define TE_VERIFY( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
#else
	#define TE_ASSERT( x, ... ) 
	#define TE_VERIFY( x, ... ) x 
#endif	//TE_ENABLE_ASSERTS

#define BIND_CB_FUNC(x) std::bind(x, this, std::placeholders::_1)
