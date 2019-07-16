#pragma once

#define BIT(x) (1 << x)

#ifdef TE_ASSERTS
	#define TE_ASSERT( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
	#define TE_VERIFY( x, ... ) { if ( (!x) ) { TE_ERROR( "Assertion Failed {0}", __VA_ARGS__ ); __debugbreak(); } }
#else
	#define TE_ASSERT( x, ... ) 
	#define TE_VERIFY( x, ... ) x 
#endif	//TE_ENABLE_ASSERTS

#define BIND_CB_FUNC(x) std::bind(x, this, std::placeholders::_1)
