#ifndef __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__
#define __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__

#include "mem/cache/replacement_policies/base.hh"
#include "base/types.hh"          // Tick / MaxTick

/** 每條 cache block 的私有資料 */
struct FrequencyReplData : public ReplacementData
{
    uint32_t freq;      ///< 存取次數 (hit+miss)
    Tick     insertTick;///< 最近一次 reset() 的時間戳

    FrequencyReplData() : freq(0), insertTick(MaxTick) {}
};

/** Frequency-Based Replacement Policy  
 *  Victim 規則：freq 最小；若相同選 insertTick 最早
 */
class FrequencyRP : public BaseReplacementPolicy
{
  public:
    FrequencyRP(const Params *p);

    ReplaceableEntry*
        getVictim(const ReplacementCandidates& cands) const override;

    void touch      (const std::shared_ptr<ReplacementData>& data) const override;
    void reset      (const std::shared_ptr<ReplacementData>& data) const override;
    void invalidate (const std::shared_ptr<ReplacementData>& data) const override;

    std::shared_ptr<ReplacementData> instantiateEntry() override;
};

#endif // __MEM_CACHE_REPLACEMENT_POLICIES_FREQUENCY_RP_HH__

