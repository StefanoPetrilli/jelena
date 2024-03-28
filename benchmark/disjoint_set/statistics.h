#include <cstdint>
#include <sstream>

namespace disjoint_set_benchmark {
struct Statistics {
  int16_t distinct_blocks;
  int16_t cycles;
  int16_t total_path_length;
  int16_t full_compression_total_pointers_update;
  int16_t path_splitting_total_pointers_update;
  int16_t path_halving_total_pointers_update;
  int16_t counter;

  Statistics()
      : distinct_blocks(0),
        cycles(0),
        total_path_length(0),
        full_compression_total_pointers_update(0),
        path_splitting_total_pointers_update(0),
        path_halving_total_pointers_update(0),
        counter(0) {}

  void update(int16_t cycles, int16_t distinct_blocks,
              int16_t total_path_length,
              int16_t full_compression_total_pointers_update,
              int16_t path_splitting_total_pointers_update,
              int16_t path_halving_total_pointers_update) {
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

  std::string ToString() const {
    std::ostringstream oss;
    oss << distinct_blocks / counter << " |" << cycles / counter << " | "
        << total_path_length / counter << " | "
        << full_compression_total_pointers_update / counter << " | "
        << path_splitting_total_pointers_update / counter << " | "
        << path_halving_total_pointers_update / counter << " |";
    return oss.str();
  }
};
}  // namespace disjoint_set_benchmark