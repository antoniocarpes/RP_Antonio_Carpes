message("------------Executing CMake core library-----------")

add_library(core_library SHARED
    utils/property_eigen.cpp
    utils/blob.cpp
    utils/id_context.cpp
    utils/serializer.cpp

    # TODO add other .cpp files
    utils/deserializer.cpp
    utils/id_placeholder.cpp
    utils/identifiable.cpp
    utils/object_data.cpp
    utils/property_container_manager.cpp
    utils/property_container.cpp
    utils/property_identifiable.cpp
    utils/property.cpp
    utils/serializable.cpp
    utils/serialization_context.cpp

    messages/base_sensor_message.cpp
    messages/odometry_message.cpp
    messages/pose_message.cpp   
)

# TODO: Include the current directory ( . ) to the list of directories to search for header files
include_directories(".")

# TODO: Include the Eigen3 library to the list of libraries to link against
#target_link_libraries(core_library Eigen3::Eigen)
target_link_libraries(core_library ${EIGEN3_LIBRARY})

message("-------------Core library executed --------------------")
