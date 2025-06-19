# Gem5 快取策略切換說明

本專案目前版本為 **Write-Through** 與 **Basic Replacement Policy**。  
若要切換為 **Write-Back** 或 **Frequency-Based Replacement Policy**，請依照下列步驟修改並重新編譯。

---

## 目錄
<pre>
1. [切換到 Write-Back 模式]<br>
   註解掉base.cc中以下程式碼<br>
   if (blk->isWritable()){<br>
 	    PacketPtr writeclean_pkt = writecleanBlk(blk, pkt->req->getDest(), pkt->id);<br>
 	    writebacks.push_back(writeclean_pkt);<br>
  }<br>
2. [切換到 Frequency-Based Replacement Policy] <br>
   註解掉Caches.py中以下程式碼<br>
   replacement_policy = FrequencyRP()<br>
</pre>


