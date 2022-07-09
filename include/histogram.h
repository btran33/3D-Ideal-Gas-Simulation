#pragma once

#include <vector>
#include "particle.h"

using glm::vec2;

namespace idealgas3d {
/**
 * The historgram of the speed of a Particle's type
 */
class Histogram {
public:
    /**
     * Constructor of the histogram
     * @param color the color of the histogram bars
     * @param histogram_position the histogram box's top-left corner position
     * @param histogram_size the histogram size/dimension in pixels, drawn to bottom-right corner
     */
    Histogram(const char* color, const vec2 histogram_position, const vec2 histogram_size);

    /**
     * Getter of the histogram's bucket list
     * @return the histogram's bucket list
     */
    std::vector<int> GetBucketList();

    /**
     * Getter of the histogram's bottom left position
     * @return histogram's bottom left position
     */
    vec2 GetHistogramPos();

    /**
     * Setter of the histogram's bottom left position
     * @param hist_pos histogram's bottom left position
     */
    void SetHistogramPos(vec2 hist_pos);

    /**
     * Adjust the bucket amount based on the given offset
     * @param bucket_amount_offset the desired offset (ex: decreasing a bucket will be -1)
     */
    void AdjustBucketAmount(const int bucket_amount_offset);

    /**
     * Initialize the buckets to 0
     */
    void InitializeBucket();

    /**
     * Display the histogram and its labels onto the screen
     */
    void Display();

    /**
     * Update buckets appropriate amount of particles and draw the histogram bars
     */
    void DrawHistogramBar();

    /**
     * Update the histogram with new particle list
     * @param Particles the list of particles with the same color
     */
    void UpdateParticles(const std::vector<Particle>& Particles);

    /**
     * Update the histogram buckets with the appropriate amount of particles
     */
    void FillHistogramBucket();

    /**
     * Draw all the buckets in the histogram
     */
    void DrawHistogramBucket();

    /**
     * Draw the individual bucket as a solid bar, with given bottom-left and top-right coordinate
     * @param bottom_left the bottom-left coordinate of the bar
     * @param top_right the top-right coordinate of the bar
     */
    void DrawBucket(vec2 bottom_left, vec2 top_right);

private:
    const char* bar_color_;
    const char* kHistogramColor = "white";
    vec2 histogram_position_;
    const vec2 histogram_size_;
    std::vector<Particle> particles_;
    int bucket_amount_ = 10;
    std::vector<int> bucket_list_;

};
} // namespace idealgas3d
