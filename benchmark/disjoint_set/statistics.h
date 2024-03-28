#include <cstdint>
#include <sstream>

namespace disjoint_set_benchmark {
struct Statistics {
  int32_t distinct_blocks;
  int32_t cycles;
  int32_t total_path_length;
  int32_t full_compression_total_pointers_update;
  int32_t path_splitting_total_pointers_update;
  int32_t path_halving_total_pointers_update;
  int32_t counter;

  Statistics()
      : distinct_blocks(0),
        cycles(0),
        total_path_length(0),
        full_compression_total_pointers_update(0),
        path_splitting_total_pointers_update(0),
        path_halving_total_pointers_update(0),
        counter(0) {}

  void Update(int32_t cycles, int32_t distinct_blocks,
              int32_t total_path_length,
              int32_t full_compression_total_pointers_update,
              int32_t path_splitting_total_pointers_update,
              int32_t path_halving_total_pointers_update) {
    this->cycles += cycles;
    this->distinct_blocks += distinct_blocks;
    this->total_path_length += total_path_length;
    this->full_compression_total_pointers_update +=
        full_compression_total_pointers_update;
    this->path_splitting_total_pointers_update +=
        path_splitting_total_pointers_update;
    this->path_halving_total_pointers_update +=
        path_halving_total_pointers_update;
    this->counter++;
  }

  std::string ToString(int32_t normalization_size) const {
    auto TPL = total_path_length / counter;
    auto TPUFC = full_compression_total_pointers_update / counter;
    auto TPUPS = path_splitting_total_pointers_update / counter;
    auto TPUPH = path_halving_total_pointers_update / counter;

    std::ostringstream oss;
    oss << distinct_blocks / counter << " |" << cycles / counter << " | " << TPL
        << " | " << TPUFC << " | " << TPUPS << " | " << TPUPH << " | "
        << static_cast<double>(TPL) / normalization_size << " | "
        << static_cast<double>(TPUFC) / normalization_size << " | "
        << static_cast<double>(TPUPS) / normalization_size << " | "
        << static_cast<double>(TPUPH) / normalization_size << " |";
    return oss.str();
  }
};
}  // namespace disjoint_set_benchmark