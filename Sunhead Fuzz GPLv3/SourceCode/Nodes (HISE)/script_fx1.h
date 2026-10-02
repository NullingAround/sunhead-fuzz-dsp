#pragma once

#include "expr1.h"
// These will improve the readability of the connection definition

#define getT(Idx) template get<Idx>()
#define connectT(Idx, target) template connect<Idx>(target)
#define getParameterT(Idx) template getParameter<Idx>()
#define setParameterT(Idx, value) template setParameter<Idx>(value)
#define setParameterWT(Idx, value) template setWrapParameter<Idx>(value)
using namespace scriptnode;
using namespace snex;
using namespace snex::Types;

namespace script_fx1_impl
{
// ==============================| Node & Parameter type declarations |==============================

DECLARE_PARAMETER_RANGE_SKEW(dry_wet_mixer_c0Range, 
                             -100., 
                             0., 
                             5.42227);

template <int NV>
using dry_wet_mixer_c0 = parameter::from0To1<core::gain<NV>, 
                                             0, 
                                             dry_wet_mixer_c0Range>;

template <int NV> using dry_wet_mixer_c1 = dry_wet_mixer_c0<NV>;

template <int NV>
using dry_wet_mixer_multimod = parameter::list<dry_wet_mixer_c0<NV>, dry_wet_mixer_c1<NV>>;

template <int NV>
using dry_wet_mixer_t = control::xfader<dry_wet_mixer_multimod<NV>, 
                                        faders::cosine>;

template <int NV>
using dry_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, dry_wet_mixer_t<NV>>, 
                                    core::gain<NV>>;

template <int NV>
using split_t = container::split<parameter::empty, 
                                 wrap::fix<2, filters::ladder<NV>>, 
                                 core::gain<NV>>;

using dry_path2_t = container::chain<parameter::empty, 
                                     wrap::fix<2, core::empty>>;

template <int NV>
using wet_path3_t = container::chain<parameter::empty, 
                                     wrap::fix<2, project::expr1<NV>>, 
                                     core::gain<NV>>;

template <int NV>
using dry_wet3_t = container::split<parameter::empty, 
                                    wrap::fix<2, dry_path2_t>, 
                                    wet_path3_t<NV>>;

template <int NV>
using wet_path_t = container::chain<parameter::empty, 
                                    wrap::fix<2, split_t<NV>>, 
                                    filters::svf_eq<NV>, 
                                    dry_wet3_t<NV>, 
                                    filters::svf_eq<NV>, 
                                    core::gain<NV>>;

template <int NV>
using dry_wet1_t = container::split<parameter::empty, 
                                    wrap::fix<2, dry_path_t<NV>>, 
                                    wet_path_t<NV>>;

namespace script_fx1_t_parameters
{
// Parameter list for script_fx1_impl::script_fx1_t ------------------------------------------------

DECLARE_PARAMETER_RANGE_SKEW_INV(PostTone_InputRange, 
                                 20., 
                                 20000., 
                                 0.229905);
DECLARE_PARAMETER_RANGE_SKEW(PostTone_0Range, 
                             20., 
                             20000., 
                             0.229905);

template <int NV>
using PostTone_0 = parameter::from0To1<filters::svf_eq<NV>, 
                                       0, 
                                       PostTone_0Range>;

template <int NV>
using PostTone = parameter::chain<PostTone_InputRange, PostTone_0<NV>>;

template <int NV>
using DryWet = parameter::plain<script_fx1_impl::dry_wet_mixer_t<NV>, 
                                0>;
template <int NV>
using LPFocus = parameter::plain<filters::svf_eq<NV>, 0>;
template <int NV>
using Drive = parameter::plain<core::gain<NV>, 0>;
template <int NV> using Input = Drive<NV>;
template <int NV> using Output = Drive<NV>;
template <int NV>
using script_fx1_t_plist = parameter::list<DryWet<NV>, 
                                           LPFocus<NV>, 
                                           PostTone<NV>, 
                                           Drive<NV>, 
                                           Input<NV>, 
                                           Output<NV>>;
}

template <int NV>
using script_fx1_t_ = container::chain<script_fx1_t_parameters::script_fx1_t_plist<NV>, 
                                       wrap::fix<2, core::gain<NV>>, 
                                       dry_wet1_t<NV>, 
                                       core::gain<NV>>;

// =================================| Root node initialiser class |=================================

template <int NV> struct instance: public script_fx1_impl::script_fx1_t_<NV>
{
	
	struct metadata
	{
		static const int NumTables = 0;
		static const int NumSliderPacks = 0;
		static const int NumAudioFiles = 0;
		static const int NumFilters = 0;
		static const int NumDisplayBuffers = 0;
		
		SNEX_METADATA_ID(script_fx1);
		SNEX_METADATA_NUM_CHANNELS(2);
		SNEX_METADATA_ENCODED_PARAMETERS(98)
		{
			0x005B, 0x0000, 0x4400, 0x7972, 0x6557, 0x0074, 0x0000, 0x0000, 
            0x0000, 0x3F80, 0x0000, 0x0000, 0x0000, 0x3F80, 0x0000, 0x0000, 
            0x015B, 0x0000, 0x4C00, 0x4650, 0x636F, 0x7375, 0x0000, 0xA000, 
            0x0041, 0x9C40, 0x0046, 0xA000, 0x0041, 0xA000, 0x0040, 0x0000, 
            0x5B00, 0x0002, 0x0000, 0x6F50, 0x7473, 0x6F54, 0x656E, 0x0000, 
            0xA000, 0x0041, 0x9C40, 0x0046, 0xA000, 0x1A41, 0x6B6C, 0x003E, 
            0x0000, 0x5B00, 0x0003, 0x0000, 0x7244, 0x7669, 0x0065, 0x0000, 
            0xC2C8, 0x0000, 0x0000, 0x0000, 0xC2C8, 0x833E, 0x40AD, 0xCCCD, 
            0x3DCC, 0x045B, 0x0000, 0x4900, 0x706E, 0x7475, 0x0000, 0xC000, 
            0x00C1, 0xC000, 0x0041, 0x0000, 0x0000, 0x8000, 0xCD3F, 0xCCCC, 
            0x5B3D, 0x0005, 0x0000, 0x754F, 0x7074, 0x7475, 0x0000, 0xC000, 
            0x00C1, 0xC000, 0x0041, 0x0000, 0x0000, 0x8000, 0xCD3F, 0xCCCC, 
            0x003D, 0x0000
		};
	};
	
	instance()
	{
		// Node References -------------------------------------------------------------------------
		
		auto& gain = this->getT(0);                                  // core::gain<NV>
		auto& dry_wet1 = this->getT(1);                              // script_fx1_impl::dry_wet1_t<NV>
		auto& dry_path = this->getT(1).getT(0);                      // script_fx1_impl::dry_path_t<NV>
		auto& dry_wet_mixer = this->getT(1).getT(0).getT(0);         // script_fx1_impl::dry_wet_mixer_t<NV>
		auto& dry_gain = this->getT(1).getT(0).getT(1);              // core::gain<NV>
		auto& wet_path = this->getT(1).getT(1);                      // script_fx1_impl::wet_path_t<NV>
		auto& split = this->getT(1).getT(1).getT(0);                 // script_fx1_impl::split_t<NV>
		auto& ladder1 = this->getT(1).getT(1).getT(0).getT(0);       // filters::ladder<NV>
		auto& gain1 = this->getT(1).getT(1).getT(0).getT(1);         // core::gain<NV>
		auto& svf_eq1 = this->getT(1).getT(1).getT(1);               // filters::svf_eq<NV>
		auto& dry_wet3 = this->getT(1).getT(1).getT(2);              // script_fx1_impl::dry_wet3_t<NV>
		auto& dry_path2 = this->getT(1).getT(1).getT(2).getT(0);     // script_fx1_impl::dry_path2_t
		auto& wet_path3 = this->getT(1).getT(1).getT(2).getT(1);     // script_fx1_impl::wet_path3_t<NV>
		auto& expr1 = this->getT(1).getT(1).getT(2).getT(1).getT(0); // project::expr1<NV>
		auto& gain2 = this->getT(1).getT(1).getT(2).getT(1).getT(1); // core::gain<NV>
		auto& svf_eq = this->getT(1).getT(1).getT(3);                // filters::svf_eq<NV>
		auto& wet_gain = this->getT(1).getT(1).getT(4);              // core::gain<NV>
		auto& gain3 = this->getT(2);                                 // core::gain<NV>
		
		// Parameter Connections -------------------------------------------------------------------
		
		this->getParameterT(0).connectT(0, dry_wet_mixer); // DryWet -> dry_wet_mixer::Value
		
		this->getParameterT(1).connectT(0, svf_eq1); // LPFocus -> svf_eq1::Frequency
		
		this->getParameterT(2).connectT(0, svf_eq); // PostTone -> svf_eq::Frequency
		
		this->getParameterT(3).connectT(0, gain2); // Drive -> gain2::Gain
		
		this->getParameterT(4).connectT(0, gain); // Input -> gain::Gain
		
		this->getParameterT(5).connectT(0, gain3); // Output -> gain3::Gain
		
		// Modulation Connections ------------------------------------------------------------------
		
		auto& dry_wet_mixer_p = dry_wet_mixer.getWrappedObject().getParameter();
		dry_wet_mixer_p.getParameterT(0).connectT(0, dry_gain); // dry_wet_mixer -> dry_gain::Gain
		dry_wet_mixer_p.getParameterT(1).connectT(0, wet_gain); // dry_wet_mixer -> wet_gain::Gain
		
		// Default Values --------------------------------------------------------------------------
		
		;                           // gain::Gain is automated
		gain.setParameterT(1, 20.); // core::gain::Smoothing
		gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		; // dry_wet_mixer::Value is automated
		
		;                               // dry_gain::Gain is automated
		dry_gain.setParameterT(1, 20.); // core::gain::Smoothing
		dry_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		ladder1.setParameterT(0, 200.);     // filters::ladder::Frequency
		ladder1.setParameterT(1, 0.460671); // filters::ladder::Q
		ladder1.setParameterT(2, 0.);       // filters::ladder::Gain
		ladder1.setParameterT(3, 0.);       // filters::ladder::Smoothing
		ladder1.setParameterT(4, 0.);       // filters::ladder::Mode
		ladder1.setParameterT(5, 1.);       // filters::ladder::Enabled
		
		gain1.setParameterT(0, -6);  // core::gain::Gain
		gain1.setParameterT(1, 20.); // core::gain::Smoothing
		gain1.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                     // svf_eq1::Frequency is automated
		svf_eq1.setParameterT(1, 0.545472);   // filters::svf_eq::Q
		svf_eq1.setParameterT(2, 0.);         // filters::svf_eq::Gain
		svf_eq1.setParameterT(3, 0.00694338); // filters::svf_eq::Smoothing
		svf_eq1.setParameterT(4, 1.);         // filters::svf_eq::Mode
		svf_eq1.setParameterT(5, 1.);         // filters::svf_eq::Enabled
		
		expr1.setParameterT(0, 1.); // project::expr1::Value
		
		;                            // gain2::Gain is automated
		gain2.setParameterT(1, 20.); // core::gain::Smoothing
		gain2.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                                  // svf_eq::Frequency is automated
		svf_eq.setParameterT(1, 0.541714); // filters::svf_eq::Q
		svf_eq.setParameterT(2, -8.976);   // filters::svf_eq::Gain
		svf_eq.setParameterT(3, 0.);       // filters::svf_eq::Smoothing
		svf_eq.setParameterT(4, 3.);       // filters::svf_eq::Mode
		svf_eq.setParameterT(5, 1.);       // filters::svf_eq::Enabled
		
		;                               // wet_gain::Gain is automated
		wet_gain.setParameterT(1, 20.); // core::gain::Smoothing
		wet_gain.setParameterT(2, 0.);  // core::gain::ResetValue
		
		;                            // gain3::Gain is automated
		gain3.setParameterT(1, 20.); // core::gain::Smoothing
		gain3.setParameterT(2, 0.);  // core::gain::ResetValue
		
		this->setParameterT(0, 0.);
		this->setParameterT(1, 20.);
		this->setParameterT(2, 20.);
		this->setParameterT(3, -100.);
		this->setParameterT(4, 0.);
		this->setParameterT(5, 0.);
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
// ======================================| Public Definition |======================================

namespace project
{
// polyphonic template declaration

template <int NV>
using script_fx1 = wrap::node<script_fx1_impl::instance<NV>>;
}


