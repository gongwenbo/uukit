include_directories(../inc)
aux_source_directory(. MEDIA)
add_library(_media STATIC ${MEDIA})