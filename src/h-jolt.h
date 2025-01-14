#pragma once

#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>
 
// All Jolt symbols are in the JPH namespace
//using namespace JPH;

// If you want your code to compile using single or double precision write 0.0_r to get a Real value that compiles to double or float depending if JPH_DOUBLE_PRECISION is set or not.
using namespace JPH::literals;

// We're also using STL classes in this example
//using namespace std;

namespace hjolt
{
    // Callback for traces, connect this to your own trace function if you have one
    static void TraceImpl(const char *inFMT, ...)
    {
        // Format the message
        va_list list;
        va_start(list, inFMT);
        char buffer[1024];
        vsnprintf(buffer, sizeof(buffer), inFMT, list);
        va_end(list);

        // Print to the TTY
        std::cout << buffer << std::endl;
    }

    // Layer that objects can be in, determines which other objects it can collide with
    // Typically you at least want to have 1 layer for moving bodies and 1 layer for static bodies, but you can have more
    // layers if you want. E.g. you could have a layer for high detail collision (which is not used by the physics simulation
    // but only if you do collision testing).
    namespace Layers
    {
        static constexpr JPH::ObjectLayer NON_MOVING = 0;
        static constexpr JPH::ObjectLayer MOVING = 1;
        static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
    };

    /// Class that determines if two object layers can collide
    class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
    {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inObject1, JPH::ObjectLayer inObject2) const override
        {
            switch (inObject1)
            {
            case Layers::NON_MOVING:
                return inObject2 == Layers::MOVING; // Non moving only collides with moving
            case Layers::MOVING:
                return true; // Moving collides with everything
            default:
                JPH_ASSERT(false);
                return false;
            }
        }
    };

    // Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
    // a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
    // You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
    // many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
    // your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
    namespace BroadPhaseLayers
    {
        static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
        static constexpr JPH::BroadPhaseLayer MOVING(1);
        static constexpr uint NUM_LAYERS(2);
    };

    // BroadPhaseLayerInterface implementation
    // This defines a mapping between object and broadphase layers.
    class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface
    {
    public:
        BPLayerInterfaceImpl()
        {
            // Create a mapping table from object to broad phase layer
            mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
            mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
        }

        virtual uint GetNumBroadPhaseLayers() const override
        {
            return BroadPhaseLayers::NUM_LAYERS;
        }

        virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override
        {
            JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
            return mObjectToBroadPhase[inLayer];
        }

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
        virtual const char *GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override
        {
            switch ((JPH::BroadPhaseLayer::Type)inLayer)
            {
            case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
                return "NON_MOVING";
            case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
                return "MOVING";
            default:
                JPH_ASSERT(false);
                return "INVALID";
            }
        }
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

    private:
        JPH::BroadPhaseLayer mObjectToBroadPhase[Layers::NUM_LAYERS];
    };

    /// Class that determines if an object layer can collide with a broadphase layer
    class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
    {
    public:
        virtual bool ShouldCollide(JPH::ObjectLayer inLayer1, JPH::BroadPhaseLayer inLayer2) const override
        {
            switch (inLayer1)
            {
            case Layers::NON_MOVING:
                return inLayer2 == BroadPhaseLayers::MOVING;
            case Layers::MOVING:
                return true;
            default:
                JPH_ASSERT(false);
                return false;
            }
        }
    };

    // An example contact listener
    class MyContactListener : public JPH::ContactListener
    {
    public:
        // See: ContactListener
        virtual JPH::ValidateResult OnContactValidate(const JPH::Body &inBody1, const JPH::Body &inBody2, JPH::RVec3Arg inBaseOffset, const JPH::CollideShapeResult &inCollisionResult) override
        {
            std::cout << "Contact validate callback" << std::endl;

            // Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
            return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
        }

        virtual void OnContactAdded(const JPH::Body &inBody1, const JPH::Body &inBody2, const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override
        {
            std::cout << "A contact was added" << std::endl;
        }

        virtual void OnContactPersisted(const JPH::Body &inBody1, const JPH::Body &inBody2, const JPH::ContactManifold &inManifold, JPH::ContactSettings &ioSettings) override
        {
            std::cout << "A contact was persisted" << std::endl;
        }

        virtual void OnContactRemoved(const JPH::SubShapeIDPair &inSubShapePair) override
        {
            std::cout << "A contact was removed" << std::endl;
        }
    };

    // An example activation listener
    class MyBodyActivationListener : public JPH::BodyActivationListener
    {
    public:
        virtual void OnBodyActivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
        {
            std::cout << "A body got activated" << std::endl;
        }

        virtual void OnBodyDeactivated(const JPH::BodyID &inBodyID, JPH::uint64 inBodyUserData) override
        {
            std::cout << "A body went to sleep" << std::endl;
        }
    };

    class Config
    {
    public:
        Config()
        {
            maxThreads = std::thread::hardware_concurrency() - 1;
        }
        int maxTempAllocatorSize = 10 * 1024 * 1024;
        int maxPhysicsJobs = JPH::cMaxPhysicsJobs;
        int maxPhysicsBarriers = JPH::cMaxPhysicsBarriers;
        int maxThreads = 1;
        int maxBodies = 1024;
        int numBodyMutexes = 0;
        int maxBodyPairs = 1024;
        int maxContactConstraints = 1024;
    };

    class Globals;
    

    class ShapeRefHelper {
        public:
        static inline const JPH::Shape *getShape(JPH::ShapeRefC*Ref) {
            return Ref->GetPtr();
        }
    };
    
    class PhysicsSystemWrapper
    {
    public:
        PhysicsSystemWrapper(Config &config)
        {
            // This is the max amount of rigid bodies that you can add to the physics system. If you try to add more you'll get an error.
            // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
            const uint cMaxBodies = config.maxBodies;

            // This determines how many mutexes to allocate to protect rigid bodies from concurrent access. Set it to 0 for the default settings.
            const uint cNumBodyMutexes = config.numBodyMutexes;

            // This is the max amount of body pairs that can be queued at any time (the broad phase will detect overlapping
            // body pairs based on their bounding boxes and will insert them into a queue for the narrowphase). If you make this buffer
            // too small the queue will fill up and the broad phase jobs will start to do narrow phase work. This is slightly less efficient.
            // Note: This value is low because this is a simple test. For a real project use something in the order of 65536.
            const uint cMaxBodyPairs = config.maxBodyPairs;

            // This is the maximum size of the contact constraint buffer. If more contacts (collisions between bodies) are detected than this
            // number then these contacts will be ignored and bodies will start interpenetrating / fall through the world.
            // Note: This value is low because this is a simple test. For a real project use something in the order of 10240.
            const uint cMaxContactConstraints = config.maxContactConstraints;

           
            // Now we can create the actual physics system.
            physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);
            
            physics_system.SetBodyActivationListener(&body_activation_listener);

            physics_system.SetContactListener(&contact_listener);

            pBodyInterfaceLocking = &physics_system.GetBodyInterface();
            pBodyInterfaceNoLocking = &physics_system.GetBodyInterfaceNoLock();
        }

         void createBody(JPH::ShapeRefC *shape) {
            // Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
            JPH::BodyCreationSettings body_settings(*shape, JPH::RVec3(0.0_r, -1.0_r, 0.0_r), JPH::Quat::sIdentity(), JPH::EMotionType::Static, Layers::NON_MOVING);

            // Create the actual rigid body
            JPH::Body *floor = pBodyInterfaceLocking->CreateBody(body_settings); // Note that if we run out of bodies this can return nullptr

        }

        ~PhysicsSystemWrapper()
        {
        }

        inline void update(float deltaTime, int steps, JPH::TempAllocator *temp_allocator, JPH::JobSystem *job_system) {
            // Step the world
            physics_system.Update(deltaTime, steps, temp_allocator, job_system);
        }
        JPH::PhysicsSystem physics_system;

        JPH::BodyInterface *pBodyInterfaceLocking;
        JPH::BodyInterface *pBodyInterfaceNoLocking;

         // Create mapping table from object layer to broadphase layer
        // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
        BPLayerInterfaceImpl broad_phase_layer_interface;

        // Create class that filters object vs broadphase layers
        // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
        ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;

        // Create class that filters object vs object layers
        // Note: As this is an interface, PhysicsSystem will take a reference to this so this instance needs to stay alive!
        ObjectLayerPairFilterImpl object_vs_object_layer_filter;

        // A body activation listener gets notified when bodies activate and go to sleep
        // Note that this is called from a job so whatever you do here needs to be thread safe.
        // Registering one is entirely optional.
        MyBodyActivationListener body_activation_listener;

        // A contact listener gets notified when bodies (are about to) collide, and when they separate again.
        // Note that this is called from a job so whatever you do here needs to be thread safe.
        // Registering one is entirely optional.
        MyContactListener contact_listener;
    };

    class Globals
    {
    public:
        std::unique_ptr<JPH::TempAllocatorImpl> _tempAllocator;
        std::unique_ptr<JPH::JobSystemThreadPool> _jobSystem;
        std::unique_ptr<Config> _config;


        Globals(Config *pConfig)
        {
            _config = std::make_unique<Config>(*pConfig);

            Config &config = *pConfig;
            // Register allocation hook. In this example we'll just let Jolt use malloc / free but you can override these if you want (see Memory.h).
            // This needs to be done before any other Jolt function is called.
            JPH::RegisterDefaultAllocator();

            // Install trace and assert callbacks
            JPH::Trace = TraceImpl;

            // Create a factory, this class is responsible for creating instances of classes based on their name or hash and is mainly used for deserialization of saved data.
            // It is not directly used in this example but still required.
            JPH::Factory::sInstance = new JPH::Factory();

            // Register all physics types with the factory and install their collision handlers with the CollisionDispatch class.
            // If you have your own custom shape types you probably need to register their handlers with the CollisionDispatch before calling this function.
            // If you implement your own default material (PhysicsMaterial::sDefault) make sure to initialize it before this function or else this function will create one for you.
            JPH::RegisterTypes();

            // We need a temp allocator for temporary allocations during the physics update. We're
            // pre-allocating 10 MB to avoid having to do allocations during the physics update.
            // B.t.w. 10 MB is way too much for this example but it is a typical value you can use.
            // If you don't want to pre-allocate you can also use TempAllocatorMalloc to fall back to
            // malloc / free.
            _tempAllocator = std::make_unique<JPH::TempAllocatorImpl>(config.maxTempAllocatorSize);

            // We need a job system that will execute physics jobs on multiple threads. Typically
            // you would implement the JobSystem interface yourself and let Jolt Physics run on top
            // of your own job scheduler. JobSystemThreadPool is an example implementation.
            _jobSystem =  std::make_unique<JPH::JobSystemThreadPool>(config.maxPhysicsJobs, config.maxPhysicsBarriers, config.maxThreads);
        }

        void updateSystem(PhysicsSystemWrapper *system, float deltaTime, int collisionSubSteps) {
            system->update(deltaTime, collisionSubSteps, _tempAllocator.get(), _jobSystem.get());
        }

        PhysicsSystemWrapper *createSystem() {
            auto system = new PhysicsSystemWrapper(*_config);
            return system;
        }

        static JPH::ShapeRefC *createBoxShape(float x, float y, float z) {
            // Next we can create a rigid body to serve as the floor, we make a large box
            // Create the settings for the collision volume (the shape).
            // Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
            JPH::BoxShapeSettings box_shape_settings(JPH::Vec3(x, y, z));

            // Create the shape
            JPH::ShapeSettings::ShapeResult box_shape_result = box_shape_settings.Create();
            JPH::ShapeRefC *box_shape = new JPH::ShapeRefC(box_shape_result.Get()); // We don't expect an error here, but you can check box_shape_result for HasError() / GetError()
            return box_shape;
        }


       
        ~Globals()
        {               
            // Unregisters all types with the factory and cleans up the default material
            JPH::UnregisterTypes();

            // Destroy the factory
            delete JPH::Factory::sInstance;
            JPH::Factory::sInstance = nullptr;
        }
    };
}

