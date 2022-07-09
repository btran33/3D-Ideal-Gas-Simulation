#include <catch2/catch.hpp>
#include "gas_simulation.h"

using idealgas3d::Histogram;
using idealgas3d::GasContainer;
using idealgas3d::Particle;

TEST_CASE("Test histogram class"){
    std::vector<Particle> *particles = new std::vector<Particle>();
    (*particles).push_back(Particle(vec3(0,0,0), vec3(0.01, 0.1, 0.02), 5, 5, "red"));

    (*particles).push_back(Particle(vec3(1,1,1), vec3(0.3, 0.01, 0.2), 5,5, "red"));


    Histogram red_histogram = Histogram("red", vec2(100,100), vec2(350,250));

    SECTION("Update histogram buckets"){
        red_histogram.UpdateParticles(*particles);
        red_histogram.FillHistogramBucket();
        std::vector<int> result = red_histogram.GetBucketList();
        REQUIRE(result == std::vector<int>({0,1,0,1,0,0,0,0,0,0}));
    }

    SECTION("Increase bucket count"){
        red_histogram.AdjustBucketAmount(1);
        red_histogram.InitializeBucket();
        REQUIRE(red_histogram.GetBucketList().size() == 11);
    }

    SECTION("Decrease bucket count"){
        red_histogram.AdjustBucketAmount(-1);
        red_histogram.InitializeBucket();
        REQUIRE(red_histogram.GetBucketList().size() == 9);
    }
}
