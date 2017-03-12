// Copyright 2017 <Célian Garcia>

#include <firefly/utils/ProcessAction.hpp>
#include "firefly/modules/fly/workers/FlyCloudPopulation.hpp"

namespace firefly {
    namespace module_fly {
        int FlyCloudPopulation::start() {
            int cloud_id = 1768;
//            // - Initiate database connection;
//            // - Initiate the cloud model with database manager;
//            // - Insert cloud entry in the database
//            //    -> return the id generated by the database.
//            //TOD (Célian) open the database manager using the module_name
//            DatabaseManager db_manager("fcloudpopulation");
//            FCloud3DModel cloud_model(&db_manager);
//            int cloud_id = cloud_model.insertCloud(FCloud3D());
//
//            SafeQueue <Operation> *operations = new SafeQueue<Operation>;
//
//            // Initiate a first thread into the thread pool
//            // This thread will write to the queue the cloud operations (add/delete)
//            pool->enqueue([name, operations] {
//                std::cout
//                        << "Thread starts for the module : " << name
//                        << std::endl;
//
//                for (int i = 0; i < 10; ++i) {
//                    Sleep(1000);
//                    operations->enqueue(Operation(OperationType::ADD, cv::Vec3f(i, i, i)));
//                    std::cout << "Enqueue operation " << i << std::endl;
//                }
//                operations->enqueue(Operation(OperationType::END, cv::Vec3f(0, 0, 0)));
//
//                std::cout
//                        << "Thread have finished the work for the module : " << name
//                        << std::endl;
//            });
//
//            // Initiate a second thread into the thread pool
//            // This thread will listen the queue continuously to populate the
//            // database cloud with listened points
//            pool->enqueue([cloud_id, operations] {
//                std::cout
//                        << "Thread starts for the cloud id : " << cloud_id
//                        << std::endl;
//
//                // Initialize connection, cloud model, and point model
//                DatabaseManager db_manager("fcloudpopulation");
//                FCloud3DModel cloud_model(&db_manager);
//                FPoint3DModel point_model(&db_manager);
//                FCloud3D cloud = cloud_model.getCloudById(cloud_id);
//
//                // Update the cloud state to populate
//                cloud.setState("POPULATE");
//                cloud_model.updateCloud(cloud);
//
//                // Listen the operation queue and populate the database
//                bool end_operation_found = false;
//                // TODO(Célian): Let the queue define and increment the operation index
//                int op_curr_index = 0;
//                while (!end_operation_found) {
//                    Operation op = operations->dequeue();
//                    cv::Vec3f op_value = op.getValue();
//                    OperationType op_type = op.getType();
//                    end_operation_found = op_type == OperationType::END;
//                    if (end_operation_found)
//                        break;
//
//                    // TODO(Célian): insert the operation into the database
//                    // using the point model.
//                    try {
//                        FPoint3D point = point_model.getPointByValueAndCloudId(
//                                op_value, cloud_id);
//
//                        // If the size of operations indices is even, the next operation should be an add
//                        // If the size of operations indices is odd , the next operation should be a remove
//                        // With this type of storing, we don't need to store the ADD or REMOVE flag.
//                        // So we can store another thing in place: the total index of the operation,
//                        // which is much more usefull in the listen part.
//                        std::vector<int> op_indices = point.getOperationsIds();
//                        if ((op_indices.size() % 2 == 0 && op_type == OperationType::ADD) ||
//                            (op_indices.size() % 2 == 1 && op_type == OperationType::REMOVE)) {
//                            point.addOperationId(op_curr_index++);
//                            point_model.updatePointOperations(point);
//                        }
//                    } catch (ObjectNotFound e) {
//                        FPoint3D new_point(op_value, cloud_id, {op_curr_index++});
//                        point_model.insertPoint(new_point);
//                    }
//                }
//
//                // Update the cloud state to finished
//                cloud.setState("FINISHED");
//                cloud_model.updateCloud(cloud);
//
//                std::cout
//                        << "Thread have finished the work for the cloud_id : " << cloud_id
//                        << std::endl;
//            });

            return cloud_id;
        }

        void FlyCloudPopulation::stop() {
            throw FireflyException(HtmlStatusCode::NOT_IMPLEMENTED, "Stop action not yet implemented");
        }

        void FlyCloudPopulation::collect() {
            throw FireflyException(HtmlStatusCode::NOT_IMPLEMENTED, "Collect action not yet implemented");
        }

        const std::vector<ProcessActionType> FlyCloudPopulation::VALID_ACTION_TYPES = {
                ProcessActionType::START,
                ProcessActionType::STOP,
                ProcessActionType::COLLECT
        };
    }
}