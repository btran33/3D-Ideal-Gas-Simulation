#include <catch2/catch.hpp>
#include "gas_simulation.h"

using idealgas3d::GasContainer;
using idealgas3d::Particle;

TEST_CASE("Test container class") {
    GasContainer container;
    container.AddParticle(Particle(vec3(1, 0.7, 0), vec3(-1, 0, 1), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 1, 0), vec3(2, -0.5, 1), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 0.7, 1), vec3(0.1, 0.2, 0.5), 1, 0.5, "red"));

    // the 6 below are for wall collision test with 6-sided cube container
    container.AddParticle(Particle(vec3(1.5, 1, 0), vec3(1, 0, 0), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(-1.5, 1, 0), vec3(-1, 0, 0), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 3.5, 0), vec3(0, 1, 0), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 0.5, 0), vec3(0, -1, 0), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 1, 1.5), vec3(0, 0, 1), 1, 0.5, "red"));
    container.AddParticle(Particle(vec3(0, 1, -1.5), vec3(0, 0, -1), 1, 0.5, "red"));

    SECTION("Update all the particles"){
        SECTION("Position update"){
            container.AdvanceOneFrame();
            std::vector<Particle> updated_p_list = container.GetParticleList();

            Particle part1 = updated_p_list[0];
            Particle part2 = updated_p_list[1];
            Particle part3 = updated_p_list[2];

            REQUIRE(part1.GetPosition() == vec3(0, 0.7, 1));
            REQUIRE(part2.GetPosition() == vec3(2, 0.5, 1));
            REQUIRE(part3.GetPosition() == vec3(0.1, 0.9, 1.5));
        }
        SECTION("Wall Collisions Update"){
            container.AdvanceOneFrame();
            std::vector<Particle> updated_p_list = container.GetParticleList();

            Particle part1 = updated_p_list[3],
                     part2 = updated_p_list[4],
                     part3 = updated_p_list[5],
                     part4 = updated_p_list[6],
                     part5 = updated_p_list[7],
                     part6 = updated_p_list[8];

            REQUIRE(part1.GetVelocity() == vec3(-1, 0, 0));
            REQUIRE(part2.GetVelocity() == vec3(1, 0, 0));
            REQUIRE(part3.GetVelocity() == vec3(0, -1, 0));
            REQUIRE(part4.GetVelocity() == vec3(0, 1, 0));
            REQUIRE(part5.GetVelocity() == vec3(0, 0, -1));
            REQUIRE(part6.GetVelocity() == vec3(0, 0, 1));
        }
    }
}


