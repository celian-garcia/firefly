// Copyright 2017 <Célian Garcia>

#pragma once

#include <queue>
#include <boost/thread.hpp>
#include "firefly/core/data/Operation.hpp"

namespace firefly {

class ConcurrentOperationQueue {
 public:
    bool isEmptyAndEnded() {
        return ended.load() && q.empty();
    }

    void endQueue() {
        this->ended.store(true);
    }

    void enqueue(Operation operation) {
        boost::lock_guard<boost::mutex> lock(m);
        q.push(operation);
        c.notify_one();
    }

    Operation dequeue() {
        boost::unique_lock<boost::mutex> lock(m);
        while (q.empty()) {
            c.wait(lock);
        }
        Operation val = q.front();
        q.pop();
        return val;
    }

 private:
    std::atomic<bool> ended = false;
    std::queue<Operation> q;
    mutable boost::mutex m;
    boost::condition_variable c;
};

}  // namespace firefly

