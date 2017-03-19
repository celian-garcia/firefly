// Copyright 2017 <Célian Garcia>

#ifndef FIREFLY_FLYCLOUDPOPULATION_HPP
#define FIREFLY_FLYCLOUDPOPULATION_HPP

#include <vector>
#include <firefly/Operation.hpp>
#include <firefly/utils/FireflyException.hpp>
#include <firefly/utils/ProcessAction.hpp>
#include <firefly/modules/common/model/DatabaseManager.hpp>
#include <firefly/modules/fly/model/Cloud3DModel.hpp>
#include <firefly/modules/fly/model/beans/Point3DBean.hpp>
#include <firefly/modules/fly/model/Point3DModel.hpp>
#include <firefly/utils/ThreadPool.hpp>

namespace firefly {
    namespace module_fly {
        class FlyCloudPopulation {
        public:

            static int start(ThreadPool* pool);

            static void stop();

            static void collect();

        private:
            static const std::vector<ProcessActionType> VALID_ACTION_TYPES;

        };
    }
}

#endif //FIREFLY_FLYCLOUDPOPULATION_HPP
