// Copyright 2017 <Célian Garcia>

#include <fly_module/workers/FlyCloudPopulation.hpp>

namespace firefly {
namespace fly_module {

const char *FlyCloudPopulation::DATABASE_NAME = "firefly_hive";

/**
 * - Initiate database connection;
 * - Initiate the cloud model with database manager;
 * - Insert cloud entry in the database;
 * - Run compute thread which put entries in queue;
 * - Run populate thread which move entries from queue to database.
 * @param pool
 * @return id generated by the database.
 */
int FlyCloudPopulation::start(int task_id, ThreadPool *pool) noexcept(false) {
    // Move task to STARTED state
    DatabaseManager db_manager(DATABASE_NAME);
    TaskModel task_model(&db_manager);
    task_model.updateTaskStateById(task_id, Task::STARTED);

    auto *operations = new ConcurrentOperationQueue;

    pool->enqueue([operations] {
        run_compute_thread(operations);
    });

    pool->enqueue([task_id, operations] {
        run_populate_thread(task_id, operations);
    });

    return task_id;
}

/**
 * Awaiting for implementation
 */
void FlyCloudPopulation::stop() {
    throw FireflyException(HtmlStatusCode::NOT_IMPLEMENTED, "Stop action not yet implemented");
}

// TODO(célian): move it to firefly_core
/**
 * Collect operations from database. We only collect the operations from the last time we collect.
 * @param task_id the id of the task we're collecting.
 * @param client_last_op index of the last operation that we performed.
 * @return operations performed from the last collect.
 */
std::vector<Operation> FlyCloudPopulation::collect(int task_id, int client_last_op) {
    DatabaseManager db_manager(DATABASE_NAME);
    OperationModel operation_model(&db_manager);
    return operation_model.getOperationsSince(task_id, client_last_op);
}

void FlyCloudPopulation::run_compute_thread(ConcurrentOperationQueue *queue) {
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        queue->enqueue({OperationType::ADD, {"fpoint3d", {i, i, i}}});
        queue->enqueue({OperationType::ADD, {"fpoint3d", {i, i, i}}});
        queue->enqueue({OperationType::DELETE, {"fpoint3d", {i, i, i}}});
        queue->enqueue({OperationType::ADD, {"fpoint3d", {i, i, i}}});
    }
    queue->endQueue();
}

void FlyCloudPopulation::run_populate_thread(int task_id, ConcurrentOperationQueue *queue) {
    std::cout << "Thread starts for the task id : " << task_id << std::endl;

    // Trying to get task from database
    DatabaseManager db_manager(DATABASE_NAME);
    TaskModel task_model(&db_manager);
    Point3DModel point_model(&db_manager);

    // Save all operations in base
    while (!queue->isEmptyAndEnded()) {
        Operation operation = queue->dequeue();
        point_model.insertOperation(operation, task_id);
    }

    // Move task to FINISHED state
    task_model.updateTaskStateById(task_id, Task::FINISHED);

    std::cout << "Thread have finished the work for the task of id : " << task_id << std::endl;
}

}  // namespace fly_module
}  // namespace firefly
