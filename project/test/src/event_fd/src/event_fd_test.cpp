#include <chrono>
#include <cstdint>
#include <stdio.h>
#include <sys/epoll.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/eventfd.h>
#include <thread>
#include <unistd.h>

int process_events(int32_t efd, struct epoll_event *events, int num_events)
{
    // printf("process_events, num_events: %d\n", num_events);
    for (int i = 0; i < num_events; i++)
    {
        int fd = events[i].data.fd;
        if (fd != efd)
        {
            continue;
        }

        if ((events[i].events & EPOLLIN) == 0)
        {
            continue;
        }

        eventfd_t count;

        eventfd_read(fd, &count);
        printf("Received event, count: %lu\n", count);
    }
    return 0;
}

int main()
{
    int efd;
    eventfd_t value;

    // 创建 eventfd，初始值为 0，非阻塞模式
    efd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (efd == -1)
    {
        perror("eventfd");
        exit(EXIT_FAILURE);
    }

    std::thread t1([&]() {
        int epoll_fd = epoll_create(8);

        struct epoll_event event;
        event.events  = EPOLLIN;
        event.data.fd = efd;
        epoll_ctl(epoll_fd, EPOLL_CTL_ADD, efd, &event);

        struct epoll_event events[10];
        while (true)
        {
            int32_t ret = epoll_wait(epoll_fd, events, 10, -1);
            if (ret > 0)
            {
                process_events(efd, events, ret);
            }
            else if (ret == 0)
            {
                printf("epoll_wait timeout");
            }
            else
            {
                printf("epoll_wait error");
            }
        }
    });
    t1.detach();

    std::thread t2([&]() {
        int32_t i = 1;
        while (true)
        {
            // write(efd, &i, sizeof(int32_t));
            eventfd_write(efd, 1);
            printf("Send event, count: %d\n", i);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    t2.detach();

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    // 关闭 eventfd
    close(efd);

    return 0;
}
