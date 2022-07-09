#include "gas_simulation.h"

namespace idealgas3d {
IdealGasApp::IdealGasApp()
    : histogram_red_("red",vec2(3, 6), vec2(3, 2)),
      histogram_green_("green", vec2(3, 3), vec2(3, 2)),
      histogram_blue_("blue", vec2(3, 0), vec2(3, 2)){
    AppBase::setWindowPos(kInitialWinPos, kInitialWinPos);
    setWindowSize(kInitialWinSize,kInitialWinSize);

    // setting up camera perspective & ui
    curr_cam_persp_ = vec3(5, 5, 10);
    curr_cam_center_ = vec3(0, 0, 0);
    camera_.lookAt(curr_cam_persp_, curr_cam_center_);
    camera_.setPerspective( 40.0f, getWindowAspectRatio(), 0.01f, 100.0f );
    camera_ui_ = CameraUi(&camera_, getWindow());
    createGrid();

    strcpy(red_char_, red_.c_str());
    strcpy(green_char_, green_.c_str());
    strcpy(blue_char_, blue_.c_str());
}

void IdealGasApp::createGrid(){
    mGrid_ = gl::VertBatch::create( GL_LINES );
    mGrid_->begin( GL_LINES );
    for (int i = -10; i <= 10; ++i ) {
        mGrid_->color(Color(0.3f, 0.3f, 0.3f ) );
        mGrid_->vertex(float(i), 0.0f, -10.0f );
        mGrid_->vertex(float(i), 0.0f, +10.0f );
        mGrid_->vertex(-10.0f, 0.0f, float(i));
        mGrid_->vertex(+10.0f, 0.0f, float(i));
    }
    mGrid_->end();
}

void IdealGasApp::draw() {
    ci::Color background(gray_, gray_, gray_);
    ci::gl::clear(background);
    setMatrices(camera_);

    if(mGrid_) {
        mGrid_->draw();

        // draw the coordinate frame with length 2.
        // gl::drawCoordinateFrame(2);
    }

    container_.Display();
    if(histogram_show_){
        histogram_red_.Display();
        histogram_green_.Display();
        histogram_blue_.Display();
    }
}

void IdealGasApp::update() {
    if(!sim_pause_){
        container_.AdvanceOneFrame(speed_);
        UpdateHistogramParticles();
    }
}

void IdealGasApp::UpdateHistogramParticles() {
    histogram_red_.UpdateParticles(container_.GetParticleList(red_char_));
    histogram_green_.UpdateParticles(container_.GetParticleList(green_char_));
    histogram_blue_.UpdateParticles(container_.GetParticleList(blue_char_));
}

void IdealGasApp::mouseDrag(MouseEvent event) {
    camera_ui_.mouseDrag(event);
}

void IdealGasApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case (KeyEvent::KEY_UP):
            container_.ScaleContainer(+0.5f);
            histogram_red_.SetHistogramPos(histogram_red_.GetHistogramPos() + vec2(0.25f, 0));
            histogram_green_.SetHistogramPos(histogram_green_.GetHistogramPos() + vec2(0.25f, 0));
            histogram_blue_.SetHistogramPos(histogram_blue_.GetHistogramPos() + vec2(0.25f, 0));
            break;
        case (KeyEvent::KEY_DOWN):
            container_.ScaleContainer(-0.5f);
            histogram_red_.SetHistogramPos(histogram_red_.GetHistogramPos() + vec2(-0.25f, 0));
            histogram_green_.SetHistogramPos(histogram_green_.GetHistogramPos() + vec2(-0.25f, 0));
            histogram_blue_.SetHistogramPos(histogram_blue_.GetHistogramPos() + vec2(-0.25f, 0));
            break;
        case (KeyEvent::KEY_LEFT):
            speed_ -= 0.1f;
            break;
        case (KeyEvent::KEY_RIGHT):
            speed_ += 0.1f;
            break;
        case (KeyEvent::KEY_p):
            sim_pause_ = !sim_pause_;
            break;
        case (KeyEvent::KEY_1):
            // preset particle
            container_.AddParticle(Particle(vec3(0, container_.GetCornerBound() / 2, 0),
                                            vec3(0.01, 0.2, 0.1), 1, 0.2, red_char_));
            break;
        case (KeyEvent::KEY_2):
            // preset particle
            container_.AddParticle(Particle(vec3(0, container_.GetCornerBound() / 2, 0),
                                            vec3(0, -0.01, -0.1), 1.5, 0.3, green_char_));
            break;
        case (KeyEvent::KEY_3):
            // preset particle
            container_.AddParticle(Particle(vec3(0, container_.GetCornerBound() / 2, 0),
                                            vec3(-0.01, 0.01, 0.02), 2, 0.4, blue_char_));
            break;
        case (KeyEvent::KEY_h):
            histogram_show_ = !histogram_show_;
            break;
        case (KeyEvent::KEY_s):
            if (event.isControlDown()) {
                CreateParticleJson();
                std::ofstream stream(getSaveFilePath());
                stream << writer.write(particle_json_);
            }
            break;
        case (KeyEvent::KEY_c):
            if (event.isControlDown()) {
                container_.ClearParticle();
                UpdateHistogramParticles();
            }
            break;
        default:
            break;
    }
}

