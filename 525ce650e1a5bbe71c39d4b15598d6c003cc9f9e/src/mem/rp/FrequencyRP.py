from m5.objects import BaseReplacementPolicy

class FrequencyRP(BaseReplacementPolicy):
    type = 'FrequencyRP'
    cxx_class = 'gem5::replacement_policy::FrequencyRP'
    cxx_header = "mem/cache/replacement_policies/frequency_rp.hh"
