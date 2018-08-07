package producer

import (
	"net"

	"github.com/couchbase/eventing/common"
	"github.com/couchbase/eventing/dcp"
	"github.com/couchbase/eventing/logging"
	"github.com/couchbase/eventing/util"
	"github.com/couchbase/gocb"
)

var commonConnectBucketOpCallback = func(args ...interface{}) error {
	logPrefix := "Producer::commonConnectBucketOpCallback"

	p := args[0].(*Producer)
	b := args[1].(**couchbase.Bucket)

	hostPortAddr := net.JoinHostPort(util.Localhost(), p.GetNsServerPort())

	var err error
	*b, err = util.ConnectBucket(hostPortAddr, "default", p.metadatabucket)
	if err != nil {
		logging.Errorf("%s [%s:%d] Connect to bucket: %s failed, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket, err)
	} else {
		logging.Infof("%s [%s:%d] Connected to bucket: %s",
			logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket)
	}

	return err
}

var getFailoverLogOpCallback = func(args ...interface{}) error {
	logPrefix := "Producer::getFailoverLogOpCallback"

	p := args[0].(*Producer)
	b := args[1].(**couchbase.Bucket)
	flogs := args[2].(*couchbase.FailoverLog)
	vbs := args[3].([]uint16)

	var err error
	*flogs, err = (*b).GetFailoverLogs(0xABCD, vbs, p.dcpConfig)
	if err != nil {
		logging.Errorf("%s [%s:%d] Failed to get failover logs, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), err)
	}

	return err
}

var startFeedCallback = func(args ...interface{}) error {
	logPrefix := "Producer::startFeedCallback"

	p := args[0].(*Producer)
	b := args[1].(**couchbase.Bucket)
	dcpFeed := args[2].(**couchbase.DcpFeed)
	kvNodeAddrs := args[3].([]string)

	feedName := couchbase.NewDcpFeedName(p.uuid + "_" + p.appName + "_undeploy")

	var err error
	*dcpFeed, err = (*b).StartDcpFeedOver(feedName, uint32(0), 0, kvNodeAddrs, 0xABCD, p.dcpConfig)
	if err != nil {
		logging.Errorf("%s [%s:%d] Failed to start dcp feed for bucket: %v, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket, err)
	}

	return err
}

var dcpGetSeqNosCallback = func(args ...interface{}) error {
	logPrefix := "Producer::dcpGetSeqNosCallback"

	p := args[0].(*Producer)
	dcpFeed := args[1].(**couchbase.DcpFeed)
	vbSeqNos := args[2].(*map[uint16]uint64)

	var err error
	*vbSeqNos, err = (*dcpFeed).DcpGetSeqnos()
	if err != nil {
		logging.Errorf("%s [%s:%d] Failed to get dcp seqnos for metadata bucket: %v, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket, err)
	}

	return err
}

var gocbConnectMetaBucketCallback = func(args ...interface{}) error {
	logPrefix := "Producer::gocbConnectMetaBucketCallback"

	p := args[0].(*Producer)

	if p.isTerminateRunning {
		return nil
	}

	kvNodes := p.KvHostPorts()

	connStr := "couchbase://"
	for index, kvNode := range kvNodes {
		if index != 0 {
			connStr = connStr + ","
		}
		connStr = connStr + kvNode
	}

	if util.IsIPv6() {
		connStr += "?ipv6=allow"
	}

	cluster, err := gocb.Connect(connStr)
	if err != nil {
		logging.Errorf("%s [%s:%d] Connect to cluster %rs failed, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), connStr, err)
		return err
	}

	err = cluster.Authenticate(&util.DynamicAuthenticator{Caller: logPrefix})
	if err != nil {
		logging.Errorf("%s [%s:%d] Failed to authenticate to the cluster %rs failed, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), connStr, err)
		return err
	}

	p.metadataBucketHandle, err = cluster.OpenBucket(p.metadatabucket, "")
	if err != nil {
		logging.Errorf("%s [%s:%d] Failed to connect to bucket %s, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket, err)
		return err
	}

	logging.Infof("%s [%s:%d] Connected to metadata bucket %s connStr: %s",
		logPrefix, p.appName, p.LenRunningConsumers(), p.metadatabucket, connStr)

	return nil
}

var setOpCallback = func(args ...interface{}) error {
	logPrefix := "Producer::setOpCallback"

	p := args[0].(*Producer)
	key := args[1].(common.Key)
	blob := args[2]

	if p.isTerminateRunning {
		return nil
	}

	if p.metadataBucketHandle == nil {
		logging.Errorf("%s [%s:%d] Bucket handle not initialized",
			logPrefix, p.appName, p.LenRunningConsumers())
		return nil
	}

	_, err := p.metadataBucketHandle.Upsert(key.Raw(), blob, 0)
	if err == gocb.ErrShutdown {
		return nil
	} else if err != nil {
		logging.Errorf("%s [%s:%d] Bucket set failed for key: %ru , err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), key.Raw(), err)
	}
	return err
}

var getOpCallback = func(args ...interface{}) error {
	logPrefix := "Producer::getOpCallback"

	p := args[0].(*Producer)
	key := args[1].(common.Key)
	blob := args[2]

	_, err := p.metadataBucketHandle.Get(key.Raw(), blob)
	if gocb.IsKeyNotFoundError(err) || err == gocb.ErrShutdown || err == gocb.ErrKeyNotFound {
		return nil
	} else if err != nil {
		logging.Errorf("%s [%s:%d] Bucket get failed for key: %ru , err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), key.Raw(), err)
	}

	return err
}

var deleteOpCallback = func(args ...interface{}) error {
	logPrefix := "Producer::deleteOpCallback"

	p := args[0].(*Producer)
	key := args[1].(common.Key)

	_, err := p.metadataBucketHandle.Remove(key.Raw(), 0)
	if gocb.IsKeyNotFoundError(err) || err == gocb.ErrShutdown {
		return nil
	} else if err != nil {
		logging.Errorf("%s [%s:%d] Bucket delete failed for key: %ru, err: %v",
			logPrefix, p.appName, p.LenRunningConsumers(), key.Raw(), err)

		// Bucket op fail with generic timeout error even in case of bucket being dropped/deleted.
		// Hence checking for it during routines called during undeploy
		hostAddress := net.JoinHostPort(util.Localhost(), p.GetNsServerPort())

		metaBucketNodeCount := util.CountActiveKVNodes(p.metadatabucket, hostAddress)
		if metaBucketNodeCount == 0 {
			logging.Infof("%s [%s:%d] MetaBucketNodeCount: %d returning",
				logPrefix, p.appName, p.LenRunningConsumers(), metaBucketNodeCount)
			return nil
		}
	}
	return err
}
