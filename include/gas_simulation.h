#pragma once

#include <fstream>
#include <iostream>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/CameraUi.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"
#include "histogram.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h"
#include "jsoncpp/json.h"

namespace idealgas3d {

using namespace ci;
using namespace ci::gl;
using namespace ci::app;

/**
 * The ideal gas application for visualizing ideal gas law under 3 dimensions
 */
class IdealGasApp : public App {
 public:
    /**
     * Default constructor for the ideal gas application
     */
    IdealGasApp();

    /**
     * Create a visualized grid in the window
     */
    void createGrid();

    /**
     * Draw all the necessary component for the application
     */
    void draw() override;

    /**
     * Updates the simulation
     */
    void update() override;

    /**
     * Handle the mouse events for the simulation
     * @param event the mouse event
     */
    void mouseDrag(MouseEvent event) override;

    /**
     * Handle the key events for the simulation
     * @param event the key event
     */
    void keyDown(KeyEvent event) override;

    /**
     * Handle the file drop event for the simulation
     * @param event the file drop event
     */
    void fileDrop(FileDropEvent event) override;

 private:
    GasContainer container_;
    float speed_ = 1.0f;
    Json::Value particle_json_;
    Json::StyledWriter writer;
    Json::Reader reader;
    std::string red_ = "red", green_ = "green", blue_ = "blue";
    char red_char_[4], green_char_[6], blue_char_[5];

    CameraPersp camera_;
    CameraUi camera_ui_;
    vec3 curr_cam_persp_;
    vec3 curr_cam_center_;
    VertBatchRef mGrid_;
    const int kInitialWinPos = 50, kInitialWinSize = 1440;
    float gray_ = 0.2f;
    bool sim_pause_ = false;

    Histogram histogram_red_, histogram_green_, histogram_blue_;
    bool histogram_show_ = false;

    /**
     * Updates all the particles in their respective histogram
     */
    void UpdateHistogramParticles();

    /**
     * Creates the current list of particles as JSON
     */
    void CreateParticleJson();

    /**
     * Updates the particles in the container to the ones from JSON
     * @param json_string the parsed json string
     */
    void UpdateContainerFromJson(const std::string& json_string);
};
} // namespace idealgas3d
