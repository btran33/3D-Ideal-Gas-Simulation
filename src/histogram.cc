#include "histogram.h"

namespace idealgas3d {
Histogram::Histogram(const char* color, const vec2 histogram_position, const vec2 histogram_size)
    : bar_color_(color), histogram_position_(histogram_position), histogram_size_(histogram_size) {}

std::vector<int> Histogram::GetBucketList(){
    return bucket_list_;
}

vec2 Histogram::GetHistogramPos() {
    return histogram_position_;
}

void Histogram::SetHistogramPos(vec2 hist_pos) {
    histogram_position_ = hist_pos;
}

void Histogram::AdjustBucketAmount(const int bucket_amount_offset) {
    bucket_amount_ += bucket_amount_offset;
}

void Histogram::InitializeBucket() {
    bucket_list_ = std::vector<int>(bucket_amount_, 0);
}

void Histogram::Display() {
    ci::gl::color(ci::Color(kHistogramColor));
    ci::Rectf bounding_box(histogram_position_, histogram_position_ + histogram_size_);
    ci::gl::drawStrokedRect(bounding_box);

    // Draw the bar if there are particles presented to draw
    if(particles_.size() != 0)
        DrawHistogramBar();
}

void Histogram::DrawHistogramBar() {
    FillHistogramBucket();
    DrawHistogramBucket();
}

void Histogram::UpdateParticles(const std::vector<Particle>& Particles) {
    particles_ = Particles;
}

void Histogram::FillHistogramBucket(){
    InitializeBucket(); // initialize to 0 every time

    for(Particle particle : particles_){
        double speed = glm::length(particle.GetVelocity());

        // assign particle's speed to the appropriate bucket
        for(int i = 0; i < bucket_amount_; i++){
            /* the speed bucket threshold will be distributed based on the bucket amount,
             * spaced out with size of 0.1, so 10 buckets will have threshold of
             * [0, 0.1), [0.1, 0.2), ... , [0.9, 1) */

            if(speed >= i/double(bucket_amount_) && speed < (i+1)/double(bucket_amount_)){
                bucket_list_[i]++;
                break;
            }
        }
    }
}

void Histogram::DrawHistogramBucket() {
    float bucket_width = histogram_size_.x/bucket_amount_; // width is based on the bucket amount
    float bucket_height = histogram_size_.y * 8 / 10; // use 80% of box height as max bucket height
    int max_particle = *std::max_element(bucket_list_.begin(), bucket_list_.end());

    for(size_t i = 0; i < bucket_list_.size(); i++){
        vec2 bottom_left = histogram_position_ + vec2(i * bucket_width, 0);
        // Scale the bucket height based on the max particle count (so max will get the highest bar)
        float height = bucket_height * bucket_list_[i] / max_particle;
        vec2 top_right = bottom_left + vec2(bucket_width, height);

        if(height != 0)
            DrawBucket(bottom_left, top_right);
    }
}

void Histogram::DrawBucket(vec2 bottom_left, vec2 top_right){
    ci::gl::color(ci::Color(bar_color_));
    ci::Rectf bounding_box(bottom_left, top_right);
    ci::gl::drawSolidRect(bounding_box);
}
} // namespace idealgas3d

