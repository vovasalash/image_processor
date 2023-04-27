add_executable(
    image_processor
    image_processor.cpp
        Write_and_Read/read.cpp Write_and_Read/read.h Write_and_Read/write.h Write_and_Read/write.cpp Write_and_Read/magic_const.h Image/color.cpp Image/color.h Image/image.cpp Image/image.h Filters/filter.h Filters/filter.cpp Filters/Sharpening/sharpening.h Filters/Sharpening/sharpening.cpp Filters/Negative/negative.h Filters/Negative/negative.cpp Filters/Grayscale/grayscale.h Filters/Grayscale/grayscale.cpp Filters/Crop/crop.h Filters/Crop/crop.cpp "Filters/Edge_Detection/edgedetection.h" "Filters/Edge_Detection/edgedetection.cpp" "Filters/Gaussian_Blur/gaussblur.h" "Filters/Gaussian_Blur/gaussblur.cpp")
