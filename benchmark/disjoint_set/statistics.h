#include <cstdint>
#include <sstream>

namespace disjoint_set_benchmark {
struct Statistics {
  int64_t distinct_blocks;
  int64_t cycles;
  int64_t total_path_length;
  int64_t total_pointers_update;
  int64_t counter;

  Statistics()
      : distinct_blocks(0),
        cycles(0),
        total_path_length(0),
        total_pointers_update(0),
        counter(0) {}

  void Update(int64_t cycles, int64_t distinct_blocks,
              int64_t total_path_length, int64_t total_pointers_update) {
    this->cycles += cycles;
    this->distinct_blocks += distinct_blocks;
    this->total_path_length += total_path_length;
    this->total_pointers_update += total_pointers_update;
    this->counter++;
  }

  std::string ToString(int64_t normalization_size, int16_t epsilon,
                       bool isFC) const {
    int64_t TPL = total_path_length / counter;
    int64_t TPU = total_pointers_update / counter;
    int64_t total_cost;
    if (isFC) {
      total_cost = 2 * TPL + epsilon * TPU;
    } else {
      total_cost = TPL + epsilon * TPU;
    }

    std::ostringstream oss;
    oss << distinct_blocks / counter << " |" << cycles / counter << " | " << TPL
        << " | " << TPU << " | "
        << static_cast<double>(TPL) / normalization_size << " | "
        << static_cast<double>(TPU) / normalization_size << " | " << total_cost
        << " | " << static_cast<double>(total_cost) / normalization_size
        << " |";
    return oss.str();
  }
};
}  // namespace disjoint_set_benchmark