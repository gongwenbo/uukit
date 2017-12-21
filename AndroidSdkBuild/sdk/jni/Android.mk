#date 11.25 by gong

LOCAL_PATH := $(call my-dir)

# Progam
include $(CLEAR_VARS)

LOCAL_CFLAGS += -DANDROID_PRINT -s -O2

LOCAL_MODULE :=hwsdkc

LOCAL_SRC_FILES :=./app/hwsdk.cpp \
./app/dcp/bhdcp.cpp \
./app/dcp/dcpAudio.cpp \
./app/dcp/dcpCbk.cpp \
./app/dcp/dcpCom.cpp \
./app/dcp/dcpDevCtlFifo.cpp \
./app/dcp/dcpDeviceMaintain.cpp \
./app/dcp/dcpDevId.cpp \
./app/dcp/dcpDevPwrFreq.cpp ./app/dcp/dcpDevStatus.cpp \
./app/dcp/dcpDiskCtl.cpp \
./app/dcp/dcpFileRecv.cpp \
./app/dcp/dcpFuncList.cpp \
./app/dcp/dcpFuncManage.cpp \
./app/dcp/dcpGetPic.cpp ./app/dcp/dcpGetWifilist.cpp \
./app/dcp/dcpIndexToAccount.cpp \
./app/dcp/dcpLocalMsg.cpp \
./app/dcp/dcpMdConf.cpp \
./app/dcp/dcpNetInfo.cpp \
./app/dcp/dcpOsdInfo.cpp \
./app/dcp/dcpOtherCtl.cpp \
./app/dcp/dcpPlayback.cpp \
./app/dcp/dcpPlaybackRecv.cpp \
./app/dcp/dcpRotate.cpp ./app/dcp/dcpSearchRecord.cpp \
./app/dcp/dcpSem.cpp \
./app/dcp/dcpSend.cpp \
./app/dcp/dcpSignal.cpp \
./app/dcp/dcpSplitFrame.cpp \
./app/dcp/dcpStreamRecv.cpp \
./app/dcp/dcpStreamReq.cpp \
./app/dcp/dcpStreamSend.cpp \
./app/dcp/dcpStreamStop.cpp \
./app/dcp/dcpStreamSwith.cpp \
./app/dcp/dcpSwitchKout.cpp \
./app/dcp/dcpTalkBack.cpp \
./app/dcp/dcpUpdate.cpp \
./app/dcp/dcpUt.cpp \
./app/dcp/dcpVarBitrate.cpp \
./app/dcp/dcpVideoBaseParam.cpp \
./app/dcp/dsessidHash.cpp \
./app/dcp/streamFrame.cpp \
./app/p2pc/p2pc.cpp \
./app/p2pc/p2pcFifo.cpp \
./app/test/dcpDeviceSearch.cpp \
./app/test/dcpLogReq.cpp \
./app/test/dcpUpdateFunc.cpp \
./app/test/dcpVideoEncodeParam.cpp \
./app/test/epoll.cpp \
./app/test/ringList.cpp \
./app/test/test.cpp \
./app/test/testDcp.cpp \
./app/test/testDcpCbk.cpp \
./app/test/testDcpSearchRecord.cpp \
./app/test/testDownloadRecord.cpp \
./app/test/testLogout.cpp \
./app/test/testLogReq.cpp \
./app/test/testMessage.cpp \
./app/test/testPcp.cpp \
./app/test/testProcon.cpp \
./app/test/testProconH264Read.cpp \
./app/test/testRand.cpp \
./app/test/testSaveFile.cpp \
./app/test/testStream.cpp \
./app/test/testUpdate.cpp \
./app/test/testWebs.cpp \
./app/test/threadPool.cpp ./app/wifi/multicastFindDev.cpp \
./app/wifi/smartLinkCli.cpp \
./common/base64.cpp \
./common/condition.cpp \
./common/debug.cpp \
./common/fifoList.cpp \
./common/gb2312.cpp \
./common/hash.cpp \
./common/linuxFile.cpp \
./common/md5.cpp \
./common/message.cpp \
./common/mutex.cpp \
./common/mymalloc.cpp \
./common/netSocket.cpp \
./common/rand.cpp \
./common/sem.cpp \
./common/thread.cpp \
./common/timeExchange.cpp \
./common/timer.cpp \
./common/ushortop.cpp \
./public/crc.cpp \
./public/hashLinear.cpp \
./public/hton.cpp \
./public/mc.cpp \
./public/sysRunTime.cpp \
./public/xmlPub.cpp \
./app/mxml/mxml-attr.c \
./app/mxml/mxml-entity.c \
./app/mxml/mxml-file.c \
./app/mxml/mxml-get.c \
./app/mxml/mxml-index.c \
./app/mxml/mxml-node.c \
./app/mxml/mxml-private.c \
./app/mxml/mxml-search.c \
./app/mxml/mxml-set.c \
./app/mxml/mxml-string.c \
./app/mxml/mxmldoc.c \
./app/sound/soundTransferSend.c \
./app/wifi/dateTime.c \
./app/procon/pcp.cpp \
./app/procon/procon.cpp \
./app/procon/proconApp.cpp \
./app/procon/proconH264.cpp \
./app/procon/proconPb.cpp \
./app/webs/UrlEncode.cpp \
./app/webs/webs.cpp \
./app/webs/websAddDev.cpp \
./app/webs/websAddGroup.cpp \
./app/webs/websAddNode.cpp \
./app/webs/websCheckCfgCode.cpp \
./app/webs/websCheckDevId.cpp \
./app/webs/websCheckUserName.cpp \
./app/webs/websCom.cpp \
./app/webs/websDelDev.cpp \
./app/webs/websDelGroup.cpp \
./app/webs/websDelNode.cpp \
./app/webs/websDelShareDev.cpp \
./app/webs/websGedDevRomInfo.cpp \
./app/webs/websGedDevSharedUser.cpp \
./app/webs/websGetCfgCode.cpp \
./app/webs/websGetChnNewMsgSize.cpp \
./app/webs/websGetClientInfo.cpp \
./app/webs/websGetDevInfo.cpp \
./app/webs/websGetDevList.cpp \
./app/webs/websGetHeadPic.cpp \
./app/webs/websGetHistoryAlarmMsg.cpp \
./app/webs/websGetMngHost.cpp \
./app/webs/websGetPushMsgRule.cpp \
./app/webs/websInfo.cpp \
./app/webs/websLogin.cpp \
./app/webs/websModifyCamera.cpp \
./app/webs/websModifyDev.cpp \
./app/webs/websModifyGroup.cpp \
./app/webs/websModifyNode.cpp \
./app/webs/websModifyUsrInfo.cpp \
./app/webs/websRecoverPwd.cpp \
./app/webs/websRegister.cpp \
./app/webs/websReportDeviceInfo.cpp \
./app/webs/websReportPhoneInfo.cpp \
./app/webs/websSendRecv.cpp \
./app/webs/websSetHeadPic.cpp \
./app/webs/websSetPushMsgRule.cpp \
./app/webs/websShareDev.cpp \
./app/webs/websSortGroup.cpp \
./app/webs/websUserFeekback.cpp

LOCAL_C_INCLUDES := \
$(LOCAL_PATH)/app \
$(LOCAL_PATH)/app/mxml \
$(LOCAL_PATH)/app/dcp \
$(LOCAL_PATH)/app/p2pc \
$(LOCAL_PATH)/app/p2psdk \
$(LOCAL_PATH)/app/procon \
$(LOCAL_PATH)/app/sound \
$(LOCAL_PATH)/app/test \
$(LOCAL_PATH)/app/webs \
$(LOCAL_PATH)/app/wifi \
$(LOCAL_PATH)/common \
$(LOCAL_PATH)/public 


LOCAL_LDLIBS := -llog -lz -lcusdk


include $(BUILD_SHARED_LIBRARY)