/*

            // The main way to interact with the bodies in the physics system is through the body interface. There is a locking and a non-locking
            // variant of this. We're going to use the locking version (even though we're not planning to access bodies from multiple threads)
            BodyInterface &body_interface = physics_system.GetBodyInterface();

            // Next we can create a rigid body to serve as the floor, we make a large box
            // Create the settings for the collision volume (the shape).
            // Note that for simple shapes (like boxes) you can also directly construct a BoxShape.
            BoxShapeSettings floor_shape_settings(Vec3(100.0f, 1.0f, 100.0f));

            // Create the shape
            ShapeSettings::ShapeResult floor_shape_result = floor_shape_settings.Create();
            ShapeRefC floor_shape = floor_shape_result.Get(); // We don't expect an error here, but you can check floor_shape_result for HasError() / GetError()

            // Create the settings for the body itself. Note that here you can also set other properties like the restitution / friction.
            BodyCreationSettings floor_settings(floor_shape, RVec3(0.0_r, -1.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);

            // Create the actual rigid body
            Body *floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr

            // Add it to the world
            body_interface.AddBody(floor->GetID(), EActivation::DontActivate);

            // Now create a dynamic body to bounce on the floor
            // Note that this uses the shorthand version of creating and adding a body to the world
            BodyCreationSettings sphere_settings(new SphereShape(0.5f), RVec3(0.0_r, 2.0_r, 0.0_r), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
            BodyID sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);

            // Now you can interact with the dynamic body, in this case we're going to give it a velocity.
            // (note that if we had used CreateBody then we could have set the velocity straight on the body before adding it to the physics system)
            body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));

            // We simulate the physics world in discrete time steps. 60 Hz is a good rate to update the physics system.
            const float cDeltaTime = 1.0f / 60.0f;

            // Optional step: Before starting the physics simulation you can optimize the broad phase. This improves collision detection performance (it's pointless here because we only have 2 bodies).
            // You should definitely not call this every frame or when e.g. streaming in a new level section as it is an expensive operation.
            // Instead insert all new objects in batches instead of 1 at a time to keep the broad phase efficient.
            physics_system.OptimizeBroadPhase();

            // Now we're ready to simulate the body, keep simulating until it goes to sleep
            uint step = 0;
            while (body_interface.IsActive(sphere_id))
            {
                // Next step
                ++step;

                // Output current position and velocity of the sphere
                RVec3 position = body_interface.GetCenterOfMassPosition(sphere_id);
                Vec3 velocity = body_interface.GetLinearVelocity(sphere_id);
                std::cout << "Step " << step << ": Position = (" << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "), Velocity = (" << velocity.GetX() << ", " << velocity.GetY() << ", " << velocity.GetZ() << ")" << endl;

                // If you take larger steps than 1 / 60th of a second you need to do multiple collision steps in order to keep the simulation stable. Do 1 collision step per 1 / 60th of a second (round up).
                const int cCollisionSteps = 1;

                // Step the world
                physics_system.Update(cDeltaTime, cCollisionSteps, &temp_allocator, &job_system);
            }

            // Remove the sphere from the physics system. Note that the sphere itself keeps all of its state and can be re-added at any time.
            body_interface.RemoveBody(sphere_id);

            // Destroy the sphere. After this the sphere ID is no longer valid.
            body_interface.DestroyBody(sphere_id);

            // Remove and destroy the floor
            body_interface.RemoveBody(floor->GetID());
            body_interface.DestroyBody(floor->GetID());
*/