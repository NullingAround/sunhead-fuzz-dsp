#pragma once

// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace expr1_impl
{
// =======================| Node & Parameter type declarations |=======================

namespace custom
{

struct expr1_
{
	static float op(float input, float value)
	{
		return (input > 0.0)
		? (input * 200.0) / (1.5 + Math.abs(input * 300.0))
		: (input * 200.0) / (0.05 + Math.abs(input * 40.0))
		+ (Math.sin(input * 0.0) * 0.5);
	}
};
}

namespace expr1_t_parameters
{
}

template <int NV>
using expr1_t_ = container::chain<parameter::plain<math::expr<NV, custom::expr1_>, 0>, 
                                  wrap::fix<2, math::expr<NV, custom::expr1_>>>;

// ===========================| Root node initialiser class |===========================

template <int NV> struct instance: public expr1_impl::expr1_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(expr1);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(16)
		{
			0x005B, 0x0000, 0x5600, 0x6C61, 0x6575, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References ------------------------------------------------------------
		
		auto& expr1_ = this->getT(0); // math::expr<NV, custom::expr1_>
		
		// Parameter Connections ------------------------------------------------------
		
		this->getParameterT(0).connectT(0, expr1_); // Value -> expr1_::Value
		
		// Default Values -------------------------------------------------------------
		
		; // expr1_::Value is automated
		
		this->setParameterT(0, 1.);
	}
	
	static constexpr bool isPolyphonic() { return NV > 1; };
	
	static constexpr bool hasTail() { return true; };
	
	static constexpr bool isSuspendedOnSilence() { return false; };
};
}

#undef getT
#undef connectT
#undef setParameterT
#undef setParameterWT
#undef getParameterT
// ================================| Public Definition |================================

namespace project
{
// polyphonic template declaration

template <int NV>
using expr1 = wrap::node<expr1_impl::instance<NV>>;
}


