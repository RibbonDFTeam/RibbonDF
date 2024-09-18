#include <cstdint>
#include <stdio.h>
#include <string>
#include <unistd.h>
// #include "fdbus_server.h"
#include "RibbonDF_config.h"
#include "fdbus/CBaseJob.h"
#include "fdbus/CBaseServer.h"
#include "fdbus/CBaseWorker.h"
#include "fdbus/CFdbCJsonMsgBuilder.h"
#include "fdbus/CFdbContext.h"
#include "fdbus/CFdbMessage.h"
#include "fdbus/cJSON/cJSON.h"
#include "fdbus/common_defs.h"
// #include "fdbus/fdbus.h"
#include "fdbus/fdb_log_trace.h"

using namespace ipc::fdbus;

static CBaseWorker main_worker;

class FDBusServer : public CBaseServer
{
   public:
    FDBusServer(const char *name = 0, CBaseWorker *worker = 0) :
        CBaseServer(name, worker)
    {
    }

    int32_t Start()
    {
        worker()->start();
        return 0;
    }

   protected:
    void onOnline(const CFdbOnlineInfo &info)
    {
        FDB_LOG_I("server session up: %d, secure: %d\n", info.mSid, info.mQOS);
        if (info.mFirstOrLast)
        {
            /* enable broadcast timer when the first client is connected */
            FDB_LOG_I("timer enabled\n");
        }
    }
    void onOffline(const CFdbOnlineInfo &info)
    {
        FDB_LOG_I("server session shutdown: %d, secure: %d\n", info.mSid, info.mQOS);
        if (info.mFirstOrLast)
        {
            /* disable broadcast timer when the last client is disconnected */
        }
    }
    void onInvoke(CBaseJob::Ptr &msg_ref)
    {
        printf("onInvoke\n");
        auto msg = castToMessage<CBaseMessage *>(msg_ref);
        switch (msg->code())
        {
        case 1: {
            CFdbCJsonMsgParser parser;
            if (msg->deserialize(parser) == 0)
            {
                return;
            }

            cJSON *root = cJSON_CreateString("OK");
            CFdbCJsonMsgBuilder builder(root);

            msg->reply(msg_ref, builder);
            break;
        }
        default: {
            break;
        }
        }
    }
};

int main(int argc, char *argv[])
{
    FDB_CONTEXT->start();
    main_worker.start();

    std::string url(FDB_URL_SVC);
    std::string service_name("test");
    url          += service_name;
    service_name += "_server";
    FDBusServer server(service_name.c_str(), &main_worker);

    server.enableWatchdog(true);
    server.enableUDP(true);
    server.setExportableLevel(FDB_EXPORTABLE_SITE);
    server.bind(url.c_str());

    while (true)
    {
        sleep(1);
    }


    return 0;
}
