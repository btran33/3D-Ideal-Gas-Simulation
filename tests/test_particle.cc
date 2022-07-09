#include <catch2/catch.hpp>
#include "particle.h"
#include "gas_container.h"

using idealgas3d::GasContainer;
using idealgas3d::Particle;

TEST_CASE("Test particle class") {
    Particle particle_one(vec3(0, 0, 1), vec3(0, 0, -.5), 1, .5, "red");
    Particle particle_two(vec3(0, 0, -1), vec3(0, 0, .5), 1, .5, "red");

    SECTION("Update Position") {
        particle_one.UpdatePosition();
        particle_two.UpdatePosition();
        REQUIRE(particle_one.GetPosition() == vec3(0, 0, 0.5));
        REQUIRE(particle_two.GetPosition() == vec3(0, 0, -0.5));
    }

    SECTION("Check Collision"){
        particle_one.UpdatePosition();
        particle_two.UpdatePosition();
        REQUIRE(particle_one.IfCollided(particle_two));
    }

    SECTION("Update velocity"){
        particle_one.UpdatePosition();
        particle_two.UpdatePosition();
        particle_one.UpdateCollidedParticlesVelocity(particle_two);

        REQUIRE((particle_one.GetVelocity() - vec3(0, 0, .5)).x < 0.0001);
        REQUIRE((particle_one.GetVelocity() - vec3(0, 0, .5)).y < 0.0001);
        REQUIRE((particle_two.GetVelocity() - vec3(0, 0, -.5)).x < 0.0001);
        REQUIRE((particle_two.GetVelocity() - vec3(0, 0, -.5)).y < 0.0001);
    }
}
