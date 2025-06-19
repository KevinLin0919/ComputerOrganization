/*******************************************************
 *  Frequency-Based Replacement Policy – 實作檔          *
 *******************************************************/
#include "mem/cache/replacement_policies/frequency_rp.hh"

#include <cassert>
#include <limits>

#include "base/trace.hh"
#include "debug/CacheRepl.hh"
#include "params/FrequencyRP.hh"     // SCons 自動產生的 Params

/*--------------- 建構子 ----------------*/
FrequencyRP::FrequencyRP(const Params *p)
    : BaseReplacementPolicy(p)
{}

/*--------------- line 失效 --------------*/
void
FrequencyRP::invalidate(const std::shared_ptr<ReplacementData>& data) const
{
    auto d = std::static_pointer_cast<FrequencyReplData>(data);
    d->freq       = 0;
    d->insertTick = curTick();
}

/*--------------- 每次 access ------------*/
void
FrequencyRP::touch(const std::shared_ptr<ReplacementData>& data) const
{
    auto d = std::static_pointer_cast<FrequencyReplData>(data);
    if (d->freq != std::numeric_limits<uint32_t>::max())
        ++d->freq;
}

/*--------------- 安裝新 line ------------*/
void
FrequencyRP::reset(const std::shared_ptr<ReplacementData>& data) const
{
    auto d = std::static_pointer_cast<FrequencyReplData>(data);
    d->freq       = 1;
    d->insertTick = curTick();
}

/*--------------- 選擇犧牲者 -------------*/
ReplaceableEntry*
FrequencyRP::getVictim(const ReplacementCandidates& cands) const
{
    assert(!cands.empty());

    ReplaceableEntry* victim = cands[0];
    auto vData = std::static_pointer_cast<FrequencyReplData>(victim->replacementData);

    for (auto& entry : cands) {
        auto eData = std::static_pointer_cast<FrequencyReplData>(entry->replacementData);

        bool betterFreq    =  eData->freq <  vData->freq;
        bool sameFreqOlder = (eData->freq == vData->freq) &&
                             (eData->insertTick < vData->insertTick);

        if (betterFreq || sameFreqOlder) {
            victim = entry;
            vData  = eData;
        }
    }
    return victim;
}

/*--------------- 產生 per-line data -----*/
std::shared_ptr<ReplacementData>
FrequencyRP::instantiateEntry()
{
    return std::make_shared<FrequencyReplData>();
}

/*--------------- SimObject glue --------*/
FrequencyRP*
FrequencyRPParams::create()
{
    return new FrequencyRP(this);
}

