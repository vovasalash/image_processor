#include <iostream>

#include "Write_and_Read/magic_const.h"
#include "Write_and_Read/read.h"
#include "Write_and_Read/write.h"
#include "Filters/Negative/negative.h"
#include "Filters/Crop/crop.h"
#include "Filters/Edge_Detection/edgedetection.h"
#include "Filters/Grayscale/grayscale.h"
#include "Filters/Sharpening/sharpening.h"
#include "Filters/Gaussian_Blur/gaussblur.h"

class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& args) : name_(name), args_(args) {
    }
    const std::string& GetName() const {
        return name_;
    }
    const std::vector<std::string>& GetArgs() const {
        return args_;
    }

private:
    std::string name_;
    std::vector<std::string> args_;
};

std::vector<Command> Parsing(int argc, char** argv) {
    std::vector<Command> commands;
    if (argc < 3) {
        std::cerr << "Data: " << argv[0]
                  << " input_file output_file [-filter1 param1 param2 ...] [-filter2 param1 param2 ...] ..."
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    std::string input_file = argv[1];
    std::string output_file = argv[2];
    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg[0] == '-') {
            std::string filter_name = arg.substr(1);
            std::vector<std::string> args;
            ++i;
            while (i < argc && argv[i][0] != '-') {
                args.push_back(argv[i]);
                ++i;
            }
            commands.emplace_back(filter_name, args);
            --i;
        }
    }
    return commands;
}

std::unique_ptr<Filter> CreateFilter(const std::string& filter_name, const std::vector<std::string>& params) {
    if (filter_name == "neg") {
        return std::make_unique<Negative>();
    } else if (filter_name == "gs") {
        return std::make_unique<Grayscale>();
    } else if (filter_name == "sharp") {
        return std::make_unique<Sharpening>();
    } else if (filter_name == "crop") {
        if (params.size() == 2) {
            size_t width = std::stoi(params[0]);
            size_t height = std::stoi(params[1]);
            return std::make_unique<Crop>(width, height);
        } else {
            throw std::invalid_argument("Wrong parameters for crop filter");
        }
    } else if (filter_name == "edge") {
        if (params.size() == 1) {
            double threshold = std::stod(params[0]);
            return std::make_unique<EdgeDetection>(threshold);
        } else {
            throw std::invalid_argument("Wrong parameters for edge filter");
        }
    } else {
        throw std::invalid_argument("Unknown filter name");
    }
}

Image ApplyFilters(const Image& input_image, const std::vector<Command>& commands) {
    Image output_image = input_image;
    for (const auto& command : commands) {
        std::string filter_name = command.GetName();
        std::vector<std::string> params = command.GetArgs();
        auto filter = CreateFilter(filter_name, params);
        if (!filter) {
            std::cerr << "Unknown filter: " << filter_name << std::endl;
            exit(EXIT_FAILURE);
        }
        output_image = filter->Apply(output_image);
    }

    return output_image;
}

int main(int argc, char** argv) {
    auto commands = Parsing(argc, argv);
    write_and_read::Reader image_reader = write_and_read::Reader(argv[1]);
    Image input_image = image_reader.ReadFile();
    Image output_image = ApplyFilters(input_image, commands);
    write_and_read::Writer image_writer = write_and_read::Writer(argv[2]);
    image_writer.WriteImage(output_image);
    return 0;
}

