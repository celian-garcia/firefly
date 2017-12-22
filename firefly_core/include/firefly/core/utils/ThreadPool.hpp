/// Copyright 2017 <Célian Garcia>

#ifndef FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_THREADPOOL_HPP_
#define FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_THREADPOOL_HPP_

#include <memory>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

namespace firefly {

struct ThreadPool {
    typedef std::unique_ptr<boost::asio::io_service::work> asio_worker;

    // TODO : find a way to not have cpplint error on element_type
    explicit ThreadPool(int threads) : service(), service_worker(new asio_worker::element_type(service)) {
        for (int i = 0; i < threads; ++i) {
            auto worker = [this] { return service.run(); };
            grp.add_thread(new boost::thread(worker));
        }
    }

    template<class F>
    void enqueue(F f) {
        service.post(f);
    }

    ~ThreadPool() {
        service_worker.reset();
        grp.join_all();
        service.stop();
    }

 private:
    boost::asio::io_service service;
    asio_worker service_worker;
    boost::thread_group grp;
};

}  // namespace firefly

#endif  // FIREFLY_CORE_INCLUDE_FIREFLY_CORE_UTILS_THREADPOOL_HPP_
