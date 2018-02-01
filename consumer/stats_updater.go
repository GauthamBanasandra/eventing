package consumer

import (
	"time"
)

func newVbProcessingStats(appName string, numVbuckets uint16) vbStats {
	vbsts := make(vbStats, numVbuckets)
	for i := uint16(0); i < numVbuckets; i++ {
		vbsts[i] = &vbStat{
			stats: make(map[string]interface{}),
		}
		vbsts[i].stats["dcp_stream_status"] = dcpStreamStopped
		vbsts[i].stats["assigned_worker"] = ""
		vbsts[i].stats["requesting_worker"] = ""

		vbsts[i].stats["plasma_last_seq_no_stored"] = uint64(0)
		vbsts[i].stats["plasma_last_seq_no_persisted"] = uint64(0)

		vbsts[i].stats["currently_processed_doc_id_timer"] = time.Now().UTC().Format(time.RFC3339)
		vbsts[i].stats["doc_id_timer_processing_worker"] = ""
		vbsts[i].stats["last_processed_doc_id_timer_event"] = time.Now().UTC().Format(time.RFC3339)
		vbsts[i].stats["next_doc_id_timer_to_process"] = time.Now().UTC().Add(time.Second).Format(time.RFC3339)

		vbsts[i].stats["next_cron_timer_to_process"] = time.Now().UTC().Add(time.Second).Format(time.RFC3339)
		vbsts[i].stats["currently_processed_cron_timer"] = time.Now().UTC().Add(time.Second).Format(time.RFC3339)
		vbsts[i].stats["last_processed_cron_timer_event"] = time.Now().UTC().Add(time.Second).Format(time.RFC3339)

		// Doc timer debug stats
		vbsts[i].stats["copied_during_rebalance_counter"] = uint64(0)
		vbsts[i].stats["deleted_during_cleanup_counter"] = uint64(0)
		vbsts[i].stats["removed_during_rebalance_counter"] = uint64(0)
		vbsts[i].stats["sent_to_worker_counter"] = uint64(0)
		vbsts[i].stats["timer_create_counter"] = uint64(0)
		vbsts[i].stats["timers_in_past_counter"] = uint64(0)
		vbsts[i].stats["transferred_during_rebalance_counter"] = uint64(0)
	}
	return vbsts
}

func (vbs vbStats) getVbStat(vb uint16, statName string) interface{} {
	vbstat := vbs[vb]
	vbstat.RLock()
	defer vbstat.RUnlock()
	return vbstat.stats[statName]
}

func (vbs vbStats) updateVbStat(vb uint16, statName string, val interface{}) {
	vbstat := vbs[vb]
	vbstat.Lock()
	defer vbstat.Unlock()
	vbstat.stats[statName] = val
}

func (vbs vbStats) copyVbStats(numVbuckets uint16) vbStats {
	vbsts := make(vbStats, numVbuckets)
	for i := uint16(0); i < numVbuckets; i++ {
		vbsts[i] = &vbStat{
			stats: make(map[string]interface{}),
		}

		// params to copy over
		vbsts[i].stats["assigned_worker"] = vbs.getVbStat(i, "assigned_worker")
		vbsts[i].stats["current_vb_owner"] = vbs.getVbStat(i, "current_vb_owner")
		vbsts[i].stats["currently_processed_doc_id_timer"] = vbs.getVbStat(i, "currently_processed_doc_id_timer")
		vbsts[i].stats["currently_processed_cron_timer"] = vbs.getVbStat(i, "currently_processed_cron_timer")
		vbsts[i].stats["dcp_stream_status"] = vbs.getVbStat(i, "dcp_stream_status")

		vbsts[i].stats["doc_id_timer_processing_worker"] = vbs.getVbStat(i, "doc_id_timer_processing_worker")
		vbsts[i].stats["last_processed_doc_id_timer_event"] = vbs.getVbStat(i, "last_processed_doc_id_timer_event")
		vbsts[i].stats["next_doc_id_timer_to_process"] = vbs.getVbStat(i, "next_doc_id_timer_to_process")

		vbsts[i].stats["last_processed_seq_no"] = vbs.getVbStat(i, "last_processed_seq_no")

		vbsts[i].stats["next_cron_timer_to_process"] = vbs.getVbStat(i, "next_cron_timer_to_process")
		vbsts[i].stats["last_processed_cron_timer_event"] = vbs.getVbStat(i, "last_processed_cron_timer_event")

		vbsts[i].stats["node_uuid"] = vbs.getVbStat(i, "node_uuid")
		vbsts[i].stats["plasma_last_persisted_seq_no"] = vbs.getVbStat(i, "plasma_last_persisted_seq_no")

		vbsts[i].stats["copied_during_rebalance_counter"] = vbs.getVbStat(i, "copied_during_rebalance_counter")
		vbsts[i].stats["deleted_during_cleanup_counter"] = vbs.getVbStat(i, "deleted_during_cleanup_counter")
		vbsts[i].stats["removed_during_rebalance_counter"] = vbs.getVbStat(i, "removed_during_rebalance_counter")
		vbsts[i].stats["sent_to_worker_counter"] = vbs.getVbStat(i, "sent_to_worker_counter")
		vbsts[i].stats["timer_create_counter"] = vbs.getVbStat(i, "timer_create_counter")
		vbsts[i].stats["timers_in_past_counter"] = vbs.getVbStat(i, "timers_in_past_counter")
		vbsts[i].stats["transferred_during_rebalance_counter"] = vbs.getVbStat(i, "transferred_during_rebalance_counter")
	}
	return vbsts
}

func (c *Consumer) updateWorkerStats() {
	for {
		select {
		case <-c.updateStatsTicker.C:
			c.dcpEventsRemainingToProcess()
			c.sendGetExecutionStats(false)
			c.sendGetFailureStats(false)
			c.sendGetLatencyStats(false)
			c.sendGetLcbExceptionStats(false)

		case <-c.updateStatsStopCh:
			return
		}
	}
}
