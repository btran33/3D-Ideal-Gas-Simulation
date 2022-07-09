#include "gas_container.h"

namespace idealgas3d {

using ci::gl::drawStrokedCube;
using namespace cinder::gl;

GasContainer::GasContainer() {
    container_size_ = vec3(corner_bound_, corner_bound_, corner_bound_);
}

void GasContainer::Display() {
    for(auto& particle : particles_){
        particle.Draw();
    }

    color(cinder::Color("white"));
    drawStrokedCube(vec3(0, container_size_.x / 2, 0), container_size_);
}

void GasContainer::ScaleContainer(const float scale) {
    container_size_ += vec3(scale);
    corner_bound_ += scale;
}

void GasContainer::AdvanceOneFrame(float speed) {
    RemoveOutOfBoundParticle();
    for(size_t i = 0; i < particles_.size(); i++){
        if(CheckBound(particles_.at(i))){
            CollideWithWall(particles_.at(i));
        }

        for(size_t j = i + 1; j < particles_.size(); j++){
            if(particles_.at(i).IfCollided(particles_.at(j))){
                particles_.at(i).UpdateCollidedParticlesVelocity(particles_.at(j));
            }
        }
        particles_.at(i).UpdatePosition(speed);
    }
}

void GasContainer::RemoveOutOfBoundParticle() {
    vec3 pos;
    double radius;
    for(auto it = particles_.begin(); it != particles_.end();){
        pos = it->GetPosition();
        radius = it->GetRadius();

        /* check if the entire particle has exited the container,
         * and remove them if they are fully outside */
        if(pos.x - radius > corner_bound_/2 || pos.x + radius < (-corner_bound_/2) ||
           pos.y - radius > corner_bound_ || pos.y + radius < 0 ||
           pos.z - radius > corner_bound_/2 || pos.z + radius < (-corner_bound_/2)){
            it = particles_.erase(it);
        }
        else{
            ++it;
        }
    }
}

bool GasContainer::CheckBound(Particle &particle) const {
    vec3 pos = particle.GetPosition();
    double radius = particle.GetRadius();
    return (abs(pos.x) + radius) >= corner_bound_/2 ||
           (pos.y + radius) >= corner_bound_ ||
           (pos.y - radius) <= 0 ||
           (abs(pos.z) + radius) >= corner_bound_/2;
}

void GasContainer::CollideWithWall(Particle& particle) const {
    vec3 pos = particle.GetPosition(),
         vel = particle.GetVelocity(),
         final;
    double radius = particle.GetRadius();

    /* For each coordinate axis, check where the particle is touching the bound at
     * and check if the velocity sign matches its position sign.
     * Reflect the velocity the same if it does match, otherwise keep the same velocity */
    if(abs(pos.x) + radius >= corner_bound_/2){
        if(pos.x < 0)
            final = vel.x < 0 ? glm::reflect(particle.GetVelocity(), vec3(1, 0, 0)) : vel;
        else if(pos.x > 0)
            final = vel.x > 0 ? glm::reflect(particle.GetVelocity(), vec3(-1, 0, 0)) : vel;
    }
    else if(pos.y + radius >= corner_bound_){
        final = vel.y > 0 ? glm::reflect(particle.GetVelocity(), vec3(0, -1, 0)) : vel;
    }
    else if(pos.y - radius <= 0){
        final = vel.y < 0 ? glm::reflect(particle.GetVelocity(), vec3(0, 1, 0)) : vel;
    }
    else if(abs(pos.z) + radius >= corner_bound_/2){
        if(pos.z < 0)
            final = vel.z < 0 ? glm::reflect(particle.GetVelocity(), vec3(0, 0, 1)) : vel;
        else if(pos.z > 0)
            final = vel.z > 0 ? glm::reflect(particle.GetVelocity(), vec3(0, 0, -1)): vel;
    }
    particle.SetVelocity(final);
}

void GasContainer::AddParticle(Particle particle) {
    particles_.push_back(particle);
}

void GasContainer::ClearParticle() {
    particles_.clear();
}

std::vector<Particle> GasContainer::GetParticleList(char* color) {
    std::vector<Particle> colored_particle_list;

    // filter out particles by color if specified
    if(color){
        for(auto& particle : particles_) {
            if (strcmp(particle.GetColor(), color) == 0)
                colored_particle_list.emplace_back(particle);
        }
    }
    else{
        colored_particle_list = particles_;
    }
    return colored_particle_list;
}

double GasContainer::GetCornerBound() const {
    return corner_bound_;
}
} // namespace idealgas3d