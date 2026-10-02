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

namespace expr_impl
{
// ======================| Node & Parameter type declarations |======================

namespace custom
{

struct expr_
{
	static float op(float input, float value)
	{
		return (input > 0.0)
		? (input * 500.0) / (1.05 + Math.abs(input * 50.0))
		: (input * 200.0) / (0.05 + Math.abs(input * 50.0))
		+ (Math.sin(input * 0.35) * 0.5);
	}
};
}

namespace expr_t_parameters
{
}

template <int NV>
using expr_t_ = container::chain<parameter::plain<math::expr<NV, custom::expr_>, 0>, 
                                 wrap::fix<2, math::expr<NV, custom::expr_>>>;

// ==========================| Root node initialiser class |==========================

template <int NV> struct instance: public expr_impl::expr_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(expr);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(16)
		{
			0x005B, 0x0000, 0x5600, 0x6C61, 0x6575, 0x0000, 0x0000, 0x0000, 
            0x8000, 0x003F, 0x8000, 0x003F, 0x8000, 0x003F, 0x0000, 0x0000
		};
	};
	
	instance()
	{
		// Node References ----------------------------------------------------------
		
		auto& expr_ = this->getT(0); // math::expr<NV, custom::expr_>
		
		// Parameter Connections ----------------------------------------------------
		
		this->getParameterT(0).connectT(0, expr_); // Value -> expr_::Value
		
		// Default Values -----------------------------------------------------------
		
		; // expr_::Value is automated
		
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
// ===============================| Public Definition |===============================

namespace project
{
// polyphonic template declaration

template <int NV>
using expr = wrap::node<expr_impl::instance<NV>>;
}


