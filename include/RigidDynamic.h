/**
 * Copyright (c) CTU  - All Rights Reserved
 * Created on: 4/30/20
 *     Author: Vladimir Petrik <vladimir.petrik@cvut.cz>
 */

#ifndef SIM_PHYSX_RIGIDDYNAMIC_H
#define SIM_PHYSX_RIGIDDYNAMIC_H

#include <Physics.h>
#include <RigidActor.h>

class RigidDynamic : public RigidActor {

private:
    /** @brief Cast physx base pointer into physx RigidDynamic pointer. */
    auto get_dyn_ptr() {
        return reinterpret_cast<physx::PxRigidDynamic *>(get_physx_ptr());
    }

public:
    RigidDynamic() : RigidDynamic(Physics::get_physics()->createRigidDynamic(physx::PxTransform(physx::PxIdentity))) {
    }

    explicit RigidDynamic(physx::PxRigidDynamic *physxPtr) :
            RigidActor(reinterpret_cast<RigidActor::type_physx *>(physxPtr)) {
    }

    void set_mass(float mass) {
        physx::PxRigidBodyExt::setMassAndUpdateInertia(*get_dyn_ptr(), mass);
    }

    auto get_mass() {
        return get_dyn_ptr()->getMass();
    }

    void set_angular_damping(float damping) {
        get_dyn_ptr()->setAngularDamping(damping);
    }

    auto get_angular_damping() {
        return get_dyn_ptr()->getAngularDamping();
    }

    void set_angular_velocity(const Eigen::Vector3f &vel) {
        get_dyn_ptr()->setAngularVelocity(eigen_to_pxvec(vel));
    }

    auto get_angular_velocity() {
        return pxvec_to_eigen(get_dyn_ptr()->getAngularVelocity());
    }

    void set_linear_damping(float damping) {
        get_dyn_ptr()->setLinearDamping(damping);
    }

    auto get_linear_damping() {
        return get_dyn_ptr()->getLinearDamping();
    }

    auto get_linear_velocity() {
        return pxvec_to_eigen(get_dyn_ptr()->getLinearVelocity());
    }

    void set_linear_velocity(const Eigen::Vector3f &vel) {
        get_dyn_ptr()->setLinearVelocity(eigen_to_pxvec(vel));
    }

    void set_max_linear_velocity(float max_vel) {
        get_dyn_ptr()->setMaxLinearVelocity(max_vel);
    }

    void set_max_angular_velocity(float max_vel) {
        get_dyn_ptr()->setMaxAngularVelocity(max_vel);
    }

    void add_force(const Eigen::Vector3f &force, physx::PxForceMode::Enum &force_mode) {
        get_dyn_ptr()->addForce(eigen_to_pxvec(force), force_mode);
    }

    void add_torque(const Eigen::Vector3f &torque, physx::PxForceMode::Enum &force_mode) {
        get_dyn_ptr()->addTorque(eigen_to_pxvec(torque), force_mode);
    }

    void set_rigid_body_flag(const physx::PxRigidBodyFlag::Enum &flag, bool value) {
        get_dyn_ptr()->setRigidBodyFlag(flag, value);
    }

    void set_kinematic_target(const Eigen::Vector3f &pos, const Eigen::Vector4f &quat) {
        get_dyn_ptr()->setKinematicTarget(eigen_to_transform(pos, quat));
    }

};

#endif //SIM_PHYSX_RIGIDDYNAMIC_H
