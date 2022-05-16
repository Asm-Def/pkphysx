#ifndef PKPHYSX_CONFIG_H
#define PKPHYSX_CONFIG_H

#include <Eigen/Eigen>
#include <PxPhysicsAPI.h>

namespace pkphysx {
    //TODO: 引出配置文件 或 宏定义
    using namespace physx;
    static const PxTolerancesScale get_tolerances_scale(){
        PxTolerancesScale scale;
        scale.length = 2.0f;
        scale.speed = 1.0f;
        return scale;
    }
    static const auto tolerances_scale = get_tolerances_scale();
}

#endif // PKPHYSX_CONFIG_H