#pragma once

#include "cinder/gl/gl.h"

using glm::vec3;
using namespace ci::gl;

namespace idealgas3d {

class Particle{
public:
    /**
     * Comparator struct between particle's velocity
     */
    struct ByVelocity {
        bool operator() (const Particle &particle1, const Particle &particle2) const{
            return glm::length(particle1.GetVelocity()) < glm::length(particle2.GetVelocity());
        }
    };

    /**
     * Constructor of the particle
     * @param position the starting position vector of the particle
     * @param velocity the starting velocity vector of the particle
     * @param mass the mass of the particle
     * @param radius the radius of the particle
     * @param color the color of the particle
     */
    Particle(const vec3 &position, const vec3 &velocity, double mass, double radius, char* color);

    /**
     * Constructor of the particle using another particle
     * @param particle a reference particle to construct from
     */
    Particle(const Particle &particle);

    /**
     * Getter of the particle's position
     * @return the particle's position
     */
    vec3 GetPosition() const;

    /**
     * Getter of the particle's velocity
     * @return the particle's velocity
     */
    vec3 GetVelocity() const;

    /**
     * Getter of the particle's mass
     * @return 
     */
    double GetMass() const;

    /**
     * Getter of the particle's radius
     * @return the particle's radius
     */
    double GetRadius() const;

    /**
     * Getter of the particle's color
     * @return the particle's color
     */
    char* GetColor() const;

    /**
     * Setter of the particle's velocity
     */
    void SetVelocity(const vec3 &velocity);

    /**
     * Draw the particle onto the screen
     */
    void Draw() const;

    /**
     * Update the position of the particle with current velocity
     * @param speed the speed control, default at 1
     */
    void UpdatePosition(float speed = 1.0f);

    /**
     * Check if the particle has collided with another particle
     * @param second_particle the second particle
     * @return the bool representing if the particle has collided
     */
    bool IfCollided(const Particle &second_particle) const;

    /**
     * Update the current AND the second particle's velocities,
     * an extension of NewparticleVelocity helper function
     * @param second_particle the second particle
     */
    void UpdateCollidedParticlesVelocity(Particle &second_particle);

    /**
     * Update the current particle's velocity, based on the second particle's parameters
     * @param second_position the second particle' position
     * @param second_velocity the second particle's velocity
     * @param second_mass the second particle's mass
     */
    void NewParticleVelocity(const vec3 &second_position, const vec3 &second_velocity, const double second_mass);

private:
    vec3 position_, velocity_;
    double mass_, radius_;
    char* color_;
};
}
