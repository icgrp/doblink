#include <backends/cxxrtl/cxxrtl.h>

#if defined(CXXRTL_INCLUDE_CAPI_IMPL) || \
    defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_capi.cc>
#endif

#if defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_vcd_capi.cc>
#endif

using namespace cxxrtl_yosys;

namespace cxxrtl_design {

// \top: 1
// \src: blink.v:1.2-10.11
struct p_blink : public module {
	// \init: 0
	// \src: blink.v:3.17-3.24
	wire<12> p_counter {0u};
	// \src: blink.v:1.33-1.36
	/*output*/ value<1> p_led;
	// \src: blink.v:1.21-1.24
	/*input*/ value<1> p_clk;
	value<1> prev_p_clk;
	bool posedge_p_clk() const {
		return !prev_p_clk.slice<0>().val() && p_clk.slice<0>().val();
	}
	p_blink() {}
	p_blink(adopt, p_blink other) {}

	void reset() override {
		*this = p_blink(adopt {}, std::move(*this));
	}

	bool eval() override;
	bool commit() override;

	void debug_eval();

	void debug_info(debug_items &items, std::string path = "") override;
}; // struct p_blink

bool p_blink::eval() {
	bool converged = true;
	bool posedge_p_clk = this->posedge_p_clk();
	// cells $procdff$4 $add$blink.v:6$2
	if (posedge_p_clk) {
		p_counter.next = add_uu<12>(p_counter.curr, value<1>{0x1u});
	}
	// connection
	p_led = p_counter.curr.slice<7>().val();
	return converged;
}

bool p_blink::commit() {
	bool changed = false;
	if (p_counter.commit()) changed = true;
	prev_p_clk = p_clk;
	return changed;
}

void p_blink::debug_eval() {
}

CXXRTL_EXTREMELY_COLD
void p_blink::debug_info(debug_items &items, std::string path) {
	assert(path.empty() || path[path.size() - 1] == ' ');
	items.add(path + "counter", debug_item(p_counter, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "led", debug_item(p_led, 0, debug_item::OUTPUT|debug_item::DRIVEN_COMB));
	items.add(path + "clk", debug_item(p_clk, 0, debug_item::INPUT|debug_item::UNDRIVEN));
}

} // namespace cxxrtl_design

extern "C"
cxxrtl_toplevel cxxrtl_design_create() {
	return new _cxxrtl_toplevel { std::unique_ptr<cxxrtl_design::p_blink>(new cxxrtl_design::p_blink) };
}
