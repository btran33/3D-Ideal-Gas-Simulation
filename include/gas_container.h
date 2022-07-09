#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

using glm::vec2;
using glm::vec3;
using namespace cinder;

namespace idealgas3d {
/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
public:
    /**
     * Default constructor to the gas container
     */
    GasContainer();

    /**
     * Displays the container walls and the current positions of the particles.
     */
    void Display();

    /**
     * Scale the container based on the scale value
     * @param scale the scale value
     */
    void ScaleContainer(const float scale);

    /**
     * Updates the positions and velocities of all particles
     * @param speed the speed control, default at 1
     */
    void AdvanceOneFrame(float speed = 1.0f);

    /**
     * Add a particle to the container
     * @param particle
     */
    void AddParticle(Particle particle);

    /**
     * Clear the particle list
     */
    void ClearParticle();

    /**
     * Get the list of particles in the container
     * @return a vector of particles presented in the container
     */
    std::vector<Particle> GetParticleList(char* color = NULL);

    /**
     * Get the corner bound of the container
     * @return the corner bound of the container
     */
    double GetCornerBound() const;

private:
    vec3 container_size_;
    double corner_bound_ = 4;
    std::vector<Particle> particles_;

    /**
     * Remove particles that are out of the container bounds
     */
    void RemoveOutOfBoundParticle();

    /**
     * Check if particle hits a wall or not
     * @param particle the particle that is being checked
     * @return a bool representing if that particle has hit a wall
     */
    bool CheckBound(Particle& particle) const;

    /**
     * Helper function to handle wall collision with a particle
     * @param particle the particle that is colliding with a wall
     */
    void CollideWithWall(Particle& particle) const;
};

}  // namespace idealgas3d