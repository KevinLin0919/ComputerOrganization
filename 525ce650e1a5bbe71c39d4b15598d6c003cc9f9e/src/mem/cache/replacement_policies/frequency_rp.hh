#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__

#include "mem/cache/replacement_policies/base.hh"

namespace gem5 {
namespace replacement_policy {

struct FrequencyEntry : public ReplacementData {
    int frequency;

    FrequencyEntry() : frequency(0) {}
};

class FrequencyRP : public BaseReplacementPolicy {
  public:
    FrequencyRP() = default;
    ~FrequencyRP() = default;

    void invalidate(const std::shared_ptr<ReplacementData>& replacement_data) override;
    void touch(const std::shared_ptr<ReplacementData>& replacement_data) const override;
    void reset(const std::shared_ptr<ReplacementData>& replacement_data) const override;
    ReplaceableEntry* getVictim(const ReplacementCandidates& candidates) const override;
    std::shared_ptr<ReplacementData> instantiateEntry() override;
};

} // namespace replacement_policy
} // namespace gem5

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__