void IdealGasApp::fileDrop(FileDropEvent event) {
    std::fstream file(event.getFile(0).string());
    std::string str_line, str_json;

    // get all the lines in Json
    while(std::getline(file, str_line)){
        str_json += str_line;
    }
    file.close();
    UpdateContainerFromJson(str_json);

    // pause simulation and update the histograms
    sim_pause_ = true;
    UpdateHistogramParticles();
}

void IdealGasApp::CreateParticleJson() {
    std::vector<Particle> particles = container_.GetParticleList();
    Json::Value part, pos_list, vec_list;
    particle_json_.clear();

    for(auto& particle : particles){
        vec3 pos = particle.GetPosition();
        vec3 vec = particle.GetVelocity();

        part.clear();
        pos_list.clear();
        vec_list.clear();

        part["color"] = particle.GetColor();
        part["radius"] = particle.GetRadius();
        part["mass"] = particle.GetMass();

        pos_list.append(pos.x);
        pos_list.append(pos.y);
        pos_list.append(pos.z);
        part["position"] = pos_list;

        vec_list.append(vec.x);
        vec_list.append(vec.y);
        vec_list.append(vec.z);
        part["velocity"] = vec_list;

        particle_json_.append(part);
    }
}

void IdealGasApp::UpdateContainerFromJson(const std::string& json_string) {
    if(reader.parse(json_string, particle_json_)) {
        char *color;
        double mass, radius;
        vec3 position, velocity;

        for (auto particle: particle_json_) {
            // set color to the parsed color
            if (strcmp(particle["color"].asCString(), red_char_) == 0) {
                color = red_char_;
            } else if (strcmp(particle["color"].asCString(), green_char_) == 0) {
                color = green_char_;
            } else if (strcmp(particle["color"].asCString(), blue_char_) == 0) {
                color = blue_char_;
            } else {
                throw std::exception("Invalid JSON file!");
            }

            mass = particle["mass"].asDouble();
            radius = particle["radius"].asDouble();

            const Json::Value pos = particle["position"], vel = particle["velocity"];

            position.x = pos[0].asFloat();
            position.y = pos[1].asFloat();
            position.z = pos[2].asFloat();

            velocity.x = vel[0].asFloat();
            velocity.y = vel[1].asFloat();
            velocity.z = vel[2].asFloat();

            container_.AddParticle(Particle(position, velocity, mass, radius, color));
        }
    }
    else {
        throw std::exception("Invalid JSON file!");
    }
}
} // namespace idealgas3d