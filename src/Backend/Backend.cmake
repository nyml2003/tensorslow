set(module_name "Backend")

file(GLOB_RECURSE tensorslow_${module_name}_files ${tensorslow_src_dir}/${module_name}/*.cpp)
set(tensorslow_backend_files ${tensorslow_backend_files} ${tensorslow_${module_name}_files})