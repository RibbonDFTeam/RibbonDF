#include <stdio.h>
#include <unistd.h>

#include "fdbus/CBaseClient.h"
#include "fdbus/CBaseJob.h"
#include "fdbus/CFdbCJsonMsgBuilder.h"
#include "fdbus/CFdbContext.h"
#include "fdbus/CFdbMessage.h"
#include "fdbus/fdbus.h"
#include "cJSON.h"

using namespace ipc::fdbus;

class FDBusClient : public CBaseClient
{
   public:
    FDBusClient(const char *name = 0, CBaseWorker *worker = 0) :
        CBaseClient(name, worker)
    {
        printf("FDBusClient created\n");
    }

    void SyncCall()
    {
        printf("SyncCall\n");
        cJSON *root = cJSON_CreateNumber(100);

        CFdbCJsonMsgBuilder builder(root);

        CBaseJob::Ptr ref(new CBaseMessage(1));
        invoke(ref, builder);

        auto msg = castToMessage<CBaseMessage *>(ref);
        if (msg->isStatus())
        {
            return;
        }

        CFdbCJsonMsgParser parser;
        if (msg->deserialize(parser))
        {
            cJSON *js_reply = parser.retrieve();
            printf("reply: %s\n", cJSON_PrintUnformatted(js_reply));
        }
    }

    void onReply(CBaseJob::Ptr &msg_ref)
    {
        auto msg = castToMessage<CBaseMessage *>(msg_ref);
        printf("onReply, code: %d\n", msg->code());
        switch (msg->code())
        {
        case 1: {
            if (msg->isStatus())
            {
                return;
            }

            CFdbCJsonMsgParser parser;
            if (msg->deserialize(parser))
            {
                cJSON *js_reply = parser.retrieve();
                printf("onReply: %s\n", cJSON_PrintUnformatted(js_reply));
            }
            break;
        }
        default:
            break;
        }
    }
};

static CBaseWorker main_worker;

int main()
{
    FDB_CONTEXT->start();
    main_worker.start();

    std::string url(FDB_URL_SVC);
    std::string service_name("test");
    url          += service_name;
    service_name += "_client";

    auto client = new FDBusClient(service_name.c_str(), &main_worker);
    client->enableReconnect(true);
    client->enableUDP(true);
    client->enableTimeStamp(true);
    client->connect(url.c_str());

    sleep(1);
    client->SyncCall();

    while (true)
    {
        sleep(1);
    }

    return 0;
}
