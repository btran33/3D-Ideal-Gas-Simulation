#include "particle.h"

namespace idealgas3d {
    Particle::Particle(const vec3 &position, const vec3 &velocity, double mass, double radius, char* color)
        : position_(position),
          velocity_(velocity),
          mass_(mass),
          radius_(radius),
          color_(color) {}

    Particle::Particle(const Particle &particle)
        : position_(particle.GetPosition()),
          velocity_(particle.GetVelocity()),
          mass_(particle.GetMass()),
          radius_(particle.GetRadius()),
          color_(particle.GetColor()) {}

    vec3 Particle::GetPosition() const {
        return position_;
    }

    vec3 Particle::GetVelocity() const {
        return velocity_;
    }

    double Particle::GetMass() const {
        return mass_;
    }

    double Particle::GetRadius() const {
        return radius_;
    }

    char* Particle::GetColor() const {
        return color_;
    }

    void Particle::SetVelocity(const vec3 &velocity){
        velocity_ = velocity;
    }

    void Particle::Draw() const{
        color(ci::Color(color_));
        drawSphere(position_, float(radius_));
    }

    void Particle::UpdatePosition(float speed) {
        position_ += (velocity_ * vec3(speed));
    }

    bool Particle::IfCollided(const Particle &second_particle) const {
        /* Return true if the two particles are moving towards each other AND
         * their position overlaps the sum of their radii */
        return glm::dot(velocity_ - second_particle.velocity_, position_ - second_particle.position_) < 0 &&
               glm::distance(position_, second_particle.position_) <= (radius_ + second_particle.radius_);
    }

    void Particle::UpdateCollidedParticlesVelocity(Particle &second_particle){
        /* Save the first Particle's parameters for the second Particle to use,
         * since it will be changed once first Particle updates its velocity */
        vec3 first_position = position_;
        vec3 first_velocity = velocity_;
        double first_mass = mass_;

        this->NewParticleVelocity(second_particle.position_,
                                  second_particle.velocity_,
                                  second_particle.mass_);
        second_particle.NewParticleVelocity(first_position,
                                            first_velocity,
                                            first_mass);
    }

    void Particle::NewParticleVelocity(const vec3 &second_position,
                                       const vec3 &second_velocity,
                                       const double second_mass) {
        double mass_ratio = (2 * second_mass / (mass_ + second_mass));
        vec3 position_difference = position_ - second_position;
        vec3 position_ratio = glm::dot(velocity_ - second_velocity,
                                       position_ - second_position) /
                              pow(glm::length(position_difference), 2) * position_difference;
        velocity_ -= vec3(mass_ratio * position_ratio.x,
                          mass_ratio * position_ratio.y,
                          mass_ratio * position_ratio.z);
    }
}