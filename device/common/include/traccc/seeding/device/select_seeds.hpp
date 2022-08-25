// Project include(s).
#include "traccc/definitions/qualifiers.hpp"
#include "traccc/device/get_prefix_sum.hpp"
#include "traccc/edm/device/doublet_counter.hpp"
#include "traccc/edm/seed.hpp"
#include "traccc/seeding/detail/seeding_config.hpp"
#include "traccc/seeding/detail/spacepoint_grid.hpp"
#include "traccc/seeding/detail/triplet.hpp"

// System include(s).
#include <cassert>
#include <cstddef>

namespace traccc::device {

/// Function used for selecting good triplets to be recorded into seed container
///
/// @param[in] globalIndex   The index of the current thread
/// @param[in] filter_config seed filter config
/// @param[in] sp_view vecmem container for internal spacepoint
/// @param[in] dc_prefix_sum view of the vector prefix sum on
/// doublet_counter_container
/// @param[in] doublet_counter_container vecmem container for doublet_counter
/// @param[in] triplet_container vecmem container for triplets
/// @param seed_container vecmem container for seeds
///
TRACCC_HOST_DEVICE
void select_seeds(
    const std::size_t globalIndex, const seedfilter_config& filter_config,
    const spacepoint_container_types::const_view& spacepoints_view,
    const sp_grid_const_view& internal_sp_view,
    const vecmem::data::vector_view<const prefix_sum_element_t>& dc_ps_view,
    const device::doublet_counter_container_types::const_view&
        doublet_counter_container,
    const triplet_container_view& tc_view,
    vecmem::data::vector_view<seed> seed_view);

}  // namespace traccc::device

// Include the implementation.
#include "traccc/seeding/device/impl/select_seeds.ipp"