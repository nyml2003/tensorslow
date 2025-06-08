set(module_name "Generation")

file(GLOB_RECURSE tensorslow_${module_name}_files ${tensorslow_src_dir}/${module_name}/*.cpp)
set(tensorslow_frontend_files ${tensorslow_frontend_files} ${tensorslow_${module_name}_files})