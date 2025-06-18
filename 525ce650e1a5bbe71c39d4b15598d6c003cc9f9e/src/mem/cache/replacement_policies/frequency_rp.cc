#include "mem/cache/replacement_policies/frequency_rp.hh"

namespace gem5 {
namespace replacement_policy {

void
FrequencyRP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
{
    std::static_pointer_cast<FrequencyEntry>(replacement_data)->frequency = 0;
}

void
FrequencyRP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::static_pointer_cast<FrequencyEntry>(replacement_data)->frequency++;
}

void
FrequencyRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::static_pointer_cast<FrequencyEntry>(replacement_data)->frequency = 1;
}

ReplaceableEntry*
FrequencyRP::getVictim(const ReplacementCandidates& candidates) const
{
    auto victim = candidates[0];
    int min_freq = std::static_pointer_cast<FrequencyEntry>(victim->replacementData)->frequency;

    for (const auto& candidate : candidates) {
        auto freq = std::static_pointer_cast<FrequencyEntry>(candidate->replacementData)->frequency;
        if (freq < min_freq) {
            victim = candidate;
            min_freq = freq;
        }
    }
    return victim;
}

std::shared_ptr<ReplacementData>
FrequencyRP::instantiateEntry()
{
    return std::make_shared<FrequencyEntry>();
}

} // namespace replacement_policy
} // namespace gem5
