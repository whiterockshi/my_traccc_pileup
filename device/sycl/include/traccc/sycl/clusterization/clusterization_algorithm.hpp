/** TRACCC library, part of the ACTS project (R&D line)
 *
 * (c) 2022 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

// SYCL library include(s).
#include "traccc/sycl/utils/queue_wrapper.hpp"

// Project include(s).
#include "traccc/edm/alt_cell.hpp"
#include "traccc/edm/alt_measurement.hpp"
#include "traccc/edm/cluster.hpp"
#include "traccc/edm/measurement.hpp"
#include "traccc/edm/spacepoint.hpp"
#include "traccc/utils/algorithm.hpp"
#include "traccc/utils/memory_resource.hpp"

// VecMem include(s).
#include <vecmem/utils/copy.hpp>

// System include(s).
#include <memory>

namespace traccc::sycl {

class clusterization_algorithm
    : public algorithm<spacepoint_collection_types::buffer(
          const alt_cell_collection_types::const_view&,
          const cell_module_collection_types::const_view&)> {

    public:
    /// Constructor for clusterization algorithm
    ///
    /// @param mr is a struct of memory resources (shared or host & device)
    /// @param queue is a wrapper for the for the sycl queue for kernel
    /// invocation
    /// @param target_cells_per_partition the average number of cells in each
    /// partition
    clusterization_algorithm(const traccc::memory_resource& mr,
                             queue_wrapper queue,
                             const unsigned short target_cells_per_partition);

    /// @param cells        a collection of cells
    /// @param modules      a collection of modules
    /// @return a spacepoint collection (buffer)
    output_type operator()(
        const alt_cell_collection_types::const_view& cells,
        const cell_module_collection_types::const_view& modules) const override;

    private:
    /// The average number of cells in each partition
    unsigned short m_target_cells_per_partition;

    traccc::memory_resource m_mr;
    mutable queue_wrapper m_queue;
    std::unique_ptr<vecmem::copy> m_copy;
};

}  // namespace traccc::sycl