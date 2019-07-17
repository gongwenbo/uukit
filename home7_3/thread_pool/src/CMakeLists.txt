include_directories(../inc)
aux_source_directory(. MEDIA)
add_library(threadpool STATIC ${MEDIA})